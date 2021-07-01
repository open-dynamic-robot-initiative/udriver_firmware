// --COPYRIGHT--,BSD
// Copyright (c) 2015, Texas Instruments Incorporated
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// *  Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//7
// *  Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// *  Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// --/COPYRIGHT
//! \file   solutions/instaspin_motion/src/proj_lab12c.c
//! \brief Dual sensored speed control using SpinTAC
//!
//! (C) Copyright 2015, Texas Instruments, Inc.

//! \defgroup PROJ_LAB12C PROJ_LAB12C
//@{

//! \defgroup PROJ_LAB12C_OVERVIEW Project Overview
//!
//! Basic implementation of FOC by using the estimator for angle and speed
//! feedback only.  Adds in SpinTAC Velocity Contol and SpinTAC Velocity Move
//!	Dual sensored speed control using SpinTAC
//!

// **************************************************************************
// the includes

// system includes
#include <math.h>
#include <amd_motorware_ext/button.h>
#include <amd_motorware_ext/utils.h>
#include "main_2mtr.h"
#include "main_helper.h"
#include "spiapi.h"
#include "spintac.h"
#include <strings.h>

#ifdef FLASH
#pragma CODE_SECTION(motor1_ISR, "ramfuncs");
#pragma CODE_SECTION(motor2_ISR, "ramfuncs");
#pragma CODE_SECTION(xint1_ISR, "ramfuncs");
#pragma CODE_SECTION(spi_ISR, "ramfuncs");
#endif

// **************************************************************************
// the defines


// **************************************************************************
// the globals

//! \name Objects and Handles
//! \brief State objects and handles for the used software modules
//!
//! Typically each module of the MotorWare library has an object type that
//! stores the state of the object as well as a handle type that is simply a
//! pointer to the object.  When calling functions of the module, the handle is
//! passed so that the function can operate on the current state.
//!
//! For most of the modules there are two object instances, one for each motor
//! (the first one in the array refers to HAL_MTR1, the second one to HAL_MTR2).
//!
//! \{

//! \brief The handles for the hardware abstraction layer for common CPU setup
HAL_Handle halHandle;
//! \brief The hardware abstraction layer object
HAL_Obj hal;

//! \brief The handles for the hardware abstraction layer specific to the motor
//! 	board.
HAL_Handle_mtr halHandleMtr[2];
//! \brief The hardware abstraction layer object specific to the motor board.
HAL_Obj_mtr halMtr[2];

//! \brief The handles for the current Clarke transform
CLARKE_Handle clarkeHandle_I[2];
//! \brief The current Clarke transform objects
CLARKE_Obj clarke_I[2];

//! \brief The handles for the current Park transfrom
PARK_Handle parkHandle[2];
//! \brief The current Parke transform objects
PARK_Obj park[2];

//! \brief The handles for the voltage Clarke transform
CLARKE_Handle clarkeHandle_V[2];
//! \brief The voltage Clarke transform objects
CLARKE_Obj clarke_V[2];

//! \brief The handles for the inverse Park transform
IPARK_Handle iparkHandle[2];
//! \brief The inverse Park transform object
IPARK_Obj ipark[2];

//! \brief The handles for the estimator
//!
//! There is no EST_Obj because this is stored in the ROM of the MCU.
EST_Handle estHandle[2];

//! \brief The handles for the PID controllers
//!
//! First dimention: 0 = motor 1, 1 = motor 2
//! Second dimention: 0 = Speed, 1 = Id, 2 = Iq
PID_Handle pidHandle[2][3];
//! \brief The objects for the PID controllers
PID_Obj pid[2][3];

//! \brief The handles for the space vector generator
SVGEN_Handle svgenHandle[2];
//! \brief The space vector generator objects
SVGEN_Obj svgen[2];

//! \brief The handles for the encoder
ENC_Handle encHandle[2];
//! \brief The encoder objects
ENC_Obj enc[2];

//! \brief The handles for the slip compensator
SLIP_Handle slipHandle[2];
//! \brief The slip compensator objects
SLIP_Obj slip[2];

//! \brief The handles for the angle compensation
ANGLE_COMP_Handle angleCompHandle[2];
//! \brief The angle compensation objects
ANGLE_COMP_Obj angleComp[2];

//! \brief The handles for the 3 current and 3 voltage filters for offset
//! 	calculation.
FILTER_FO_Handle filterHandle[2][6];
//! \brief the 3-current and 3-voltage filters for offset calculation of each
//! 	motor.
FILTER_FO_Obj filter[2][6];

//! \brief The handles for the SpinTAC objects
ST_Handle stHandle[2];
//! \brief The SpinTAC objects
ST_Obj st_obj[2];


//! \}

//! \name Counters
//! \brief Counter variables used for decimation and timing of processes
//! \{

//! \brief Count variable to decimate the execution of the high-level controller
uint16_t stCntSpeed[2] = {0, 0};

//! \brief Count variable to decimate the execution of SpinTAC Position
//! 	Converter
uint16_t stCntPosConv[2] = {0, 0};

//! \brief Count variable to measure duration of the offset calculation
uint32_t gOffsetCalcCount[2] = {0, 0};

//! \brief Count variable to measure duration of the motor alignment
uint32_t gAlignCount[2] = {0, 0};

//! \}


//! \name Enable Flags
//! \brief Flags to enable/disable parts of the program
//! \{


//! While set, the current position is stored as offset which is removed from
//! the position before sending it via SPI (i.e. the current position becomes
//! zero).
//! \note This feature is currently disabled!
bool gFlag_resetZeroPositionOffset = false;

//! \brief If true, a rollover of the PosConv module will trigger an error.
//!
//! This is nice for position control applications where the motor is not
//! expected to move far enough to ever observe an rollover.  By throwing an
//! error in the case it happens nonetheless, it is ensured that the system will
//! not explode.
//!
//! \note For applications where rollovers are expected (i.e. motor spinning
//! freely), this should be disabled!
bool gFlag_enablePosRolloverError = false;

//! \}


//! \name Data Variables
//! \brief These variables are used to store data values like measured current,
//! 	voltage, reference values in pu, scale factors, etc.
//! \{

//! \brief Contains the pwm values for each phase.
//!
//! -1.0 is 0%, 1.0 is 100%
HAL_PwmData_t gPwmData[2] = {
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)}
};

//! \brief Contains three current values, three voltage values and one DC bus
//! 	value.
HAL_AdcData_t gAdcData[2];

//! \brief Contains the offsets for the current feedback
MATH_vec3 gOffsets_I_pu[2] = {
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)}
};

//! \brief Contains the offsets for the voltage feedback
MATH_vec3 gOffsets_V_pu[2] = {
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0), _IQ(0.0)}
};

//! \brief Contains the Id and Iq references
MATH_vec2 gIdq_ref_pu[2] = {
		{_IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0)}
};

//! \brief Contains the output Vd and Vq from the current controllers
MATH_vec2 gVdq_out_pu[2] = {
		{_IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0)}
};

//! \brief Contains the Id and Iq measured values
MATH_vec2 gIdq_pu[2] = {
		{_IQ(0.0), _IQ(0.0)},
		{_IQ(0.0), _IQ(0.0)}
};


//! \brief Some scale factor used for torque computation
_iq gTorque_Ls_Id_Iq_pu_to_Nm_sf[2];

//! \brief Some scale factor used for torque computation
_iq gTorque_Flux_Iq_pu_to_Nm_sf[2];

//! \brief Scale factor to convert speed from pu to krpm
_iq gSpeed_pu_to_krpm_sf[2];

//! \brief Scale factor to convert current from A to pu
_iq gCurrent_A_to_pu_sf[2];

//! \brief Offset that is removed from the position before sending it via SPI.
_iq gZeroPositionOffset[2] = {0, 0};

//! \brief Flag to enable the index encoder offset compensation. (position=0 at the index)
bool gEnableIndexOffsetCompensation[2] = {false,false};

//! \brief last position used by the Custom software Velocity Filter
_iq gLastPosition[2] = {0,0};

//! \}


//! \brief Decimation factor for the SpinTAC Position Converter
//!
//! Store this to array so it can be used in generic_motor_ISR.
const uint16_t  gNumIsrTicksPerPosConvTick[2] = {
        ISR_TICKS_PER_POSCONV_TICK,
        ISR_TICKS_PER_POSCONV_TICK_2
};

//! \brief User Parameters
//!
//! Contains parameters from the user*.h config files.
USER_Params gUserParams[2];

//! \brief Global motor variables
//!
//! Several status information about the motors is stored here so they can be
//! accessed from the debugger or the GUI.
volatile MOTOR_Vars_t gMotorVars[2] = {MOTOR_Vars_INIT_Mtr1,
		MOTOR_Vars_INIT_Mtr2};

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;
#endif

#ifdef DRV8301_SPI
// Watch window interface to the 8301 SPI
DRV_SPI_8301_Vars_t gDrvSpi8301Vars[2];
#endif

#ifdef DRV8305_SPI
// Watch window interface to the 8305 SPI
DRV_SPI_8305_Vars_t gDrvSpi8305Vars[2];
#endif

//! Timestamp based on timer 0 (increased by one at each timer interrupt).
uint32_t gTimer0_cnt = 0;

//! Timestamp based on gtimer0_cnt and rectified to count milleseconds elapsed.
uint32_t gTimer0_stamp = 0;

//! Last time the blinking status LED was toggled (based on gTimer0_stamp).
uint32_t gStatusLedBlinkLastToggleTime = 0;

//! Last time a IqRef message was received via SPI (based on gTimer0_stamp).
uint32_t gSPILastReceivedIqRef_stamp = 0;

//! Timeout for incoming IqRef messages.  If exceeded, error is set.  To disable
//! timeout, set to 0.
uint32_t gSPIReceiveIqRefTimeout = 0;


//! Errors that occured in the system.  gErrors.all == 0 if no errors occured.
Error_t gErrors;

//! QEP index watchdog data for both encoders.
QepIndexWatchdog_t gQepIndexWatchdog[2] = {
		{.isInitialized = false, .indexError_counts = 0, .toggleBit = false},
		{.isInitialized = false, .indexError_counts = 0, .toggleBit = false}};


// function prototypes
interrupt void xint1_ISR(void);
inline void spi_load_firsts_words();
inline void spi_prepare_and_read_msg();
inline void spi_apply_mode_commands(uint16_t *packet);
inline void spi_apply_command_motor(uint16_t *packet);


//Holds 2 spi packets (one to read, one to write) and a boolean to indicate which is which
spi_SUPER_packets gSPI_packets_recv;
spi_SUPER_packets gSPI_packets_send;

//Current packet to read and write to in SPI interrupts
volatile uint16_t *gSPI_current_rx_packet;
volatile uint16_t *gSPI_current_tx_packet;

volatile int gSPI_rx_ptr;
volatile int gSPI_tx_ptr;

//Running CRCs
uint32_t gSPI_crc_send;
uint32_t gSPI_crc_recv;

long int gDebug_wrong_CRC = 0;

//Is SPI currently transmitting ?
volatile bool gSPI_transmitting = false;

//Is a new packet ready to send ?
volatile bool gSPI_msg_prepared = false;

//Has a new SPI packet arrived completely ?
volatile bool gSPI_msg_received = false;

//Indicate when to read receive packets and prepare a new one to send (asynchronously)
volatile bool gSPI_timer = false;


//! \brief Feedforward Iq Currents
_iq gIqFeedforward_A[2] = {0,0};

//! \brief Position gains
_iq gKp_ApMrev[2] =  {0,0};

//! \brief Velocity gains
_iq gKd_Apkrpm[2] = {0,0};

//! \brief PD+ saturation current.
_iq gIqSat[2] = {0,0};

//! \brief reference positions
_iq gPositionRef[2] = {0,0};

//! \brief reference velocities
_iq gVelocityRef[2] = {0,0};




void setupSPI() {
    bzero(&gSPI_packets_recv, sizeof(spi_SUPER_packets));
    bzero(&gSPI_packets_send, sizeof(spi_SUPER_packets));
    gSPI_current_rx_packet = (void*) packet_to_write(gSPI_packets_recv);
    gSPI_current_tx_packet = (void*) packet_ready(gSPI_packets_send);
    gSPI_rx_ptr = 0;
    gSPI_tx_ptr = 0;
}


// **************************************************************************
// the functions

inline void spi_apply_mode_commands(uint16_t *packet) {

        uint16_t mode = SPI_REG_u16(packet, SPI_COMMAND_MODE);

        //Enable system only if there is no error
        if(gErrors.all==0)
        {
            gMotorVars[HAL_MTR1].Flag_enableSys = (bool) ((mode & SPI_COMMAND_MODE_ES) != 0);
        }
        gMotorVars[HAL_MTR1].Flag_Run_Identify = ((mode & SPI_COMMAND_MODE_EM1) != 0);
        gMotorVars[HAL_MTR2].Flag_Run_Identify = ((mode & SPI_COMMAND_MODE_EM2) != 0);

        gSPIReceiveIqRefTimeout = mode & SPI_COMMAND_MODE_TIMEOUT;

        gFlag_enablePosRolloverError = ((mode & SPI_COMMAND_MODE_EPRE) != 0);

        gEnableIndexOffsetCompensation[HAL_MTR1] = ((mode & SPI_COMMAND_MODE_EI1OC) != 0);
        gEnableIndexOffsetCompensation[HAL_MTR2] = ((mode & SPI_COMMAND_MODE_EI2OC) != 0);

}

inline void spi_load_firsts_words() {
    HAL_Obj *obj = (HAL_Obj *)halHandle;
    SPI_Obj *spiB = (SPI_Obj *)obj->spiBHandle;

    /* Reset FIFOs and disable interrupts */
    SPI_resetTxFifo(spiB);
    SPI_enableTxFifo(spiB);

    /* reset pointers */
    gSPI_tx_ptr = 0;
    gSPI_crc_send = 0xFFFFFFFF;


    /* Start filling the TX FIFO with the next packet */
    // I have to fill 'by hand' otherwise the first word of RXFIFO is not push in it for the 1st word of the transmission...
    spiB->SPIDAT = gSPI_current_tx_packet[0];
    updateCRC(&gSPI_crc_send, gSPI_current_tx_packet[0]);
    for(gSPI_tx_ptr=1;gSPI_tx_ptr<5;gSPI_tx_ptr++) {
        SPI_write(spiB, gSPI_current_tx_packet[gSPI_tx_ptr]);
        updateCRC(&gSPI_crc_send, gSPI_current_tx_packet[gSPI_tx_ptr]);
    }
}

interrupt void xint1_ISR() // generated when the SPI-CS line changes, indicating the start or the end of a packet
{
    HAL_Obj *obj = (HAL_Obj *)halHandle;
    SPI_Obj *spiB = (SPI_Obj *)obj->spiBHandle;


    if(GPIO_read(obj->gpioHandle,GPIO_Number_27)) { //CS Line goes high <=> This is the end of a packet

        /* This interrupt can be triggered before spi_ISR, so the last two words can still be in the buffer */
        if(gSPI_rx_ptr < SPI_TOTAL_LEN) { //1st word
            gSPI_current_rx_packet[gSPI_rx_ptr++] = SPI_read(spiB);
            updateCRC(&gSPI_crc_recv, gSPI_current_rx_packet[gSPI_rx_ptr-1]);
        }
        if(gSPI_rx_ptr < SPI_TOTAL_LEN) { //2nd word
            gSPI_current_rx_packet[gSPI_rx_ptr++] = SPI_read(spiB);
            updateCRC(&gSPI_crc_recv, gSPI_current_rx_packet[gSPI_rx_ptr-1]);
        }

        /* Resets SPI */
        SPI_resetRxFifo(spiB);
        SPI_enableRxFifo(spiB);

        /* One message has been received */
        gSPI_msg_received = true;

        /* End of transmission */
        gSPI_transmitting = false;

        spi_load_firsts_words();

    } else { //CS Line goes low <=> beginning of a packet

        /* Beginning of transmission */
        gSPI_transmitting = true;

        /* Prevent reading the packet that is being written */
        gSPI_msg_received = false;

        /* Initialize CRC */
        gSPI_crc_recv = 0xFFFFFFFF;

        /* Reset pointer */
        gSPI_rx_ptr = 0;
    }

    /* Acknowledge the interrupt */
    PIE_clearInt(obj->pieHandle, PIE_GroupNumber_1);
}

interrupt void spi_ISR() // generated every 2 words received/sent
{
    HAL_Obj *obj = (HAL_Obj *)halHandle;
    SPI_Obj *spiB = (SPI_Obj *)obj->spiBHandle;

    if(gSPI_transmitting) { //If this interrupt occurs after the CS went high the words received has already been handled in xint1_ISR

        /* Remove the 2 words received from RX FIFO and put it in the global rx packet */
            gSPI_current_rx_packet[gSPI_rx_ptr++] = SPI_read(spiB);   //1st word
            updateCRC(&gSPI_crc_recv, gSPI_current_rx_packet[gSPI_rx_ptr-1]); //running CRC

            gSPI_current_rx_packet[gSPI_rx_ptr++] = SPI_read(spiB);   //2nd word
            updateCRC(&gSPI_crc_recv, gSPI_current_rx_packet[gSPI_rx_ptr-1]); //running CRC

            /* Fill the TX FIFO with data from global tx packet */
                /* Checks if everything has already been put in the FIFO*/
            if(gSPI_tx_ptr < SPI_TOTAL_LEN) {
                updateCRC(&gSPI_crc_send, gSPI_current_tx_packet[gSPI_tx_ptr]); //running CRC
                SPI_write(spiB, gSPI_current_tx_packet[gSPI_tx_ptr++]); //1st word
            }
                /* Checks if the only remaining data to send is the CRC*/
            if(gSPI_tx_ptr == SPI_TOTAL_LEN - 2) {
                SPI_REG_u32(gSPI_current_tx_packet, SPI_TOTAL_CRC) = gSPI_crc_send; //Copy running CRC at the right place in the global tx packet
            }

                /* Same for the 2nd word */
            if(gSPI_tx_ptr < SPI_TOTAL_LEN) {
                updateCRC(&gSPI_crc_send, gSPI_current_tx_packet[gSPI_tx_ptr]);
                SPI_write(spiB, gSPI_current_tx_packet[gSPI_tx_ptr++]);
            }
            if(gSPI_tx_ptr == SPI_TOTAL_LEN - 2) {
                SPI_REG_u32(gSPI_current_tx_packet, SPI_TOTAL_CRC) = gSPI_crc_send;
            }

        }

        /* Acknowledge the interrupt */
        SPI_clearRxFifoInt(spiB);
        PIE_clearInt(obj->pieHandle, PIE_GroupNumber_6);
}


void main(void)
{
	// IMPORTANT NOTE: If you are not familiar with MotorWare coding guidelines
	// please refer to the following document:
	// C:/ti/motorware/motorware_1_01_00_1x/docs/motorware_coding_standards.pdf

	// Only used if running from FLASH
	// Note that the variable FLASH is defined by the project

#ifdef FLASH
	// Copy time critical code and Flash setup code to RAM
	// The RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
	// symbols are created by the linker. Refer to the linker files.
	memCopy((uint16_t *)&RamfuncsLoadStart, (uint16_t *)&RamfuncsLoadEnd,
			(uint16_t *)&RamfuncsRunStart);
#endif

	// At the beginning, there are no errors
	gErrors.all = 0;

	// Enable the motors programmatically.
	gMotorVars[HAL_MTR1].Flag_enableSys = true;  // enable the system in general
	gMotorVars[HAL_MTR1].Flag_Run_Identify = true;  // enable the motor
	gMotorVars[HAL_MTR2].Flag_enableSys = true;  // enable the system in general
	gMotorVars[HAL_MTR2].Flag_Run_Identify = true;  // enable the motor

	// Speedup the initialization time by a factor of 10.
	gUserParams[HAL_MTR1].ctrlWaitTime[CTRL_State_OffLine] /= 10;
	gUserParams[HAL_MTR2].ctrlWaitTime[CTRL_State_OffLine] /= 10;

	// Lower the current used for alignment to be less agressive and demand less
	// power from the power supply.
	gUserParams[HAL_MTR1].maxCurrent_resEst /= 5.;
	gUserParams[HAL_MTR2].maxCurrent_resEst /= 5.;

	// Run a P controller by default. This is useful for testing the udriver
	// without attaching a master board to it.
	gIqSat[HAL_MTR1] = _IQ(2.0);
	gIqSat[HAL_MTR2] = _IQ(2.0);

	gKp_ApMrev[HAL_MTR1] = _IQ(1.);
	gKp_ApMrev[HAL_MTR2] = _IQ(1.);

	// initialize the Hardware Abstraction Layer  (HAL)
	// halHandle will be used throughout the code to interface with the HAL
	// (set parameters, get and set functions, etc) halHandle is required since
	// this is how all objects are interfaced, and it allows interface with
	// multiple objects by simply passing a different handle. The use of
	// handles is explained in this document:
	// C:/ti/motorware/motorware_1_01_00_1x/docs/motorware_coding_standards.pdf
	halHandle = HAL_init(&hal, sizeof(hal));


	// initialize the user parameters
	// This function initializes all values of structure gUserParams with
	// values defined in user.h. The values in gUserParams will be then used by
	// the hardware abstraction layer (HAL) to configure peripherals such as
	// PWM, ADC, interrupts, etc.
	USER_setParamsMtr1(&gUserParams[HAL_MTR1]);
	USER_setParamsMtr2(&gUserParams[HAL_MTR2]);

	// set the hardware abstraction layer parameters
	// This function initializes all peripherals through a Hardware Abstraction
	// Layer (HAL). It uses all values stored in gUserParams.
	HAL_setParams(halHandle, &gUserParams[HAL_MTR1]);

	// Overwrite GPIO Qualification Settings
	// =====================================
	// To allow fast movement with lots-of-lines-encoders, the sampling period
	// of the GPIO qualification filter has to be reduced (otherwise encoder
	// pulses get rejected as noise).  The following lines overwrite the
	// settings done in HAL_setupGpio() (hal.c).
	// "period = 11" results in actual sampling period 11*2*(1/90MHz) = 0.24us
	// Note: Setting the period is done for blocks of GPIO pins.
	//
	// GPIO 16-23 (covering eQEP1)
	GPIO_setQualificationPeriod(hal.gpioHandle, GPIO_Number_16, 11); //GPIO16-23
	// GPIO 50-55 and 56-58 (covering eQEP2)
	GPIO_setQualificationPeriod(hal.gpioHandle, GPIO_Number_50, 11); //GPIO50-55
	GPIO_setQualificationPeriod(hal.gpioHandle, GPIO_Number_56, 11); //GPIO56-58

	// Overwrite the settings for timer0 (we want it faster)
	uint32_t timerPeriod_cnts = ((uint32_t)gUserParams[0].systemFreq_MHz * 1e6l)
			/ TIMER0_FREQ_Hz - 1;
	overwriteSetupTimer0(halHandle, timerPeriod_cnts);

	// initialize the estimator
	estHandle[HAL_MTR1] = EST_init((void *)USER_EST_HANDLE_ADDRESS, 0x200);
	estHandle[HAL_MTR2] = EST_init((void *)USER_EST_HANDLE_ADDRESS_1, 0x200);

	{
		uint_least8_t mtrNum;

		for(mtrNum=HAL_MTR1;mtrNum<=HAL_MTR2;mtrNum++)
		{

			// initialize the individual motor hal files
			halHandleMtr[mtrNum] = HAL_init_mtr(
					&halMtr[mtrNum],
					sizeof(halMtr[mtrNum]),
					(HAL_MtrSelect_e)mtrNum);

			// Setup each motor board to its specific setting
			HAL_setParamsMtr(
			        halHandleMtr[mtrNum], halHandle, &gUserParams[mtrNum]);

			{
				// These function calls are used to initialize the estimator
				// with ROM function calls. It needs the specific address where
				// the controller object is declared by the ROM code.
				CTRL_Handle ctrlHandle = CTRL_init(
						(void *)USER_CTRL_HANDLE_ADDRESS, 0x200);
				CTRL_Obj *obj = (CTRL_Obj *)ctrlHandle;

				// this sets the estimator handle (part of the controller
				// object) to the same value initialized above by the
				// EST_init() function call. This is done so the next function
				// implemented in ROM, can successfully initialize the
				// estimator as part of the controller object.
				obj->estHandle = estHandle[mtrNum];

				// initialize the estimator through the controller. These three
				// function calls are needed for the F2806xF/M implementation
				// of InstaSPIN.
				CTRL_setParams(ctrlHandle, &gUserParams[mtrNum]);
				CTRL_setUserMotorParams(ctrlHandle);
				CTRL_setupEstIdleState(ctrlHandle);
			}

			//Compensates for the delay introduced
			//from the time when the system inputs are sampled to when the PWM
			//voltages are applied to the motor windings.
			angleCompHandle[mtrNum] = ANGLE_COMP_init(
					&angleComp[mtrNum],
					sizeof(angleComp[mtrNum]));
			ANGLE_COMP_setParams(angleCompHandle[mtrNum],
					gUserParams[mtrNum].iqFullScaleFreq_Hz,
					gUserParams[mtrNum].pwmPeriod_usec,
					gUserParams[mtrNum].numPwmTicksPerIsrTick);


			// initialize the Clarke modules
			// Clarke handle initialization for current signals
			clarkeHandle_I[mtrNum] = CLARKE_init(
					&clarke_I[mtrNum],
					sizeof(clarke_I[mtrNum]));

			// Clarke handle initialization for voltage signals
			clarkeHandle_V[mtrNum] = CLARKE_init(
					&clarke_V[mtrNum],
					sizeof(clarke_V[mtrNum]));

			// Park handle initialization for current signals
			parkHandle[mtrNum] = PARK_init(
			        &park[mtrNum], sizeof(park[mtrNum]));


			//*** compute scaling factors

			gTorque_Ls_Id_Iq_pu_to_Nm_sf[mtrNum] =
			        USER_computeTorque_Ls_Id_Iq_pu_to_Nm_sf(
			                &gUserParams[mtrNum]);

			gTorque_Flux_Iq_pu_to_Nm_sf[mtrNum] =
			        USER_computeTorque_Flux_Iq_pu_to_Nm_sf(
			                &gUserParams[mtrNum]);

			gSpeed_pu_to_krpm_sf[mtrNum] = _IQ(
					(gUserParams[mtrNum].iqFullScaleFreq_Hz * 60.0)
					/ ((float_t)gUserParams[mtrNum].motor_numPolePairs
					        * 1000.0));

			gCurrent_A_to_pu_sf[mtrNum] = _IQ(
					1.0 / gUserParams[mtrNum].iqFullScaleCurrent_A);


			// disable Rs recalculation
			EST_setFlag_enableRsRecalc(estHandle[mtrNum], false);

			// set the number of current sensors
			setupClarke_I(clarkeHandle_I[mtrNum],
					gUserParams[mtrNum].numCurrentSensors);

			// set the number of voltage sensors
			setupClarke_V(clarkeHandle_V[mtrNum],
					gUserParams[mtrNum].numVoltageSensors);

			// initialize the PID controllers

			// There are two PI controllers, one for Iq and one for Id.
			// This is for the Id current controller
			pidHandle[mtrNum][1] = PID_init(&pid[mtrNum][1],
					sizeof(pid[mtrNum][1]));
			// This is for the Iq current controller
			pidHandle[mtrNum][2] = PID_init(&pid[mtrNum][2],
					sizeof(pid[mtrNum][2]));
			// This sets up both controllers
			pidSetup(pidHandle[mtrNum], gUserParams[mtrNum]);

			// initialize the inverse Park module
			iparkHandle[mtrNum] = IPARK_init(&ipark[mtrNum],
					sizeof(ipark[mtrNum]));

			// initialize the space vector generator module
			svgenHandle[mtrNum] = SVGEN_init(&svgen[mtrNum],
					sizeof(svgen[mtrNum]));

			// initialize and configure offsets using filters
			{
				uint16_t cnt = 0;
				_iq b0 = _IQ(gUserParams[mtrNum].offsetPole_rps
						/ (float_t)gUserParams[mtrNum].ctrlFreq_Hz);
				_iq a1 = (b0 - _IQ(1.0));
				_iq b1 = _IQ(0.0);

				for(cnt=0;cnt<6;cnt++)
				{
					filterHandle[mtrNum][cnt] = FILTER_FO_init(
							&filter[mtrNum][cnt],
							sizeof(filter[mtrNum][0]));
					FILTER_FO_setDenCoeffs(filterHandle[mtrNum][cnt], a1);
					FILTER_FO_setNumCoeffs(filterHandle[mtrNum][cnt], b0, b1);
					FILTER_FO_setInitialConditions(filterHandle[mtrNum][cnt],
							_IQ(0.0),
							_IQ(0.0));
				}

				gMotorVars[mtrNum].Flag_enableOffsetcalc = false;
			}

			// initialize the encoder module
			encHandle[mtrNum] = ENC_init(&enc[mtrNum], sizeof(enc[mtrNum]));

			// initialize the slip compensation module
			slipHandle[mtrNum] = SLIP_init(
			        &slip[mtrNum], sizeof(slip[mtrNum]));
			// setup the SLIP module
			SLIP_setup(slipHandle[mtrNum],
			        _IQ(gUserParams[mtrNum].ctrlPeriod_sec));

			// setup faults
			HAL_setupFaults(halHandleMtr[mtrNum]);

			// initialize the SpinTAC Components
			stHandle[mtrNum] = ST_init(
			        &st_obj[mtrNum], sizeof(st_obj[mtrNum]));

		} // End of for loop
	}

	// setup the encoder module
	ENC_setup(
			encHandle[HAL_MTR1],
			1,
			USER_MOTOR_NUM_POLE_PAIRS,
			USER_MOTOR_ENCODER_LINES,
			0,
			USER_IQ_FULL_SCALE_FREQ_Hz,
			USER_ISR_FREQ_Hz,
			8000.0);
	ENC_setup(
			encHandle[HAL_MTR2],
			1,
			USER_MOTOR_NUM_POLE_PAIRS_2,
			USER_MOTOR_ENCODER_LINES_2,
			0,
			USER_IQ_FULL_SCALE_FREQ_Hz_2,
			USER_ISR_FREQ_Hz_2,
			8000.0);

	// setup encoder index interrupts
	setupQepIndexInterrupt(halHandle, halHandleMtr, &qep1IndexISR,
			&qep2IndexISR);

	// setup the SpinTAC Components
	ST_setupPosConv_mtr1(stHandle[HAL_MTR1]);
	ST_setupPosConv_mtr2(stHandle[HAL_MTR2]);

	// set the pre-determined current and voltage feedback offset values
	gOffsets_I_pu[HAL_MTR1].value[0] = _IQ(I_A_offset);
	gOffsets_I_pu[HAL_MTR1].value[1] = _IQ(I_B_offset);
	gOffsets_I_pu[HAL_MTR1].value[2] = _IQ(I_C_offset);
	gOffsets_V_pu[HAL_MTR1].value[0] = _IQ(V_A_offset);
	gOffsets_V_pu[HAL_MTR1].value[1] = _IQ(V_B_offset);
	gOffsets_V_pu[HAL_MTR1].value[2] = _IQ(V_C_offset);

	gOffsets_I_pu[HAL_MTR2].value[0] = _IQ(I_A_offset_2);
	gOffsets_I_pu[HAL_MTR2].value[1] = _IQ(I_B_offset_2);
	gOffsets_I_pu[HAL_MTR2].value[2] = _IQ(I_C_offset_2);
	gOffsets_V_pu[HAL_MTR2].value[0] = _IQ(V_A_offset_2);
	gOffsets_V_pu[HAL_MTR2].value[1] = _IQ(V_B_offset_2);
	gOffsets_V_pu[HAL_MTR2].value[2] = _IQ(V_C_offset_2);

	// initialize the interrupt vector table
	HAL_initIntVectorTable(halHandle);

	// enable the ADC interrupts
	HAL_enableAdcInts(halHandle);

	// enable global interrupts
	HAL_enableGlobalInts(halHandle);

	// enable debug interrupts
	HAL_enableDebugInt(halHandle);

	// enable the Timer 0 interrupts
	HAL_enableTimer0Int(halHandle);
	PIE_registerTimer0IntHandler(hal.pieHandle, &timer0_ISR);

	// disable the PWM
	HAL_disablePwm(halHandleMtr[HAL_MTR1]);
	HAL_disablePwm(halHandleMtr[HAL_MTR2]);

	// reconfigure GPIO pins for LEDs and button
	HAL_overwriteSetupGpio(halHandle);

	//Interrupt on SPI CS Line
	GPIO_setDirection(halHandle->gpioHandle,GPIO_Number_27,GPIO_Direction_Input); // something was overriding my GPIO22 input setting, so we'll do it here again
	GPIO_setExtInt(halHandle->gpioHandle, GPIO_Number_27, CPU_ExtIntNumber_1);
    setupXINT1(halHandle, &xint1_ISR);

    //Interrupt on SPI RX FIFO
    setupSPIBRXInt(halHandle, &spi_ISR);

	// Setup everything related to SPI communication
	setupSPI();

	// enable the system by default
	gMotorVars[HAL_MTR1].Flag_enableSys = true;

#ifdef DRV8301_SPI
	// turn on the DRV8301 if present
	HAL_enableDrv(halHandleMtr[HAL_MTR1]);
	HAL_enableDrv(halHandleMtr[HAL_MTR2]);

	// initialize the DRV8301 interface
	HAL_setupDrvSpi(halHandleMtr[HAL_MTR1], &gDrvSpi8301Vars[HAL_MTR1]);
	HAL_setupDrvSpi(halHandleMtr[HAL_MTR2], &gDrvSpi8301Vars[HAL_MTR2]);
#endif

#ifdef DRV8305_SPI
	// turn on the DRV8305 if present
	HAL_enableDrv(halHandleMtr[HAL_MTR1]);
	HAL_enableDrv(halHandleMtr[HAL_MTR2]);

//    HAL_turnLedOn(halHandle, LED_ONBOARD_RED);
//    HAL_turnLedOn(halHandle, LED_EXTERN_RED);

	// initialize the DRV8305 interface
	HAL_setupDrvSpi(halHandleMtr[HAL_MTR1], &gDrvSpi8305Vars[HAL_MTR1]);
	HAL_setupDrvSpi(halHandleMtr[HAL_MTR2], &gDrvSpi8305Vars[HAL_MTR2]);
#endif

	//Can be used for debugging purpose
    //GPIO_setDirection(hal.gpioHandle, GPIO_Number_57, GPIO_Direction_Output);
    //GPIO_setDirection(hal.gpioHandle, GPIO_Number_44, GPIO_Direction_Output);
	GPIO_setDirection(hal.gpioHandle, GPIO_Number_33, GPIO_Direction_Output);

	// Begin the background loop
	for(;;)
	{
		// Waiting for enable system flag to be set
		// Motor 1 Flag_enableSys is the master control.
		while(!(gMotorVars[HAL_MTR1].Flag_enableSys))
		{
			LED_run(halHandle);

			/* Asynchronous SPI message read and write */
			if(!gSPI_transmitting && gSPI_timer) {
                spi_prepare_and_read_msg();
                gSPI_timer = false;
            }
		}

		// loop while the enable system flag is true
		// Motor 1 Flag_enableSys is the master control.
		while(gMotorVars[HAL_MTR1].Flag_enableSys)
		{
			uint_least8_t mtrNum = HAL_MTR1;

			/*** Error Checks ***/
			checkErrors();

			LED_run(halHandle);
			// When there is an error, shut down the system to be safe
			if (gErrors.all) {
				gMotorVars[HAL_MTR1].Flag_enableSys = false;
				break; // immediately exit the enabled == true loop
			}

			/* Asynchronous SPI message read and write */
			if(!gSPI_transmitting && gSPI_timer) {
                spi_prepare_and_read_msg();
                gSPI_timer = false;
            }

			// Set the position reset flag via button on a GPIO
			//gFlag_resetZeroPositionOffset = BUTTON_isPressed(hal.gpioHandle);
			// We don't really need the position offset. Rather use the button
			// as a soft emergency stop (i.e. disable system)
			if (BUTTON_isPressed(hal.gpioHandle)) {
			    //EA: This always stops the modified µDriver from running.
				//gMotorVars[HAL_MTR1].Flag_enableSys = false;
			}


			for(mtrNum=HAL_MTR1;mtrNum<=HAL_MTR2;mtrNum++)
			{
				// If the flag is set, set current position as zero offset
				//if (gFlag_resetZeroPositionOffset) {
				//	gZeroPositionOffset[mtrNum] = STPOSCONV_getPosition_mrev(
				//			st_obj[mtrNum].posConvHandle);
				//}

				// If Flag_enableSys is set AND Flag_Run_Identify is set THEN
				// enable PWMs and set the speed reference
				if(gMotorVars[mtrNum].Flag_Run_Identify)
				{

					// update estimator state
					EST_updateState(estHandle[mtrNum], 0);

#ifdef FAST_ROM_V1p6
					// call this function to fix 1p6. This is only used for
					// F2806xF/M implementation of InstaSPIN (version 1.6 of
					// ROM), since the inductance calculation is not done
					// correctly in ROM, so this function fixes that ROM bug.
					softwareUpdate1p6(estHandle[mtrNum], &gUserParams[mtrNum]);
#endif


					// enable the PWM
					HAL_enablePwm(halHandleMtr[mtrNum]);
				}
				else  // Flag_enableSys is set AND Flag_Run_Identify is not set
				{
					// set estimator to Idle
					EST_setIdle(estHandle[mtrNum]);

					// disable the PWM
					HAL_disablePwm(halHandleMtr[mtrNum]);

					// clear integrator outputs
					PID_setUi(pidHandle[mtrNum][0], _IQ(0.0));
					PID_setUi(pidHandle[mtrNum][1], _IQ(0.0));
					PID_setUi(pidHandle[mtrNum][2], _IQ(0.0));

					// clear Id and Iq references
					gIdq_ref_pu[mtrNum].value[0] = _IQ(0.0);
					gIdq_ref_pu[mtrNum].value[1] = _IQ(0.0);
				}

				// update the global variables
				updateGlobalVariables(mtrNum);

				// enable/disable the forced angle
				EST_setFlag_enableForceAngle(estHandle[mtrNum],
						gMotorVars[mtrNum].Flag_enableForceAngle);

#ifdef DRV8301_SPI
				HAL_writeDrvData(
				        halHandleMtr[mtrNum], &gDrvSpi8301Vars[mtrNum]);
				HAL_readDrvData(
				        halHandleMtr[mtrNum], &gDrvSpi8301Vars[mtrNum]);
#endif
#ifdef DRV8305_SPI
				HAL_writeDrvData(
				        halHandleMtr[mtrNum], &gDrvSpi8305Vars[mtrNum]);
				HAL_readDrvData(
				        halHandleMtr[mtrNum], &gDrvSpi8305Vars[mtrNum]);
#endif

			} // end of for loop
		} // end of while(gFlag_enableSys) loop

		// disable the PWM
		HAL_disablePwm(halHandleMtr[HAL_MTR1]);
		HAL_disablePwm(halHandleMtr[HAL_MTR2]);

		gMotorVars[HAL_MTR1].Flag_Run_Identify = false;
		gMotorVars[HAL_MTR2].Flag_Run_Identify = false;

	} // end of for(;;) loop
} // end of main() function


//! \brief     The main ISR that implements the motor control.
interrupt void motor1_ISR(void)
{
    HAL_toggleGpio(halHandle, GPIO_Number_33);
    /* Makes the motor interrupt interruptible (the SPI interrupts are more important) */
    HAL_Obj *obj = (HAL_Obj *)halHandle;
    obj->pieHandle->PIEACK = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycle
    EINT;                                 // Clear INTM to enable interrupts

	// acknowledge the ADC interrupt
	HAL_acqAdcInt(halHandle, ADC_IntNumber_1);

	generic_motor_ISR(HAL_MTR1);

	DINT; //interrupts back to normal
	return;
} // end of motor1_ISR() function


interrupt void motor2_ISR(void)
{
    /* Makes the motor interrupt interruptible (the SPI interrupts are more important) */
    HAL_Obj *obj = (HAL_Obj *)halHandle;
    obj->pieHandle->PIEACK = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycles
    EINT;                                 // Clear INTM to enable interrupts

	// acknowledge the ADC interrupt
	HAL_acqAdcInt(halHandle, ADC_IntNumber_2);

	generic_motor_ISR(HAL_MTR2);

	DINT; //interrupts back to normal
	return;
} // end of motor2_ISR() function

inline void generic_motor_ISR(const HAL_MtrSelect_e mtrNum)
{
    // Declaration of local variables
	static _iq angle_pu[2] = {_IQ(0.0), _IQ(0.0)};
	_iq speed_pu = _IQ(0.0);
	_iq oneOverDcBus;
	MATH_vec2 Iab_pu;
	MATH_vec2 Vab_pu;
	MATH_vec2 phasor;

	// convert the ADC data
	HAL_readAdcDataWithOffsets(
	        halHandle, halHandleMtr[mtrNum], &gAdcData[mtrNum]);

	// remove offsets
	gAdcData[mtrNum].I.value[0] =
	        gAdcData[mtrNum].I.value[0] - gOffsets_I_pu[mtrNum].value[0];
	gAdcData[mtrNum].I.value[1] =
	        gAdcData[mtrNum].I.value[1] - gOffsets_I_pu[mtrNum].value[1];
	gAdcData[mtrNum].I.value[2] =
	        gAdcData[mtrNum].I.value[2] - gOffsets_I_pu[mtrNum].value[2];
	gAdcData[mtrNum].V.value[0] =
	        gAdcData[mtrNum].V.value[0] - gOffsets_V_pu[mtrNum].value[0];
	gAdcData[mtrNum].V.value[1] =
	        gAdcData[mtrNum].V.value[1] - gOffsets_V_pu[mtrNum].value[1];
	gAdcData[mtrNum].V.value[2] =
	        gAdcData[mtrNum].V.value[2] - gOffsets_V_pu[mtrNum].value[2];

	// run Clarke transform on current.  Three values are passed, two values
	// are returned.
	CLARKE_run(clarkeHandle_I[mtrNum], &gAdcData[mtrNum].I, &Iab_pu);

	// compute the sine and cosine phasor values which are part of the
	// Park transform calculations. Once these values are computed,
	// they are copied into the PARK module, which then uses them to
	// transform the voltages from Alpha/Beta to DQ reference frames.
	phasor.value[0] = _IQcosPU(angle_pu[mtrNum]);
	phasor.value[1] = _IQsinPU(angle_pu[mtrNum]);

	// set the phasor in the Park transform
	PARK_setPhasor(parkHandle[mtrNum], &phasor);

	// Run the Park module.  This converts the current vector from
	// stationary frame values to synchronous frame values.
	PARK_run(parkHandle[mtrNum], &Iab_pu, &gIdq_pu[mtrNum]);

	// compute the electrical angle
	ENC_calcElecAngle(
	        encHandle[mtrNum], HAL_getQepPosnCounts(halHandleMtr[mtrNum]));

	if(++stCntPosConv[mtrNum] >= gNumIsrTicksPerPosConvTick[mtrNum])
	{
	    stCntPosConv[mtrNum] = 0;
		// Calculate the feedback speed
		ST_runPosConv(
				stHandle[mtrNum],
				encHandle[mtrNum],
				slipHandle[mtrNum],
				&gIdq_pu[mtrNum],
				gUserParams[mtrNum].motor_type);
	}

	// run the appropriate controller
	if(gMotorVars[mtrNum].Flag_Run_Identify)
	{
		// Declaration of local variables.
		_iq refValue;
		_iq fbackValue;
		_iq outMax_pu;

		_iq position_mrev;
		_iq velocity_pups;
		_iq velocity_krpm;
		_iq current_sat_A;

		// check if the motor should be forced into encoder alignment
		if(gMotorVars[mtrNum].Flag_enableAlignment == false)
		{
		    /*********** PD+Feedforward controller ************/
			// Read position and velocity
			position_mrev = STPOSCONV_getPosition_mrev(st_obj[mtrNum].posConvHandle);
			velocity_pups = STPOSCONV_getVelocityFiltered(st_obj[mtrNum].posConvHandle);
			velocity_krpm = _IQmpy(velocity_pups,gSpeed_pu_to_krpm_sf[mtrNum]);
			//PD+ controller: Iq_ref = Iq_feeforward + Kp*err_pos + Kd*err_vel
			gMotorVars[mtrNum].IqRef_A = _IQmpy(gPositionRef[mtrNum]-position_mrev , gKp_ApMrev[mtrNum]) +
			                             _IQmpy(gVelocityRef[mtrNum]-velocity_krpm , gKd_Apkrpm[mtrNum]) +
			                             gIqFeedforward_A[mtrNum];

			current_sat_A = gIqSat[mtrNum];
			if (current_sat_A != 0)
			{
			    if (gMotorVars[mtrNum].IqRef_A > current_sat_A)
			    {
			        gMotorVars[mtrNum].IqRef_A = current_sat_A;
			    } else if (gMotorVars[mtrNum].IqRef_A < -gIqSat[mtrNum])
			    {
			        gMotorVars[mtrNum].IqRef_A = -current_sat_A;
			    }
			}

			gIdq_ref_pu[mtrNum].value[0] = _IQmpy(gMotorVars[mtrNum].IdRef_A, gCurrent_A_to_pu_sf[mtrNum]);
			gIdq_ref_pu[mtrNum].value[1] = _IQmpy(gMotorVars[mtrNum].IqRef_A, gCurrent_A_to_pu_sf[mtrNum]);
			/************* End of PD+Feedforward **************/

			// generate the motor electrical angle
			if(gUserParams[mtrNum].motor_type == MOTOR_Type_Induction)
			{
				// update the electrical angle for the SLIP module
				SLIP_setElectricalAngle(slipHandle[mtrNum],
						ENC_getElecAngle(encHandle[mtrNum]));
				// compute the amount of slip
				SLIP_run(slipHandle[mtrNum]);
				// set magnetic angle
				angle_pu[mtrNum] = SLIP_getMagneticAngle(slipHandle[mtrNum]);
			}
			else
			{
				angle_pu[mtrNum] = ENC_getElecAngle(encHandle[mtrNum]);
			}

			speed_pu = STPOSCONV_getVelocity(st_obj[mtrNum].posConvHandle);
		}
		else
		{
			// The alignment procedure is in effect.
			// For the first CTRL_State_OffLine wait time, do nothing. This allows
			// the card to initialize during startup. Then, run the calibration procedure.
			if(gAlignCount[mtrNum]++ < gUserParams[mtrNum].ctrlWaitTime[CTRL_State_OffLine]) {
				angle_pu[mtrNum] = _IQ(0.0);
				speed_pu = _IQ(0.0);

				gIdq_ref_pu[mtrNum].value[1] = _IQ(0.0);
				gIdq_ref_pu[mtrNum].value[0] = _IQ(0.0);
			} else {
				// force motor angle and speed to 0
				angle_pu[mtrNum] = _IQ(0.0);
				speed_pu = _IQ(0.0);

				// set D-axis current to Rs estimation current
				gIdq_ref_pu[mtrNum].value[0] = _IQmpy(
					_IQ(gUserParams[mtrNum].maxCurrent_resEst),
					gCurrent_A_to_pu_sf[mtrNum]);
				// set Q-axis current to 0
				gIdq_ref_pu[mtrNum].value[1] = _IQ(0.0);

				// save encoder reading when forcing motor into alignment
				if(gUserParams[mtrNum].motor_type == MOTOR_Type_Pm)
				{
					ENC_setZeroOffset(encHandle[mtrNum],
						(uint32_t)(HAL_getQepPosnMaximum(halHandleMtr[mtrNum])
								- HAL_getQepPosnCounts(halHandleMtr[mtrNum])));
				}

				// if alignment counter exceeds threshold, exit alignment
				if(gAlignCount[mtrNum]
						>= 2*gUserParams[mtrNum].ctrlWaitTime[CTRL_State_OffLine])
				{
					gMotorVars[mtrNum].Flag_enableAlignment = false;
					gAlignCount[mtrNum] = 0;
					gIdq_ref_pu[mtrNum].value[0] = _IQ(0.0);
				}
			}
		}

		// Get the reference value for the d-axis current controller.
		refValue = gIdq_ref_pu[mtrNum].value[0];

		// Get the actual value of Id
		fbackValue = gIdq_pu[mtrNum].value[0];

		// The next instruction executes the PI current controller for the
		// d axis and places its output in Vdq_pu.value[0], which is the
		// control voltage along the d-axis (Vd)
		PID_run(pidHandle[mtrNum][1],
				refValue,
				fbackValue,
				&(gVdq_out_pu[mtrNum].value[0]));

		// get the Iq reference value
		refValue = gIdq_ref_pu[mtrNum].value[1];

		// get the actual value of Iq
		fbackValue = gIdq_pu[mtrNum].value[1];

		// The voltage limits on the output of the q-axis current controller
		// are dynamic, and are dependent on the output voltage from the d-axis
		// current controller.  In other words, the d-axis current controller
		// gets first dibs on the available voltage, and the q-axis current
		// controller gets what's left over.  That is why the d-axis current
		// controller executes first. The next instruction calculates the
		// maximum limits for this voltage as:
		// Vq_min_max = +/- sqrt(Vbus^2 - Vd^2)
		outMax_pu = _IQsqrt(
				_IQ(gUserParams[mtrNum].maxVsMag_pu
						* gUserParams[mtrNum].maxVsMag_pu)
				- _IQmpy(gVdq_out_pu[mtrNum].value[0],
						gVdq_out_pu[mtrNum].value[0]));

		// Set the limits to +/- outMax_pu
		PID_setMinMax(pidHandle[mtrNum][2], -outMax_pu, outMax_pu);

		// The next instruction executes the PI current controller for the
		// q axis and places its output in Vdq_pu.value[1], which is the
		// control voltage vector along the q-axis (Vq)
		PID_run(pidHandle[mtrNum][2],
				refValue,
				fbackValue,
				&(gVdq_out_pu[mtrNum].value[1]));

		// The voltage vector is now calculated and ready to be applied to the
		// motor in the form of three PWM signals.  However, even though the
		// voltages may be supplied to the PWM module now, they won't be
		// applied to the motor until the next PWM cycle. By this point, the
		// motor will have moved away from the angle that the voltage vector
		// was calculated for, by an amount which is proportional to the
		// sampling frequency and the speed of the motor.  For steady-state
		// speeds, we can calculate this angle delay and compensate for it.
		ANGLE_COMP_run(angleCompHandle[mtrNum], speed_pu, angle_pu[mtrNum]);
		angle_pu[mtrNum] = ANGLE_COMP_getAngleComp_pu(angleCompHandle[mtrNum]);

		// compute the sine and cosine phasor values which are part of the
		// inverse Park transform calculations. Once these values are computed,
		// they are copied into the IPARK module, which then uses them to
		// transform the voltages from DQ to Alpha/Beta reference frames.
		phasor.value[0] = _IQcosPU(angle_pu[mtrNum]);
		phasor.value[1] = _IQsinPU(angle_pu[mtrNum]);

		// set the phasor in the inverse Park transform
		IPARK_setPhasor(iparkHandle[mtrNum], &phasor);

		// Run the inverse Park module.  This converts the voltage vector from
		// synchronous frame values to stationary frame values.
		IPARK_run(iparkHandle[mtrNum], &gVdq_out_pu[mtrNum], &Vab_pu);

		// These 3 statements compensate for variations in the DC bus by
		// adjusting the PWM duty cycle. The goal is to achieve the same
		// volt-second product regardless of the DC bus value.  To do this, we
		// must divide the desired voltage values by the DC bus value.  Or...it
		// is easier to multiply by 1/(DC bus value).
		oneOverDcBus = _IQdiv(_IQ(1.0), gAdcData[mtrNum].dcBus);
		Vab_pu.value[0] = _IQmpy(Vab_pu.value[0], oneOverDcBus);
		Vab_pu.value[1] = _IQmpy(Vab_pu.value[1], oneOverDcBus);

		// Now run the space vector generator (SVGEN) module.
		// There is no need to do an inverse CLARKE transform, as this is
		// handled in the SVGEN_run function.
		SVGEN_run(svgenHandle[mtrNum], &Vab_pu, &(gPwmData[mtrNum].Tabc));
	}
	else if(gMotorVars[mtrNum].Flag_enableOffsetcalc == true)
	{
		runOffsetsCalculation(mtrNum);
	}
	else  // gMotorVars.Flag_Run_Identify = 0
	{
		// disable the PWM
		HAL_disablePwm(halHandleMtr[mtrNum]);

		// Set the PWMs to 50% duty cycle
		gPwmData[mtrNum].Tabc.value[0] = _IQ(0.0);
		gPwmData[mtrNum].Tabc.value[1] = _IQ(0.0);
		gPwmData[mtrNum].Tabc.value[2] = _IQ(0.0);
	}

	// write to the PWM compare registers, and then we are done!
	HAL_writePwmData(halHandleMtr[mtrNum], &gPwmData[mtrNum]);
}


interrupt void timer0_ISR()
{
    ++gTimer0_cnt;
	gTimer0_stamp = 1000 * gTimer0_cnt / TIMER0_FREQ_Hz;
	gSPI_timer = true;

	//If the SPI isn't currently transmitting and if a new packet has been prepared asynchronously
    if(!gSPI_transmitting && gSPI_msg_prepared) {
        spi_change_packets(gSPI_packets_send); //Change the (pointer to the) packet to prepare
        spi_load_firsts_words(); //Loads the first words of the prepared packet into the SPI FIFO to be ready
        gSPI_msg_prepared = false;
    }

    // acknowledge interrupt
    HAL_acqTimer0Int(halHandle);
}

inline void spi_prepare_and_read_msg() {
    //TODO: Set the motor and ADC values when read , not in this isr...

    /* prepare the next packet */
    setSPIMotorData(HAL_MTR1);
    setSPIMotorData(HAL_MTR2);

    uint16_t *to_write = packet_to_write(gSPI_packets_send);

    SPI_REG_u16(to_write, SPI_SENSOR_TIMESTAMP) = gTimer0_stamp & (0xFFFF);

    SPI_REG_u16(to_write, SPI_SENSOR_ADC_1) = D32Q24_TO_D16QN(HAL_readAdcResult(halHandle, POTI_RESULT1), SPI_QN_ADC);
    SPI_REG_u16(to_write, SPI_SENSOR_ADC_2) = D32Q24_TO_D16QN(HAL_readAdcResult(halHandle, POTI_RESULT2), SPI_QN_ADC);

    SPI_REG_u16(to_write, SPI_SENSOR_CR_1) = D32Q24_TO_D16QN(0, SPI_QN_CR);
    SPI_REG_u16(to_write, SPI_SENSOR_CR_2) = D32Q24_TO_D16QN(0, SPI_QN_CR);

    SPI_REG_u16(to_write, SPI_TOTAL_INDEX) = SPI_REG_u16(packet_ready(gSPI_packets_recv), SPI_TOTAL_INDEX);

    spi_setStatus(to_write);

    gSPI_msg_prepared = true;

    /* if a message has been received, read it */
    if(gSPI_msg_received && !gSPI_transmitting) {
        uint16_t *to_write = packet_to_write(gSPI_packets_recv);

        /* Check if the packet received is correct*/
        if(gSPI_crc_recv == 0) {
            spi_apply_mode_commands(to_write);

            spi_apply_command_motor(to_write);

            //The 'ready' packet must always be one with valid Iq, Kp, Kd, ... values
            //Because the CRC of this one is valid, it can be set as the 'ready' one
            spi_change_packets(gSPI_packets_recv);
            gSPI_current_rx_packet = (void*) packet_to_write(gSPI_packets_recv);

            //Reset safety timeout
            gSPILastReceivedIqRef_stamp = gTimer0_stamp;

            //HAL_setGpioLow(halHandle, GPIO_Number_57);
        } else {
            gDebug_wrong_CRC++;
            //HAL_setGpioHigh(halHandle, GPIO_Number_57);
        }
        gSPI_msg_received = false;
    }
}

inline void spi_apply_command_motor(uint16_t *packet) {
	_iq position_raw;
	gIqFeedforward_A[0] = D16QN_TO_D32Q24(SPI_REG_16(packet, SPI_COMMAND_IQ_1), SPI_QN_IQ);
	gIqFeedforward_A[1] = D16QN_TO_D32Q24(SPI_REG_16(packet, SPI_COMMAND_IQ_2), SPI_QN_IQ);

	gKp_ApMrev[0] =  uD16QN_TO_D32Q24( SPI_REG_u16(packet, SPI_COMMAND_KP_1), SPI_QN_KP);
	gKp_ApMrev[1] =  uD16QN_TO_D32Q24( SPI_REG_u16(packet, SPI_COMMAND_KP_2), SPI_QN_KP);

	gKd_Apkrpm[0] = uD16QN_TO_D32Q24(SPI_REG_u16(packet, SPI_COMMAND_KD_1), SPI_QN_KD);
	gKd_Apkrpm[1] = uD16QN_TO_D32Q24(SPI_REG_u16(packet, SPI_COMMAND_KD_2), SPI_QN_KD);

	position_raw = ((int32_t) SPI_REG_16(packet, SPI_COMMAND_POS_1) << 16) | (0xffff & SPI_REG_16(packet, SPI_COMMAND_POS_1+1));
	if (gEnableIndexOffsetCompensation[0])
		gPositionRef[0] = position_raw + gZeroPositionOffset[0];
	else
		gPositionRef[0] = position_raw;


	position_raw = ((int32_t) SPI_REG_16(packet, SPI_COMMAND_POS_2) << 16) | (0xffff & SPI_REG_16(packet, SPI_COMMAND_POS_2+1));
	if (gEnableIndexOffsetCompensation[1])
		gPositionRef[1] = position_raw + gZeroPositionOffset[1];
	else
		gPositionRef[1] = position_raw;

	gVelocityRef[0] = D16QN_TO_D32Q24(SPI_REG_16(packet, SPI_COMMAND_VEL_1), SPI_QN_VEL);
	gVelocityRef[1] = D16QN_TO_D32Q24(SPI_REG_16(packet, SPI_COMMAND_VEL_2), SPI_QN_VEL);

	gIqSat[0] = uD16QN_TO_D32Q24((0xff & SPI_REG_16(packet, SPI_COMMAND_ISAT_12)), SPI_QN_ISAT);
	gIqSat[1] = uD16QN_TO_D32Q24(((0xff00 & SPI_REG_16(packet, SPI_COMMAND_ISAT_12)) >> 8), SPI_QN_ISAT);
}

void runOffsetsCalculation(HAL_MtrSelect_e mtrNum)
{
	uint16_t cnt;

	// enable the PWM
	HAL_enablePwm(halHandleMtr[mtrNum]);

	for(cnt=0;cnt<3;cnt++)
	{
		// Set the PWMs to 50% duty cycle
		gPwmData[mtrNum].Tabc.value[cnt] = _IQ(0.0);

		// reset offsets used
		gOffsets_I_pu[mtrNum].value[cnt] = _IQ(0.0);
		gOffsets_V_pu[mtrNum].value[cnt] = _IQ(0.0);

		// run offset estimation
		FILTER_FO_run(filterHandle[mtrNum][cnt],
				gAdcData[mtrNum].I.value[cnt]);
		FILTER_FO_run(filterHandle[mtrNum][cnt+3],
				gAdcData[mtrNum].V.value[cnt]);
	}

	if(gOffsetCalcCount[mtrNum]++
			>= gUserParams[mtrNum].ctrlWaitTime[CTRL_State_OffLine])
	{
		gMotorVars[mtrNum].Flag_enableOffsetcalc = false;
		gOffsetCalcCount[mtrNum] = 0;

		for(cnt=0;cnt<3;cnt++)
		{
			// get calculated offsets from filter
			gOffsets_I_pu[mtrNum].value[cnt] = FILTER_FO_get_y1(
					filterHandle[mtrNum][cnt]);
			gOffsets_V_pu[mtrNum].value[cnt] = FILTER_FO_get_y1(
					filterHandle[mtrNum][cnt+3]);

			// clear filters
			FILTER_FO_setInitialConditions(
			        filterHandle[mtrNum][cnt], _IQ(0.0), _IQ(0.0));
			FILTER_FO_setInitialConditions(
			        filterHandle[mtrNum][cnt+3], _IQ(0.0), _IQ(0.0));
		}
	}

	return;
} // end of runOffsetsCalculation() function


//! \brief     Update the global variables (gMotorVars).
//! \param[in] handle  The estimator (EST) handle
void updateGlobalVariables(const uint_least8_t mtrNum)
{
	// get the speed estimate
	gMotorVars[mtrNum].Speed_krpm = _IQmpy(
			STPOSCONV_getVelocityFiltered(st_obj[mtrNum].posConvHandle),
			gSpeed_pu_to_krpm_sf[mtrNum]);

	// Get the DC buss voltage
	gMotorVars[mtrNum].VdcBus_kV = _IQmpy(gAdcData[mtrNum].dcBus,
			_IQ(gUserParams[mtrNum].iqFullScaleVoltage_V / 1000.0));

	// read Vd and Vq vectors per units
	gMotorVars[mtrNum].Vd = gVdq_out_pu[mtrNum].value[0];
	gMotorVars[mtrNum].Vq = gVdq_out_pu[mtrNum].value[1];

	// calculate vector Vs in per units: (Vs = sqrt(Vd^2 + Vq^2))
	gMotorVars[mtrNum].Vs =
			_IQsqrt(_IQmpy(gMotorVars[mtrNum].Vd, gMotorVars[mtrNum].Vd)
			+ _IQmpy(gMotorVars[mtrNum].Vq, gMotorVars[mtrNum].Vq));

	// read Id and Iq vectors in amps
	gMotorVars[mtrNum].Id_A = _IQmpy(gIdq_pu[mtrNum].value[0],
			_IQ(gUserParams[mtrNum].iqFullScaleCurrent_A));
	gMotorVars[mtrNum].Iq_A = _IQmpy(gIdq_pu[mtrNum].value[1],
			_IQ(gUserParams[mtrNum].iqFullScaleCurrent_A));

	// calculate vector Is in amps:  (Is_A = sqrt(Id_A^2 + Iq_A^2))
	gMotorVars[mtrNum].Is_A =
			_IQsqrt(_IQmpy(gMotorVars[mtrNum].Id_A, gMotorVars[mtrNum].Id_A)
			+ _IQmpy(gMotorVars[mtrNum].Iq_A, gMotorVars[mtrNum].Iq_A));

	// get the torque estimate
	gMotorVars[mtrNum].Torque_Nm = UTILS_computeTorque_Nm(
			estHandle[mtrNum],
			gIdq_pu[mtrNum],
			gTorque_Flux_Iq_pu_to_Nm_sf[mtrNum],
			gTorque_Ls_Id_Iq_pu_to_Nm_sf[mtrNum]);


	// get the Position Converter error
	gMotorVars[mtrNum].SpinTAC.PosConvErrorID =
			STPOSCONV_getErrorID(st_obj[mtrNum].posConvHandle);

	return;
} // end of updateGlobalVariables() function


void spi_setStatus(uint16_t *packet)
{
	uint16_t *mode = &(SPI_REG_u16(packet, SPI_SENSOR_STATUS));

	*mode = 0;
	*mode |= gMotorVars[HAL_MTR1].Flag_enableSys ? SPI_SENSOR_STATUS_SE : 0;
	*mode |= gMotorVars[HAL_MTR1].Flag_Run_Identify ? SPI_SENSOR_STATUS_M1E : 0;
	*mode |= !gMotorVars[HAL_MTR1].Flag_enableAlignment ? SPI_SENSOR_STATUS_M1R : 0;
	*mode |= gMotorVars[HAL_MTR2].Flag_Run_Identify ? SPI_SENSOR_STATUS_M2E : 0;
	*mode |= !gMotorVars[HAL_MTR2].Flag_enableAlignment ? SPI_SENSOR_STATUS_M2R : 0;
    *mode |= gQepIndexWatchdog[HAL_MTR1].isInitialized ? SPI_SENSOR_STATUS_IDX1D : 0;
    *mode |= gQepIndexWatchdog[HAL_MTR2].isInitialized ? SPI_SENSOR_STATUS_IDX2D : 0;
    *mode |= gQepIndexWatchdog[HAL_MTR1].toggleBit ? SPI_SENSOR_STATUS_IDX1T : 0;
    *mode |= gQepIndexWatchdog[HAL_MTR2].toggleBit ? SPI_SENSOR_STATUS_IDX2T : 0;
	if (gErrors.bit.qep1_error) {
	    *mode |= SPI_SENSOR_STATUS_ERROR_ENCODER1;
	} else if (gErrors.bit.qep2_error) {
	    *mode |= SPI_SENSOR_STATUS_ERROR_ENCODER2;
	} else if (gErrors.bit.can_error) {
		// There is not really a point in reporting this error, the message
		// most likely won't come through.  So do it here for completeness but
		// don't waste a separate error code on this.
	    *mode |= SPI_SENSOR_STATUS_ERROR_OTHER;
	} else if (gErrors.bit.spi_recv_timeout) {
	    *mode |= SPI_SENSOR_STATUS_ERROR_SPI_RECV_TIMEOUT;
	} else if (gErrors.bit.posconv_error) {
	    *mode |= SPI_SENSOR_STATUS_ERROR_POSCONV;
	} else if (gErrors.bit.pos_rollover) {
	    *mode |= SPI_SENSOR_STATUS_ERROR_POS_ROLLOVER;
	} else {
	    *mode |= SPI_SENSOR_STATUS_ERROR_NO_ERROR;
	}

}


void setSPIMotorData(const HAL_MtrSelect_e mtrNum)
{
	_iq current_iq, position, speed;
	ST_Obj *st = (ST_Obj*) stHandle[mtrNum];

	// take last current measurement and convert to Ampere
	current_iq = _IQmpy(gIdq_pu[mtrNum].value[1],
			_IQ(gUserParams[mtrNum].iqFullScaleCurrent_A));

	// take the current position
	position = STPOSCONV_getPosition_mrev(st->posConvHandle);
	// remove zero position offset (feature disabled)
	//_iq mrev_rollover = STPOSCONV_getMRevMaximum_mrev(st->posConvHandle);
	//position = removePositionOffset(position, gZeroPositionOffset[mtrNum],
	//		mrev_rollover);

	//TODO check for rollover  (removePositionOffset is not define in this project)
	if (gEnableIndexOffsetCompensation[mtrNum])
	{
	    position = position - gZeroPositionOffset[mtrNum];
	}
	// take current velocity and convert to krpm
	speed = _IQmpy(
			STPOSCONV_getVelocityFiltered(st->posConvHandle),
			gSpeed_pu_to_krpm_sf[mtrNum]);

	uint16_t *to_write = packet_to_write(gSPI_packets_send);

    if (mtrNum == HAL_MTR1) {
        SPI_REG_16(to_write, SPI_SENSOR_IQ_1) = D32Q24_TO_D16QN(current_iq, SPI_QN_IQ);
        //SPI_REG_32(to_write, SPI_SENSOR_POS_1) = position;
        SPI_REG_16(to_write, SPI_SENSOR_POS_1    ) = position >> 16;
        SPI_REG_16(to_write, SPI_SENSOR_POS_1 + 1) = position & 0xFFFF;
        SPI_REG_16(to_write, SPI_SENSOR_VEL_1) = D32Q24_TO_D16QN(speed, SPI_QN_VEL);
    } else {
        SPI_REG_16(to_write, SPI_SENSOR_IQ_2) = D32Q24_TO_D16QN(current_iq, SPI_QN_IQ);
        //SPI_REG_32(to_write, SPI_SENSOR_POS_2) = position;
        SPI_REG_16(to_write, SPI_SENSOR_POS_2    ) = position >> 16;
        SPI_REG_16(to_write, SPI_SENSOR_POS_2 + 1) = position & 0xFFFF;
        SPI_REG_16(to_write, SPI_SENSOR_VEL_2) = D32Q24_TO_D16QN(speed, SPI_QN_VEL);
    }

	return;
}


interrupt void qep1IndexISR()
{
	genericQepIndexISR(HAL_MTR1);
}


interrupt void qep2IndexISR()
{
	genericQepIndexISR(HAL_MTR2);
}


inline void genericQepIndexISR(const HAL_MtrSelect_e mtrNum)
{
	HAL_Obj *obj = (HAL_Obj *)halHandle;
	HAL_Obj_mtr *halMtrObj = (HAL_Obj_mtr *)halHandleMtr[mtrNum];

	uint32_t index_posn = QEP_read_posn_index_latch(halMtrObj->qepHandle);

	//Flip the toggle_bit
	gQepIndexWatchdog[mtrNum].toggleBit = !gQepIndexWatchdog[mtrNum].toggleBit;

	// Compute position error compared to first index
	if (gQepIndexWatchdog[mtrNum].isInitialized) {
		gQepIndexWatchdog[mtrNum].indexError_counts = index_posn
				- gQepIndexWatchdog[mtrNum].indexPosition_counts;
	} else {
		gQepIndexWatchdog[mtrNum].isInitialized = true;
		gQepIndexWatchdog[mtrNum].indexPosition_counts = index_posn;
		ST_Obj *st = (ST_Obj*) stHandle[mtrNum];
	    gZeroPositionOffset[mtrNum] = STPOSCONV_getPosition_mrev(st->posConvHandle);
	}

	// acknowledge QEP interrupt
	// for some reason I have to clear *all* flags, not only Iel
	QEP_clear_all_interrupt_flags(halMtrObj->qepHandle);
	// acknowledge interrupt from PIE group 5
	PIE_clearInt(obj->pieHandle, PIE_GroupNumber_5);
}


bool checkEncoderError(const QepIndexWatchdog_t qiwd)
{
	return abs(qiwd.indexError_counts) > QEP_MAX_INDEX_ERROR;
}


void checkErrors()
{
	//*** SPI Timeout

	gErrors.bit.spi_recv_timeout = (
			gSPIReceiveIqRefTimeout != 0 // and timeout is enabled
			// check if one of the motors is enabled and has a IqRef != 0
			&& ((gMotorVars[HAL_MTR1].Flag_Run_Identify
					&& gMotorVars[HAL_MTR1].IqRef_A != 0)
					|| (gMotorVars[HAL_MTR2].Flag_Run_Identify
							&& gMotorVars[HAL_MTR2].IqRef_A != 0))
			// finally check if last message exceeds timeout
			&& (gSPILastReceivedIqRef_stamp
					< gTimer0_stamp - gSPIReceiveIqRefTimeout)
			);

	//*** Encoder Errors
	gErrors.bit.qep1_error = checkEncoderError(gQepIndexWatchdog[0]);
	gErrors.bit.qep2_error = checkEncoderError(gQepIndexWatchdog[1]);

	//*** POSCONV error
	gErrors.bit.posconv_error = (
			(STPOSCONV_getErrorID(st_obj[HAL_MTR1].posConvHandle) != 0) ||
			(STPOSCONV_getErrorID(st_obj[HAL_MTR2].posConvHandle) != 0)
			);

	//*** Position Rollover (only check if enabled)
	gErrors.bit.pos_rollover = gFlag_enablePosRolloverError && (
			(STPOSCONV_getPositionRollOver(st_obj[HAL_MTR1].posConvHandle) != 0)
			||
			(STPOSCONV_getPositionRollOver(st_obj[HAL_MTR2].posConvHandle) != 0)
			);
}


void LED_run(HAL_Handle halHandle)
{
	//*** GREEN/BLUE LED
	// Off = system disabled
	// On = system enabled
	// Slow Blinking = motor enabled
	// Fast Blinking = aligning motor
	if (gMotorVars[0].Flag_enableSys) {
		// Show system and motor status using the blue LED
		if (gMotorVars[0].Flag_Run_Identify || gMotorVars[1].Flag_Run_Identify)
		{
			uint32_t blink_duration = TIMER0_FREQ_Hz / LED_BLINK_FREQ_Hz;

			// blink faster while motors are aligned
			if ((gMotorVars[0].Flag_Run_Identify
					&& gMotorVars[0].Flag_enableAlignment)
					|| (gMotorVars[1].Flag_Run_Identify
							&& gMotorVars[1].Flag_enableAlignment)) {
				blink_duration /= 4;
			}

			// toggle status LED
			if(gStatusLedBlinkLastToggleTime
					< (gTimer0_stamp - blink_duration))
			{
				HAL_toggleLed(halHandle, LED_ONBOARD_BLUE);
				HAL_toggleLed(halHandle, LED_EXTERN_GREEN);
				gStatusLedBlinkLastToggleTime = gTimer0_stamp;
			}
		}
		else
		{
			HAL_turnLedOn(halHandle, LED_ONBOARD_BLUE);
			HAL_turnLedOn(halHandle, LED_EXTERN_GREEN);
		}
	}
	else // system disabled
	{
		HAL_turnLedOff(halHandle, LED_ONBOARD_BLUE);
		HAL_turnLedOff(halHandle, LED_EXTERN_GREEN);
	}


	//*** YELLOW LED
	//HAL_turnLedOn(halHandle, LED_EXTERN_YELLOW);

	//*** RED LED
	// Turn on if there is an error
	if (gErrors.all) {
		HAL_turnLedOn(halHandle, LED_ONBOARD_RED);
		HAL_turnLedOn(halHandle, LED_EXTERN_RED);
	} else {
		HAL_turnLedOff(halHandle, LED_ONBOARD_RED);
		HAL_turnLedOff(halHandle, LED_EXTERN_RED);
	}

}

//@} //defgroup
// end of file
