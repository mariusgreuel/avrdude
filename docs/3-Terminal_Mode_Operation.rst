.. _Terminal_Mode_Operation:

***********************
Terminal Mode Operation
***********************

AVRDUDE has an interactive mode called `terminal mode` that is
enabled by the *-t* option.  This mode allows one to enter
interactive commands to display and modify the various device memories,
perform a chip erase, display the device signature bytes and part
parameters, and to send raw programming commands.  Commands and
parameters may be abbreviated to their shortest unambiguous form.
Terminal mode also supports a command history so that previously entered
commands can be recalled and edited.

.. _Terminal_Mode_Commands:

Terminal Mode Commands
======================

The following commands are implemented:



*dump `memtype` `addr` `nbytes`*
  Read `nbytes` from the specified memory area, and display them in
  the usual hexadecimal and ASCII form.


*dump*
  Continue dumping the memory contents for another `nbytes` where the
  previous dump command left off.


*write `memtype` `addr` `byte1` ... `byteN`*
  Manually program the respective memory cells, starting at address addr,
  using the values `byte1` through `byteN`.  This feature is not
  implemented for bank-addressed memories such as the flash memory of
  ATMega devices.


*erase*
  Perform a chip erase.


*send `b1` `b2` `b3` `b4`*
  Send raw instruction codes to the AVR device.  If you need access to a
  feature of an AVR part that is not directly supported by AVRDUDE, this
  command allows you to use it, even though AVRDUDE does not implement the
  command.   When using direct SPI mode, up to 3 bytes
  can be omitted.


*sig*
  Display the device signature bytes.


*spi*
  Enter direct SPI mode.  The *pgmled* pin acts as slave select.
  *Only supported on parallel bitbang programmers.*


*part*
  Display the current part settings and parameters.  Includes chip
  specific information including all memory types supported by the
  device, read/write timing, etc.


*pgm*
  Return to programming mode (from direct SPI mode).


*verbose [`level`]*
  Change (when `level` is provided), or display the verbosity
  level.
  The initial verbosity level is controlled by the number of `-v` options
  given on the command line.


*?*

*help*
  Give a short on-line summary of the available commands.


*quit*
  Leave terminal mode and thus AVRDUDE.


In addition, the following commands are supported on the STK500
and STK600 programmer:



*vtarg `voltage`*
  Set the target's supply voltage to `voltage` Volts.


*varef [`channel`] `voltage`*
  Set the adjustable voltage source to `voltage` Volts.
  This voltage is normally used to drive the target's
  *Aref* input on the STK500 and STK600.
  The STK600 offers two reference voltages, which can be
  selected by the optional parameter `channel` (either
  0 or 1).


*fosc `freq`[`M`|`k`]*
  Set the master oscillator to `freq` Hz.
  An optional trailing letter `M`
  multiplies by 1E6, a trailing letter `k` by 1E3.


*fosc off*
  Turn the master oscillator off.


*sck `period`*
  *STK500 and STK600 only:*
  Set the SCK clock period to `period` microseconds.

  *JTAG ICE only:*
  Set the JTAG ICE bit clock period to `period` microseconds.
  Note that unlike STK500 settings, this setting will be reverted to
  its default value (approximately 1 microsecond) when the programming
  software signs off from the JTAG ICE.
  This parameter can also be used on the JTAG ICE mkII/3 to specify the
  ISP clock period when operating the ICE in ISP mode.


*parms*
  *STK500 and STK600 only:*
  Display the current voltage and master oscillator parameters.

  *JTAG ICE only:*
  Display the current target supply voltage and JTAG bit clock rate/period.


.. _Terminal_Mode_Examples:

Terminal Mode Examples
======================

Display part parameters, modify eeprom cells, perform a chip erase:


::

  @cartouche
  % avrdude -p m128 -c stk500 -t

  avrdude: AVR device initialized and ready to accept instructions
  avrdude: Device signature = 0x1e9702
  avrdude: current erase-rewrite cycle count is 52 (if being tracked)
  avrdude> part
  >>> part 

  AVR Part              : ATMEGA128
  Chip Erase delay      : 9000 us
  PAGEL                 : PD7
  BS2                   : PA0
  RESET disposition     : dedicated
  RETRY pulse           : SCK
  serial program mode   : yes
  parallel program mode : yes
  Memory Detail         :

                              Page                       Polled
    Memory Type Paged  Size   Size #Pages MinW  MaxW   ReadBack
    ----------- ------ ------ ---- ------ ----- ----- ---------
    eeprom      no       4096    8     0  9000  9000 0xff 0xff
    flash       yes    131072  256   512  4500  9000 0xff 0x00
    lfuse       no          1    0     0     0     0 0x00 0x00
    hfuse       no          1    0     0     0     0 0x00 0x00
    efuse       no          1    0     0     0     0 0x00 0x00
    lock        no          1    0     0     0     0 0x00 0x00
    calibration no          1    0     0     0     0 0x00 0x00
    signature   no          3    0     0     0     0 0x00 0x00

  avrdude> dump eeprom 0 16
  >>> dump eeprom 0 16 
  0000  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|

  avrdude> write eeprom 0 1 2 3 4
  >>> write eeprom 0 1 2 3 4 

  avrdude> dump eeprom 0 16
  >>> dump eeprom 0 16 
  0000  01 02 03 04 ff ff ff ff  ff ff ff ff ff ff ff ff  |................|

  avrdude> erase
  >>> erase 
  avrdude: erasing chip
  avrdude> dump eeprom 0 16
  >>> dump eeprom 0 16 
  0000  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|

  avrdude> 
  @end cartouche
  

Program the fuse bits of an ATmega128 (disable M103 compatibility,
enable high speed external crystal, enable brown-out detection, slowly
rising power).  Note since we are working with fuse bits the -u (unsafe)
option is specified, which allows you to modify the fuse bits. First 
display the factory defaults, then reprogram:


::

  @cartouche
  % avrdude -p m128 -u -c stk500 -t

  avrdude: AVR device initialized and ready to accept instructions
  avrdude: Device signature = 0x1e9702
  avrdude: current erase-rewrite cycle count is 52 (if being tracked)
  avrdude> d efuse
  >>> d efuse 
  0000  fd                                                |.               |

  avrdude> d hfuse
  >>> d hfuse 
  0000  99                                                |.               |

  avrdude> d lfuse
  >>> d lfuse 
  0000  e1                                                |.               |

  avrdude> w efuse 0 0xff
  >>> w efuse 0 0xff 

  avrdude> w hfuse 0 0x89
  >>> w hfuse 0 0x89 

  avrdude> w lfuse 0 0x2f
  >>> w lfuse 0 0x2f 

  avrdude> 
  @end cartouche
  

