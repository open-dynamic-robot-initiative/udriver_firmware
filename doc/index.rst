********************************
ODRI Firmware for uDriver Boards
********************************

.. toctree::
   :hidden:
   :maxdepth: 3

   Build & Flash <build_instructions>
   motor_alignment
   program_structure_and_frequencies
   CAN <can/index>
   SPI <spi/index>


This documentation describes the firmware for the `Open Robot Actuator Motor
Boards`_.  There are two versions of the firmware, one for communication via
:ref:`CAN <can>` and one for :ref:`SPI <spi>` (use the latter when communicating
through a master board).

While the two versions differ in details, the basic principle is the same.
Pages of this documentation that are not in the "CAN" or "SPI" sections apply
to both versions.


Links
=====

- Find the source on `GitHub
  <https://github.com/open-dynamic-robot-initiative/udriver_firmware>`_.
- If you have questions, see our `forum <https://odri.discourse.group>`_.


.. _Open Robot Actuator Motor Boards: https://github.com/open-dynamic-robot-initiative/open_robot_actuator_hardware
