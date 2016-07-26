# home_energy_control_water_system
Arduino sketch for controlling my home's water systems

Should considerably reduce the monthly energy consumption.
Expecting a 30% decrease.

The project consists of a clock and a digital pin controller.
I'm starting with an Arduino UNO R3 as the microcontroller, since only 8 digital ports and a very small quantity of memory are needed.

The clock was implemented the following way:
When the Arduino starts, it checks the EEPROM for a pre-stored time. If it doesn't find any, it tries to read a UNIX time constant, preceded by the letter 'T', from the serial port. The program won't continue until a valid time is inputted. Once the reading is done, it will set the device clock and store the entered time in the EEPROM. If, on the other hand, when checking the EEPROM it finds a stored time, the program will check a calculated EEPROM address for the number of times this value was accessed. Should this number be equal to or bigger than a pre-defined maximum, the stored time will be cleared from the EEPROM and the program will assume no pre-stored time was found. In case the number of accesses is smaller than the maximum, it will be incremented and re-stored, and the found time will be set as the device time.

This was done because, unfortunately, my MacBook has broken and I now only have a desktop, the place where I have to install the system being very distant from my desk. So, the plan is to set the clock 10 min in the future, which should be enough for me to install the board. Adding a display and some keys to the Arduino, although simple enough, is beyond the current scope of this project.
