.. _Command_Line_Options:

********************
Command Line Options
********************

.. index:: options

.. _Option_Descriptions:

Option Descriptions
===================

AVRDUDE is a command line tool, used as follows:


::

  avrdude -p partno `options` ...
  

Command line options are used to control AVRDUDE's behaviour.  The
following options are recognized:



*-p `partno`*
  This is the only mandatory option and it tells AVRDUDE what type of part
  (MCU) that is connected to the programmer.  The `partno` parameter
  is the part's id listed in the configuration file.  Specify -p ? to list
  all parts in the configuration file.  If a part is unknown
  to AVRDUDE, it means that there is no config file entry for that part,
  but it can be added to the configuration file if you have the Atmel
  datasheet so that you can enter the programming specifications.
  Currently, the following MCU types are understood:

  @multitable @columnfractions .15 .3

*`uc3a0512` @tab AT32UC3A0512*

*`c128` @tab AT90CAN128*

*`c32` @tab AT90CAN32*

*`c64` @tab AT90CAN64*

*`pwm2` @tab AT90PWM2*

*`pwm216` @tab AT90PWM216*

*`pwm2b` @tab AT90PWM2B*

*`pwm3` @tab AT90PWM3*

*`pwm316` @tab AT90PWM316*

*`pwm3b` @tab AT90PWM3B*

*`1200` @tab AT90S1200 (****)*

*`2313` @tab AT90S2313*

*`2333` @tab AT90S2333*

*`2343` @tab AT90S2343 (*)*

*`4414` @tab AT90S4414*

*`4433` @tab AT90S4433*

*`4434` @tab AT90S4434*

*`8515` @tab AT90S8515*

*`8535` @tab AT90S8535*

*`usb1286` @tab AT90USB1286*

*`usb1287` @tab AT90USB1287*

*`usb162` @tab AT90USB162*

*`usb646` @tab AT90USB646*

*`usb647` @tab AT90USB647*

*`usb82` @tab AT90USB82*

*`m103` @tab ATmega103*

*`m128` @tab ATmega128*

*`m1280` @tab ATmega1280*

*`m1281` @tab ATmega1281*

*`m1284` @tab ATmega1284*

*`m1284p` @tab ATmega1284P*

*`m1284rfr2` @tab ATmega1284RFR2*

*`m128rfa1` @tab ATmega128RFA1*

*`m128rfr2` @tab ATmega128RFR2*

*`m16` @tab ATmega16*

*`m1608` @tab ATmega1608*

*`m1609` @tab ATmega1609*

*`m161` @tab ATmega161*

*`m162` @tab ATmega162*

*`m163` @tab ATmega163*

*`m164p` @tab ATmega164P*

*`m168` @tab ATmega168*

*`m168p` @tab ATmega168P*

*`m168pb` @tab ATmega168PB*

*`m169` @tab ATmega169*

*`m16u2` @tab ATmega16U2*

*`m2560` @tab ATmega2560 (**)*

*`m2561` @tab ATmega2561 (**)*

*`m2564rfr2` @tab ATmega2564RFR2*

*`m256rfr2` @tab ATmega256RFR2*

*`m32` @tab ATmega32*

*`m3208` @tab ATmega3208*

*`m3209` @tab ATmega3209*

*`m324a` @tab ATmega324A*

*`m324p` @tab ATmega324P*

*`m324pa` @tab ATmega324PA*

*`m324pb` @tab ATmega324PB*

*`m325` @tab ATmega325*

*`m3250` @tab ATmega3250*

*`m328` @tab ATmega328*

*`m328p` @tab ATmega328P*

*`m328pb` @tab ATmega328PB*

*`m329` @tab ATmega329*

*`m3290` @tab ATmega3290*

*`m3290p` @tab ATmega3290P*

*`m329p` @tab ATmega329P*

*`m32m1` @tab ATmega32M1*

*`m32u2` @tab ATmega32U2*

*`m32u4` @tab ATmega32U4*

*`m406` @tab ATMEGA406*

*`m48` @tab ATmega48*

*`m4808` @tab ATmega4808*

*`m4809` @tab ATmega4809*

*`m48p` @tab ATmega48P*

*`m48pb` @tab ATmega48PB*

*`m64` @tab ATmega64*

*`m640` @tab ATmega640*

*`m644` @tab ATmega644*

*`m644p` @tab ATmega644P*

*`m644rfr2` @tab ATmega644RFR2*

*`m645` @tab ATmega645*

*`m6450` @tab ATmega6450*

*`m649` @tab ATmega649*

*`m6490` @tab ATmega6490*

*`m64m1` @tab ATmega64M1*

*`m64rfr2` @tab ATmega64RFR2*

*`m8` @tab ATmega8*

*`m808` @tab ATmega808*

*`m809` @tab ATmega809*

*`m8515` @tab ATmega8515*

*`m8535` @tab ATmega8535*

*`m88` @tab ATmega88*

*`m88p` @tab ATmega88P*

*`m88pb` @tab ATmega88PB*

*`m8a` @tab ATmega8A*

*`m8u2` @tab ATmega8U2*

*`t10` @tab ATtiny10*

*`t11` @tab ATtiny11 (***)*

*`t12` @tab ATtiny12*

*`t13` @tab ATtiny13*

*`t15` @tab ATtiny15*

*`t1604` @tab ATtiny1604*

*`t1606` @tab ATtiny1606*

*`t1607` @tab ATtiny1607*

*`t1614` @tab ATtiny1614*

*`t1616` @tab ATtiny1616*

*`t1617` @tab ATtiny1617*

*`t1624` @tab ATtiny1624*

*`t1626` @tab ATtiny1626*

*`t1627` @tab ATtiny1627*

*`t1634` @tab ATtiny1634*

*`t20` @tab ATtiny20*

*`t202` @tab ATtiny202*

*`t204` @tab ATtiny204*

*`t212` @tab ATtiny212*

*`t214` @tab ATtiny214*

*`t2313` @tab ATtiny2313*

*`t24` @tab ATtiny24*

*`t25` @tab ATtiny25*

*`t26` @tab ATtiny26*

*`t261` @tab ATtiny261*

*`t28` @tab ATtiny28*

*`t3216` @tab ATtiny3216*

*`t3217` @tab ATtiny3217*

*`t4` @tab ATtiny4*

*`t40` @tab ATtiny40*

*`t402` @tab ATtiny402*

*`t404` @tab ATtiny404*

*`t406` @tab ATtiny406*

*`t412` @tab ATtiny412*

*`t414` @tab ATtiny414*

*`t416` @tab ATtiny416*

*`t417` @tab ATtiny417*

*`t424` @tab ATtiny424*

*`t426` @tab ATtiny426*

*`t427` @tab ATtiny427*

*`t4313` @tab ATtiny4313*

*`t43u` @tab ATtiny43u*

*`t44` @tab ATtiny44*

*`t441` @tab ATtiny441*

*`t45` @tab ATtiny45*

*`t461` @tab ATtiny461*

*`t5` @tab ATtiny5*

*`t804` @tab ATtiny804*

*`t806` @tab ATtiny806*

*`t807` @tab ATtiny807*

*`t814` @tab ATtiny814*

*`t816` @tab ATtiny816*

*`t817` @tab ATtiny817*

*`t824` @tab ATtiny824*

*`t826` @tab ATtiny826*

*`t827` @tab ATtiny827*

*`t84` @tab ATtiny84*

*`t841` @tab ATtiny841*

*`t85` @tab ATtiny85*

*`t861` @tab ATtiny861*

*`t88` @tab ATtiny88*

*`t9` @tab ATtiny9*

*`x128a1` @tab ATxmega128A1*

*`x128a1d` @tab ATxmega128A1revD*

*`x128a1u` @tab ATxmega128A1U*

*`x128a3` @tab ATxmega128A3*

*`x128a3u` @tab ATxmega128A3U*

*`x128a4` @tab ATxmega128A4*

*`x128a4u` @tab ATxmega128A4U*

*`x128b1` @tab ATxmega128B1*

*`x128b3` @tab ATxmega128B3*

*`x128c3` @tab ATxmega128C3*

*`x128d3` @tab ATxmega128D3*

*`x128d4` @tab ATxmega128D4*

*`x16a4` @tab ATxmega16A4*

*`x16a4u` @tab ATxmega16A4U*

*`x16c4` @tab ATxmega16C4*

*`x16d4` @tab ATxmega16D4*

*`x16e5` @tab ATxmega16E5*

*`x192a1` @tab ATxmega192A1*

*`x192a3` @tab ATxmega192A3*

*`x192a3u` @tab ATxmega192A3U*

*`x192c3` @tab ATxmega192C3*

*`x192d3` @tab ATxmega192D3*

*`x256a1` @tab ATxmega256A1*

*`x256a3` @tab ATxmega256A3*

*`x256a3b` @tab ATxmega256A3B*

*`x256a3bu` @tab ATxmega256A3BU*

*`x256a3u` @tab ATxmega256A3U*

*`x256c3` @tab ATxmega256C3*

*`x256d3` @tab ATxmega256D3*

*`x32a4` @tab ATxmega32A4*

*`x32a4u` @tab ATxmega32A4U*

*`x32c4` @tab ATxmega32C4*

*`x32d4` @tab ATxmega32D4*

*`x32e5` @tab ATxmega32E5*

*`x384c3` @tab ATxmega384C3*

*`x384d3` @tab ATxmega384D3*

*`x64a1` @tab ATxmega64A1*

*`x64a1u` @tab ATxmega64A1U*

*`x64a3` @tab ATxmega64A3*

*`x64a3u` @tab ATxmega64A3U*

*`x64a4` @tab ATxmega64A4*

*`x64a4u` @tab ATxmega64A4U*

*`x64b1` @tab ATxmega64B1*

*`x64b3` @tab ATxmega64B3*

*`x64c3` @tab ATxmega64C3*

*`x64d3` @tab ATxmega64D3*

*`x64d4` @tab ATxmega64D4*

*`x8e5` @tab ATxmega8E5*

*`avr128da28` @tab AVR128DA28*

*`avr128da32` @tab AVR128DA32*

*`avr128da48` @tab AVR128DA48*

*`avr128da64` @tab AVR128DA64*

*`avr128db28` @tab AVR128DB28*

*`avr128db32` @tab AVR128DB32*

*`avr128db48` @tab AVR128DB48*

*`avr128db64` @tab AVR128DB64*

*`avr32da28` @tab AVR32DA28*

*`avr32da32` @tab AVR32DA32*

*`avr32da48` @tab AVR32DA48*

*`avr32db28` @tab AVR32DB28*

*`avr32db32` @tab AVR32DB32*

*`avr32db48` @tab AVR32DB48*

*`avr64da28` @tab AVR64DA28*

*`avr64da32` @tab AVR64DA32*

*`avr64da48` @tab AVR64DA48*

*`avr64da64` @tab AVR64DA64*

*`avr64db28` @tab AVR64DB28*

*`avr64db32` @tab AVR64DB32*

*`avr64db48` @tab AVR64DB48*

*`avr64db64` @tab AVR64DB64*

*`ucr2` @tab deprecated,*

*`lgt8fx168p` @tab LGT8FX168P*

*`lgt8fx328p` @tab LGT8FX328P*

*`lgt8fx88p` @tab LGT8FX88P*
  @end multitable

  (*)   The AT90S2323 and ATtiny22 use the same algorithm.

  (**)  Flash addressing above 128 KB is not supported by all
  programming hardware.  Known to work are jtag2, stk500v2,
  and bit-bang programmers.

  (***)
  The ATtiny11 can only be
  programmed in high-voltage serial mode.

  (****)
  The ISP programming protocol of the AT90S1200 differs in subtle ways
  from that of other AVRs.  Thus, not all programmers support this
  device.  Known to work are all direct bitbang programmers, and all
  programmers talking the STK500v2 protocol.


*-b `baudrate`*
  Override the RS-232 connection baud rate specified in the respective
  programmer's entry of the configuration file.


*-B `bitclock`*
  Specify the bit clock period for the JTAG interface or the ISP clock (JTAG ICE only).
  The value is a floating-point number in microseconds.
  Alternatively, the value might be suffixed with "Hz", "kHz", or "MHz",
  in order to specify the bit clock frequency, rather than a period.
  The default value of the JTAG ICE results in about 1 microsecond bit
  clock period, suitable for target MCUs running at 4 MHz clock and
  above.
  Unlike certain parameters in the STK500, the JTAG ICE resets all its
  parameters to default values when the programming software signs
  off from the ICE, so for MCUs running at lower clock speeds, this
  parameter must be specified on the command-line.
  It can also be set in the configuration file by using the 'default_bitclock'
  keyword.


*-c `programmer-id`*
  Specify the programmer to be used.  AVRDUDE knows about several common
  programmers.  Use this option to specify which one to use.  The
  `programmer-id` parameter is the programmer's id listed in the
  configuration file.  Specify -c ? to list all programmers in the
  configuration file.  If you have a programmer that is unknown to
  AVRDUDE, and the programmer is controlled via the PC parallel port,
  there's a good chance that it can be easily added to the configuration
  file without any code changes to AVRDUDE.  Simply copy an existing entry
  and change the pin definitions to match that of the unknown programmer.
  Currently, the following programmer ids are understood and supported:

  @multitable @columnfractions .2 .6

*`2232HIO` @tab FT2232H based generic programmer*

*`4232h` @tab FT4232H based generic programmer*

*`arduino` @tab Arduino*

*`arduino-ft232r` @tab Arduino: FT232R connected to ISP*

*`atmelice` @tab Atmel-ICE (ARM/AVR) in JTAG mode*

*`atmelice_dw` @tab Atmel-ICE (ARM/AVR) in debugWIRE mode*

*`atmelice_isp` @tab Atmel-ICE (ARM/AVR) in ISP mode*

*`atmelice_pdi` @tab Atmel-ICE (ARM/AVR) in PDI mode*

*`atmelice_updi` @tab Atmel-ICE (ARM/AVR) in UPDI mode*

*`avr109` @tab Atmel AppNote AVR109 Boot Loader*

*`avr910` @tab Atmel Low Cost Serial Programmer*

*`avr911` @tab Atmel AppNote AVR911 AVROSP*

*`avrftdi` @tab FT2232D based generic programmer*

*`avrisp` @tab Atmel AVR ISP*

*`avrisp2` @tab Atmel AVR ISP mkII*

*`avrispmkII` @tab Atmel AVR ISP mkII*

*`avrispv2` @tab Atmel AVR ISP V2*

*`buspirate` @tab The Bus Pirate*

*`buspirate_bb` @tab The Bus Pirate (bitbang interface, supports TPI)*

*`butterfly` @tab Atmel Butterfly Development Board*

*`butterfly_mk` @tab Mikrokopter.de Butterfly*

*`bwmega` @tab BitWizard ftdi_atmega builtin programmer*

*`C232HM` @tab FT232H based module from FTDI and Glyn.com.au*

*`c2n232i` @tab serial port banging, reset=dtr sck=!rts mosi=!txd miso=!cts*

*`dasa` @tab serial port banging, reset=rts sck=dtr mosi=txd miso=cts*

*`dasa3` @tab serial port banging, reset=!dtr sck=rts mosi=txd miso=cts*

*`diecimila` @tab alias for arduino-ft232r*

*`dragon_dw` @tab Atmel AVR Dragon in debugWire mode*

*`dragon_hvsp` @tab Atmel AVR Dragon in HVSP mode*

*`dragon_isp` @tab Atmel AVR Dragon in ISP mode*

*`dragon_jtag` @tab Atmel AVR Dragon in JTAG mode*

*`dragon_pdi` @tab Atmel AVR Dragon in PDI mode*

*`dragon_pp` @tab Atmel AVR Dragon in PP mode*

*`ehajo-isp` @tab avr-isp-programmer from eHaJo,@**
  `http://www.eHaJo.de <http://www.eHaJo.de>`_

*`flip1` @tab FLIP USB DFU protocol version 1 (doc7618)*

*`flip2` @tab FLIP USB DFU protocol version 2 (AVR4023)*

*`ft232r` @tab FT232R Synchronous BitBang*

*`ft245r` @tab FT245R Synchronous BitBang*

*`iseavrprog` @tab USBtiny-based USB programmer, https://github.com/IowaScaledEngineering/ckt-avrp*

*`jtag1` @tab Atmel JTAG ICE (mkI)*

*`jtag1slow` @tab Atmel JTAG ICE (mkI)*

*`jtag2` @tab Atmel JTAG ICE mkII*

*`jtag2avr32` @tab Atmel JTAG ICE mkII im AVR32 mode*

*`jtag2dw` @tab Atmel JTAG ICE mkII in debugWire mode*

*`jtag2fast` @tab Atmel JTAG ICE mkII*

*`jtag2isp` @tab Atmel JTAG ICE mkII in ISP mode*

*`jtag2pdi` @tab Atmel JTAG ICE mkII PDI mode*

*`jtag2slow` @tab Atmel JTAG ICE mkII*

*`jtag2updi` @tab JTAGv2 to UPDI bridge*

*`jtag3` @tab Atmel AVR JTAGICE3 in JTAG mode*

*`jtag3dw` @tab Atmel AVR JTAGICE3 in debugWIRE mode*

*`jtag3isp` @tab Atmel AVR JTAGICE3 in ISP mode*

*`jtag3pdi` @tab Atmel AVR JTAGICE3 in PDI mode*

*`jtag3updi` @tab Atmel AVR JTAGICE3 in UPDI mode*

*`jtagkey` @tab Amontec JTAGKey, JTAGKey-Tiny and JTAGKey2*

*`jtagmkI` @tab Atmel JTAG ICE (mkI)*

*`jtagmkII` @tab Atmel JTAG ICE mkII*

*`jtagmkII_avr32` @tab Atmel JTAG ICE mkII im AVR32 mode*

*`lm3s811` @tab Luminary Micro LM3S811 Eval Board (Rev. A)*

*`mib510` @tab Crossbow MIB510 programming board*

*`micronucleus` @tab Micronucleus Bootloader*

*`mkbutterfly` @tab Mikrokopter.de Butterfly*

*`nibobee` @tab NIBObee*

*`o-link` @tab O-Link, OpenJTAG from www.100ask.net*

*`openmoko` @tab Openmoko debug board (v3)*

*`pavr` @tab Jason Kyle's pAVR Serial Programmer*

*`pickit2` @tab MicroChip's PICkit2 Programmer*

*`pickit4_isp` @tab MPLAB(R) PICkit 4 in ISP mode*

*`pickit4_pdi` @tab MPLAB(R) PICkit 4 in PDI mode*

*`pickit4_updi` @tab MPLAB(R) PICkit 4 in UPDI mode*

*`pkobn_updi` @tab Curiosity nano (nEDBG) in UPDI mode*

*`ponyser` @tab design ponyprog serial, reset=!txd sck=rts mosi=dtr miso=cts*

*`powerdebugger` @tab Atmel PowerDebugger (ARM/AVR) in JTAG mode*

*`powerdebugger_dw` @tab Atmel PowerDebugger (ARM/AVR) in debugWire mode*

*`powerdebugger_isp` @tab Atmel PowerDebugger (ARM/AVR) in ISP mode*

*`powerdebugger_pdi` @tab Atmel PowerDebugger (ARM/AVR) in PDI mode*

*`powerdebugger_updi` @tab Atmel PowerDebugger (ARM/AVR) in UPDI mode*

*`serialupdi` @tab SerialUPDI*

*`siprog` @tab Lancos SI-Prog,@**
  `http://www.lancos.com/siprogsch.html <http://www.lancos.com/siprogsch.html>`_

*`snap_isp` @tab MPLAB(R) SNAP in ISP mode*

*`snap_pdi` @tab MPLAB(R) SNAP in PDI mode*

*`snap_updi` @tab MPLAB(R) SNAP in UPDI mode*

*`stk500` @tab Atmel STK500*

*`stk500hvsp` @tab Atmel STK500 V2 in high-voltage serial programming mode*

*`stk500pp` @tab Atmel STK500 V2 in parallel programming mode*

*`stk500v1` @tab Atmel STK500 Version 1.x firmware*

*`stk500v2` @tab Atmel STK500 Version 2.x firmware*

*`stk600` @tab Atmel STK600*

*`stk600hvsp` @tab Atmel STK600 in high-voltage serial programming mode*

*`stk600pp` @tab Atmel STK600 in parallel programming mode*

*`tc2030` @tab Tag-Connect TC2030*

*`ttl232r` @tab FTDI TTL232R-5V with ICSP adapter*

*`tumpa` @tab TIAO USB Multi-Protocol Adapter*

*`UM232H` @tab FT232H based module from FTDI and Glyn.com.au*

*`uncompatino` @tab uncompatino with all pairs of pins shorted*

*`usbasp` @tab USBasp,@**
  `http://www.fischl.de/usbasp/ <http://www.fischl.de/usbasp/>`_

*`usbasp-clone` @tab Any usbasp clone with correct VID/PID*

*`usbtiny` @tab USBtiny simple USB programmer, https://learn.adafruit.com/usbtinyisp*

*`wiring` @tab Wiring*

*`xbee` @tab XBee Series 2 Over-The-Air (XBeeBoot)*

*`xplainedmini` @tab Atmel AVR XplainedMini in ISP mode*

*`xplainedmini_dw` @tab Atmel AVR XplainedMini in debugWIRE mode*

*`xplainedmini_updi` @tab Atmel AVR XplainedMini in UPDI mode*

*`xplainedpro` @tab Atmel AVR XplainedPro in JTAG mode*

*`xplainedpro_updi` @tab Atmel AVR XplainedPro in UPDI mode*
  @end multitable


*-C `config-file`*
  Use the specified config file for configuration data.  This file
  contains all programmer and part definitions that AVRDUDE knows about.
  If not specified, AVRDUDE looks for the configuration file in the following
  two locations:



**
    `<directory from which application loaded>/../etc/avrdude.conf`


**
    `<directory from which application loaded>/avrdude.conf`


  If not found there, the lookup procedure becomes platform dependent. On FreeBSD
  and Linux, AVRDUDE looks at `/usr/local/etc/avrdude.conf`. See Appendix A
  for the method of searching on Windows.

  If `config-file` is written as `+filename`
  then this file is read after the system wide and user configuration 
  files. This can be used to add entries to the configuration
  without patching your system wide configuration file. It can be used 
  several times, the files are read in same order as given on the command 
  line.


*-D*
  Disable auto erase for flash.  When the -U option with flash memory is 
  specified, avrdude will perform a chip erase before starting any of the 
  programming operations, since it generally is a mistake to program the flash
  without performing an erase first.  This option disables that.
  Auto erase is not used for ATxmega devices as these devices can
  use page erase before writing each page so no explicit chip erase
  is required.
  Note however that any page not affected by the current operation
  will retain its previous contents.


*-e*
  Causes a chip erase to be executed.  This will reset the contents of the
  flash ROM and EEPROM to the value `0xff', and clear all lock bits.
  Except for ATxmega devices which can use page erase,
  it is basically a
  prerequisite command before the flash ROM can be reprogrammed again.
  The only exception would be if the new contents would exclusively cause
  bits to be programmed from the value `1' to `0'.  Note that in order
  to reprogram EERPOM cells, no explicit prior chip erase is required
  since the MCU provides an auto-erase cycle in that case before
  programming the cell.


*-E `exitspec`[,...]*
  By default, AVRDUDE leaves the parallel port in the same state at exit
  as it has been found at startup.  This option modifies the state of the
  `/RESET' and `Vcc' lines the parallel port is left at, according to
  the exitspec arguments provided, as follows:



*reset*
    The `/RESET' signal will be left activated at program exit, that is it
    will be held low, in order to keep the MCU in reset state afterwards.
    Note in particular that the programming algorithm for the AT90S1200
    device mandates that the `/RESET' signal is active before powering up
    the MCU, so in case an external power supply is used for this MCU type,
    a previous invocation of AVRDUDE with this option specified is one of
    the possible ways to guarantee this condition.


*noreset*
    The `/RESET' line will be deactivated at program exit, thus allowing the
    MCU target program to run while the programming hardware remains
    connected.


*vcc*
    This option will leave those parallel port pins active (i. e. high) that
    can be used to supply `Vcc' power to the MCU.


*novcc*
    This option will pull the `Vcc' pins of the parallel port down at
    program exit.


*d_high*
    This option will leave the 8 data pins on the parallel port active
    (i. e. high).


*d_low*
    This option will leave the 8 data pins on the parallel port inactive
    (i. e. low).


  Multiple `exitspec` arguments can be separated with commas.


*-F*
  Normally, AVRDUDE tries to verify that the device signature read from
  the part is reasonable before continuing.  Since it can happen from time
  to time that a device has a broken (erased or overwritten) device
  signature but is otherwise operating normally, this options is provided
  to override the check.
  Also, for programmers like the Atmel STK500 and STK600 which can
  adjust parameters local to the programming tool (independent of an
  actual connection to a target controller), this option can be used
  together with *-t* to continue in terminal mode.


*-i `delay`*
  For bitbang-type programmers, delay for approximately
  `delay`
  microseconds between each bit state change.
  If the host system is very fast, or the target runs off a slow clock
  (like a 32 kHz crystal, or the 128 kHz internal RC oscillator), this
  can become necessary to satisfy the requirement that the ISP clock
  frequency must not be higher than 1/4 of the CPU clock frequency.
  This is implemented as a spin-loop delay to allow even for very
  short delays.
  On Unix-style operating systems, the spin loop is initially calibrated
  against a system timer, so the number of microseconds might be rather
  realistic, assuming a constant system load while AVRDUDE is running.
  On Win32 operating systems, a preconfigured number of cycles per
  microsecond is assumed that might be off a bit for very fast or very
  slow machines.


*-l `logfile`*
  Use `logfile` rather than `stderr` for diagnostics output.
  Note that initial diagnostic messages (during option parsing) are still
  written to `stderr` anyway.


*-n*
  No-write - disables actually writing data to the MCU (useful for
  debugging AVRDUDE).


*-O*
  Perform a RC oscillator run-time calibration according to Atmel
  application note AVR053.
  This is only supported on the STK500v2, AVRISP mkII, and JTAG ICE mkII
  hardware.
  Note that the result will be stored in the EEPROM cell at address 0.


*-P `port`*
  Use port to identify the device to which the programmer is attached.
  Normally, the default parallel port is used, but if the programmer type
  normally connects to the serial port, the default serial port will be
  used. See Appendix A, Platform Dependent Information, to find out the
  default port names for your platform. If you need to use a different
  parallel or serial port, use this option to specify the alternate port name.

  On Win32 operating systems, the parallel ports are referred to as lpt1
  through lpt3, referring to the addresses 0x378, 0x278, and 0x3BC,
  respectively.  If the parallel port can be accessed through a different
  address, this address can be specified directly, using the common C
  language notation (i. e., hexadecimal values are prefixed by `0x`).

  For the JTAG ICE mkII, if AVRDUDE has been built with libusb support,
  `port` may alternatively be specified as
  `usb`[:`serialno`].  In that case, the JTAG ICE mkII will be
  looked up on USB.  If `serialno` is also specified, it will be
  matched against the serial number read from any JTAG ICE mkII found on
  USB.  The match is done after stripping any existing colons from the
  given serial number, and right-to-left, so only the least significant
  bytes from the serial number need to be given.
  For a trick how to find out the serial numbers of all JTAG ICEs
  attached to USB, see :ref:`Example_Command_Line_Invocations`.

  As the AVRISP mkII device can only be talked to over USB, the very
  same method of specifying the port is required there.

  For the USB programmer "AVR-Doper" running in HID mode, the port must
  be specified as `avrdoper`. Libhidapi support is required on Unix
  and Mac OS but not on Windows. For more information about AVR-Doper see
  `http://www.obdev.at/avrusb/avrdoper.html <http://www.obdev.at/avrusb/avrdoper.html>`_.

  For the USBtinyISP, which is a simplistic device not implementing
  serial numbers, multiple devices can be distinguished by their
  location in the USB hierarchy.
  See the respective
  :ref:`Troubleshooting` entry for examples.

  For the XBee programmer the target MCU is to be programmed wirelessly
  over a ZigBee mesh using the XBeeBoot bootloader.  The ZigBee 64-bit
  address for the target MCU's own XBee device must be supplied as a
  16-character hexadecimal value as a port prefix, followed by the
  @code{} character, and the serial device to connect to a second
  directly contactable XBee device associated with the same mesh (with
  a default baud rate of 9600).  This may look similar to:
  `0013a20000000001@/dev/tty.serial`.

  For diagnostic purposes, if the target MCU with an XBeeBoot
  bootloader is connected directly to the serial port, the
  64-bit address field can be omitted.  In this mode the
  default baud rate will be 19200.

  For programmers that attach to a serial port using some kind of
  higher level protocol (as opposed to bit-bang style programmers),
  `port` can be specified as `net`:`host`:`port`.
  In this case, instead of trying to open a local device, a TCP
  network connection to (TCP) `port` on `host`
  is established.
  Square brackets may be placed around `host` to improve
  readability for numeric IPv6 addresses (e.g.
  `net:[2001:db8::42]:1337`).
  The remote endpoint is assumed to be a terminal or console server
  that connects the network stream to a local serial port where the
  actual programmer has been attached to.
  The port is assumed to be properly configured, for example using a
  transparent 8-bit data connection without parity at 115200 Baud
  for a STK500.

  Note: The ability to handle IPv6 hostnames and addresses is limited to
  Posix systems (by now).


*-q*
  Disable (or quell) output of the progress bar while reading or writing
  to the device.  Specify it a second time for even quieter operation.


*-u*
  Disables the default behaviour of reading out the fuses three times before
  programming, then verifying at the end of programming that the fuses have not
  changed. If you want to change fuses you will need to specify this option,
  as avrdude will see the fuses have changed (even though you wanted to) and
  will change them back for your "safety". This option was designed to
  prevent cases of fuse bits magically changing (usually called *safemode*).

  If one of the configuration files contains a line

  `default_safemode = no;`

  safemode is disabled by default.
  The *-u* option's effect is negated in that case, i. e. it
  *enables* safemode.

  Safemode is always disabled for AVR32, Xmega and TPI devices.


*-s*
  Disable safemode prompting.  When safemode discovers that one or more
  fuse bits have unintentionally changed, it will prompt for
  confirmation regarding whether or not it should attempt to recover the
  fuse bit(s).  Specifying this flag disables the prompt and assumes
  that the fuse bit(s) should be recovered without asking for
  confirmation first.


*-t*
  Tells AVRDUDE to enter the interactive 'terminal' mode instead of up-
  or downloading files.  See below for a detailed description of the
  terminal mode.


*-U `memtype`:`op`:`filename`[:`format`]*
  Perform a memory operation.
  Multiple *-U* options can be specified in order to operate on
  multiple memories on the same command-line invocation.  The
  `memtype` field specifies the memory type to operate on. Use
  the *-v* option on the command line or the `part` command from
  terminal mode to display all the memory types supported by a particular
  device.
  Typically, a device's memory configuration at least contains
  the memory types
  `flash`
  and
  `eeprom`.
  All memory types currently known are:


*calibration*
    One or more bytes of RC oscillator calibration data.

*eeprom*
    The EEPROM of the device.

*efuse*
    The extended fuse byte.

*flash*
    The flash ROM of the device.

*fuse*
    The fuse byte in devices that have only a single fuse byte.

*hfuse*
    The high fuse byte.

*lfuse*
    The low fuse byte.

*lock*
    The lock byte.

*signature*
    The three device signature bytes (device ID).

*fuse*N**
    The fuse bytes of ATxmega devices, *N* is an integer number
    for each fuse supported by the device.

*application*
    The application flash area of ATxmega devices.

*apptable*
    The application table flash area of ATxmega devices.

*boot*
    The boot flash area of ATxmega devices.

*prodsig*
    The production signature (calibration) area of ATxmega devices.

*usersig*
    The user signature area of ATxmega devices.

  The `op` field specifies what operation to perform:



*r*
    read the specified device memory and write to the specified file


*w*
    read the specified file and write it to the specified device memory


*v*
    read the specified device memory and the specified file and perform a verify operation


  The `filename` field indicates the name of the file to read or
  write.  The `format` field is optional and contains the format of
  the file to read or write.  Possible values are:



*i*
    Intel Hex


*s*
    Motorola S-record


*r*
    raw binary; little-endian byte order, in the case of the flash ROM data


*e*
    ELF (Executable and Linkable Format), the final output file from the
    linker; currently only accepted as an input file


*m*
    immediate mode; actual byte values specified on the command line,
    separated by commas or spaces in place of the `filename` field of
    the *-U* option.  This is useful
    for programming fuse bytes without having to create a single-byte file
    or enter terminal mode.  If the number specified begins with `0x`,
    it is treated as a hex value.  If the number otherwise begins with a
    leading zero (`0`) it is treated as octal.  Otherwise, the value is
    treated as decimal.


*a*
    auto detect; valid for input only, and only if the input is not provided
    at stdin.


*d*
    decimal; this and the following formats are only valid on output.
    They generate one line of output for the respective memory section,
    forming a comma-separated list of the values.
    This can be particularly useful for subsequent processing, like for
    fuse bit settings.


*h*
    hexadecimal; each value will get the string *0x* prepended.


*o*
    octal; each value will get a *0*
    prepended unless it is less than 8 in which case it gets no prefix.


*b*
    binary; each value will get the string *0b* prepended.


  The default is to use auto detection for input files, and raw binary
  format for output files.

  Note that if `filename` contains a colon, the `format` field is
  no longer optional since the filename part following the colon would
  otherwise be misinterpreted as `format`.

  When reading any kind of flash memory area (including the various sub-areas
  in Xmega devices), the resulting output file will be truncated to not contain
  trailing 0xFF bytes which indicate unprogrammed (erased) memory.
  Thus, if the entire memory is unprogrammed, this will result in an output
  file that has no contents at all.

  As an abbreviation, the form `-U` `filename`
  is equivalent to specifying
  `-U` *flash:w:*`filename`*:a*.
  This will only work if `filename` does not have a colon in it.


*-v*
  Enable verbose output.
  More `-v` options increase verbosity level.


*-V*
  Disable automatic verify check when uploading data.


*-x `extended_param`*
  Pass `extended_param` to the chosen programmer implementation as
  an extended parameter.  The interpretation of the extended parameter
  depends on the programmer itself.  See below for a list of programmers
  accepting extended parameters.


@page

.. _Programmers_accepting_extended_parameters:

Programmers accepting extended parameters
=========================================



*JTAG ICE mkII/3*

*AVR Dragon*
  When using the JTAG ICE mkII/3 or AVR Dragon in JTAG mode, the
  following extended parameter is accepted:


*@samp{jtagchain=UB,UA,BB,BA}*
    Setup the JTAG scan chain for `UB` units before, `UA` units
    after, `BB` bits before, and `BA` bits after the target AVR,
    respectively.
    Each AVR unit within the chain shifts by 4 bits.
    Other JTAG units might require a different bit shift count.


*AVR910*
  The AVR910 programmer type accepts the following extended parameter:


*@samp{devcode=VALUE}*
    Override the device code selection by using `VALUE`
    as the device code.
    The programmer is not queried for the list of supported
    device codes, and the specified `VALUE`
    is not verified but used directly within the
    `T` command sent to the programmer.
    `VALUE` can be specified using the conventional number notation of the
    C programming language.

*@samp{no_blockmode}*
    Disables the default checking for block transfer capability.
    Use 
    @samp{no_blockmode} only if your @samp{AVR910} 
    programmer creates errors during initial sequence.


*BusPirate*
  The BusPirate programmer type accepts the following extended parameters:


*@samp{reset=cs,aux,aux2}*
    The default setup assumes the BusPirate's CS output pin connected to
    the RESET pin on AVR side. It is however possible to have multiple AVRs
    connected to the same BP with MISO, MOSI and SCK lines common for all of them.
    In such a case one AVR should have its RESET connected to BusPirate's
    *CS*
    pin, second AVR's RESET connected to BusPirate's
    *AUX*
    pin and if your BusPirate has an
    *AUX2*
    pin (only available on BusPirate version v1a with firmware 3.0 or newer)
    use that to activate RESET on the third AVR.

    It may be a good idea to decouple the BusPirate and the AVR's SPI buses from
    each other using a 3-state bus buffer. For example 74HC125 or 74HC244 are some
    good candidates with the latches driven by the appropriate reset pin (cs,
    aux or aux2). Otherwise the SPI traffic in one active circuit may interfere
    with programming the AVR in the other design.


*@samp{spifreq=`0..7`}*
    @multitable @columnfractions .05 .3

*`0` @tab  30 kHz (default)*

*`1` @tab 125 kHz*

*`2` @tab 250 kHz*

*`3` @tab   1 MHz*

*`4` @tab   2 MHz*

*`5` @tab   2.6 MHz*

*`6` @tab   4 MHz*

*`7` @tab   8 MHz*
    @end multitable


*@samp{rawfreq=0..3}*
    Sets the SPI speed and uses the Bus Pirate's binary 'raw-wire' mode instead
    of the default binary SPI mode:

    @multitable @columnfractions .05 .3

*`0` @tab 5 kHz*

*`1` @tab 50 kHz*

*`2` @tab 100 kHz (Firmware v4.2+ only)*

*`3` @tab 400 kHz (v4.2+)*
    @end multitable

    The only advantage of the 'raw-wire' mode is that different SPI frequencies
    are available. Paged writing is not implemented in this mode.


*@samp{ascii}*
    Attempt to use ASCII mode even when the firmware supports BinMode (binary
    mode).
    BinMode is supported in firmware 2.7 and newer, older FW's either don't
    have BinMode or their BinMode is buggy. ASCII mode is slower and makes
    the above
    @samp{reset=}, @samp{spifreq=}
    and
    @samp{rawfreq=}
    parameters unavailable. Be aware that ASCII mode is not guaranteed to work
    with newer firmware versions, and is retained only to maintain compatibility
    with older firmware versions.


*@samp{nopagedwrite}*
    Firmware versions 5.10 and newer support a binary mode SPI command that enables
    whole pages to be written to AVR flash memory at once, resulting in a
    significant write speed increase. If use of this mode is not desirable for some
    reason, this option disables it.


*@samp{nopagedread}*
    Newer firmware versions support in binary mode SPI command some AVR Extended 
    Commands. Using the 'Bulk Memory Read from Flash' results in a
    significant read speed increase. If use of this mode is not desirable for some
    reason, this option disables it.


*@samp{cpufreq=`125..4000`}*
    This sets the *AUX*  pin to output a frequency of `n` kHz. Connecting
    the *AUX* pin to the XTAL1 pin of your MCU, you can provide it a clock, 
    for example when it needs an external clock because of wrong fuses settings.
    Make sure the CPU frequency is at least four times the SPI frequency.  


*@samp{serial_recv_timeout=`1...`}*
    This sets the serial receive timeout to the given value. 
    The timeout happens every time avrdude waits for the BusPirate prompt. 
    Especially in ascii mode this happens very often, so setting a smaller value 
    can speed up programming a lot. 
    The default value is 100ms. Using 10ms might work in most cases.  



*Micronucleus bootloader*
  When using the Micronucleus programmer type, the
  following optional extended parameter is accepted:


*@samp{wait=`timeout`}*
    If the device is not connected, wait for the device to be plugged in.
    The optional `timeout` specifies the connection time-out in seconds.
    If no time-out is specified, AVRDUDE will wait indefinitely until the
    device is plugged in.


*Wiring*
  When using the Wiring programmer type, the
  following optional extended parameter is accepted:


*@samp{snooze=`0..32767`}*
    After performing the port open phase, AVRDUDE will wait/snooze for
    `snooze` milliseconds before continuing to the protocol sync phase.
    No toggling of DTR/RTS is performed if `snooze` > 0.


*PICkit2*
  Connection to the PICkit2 programmer:
  @multitable @columnfractions .05 .3

*`(AVR)` @tab      `(PICkit2)`*

*`RST` @tab      `VPP/MCLR (1)`*

*`VDD` @tab      `VDD Target (2) -- possibly optional if AVR self powered`*

*`GND` @tab      `GND (3)`*

*`MISO` @tab      `PGD (4)`*

*`SCLK` @tab      `PDC (5)`*

*`OSI` @tab      `AUX (6)`*
  @end multitable

  Extended command line parameters:


*@samp{clockrate=`rate`}*
    Sets the SPI clocking rate in Hz (default is 100kHz). Alternately the -B or -i options can be used to set the period.

*@samp{timeout=`usb-transaction-timeout`}*
    Sets the timeout for USB reads and writes in milliseconds (default is 1500 ms).


*USBasp*
  Extended parameters:


*@samp{section_config}*
    Programmer will erase
    configuration section with option '-e' (chip erase),
    rather than entire chip.
    Only applicable to TPI devices (ATtiny 4/5/9/10/20/40).


*xbee*
  Extended parameters:


*@samp{xbeeresetpin=`1..7`}*
    Select the XBee pin `DIO<1..7>` that is connected to the MCU's
    ‘/RESET’ line.  The programmer needs to know which DIO pin to use to
    reset into the bootloader.  The default (3) is the `DIO3` pin
    (XBee pin 17), but some commercial products use a different XBee
    pin.

    The remaining two necessary XBee-to-MCU connections are not selectable
    - the XBee `DOUT` pin (pin 2) must be connected to the MCU's
    ‘RXD’ line, and the XBee `DIN` pin (pin 3) must be connected to
    the MCU's ‘TXD’ line.


@page

.. _Example_Command_Line_Invocations:

Example Command Line Invocations
================================

Download the file `diag.hex` to the ATmega128 chip using the
STK500 programmer connected to the default serial port:


::

  @cartouche
  % avrdude -p m128 -c stk500 -e -U flash:w:diag.hex 

  avrdude: AVR device initialized and ready to accept instructions

  Reading | ################################################## | 100% 0.03s

  avrdude: Device signature = 0x1e9702
  avrdude: erasing chip
  avrdude: done.
  avrdude: performing op: 1, flash, 0, diag.hex
  avrdude: reading input file "diag.hex"
  avrdude: input file diag.hex auto detected as Intel Hex
  avrdude: writing flash (19278 bytes):

  Writing | ################################################## | 100% 7.60s

  avrdude: 19456 bytes of flash written
  avrdude: verifying flash memory against diag.hex:
  avrdude: load data flash data from input file diag.hex:
  avrdude: input file diag.hex auto detected as Intel Hex
  avrdude: input file diag.hex contains 19278 bytes
  avrdude: reading on-chip flash data:

  Reading | ################################################## | 100% 6.83s

  avrdude: verifying ...
  avrdude: 19278 bytes of flash verified

  avrdude: safemode: Fuses OK

  avrdude done.  Thank you.

  %
  @end cartouche
  

@page

Upload the flash memory from the ATmega128 connected to the STK500
programmer and save it in raw binary format in the file named
`c:/diag flash.bin`:


::

  @cartouche
  % avrdude -p m128 -c stk500 -U flash:r:"c:/diag flash.bin":r 

  avrdude: AVR device initialized and ready to accept instructions

  Reading | ################################################## | 100% 0.03s

  avrdude: Device signature = 0x1e9702
  avrdude: reading flash memory:

  Reading | ################################################## | 100% 46.10s

  avrdude: writing output file "c:/diag flash.bin"

  avrdude: safemode: Fuses OK

  avrdude done.  Thank you.

  % 
  @end cartouche
  

@page

Using the default programmer, download the file `diag.hex` to
flash, `eeprom.hex` to EEPROM, and set the Extended, High, and Low
fuse bytes to 0xff, 0x89, and 0x2e respectively:


::

  @cartouche

  % avrdude -p m128 -u -U flash:w:diag.hex \\
  >                 -U eeprom:w:eeprom.hex \\
  >                 -U efuse:w:0xff:m      \\
  >                 -U hfuse:w:0x89:m      \\
  >                 -U lfuse:w:0x2e:m

  avrdude: AVR device initialized and ready to accept instructions

  Reading | ################################################## | 100% 0.03s

  avrdude: Device signature = 0x1e9702
  avrdude: NOTE: FLASH memory has been specified, an erase cycle will be performed
           To disable this feature, specify the -D option.
  avrdude: erasing chip
  avrdude: reading input file "diag.hex"
  avrdude: input file diag.hex auto detected as Intel Hex
  avrdude: writing flash (19278 bytes):

  Writing | ################################################## | 100% 7.60s

  avrdude: 19456 bytes of flash written
  avrdude: verifying flash memory against diag.hex:
  avrdude: load data flash data from input file diag.hex:
  avrdude: input file diag.hex auto detected as Intel Hex
  avrdude: input file diag.hex contains 19278 bytes
  avrdude: reading on-chip flash data:

  Reading | ################################################## | 100% 6.84s

  avrdude: verifying ...
  avrdude: 19278 bytes of flash verified

  [ ... other memory status output skipped for brevity ... ]

  avrdude done.  Thank you.

  % 
  @end cartouche
  

@page

Connect to the JTAG ICE mkII which serial number ends up in 1C37 via
USB, and enter terminal mode:


::

  @cartouche

  % avrdude -c jtag2 -p m649 -P usb:1c:37 -t

  avrdude: AVR device initialized and ready to accept instructions

  Reading | ################################################## | 100% 0.03s

  avrdude: Device signature = 0x1e9603

  [ ... terminal mode output skipped for brevity ... ]

  avrdude done.  Thank you.

  @end cartouche
  

List the serial numbers of all JTAG ICEs attached to USB.  This is
done by specifying an invalid serial number, and increasing the
verbosity level.


::

  @cartouche

  % avrdude -c jtag2 -p m128 -P usb:xx -v
  [...]
           Using Port            : usb:xxx
           Using Programmer      : jtag2
  avrdude: usbdev_open(): Found JTAG ICE, serno: 00A000001C6B
  avrdude: usbdev_open(): Found JTAG ICE, serno: 00A000001C3A
  avrdude: usbdev_open(): Found JTAG ICE, serno: 00A000001C30
  avrdude: usbdev_open(): did not find any (matching) USB device "usb:xxx"

  @end cartouche
  

