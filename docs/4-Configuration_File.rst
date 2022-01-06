.. _Configuration_File:

******************
Configuration File
******************

AVRDUDE reads a configuration file upon startup which describes all of
the parts and programmers that it knows about.  The advantage of this is
that if you have a chip that is not currently supported by AVRDUDE, you
can add it to the configuration file without waiting for a new release
of AVRDUDE.  Likewise, if you have a parallel port programmer that is
not supported by AVRDUDE, chances are good that you can copy and
existing programmer definition, and with only a few changes, make your
programmer work with AVRDUDE.

AVRDUDE first looks for a system wide configuration file in a platform
dependent location.  On Unix, this is usually
`/usr/local/etc/avrdude.conf`, while on Windows it is usually in the
same location as the executable file.  The name of this file can be
changed using the *-C* command line option.  After the system wide
configuration file is parsed, AVRDUDE looks for a per-user configuration
file to augment or override the system wide defaults.  On Unix, the
per-user file is `.avrduderc` within the user's home directory.  On
Windows, this file is the `avrdude.rc` file located in the same
directory as the executable.

.. _AVRDUDE_Defaults:

AVRDUDE Defaults
================



*default_parallel = "`default-parallel-device`";*
  Assign the default parallel port device.  Can be overridden using the
  *-P* option.


*default_serial = "`default-serial-device`";*
  Assign the default serial port device.  Can be overridden using the
  *-P* option.


*default_programmer = "`default-programmer-id`";*
  Assign the default programmer id.  Can be overridden using the *-c*
  option.


*default_bitclock = "`default-bitclock`";*
  Assign the default bitclock value.  Can be overridden using the *-B*
  option.


.. _Programmer_Definitions:

Programmer Definitions
======================

The format of the programmer definition is as follows:


::

  programmer
      parent <id>                                 # <id> is a quoted string
      id       = <id1> [, <id2> [, <id3>] ...] ;  # <idN> are quoted strings
      desc     = <description> ;                  # quoted string
      type     = "par" | "stk500" | ... ;         # programmer type (see below for a list)
      baudrate = <num> ;                          # baudrate for serial ports
      vcc      = <num1> [, <num2> ... ] ;         # pin number(s)
      buff     = <num1> [, <num2> ... ] ;         # pin number(s)
      reset    = <num> ;                          # pin number
      sck      = <num> ;                          # pin number
      mosi     = <num> ;                          # pin number
      miso     = <num> ;                          # pin number
      errled   = <num> ;                          # pin number
      rdyled   = <num> ;                          # pin number
      pgmled   = <num> ;                          # pin number
      vfyled   = <num> ;                          # pin number
      usbvid   = <hexnum>;                        # USB VID (Vendor ID)
      usbpid   = <hexnum> [, <hexnum> ...];       # USB PID (Product ID)
      usbdev   = <interface>;                     # USB interface or other device info 
      usbvendor = <vendorname>;                   # USB Vendor Name
      usbproduct = <productname>;                 # USB Product Name
      usbsn    = <serialno>;                      # USB Serial Number
    ;
  

If a parent is specified, all settings of it (except its ids) are used for the new 
programmer. These values can be changed by new setting them for the new programmer.

To invert a bit in the pin definitions, use `= ~ <num>`.

Not all programmer types can handle a list of USB PIDs.

Following programmer types are currently implemented:

@multitable @columnfractions .25 .6
* `arduino` @tab Arduino programmer
* `avr910` @tab Serial programmers using protocol described in application note AVR910
* `avrftdi` @tab Interface to the MPSSE Engine of FTDI Chips using libftdi.
* `buspirate` @tab Using the Bus Pirate's SPI interface for programming
* `buspirate_bb` @tab Using the Bus Pirate's bitbang interface for programming
* `butterfly` @tab Atmel Butterfly evaluation board; Atmel AppNotes AVR109, AVR911
* `butterfly_mk` @tab Mikrokopter.de Butterfly
* `dragon_dw` @tab Atmel AVR Dragon in debugWire mode
* `dragon_hvsp` @tab Atmel AVR Dragon in HVSP mode
* `dragon_isp` @tab Atmel AVR Dragon in ISP mode
* `dragon_jtag` @tab Atmel AVR Dragon in JTAG mode
* `dragon_pdi` @tab Atmel AVR Dragon in PDI mode
* `dragon_pp` @tab Atmel AVR Dragon in PP mode
* `flip1` @tab FLIP USB DFU protocol version 1 (doc7618)
* `flip2` @tab FLIP USB DFU protocol version 2 (AVR4023)
* `ftdi_syncbb` @tab FT245R/FT232R Synchronous BitBangMode Programmer
* `jtagmki` @tab Atmel JTAG ICE mkI
* `jtagmkii` @tab Atmel JTAG ICE mkII
* `jtagmkii_avr32` @tab Atmel JTAG ICE mkII in AVR32 mode
* `jtagmkii_dw` @tab Atmel JTAG ICE mkII in debugWire mode
* `jtagmkii_isp` @tab Atmel JTAG ICE mkII in ISP mode
* `jtagmkii_pdi` @tab Atmel JTAG ICE mkII in PDI mode
* `jtagice3` @tab Atmel JTAGICE3
* `jtagice3_pdi` @tab Atmel JTAGICE3 in PDI mode
* `jtagice3_updi` @tab Atmel JTAGICE3 in UPDI mode
* `jtagice3_dw` @tab Atmel JTAGICE3 in debugWire mode
* `jtagice3_isp` @tab Atmel JTAGICE3 in ISP mode
* `linuxgpio` @tab GPIO bitbanging using the Linux sysfs interface (not available)
* `linuxspi` @tab SPI using Linux spidev driver (not available)
* `micronucleus` @tab Micronucleus Bootloader
* `par` @tab Parallel port bitbanging
* `pickit2` @tab Microchip's PICkit2 Programmer
* `serbb` @tab Serial port bitbanging
* `serialupdi` @tab Driver for SerialUPDI programmers
* `stk500` @tab Atmel STK500 Version 1.x firmware
* `stk500generic` @tab Atmel STK500, autodetect firmware version
* `stk500v2` @tab Atmel STK500 Version 2.x firmware
* `stk500hvsp` @tab Atmel STK500 V2 in high-voltage serial programming mode
* `stk500pp` @tab Atmel STK500 V2 in parallel programming mode
* `stk600` @tab Atmel STK600
* `stk600hvsp` @tab Atmel STK600 in high-voltage serial programming mode
* `stk600pp` @tab Atmel STK600 in parallel programming mode
* `teensy` @tab Teensy Bootloader
* `usbasp` @tab USBasp programmer, see `http://www.fischl.de/usbasp/ <http://www.fischl.de/usbasp/>`_
* `usbtiny` @tab Driver for "usbtiny"-type programmers
* `wiring` @tab `http://wiring.org.co/ <http://wiring.org.co/>`_, Basically STK500v2 protocol, with some glue to trigger the bootloader.
* `xbee` @tab XBee Series 2 Over-The-Air (XBeeBoot)
@end multitable

.. _Part_Definitions:

Part Definitions
================


::

  part
      id               = <id> ;                 # quoted string
      desc             = <description> ;        # quoted string
      family_id        = <description> ;        # quoted string
      has_jtag         = <yes/no> ;             # part has JTAG i/f
      has_debugwire    = <yes/no> ;             # part has debugWire i/f
      has_pdi          = <yes/no> ;             # part has PDI i/f
      has_updi         = <yes/no> ;             # part has UPDI i/f
      has_tpi          = <yes/no> ;             # part has TPI i/f
      devicecode       = <num> ;                # numeric
      stk500_devcode   = <num> ;                # numeric
      avr910_devcode   = <num> ;                # numeric
      signature        = <num> <num> <num> ;    # signature bytes
      usbpid           = <num> ;                # DFU USB PID
      reset            = dedicated | io;
      retry_pulse      = reset | sck;
      pgm_enable       = <instruction format> ;
      chip_erase       = <instruction format> ;
      chip_erase_delay = <num> ;                # micro-seconds
      # STK500 parameters (parallel programming IO lines)
      pagel            = <num> ;                # pin name in hex, i.e., 0xD7
      bs2              = <num> ;                # pin name in hex, i.e., 0xA0
      serial           = <yes/no> ;             # can use serial downloading
      parallel         = <yes/no/pseudo>;       # can use par. programming
      # STK500v2 parameters, to be taken from Atmel's XML files
      timeout          = <num> ;
      stabdelay        = <num> ;
      cmdexedelay      = <num> ;
      synchloops       = <num> ;
      bytedelay        = <num> ;
      pollvalue        = <num> ;
      pollindex        = <num> ;
      predelay         = <num> ;
      postdelay        = <num> ;
      pollmethod       = <num> ;
      mode             = <num> ;
      delay            = <num> ;
      blocksize        = <num> ;
      readsize         = <num> ;
      hvspcmdexedelay  = <num> ;
      # STK500v2 HV programming parameters, from XML
      pp_controlstack  = <num>, <num>, ...;     # PP only
      hvsp_controlstack = <num>, <num>, ...;    # HVSP only
      hventerstabdelay = <num>;
      progmodedelay    = <num>;                 # PP only
      latchcycles      = <num>;
      togglevtg        = <num>;
      poweroffdelay    = <num>;
      resetdelayms     = <num>;
      resetdelayus     = <num>;
      hvleavestabdelay = <num>;
      resetdelay       = <num>;
      synchcycles      = <num>;                 # HVSP only
      chiperasepulsewidth = <num>;              # PP only
      chiperasepolltimeout = <num>;
      chiperasetime    = <num>;                 # HVSP only
      programfusepulsewidth = <num>;            # PP only
      programfusepolltimeout = <num>;
      programlockpulsewidth = <num>;            # PP only
      programlockpolltimeout = <num>;
      # JTAG ICE mkII parameters, also from XML files
      allowfullpagebitstream = <yes/no> ;
      enablepageprogramming = <yes/no> ;
      idr              = <num> ;                # IO addr of IDR (OCD) reg.
      rampz            = <num> ;                # IO addr of RAMPZ reg.
      spmcr            = <num> ;                # mem addr of SPMC[S]R reg.
      eecr             = <num> ;                # mem addr of EECR reg.
                                                # (only when != 0x3c)
      is_at90s1200     = <yes/no> ;             # AT90S1200 part
      is_avr32         = <yes/no> ;             # AVR32 part

      memory <memtype>
          paged           = <yes/no> ;          # yes / no
          size            = <num> ;             # bytes
          page_size       = <num> ;             # bytes
          num_pages       = <num> ;             # numeric
          min_write_delay = <num> ;             # micro-seconds
          max_write_delay = <num> ;             # micro-seconds
          readback_p1     = <num> ;             # byte value
          readback_p2     = <num> ;             # byte value
          pwroff_after_write = <yes/no> ;       # yes / no
          read            = <instruction format> ;
          write           = <instruction format> ;
          read_lo         = <instruction format> ;
          read_hi         = <instruction format> ;
          write_lo        = <instruction format> ;
          write_hi        = <instruction format> ;
          loadpage_lo     = <instruction format> ;
          loadpage_hi     = <instruction format> ;
          writepage       = <instruction format> ;
        ;
    ;
  

.. _Parent_Part:

Parent Part
-----------

Parts can also inherit parameters from previously defined parts
using the following syntax. In this case specified integer and 
string values override parameter values from the parent part. New 
memory definitions are added to the definitions inherited from the 
parent.


::

     part parent <id>                              # quoted string
         id               = <id> ;                 # quoted string
         <any set of other parameters from the list above>
       ;
  

.. _Instruction_Format:

Instruction Format
------------------

Instruction formats are specified as a comma separated list of string
values containing information (bit specifiers) about each of the 32 bits
of the instruction.  Bit specifiers may be one of the following formats:



*1*
  The bit is always set on input as well as output


*0*
  the bit is always clear on input as well as output


*x*
  the bit is ignored on input and output


*a*
  the bit is an address bit, the bit-number matches this bit specifier's
  position within the current instruction byte


*a`N`*
  the bit is the `N`th address bit, bit-number = N, i.e., `a12`
  is address bit 12 on input, `a0` is address bit 0.


*i*
  the bit is an input data bit


*o*
  the bit is an output data bit


Each instruction must be composed of 32 bit specifiers.  The instruction
specification closely follows the instruction data provided in Atmel's
data sheets for their parts.  For example, the EEPROM read and write
instruction for an AT90S2313 AVR part could be encoded as:


::

  read  = "1  0  1  0   0  0  0  0   x x x x  x x x x",
          "x a6 a5 a4  a3 a2 a1 a0   o o o o  o o o o";

  write = "1  1  0  0   0  0  0  0   x x x x  x x x x",
          "x a6 a5 a4  a3 a2 a1 a0   i i i i  i i i i";

  

.. _Other_Notes:

Other Notes
===========


* 
  The `devicecode` parameter is the device code used by the STK500
  and is obtained from the software section (`avr061.zip`) of
  Atmel's AVR061 application note available from
  `http://www.atmel.com/dyn/resources/prod_documents/doc2525.pdf <http://www.atmel.com/dyn/resources/prod_documents/doc2525.pdf>`_.

* 
  Not all memory types will implement all instructions.

* 
  AVR Fuse bits and Lock bits are implemented as a type of memory.

* 
  Example memory types are: `flash`, `eeprom`, `fuse`,
  `lfuse` (low fuse), `hfuse` (high fuse), `efuse`
  (extended fuse), `signature`, `calibration`, `lock`.

* 
  The memory type specified on the AVRDUDE command line must match one of
  the memory types defined for the specified chip.

* 
  The `pwroff_after_write` flag causes AVRDUDE to attempt to power
  the device off and back on after an unsuccessful write to the affected
  memory area if VCC programmer pins are defined.  If VCC pins are not
  defined for the programmer, a message indicating that the device needs a
  power-cycle is printed out.  This flag was added to work around a
  problem with the at90s4433/2333's; see the at90s4433 errata at:

  `http://www.atmel.com/dyn/resources/prod_documents/doc1280.pdf <http://www.atmel.com/dyn/resources/prod_documents/doc1280.pdf>`_

* 
  The boot loader from application note AVR109 (and thus also the AVR
  Butterfly) does not support writing of fuse bits.  Writing lock bits
  is supported, but is restricted to the boot lock bits (BLBxx).  These
  are restrictions imposed by the underlying SPM instruction that is used
  to program the device from inside the boot loader.  Note that programming
  the boot lock bits can result in a 'shoot-into-your-foot' scenario as
  the only way to unprogram these bits is a chip erase, which will also
  erase the boot loader code.

  The boot loader implements the 'chip erase' function by erasing the
  flash pages of the application section.

  Reading fuse and lock bits is fully supported.

  Note that due to the inability to write the fuse bits, the safemode
  functionality does not make sense for these boot loaders.


