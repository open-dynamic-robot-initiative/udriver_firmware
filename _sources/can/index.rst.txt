.. _can:

******************************
Firmware for CAN Communication
******************************

**This section contains information that is specific to the CAN-version of the
firmware.**

This firmware allows torque control of two motors at once using communication
via CAN.  Use this firmware when you want to connect a TI LaunchPad evaluation
board or a BLMC µDriver board via CAN.  If you want to communicate via Ethernet,
using a Master Board, use the :ref:`SPI-version <spi>` instead.

This firmware can be used with the `Universal Dual Motor GUI`_.


.. toctree::
   :caption: Content:
   :maxdepth: 1

   can_connection
   CAN Protocol <can_interface>
   led_codes


.. _Universal Dual Motor GUI: https://github.com/open-dynamic-robot-initiative/mw_gui_universal
