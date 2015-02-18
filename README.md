# PSoC-4-Motor-Controller
This will be a modbus slave which can control a motor through PID and encoders.

it is using the same Modbus library which I made which you can find in the repos.

If you wish to just use it as a generic PSoC 4 PID Motor speed controller then just
remove the modbus code from Main and remove modbus.c. From the schematic you can
delete all of the modbus page and just keep the motor page. The rest should be self
explanatory. 
I have tested it on the PSoC 4 Pioneer board only.
