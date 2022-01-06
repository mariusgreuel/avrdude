************
Introduction
************

.. index:: introduction

AVRDUDE - AVR Downloader Uploader - is a program for downloading and
uploading the on-chip memories of Atmel's AVR microcontrollers. It can
program the Flash and EEPROM, and where supported by the serial
programming protocol, it can program fuse and lock bits. AVRDUDE also
supplies a direct instruction mode allowing one to issue any programming
instruction to the AVR chip regardless of whether AVRDUDE implements
that specific feature of a particular chip.

AVRDUDE can be used effectively via the command line to read or write
all chip memory types (eeprom, flash, fuse bits, lock bits, signature
bytes) or via an interactive (terminal) mode. Using AVRDUDE from the
command line works well for programming the entire memory of the chip
from the contents of a file, while interactive mode is useful for
exploring memory contents, modifying individual bytes of eeprom,
programming fuse/lock bits, etc.

AVRDUDE supports the following basic programmer types: Atmel's STK500,
Atmel's AVRISP and AVRISP mkII devices,
Atmel's STK600,
Atmel's JTAG ICE (the original one, mkII, and 3, the latter two also in ISP mode), appnote
avr910, appnote avr109 (including the AVR Butterfly),
serial bit-bang adapters,
and the PPI (parallel port interface). PPI represents a class
of simple programmers where the programming lines are directly
connected to the PC parallel port. Several pin configurations exist
for several variations of the PPI programmers, and AVRDUDE can be
configured to work with them by either specifying the appropriate
programmer on the command line or by creating a new entry in its
configuration file. All that's usually required for a new entry is to
tell AVRDUDE which pins to use for each programming function.

A number of equally simple bit-bang programming adapters that connect
to a serial port are supported as well, among them the popular
Ponyprog serial adapter, and the DASA and DASA3 adapters that used to
be supported by uisp(1).  Note that these adapters are meant to be
attached to a physical serial port.  Connecting to a serial port
emulated on top of USB is likely to not work at all, or to work
abysmally slow.

If you happen to have a Linux system with at least 4 hardware GPIOs 
available (like almost all embedded Linux boards) you can do without 
any additional hardware - just connect them to the MOSI, MISO, RESET 
and SCK pins on the AVR and use the linuxgpio programmer type. It bitbangs
the lines using the Linux sysfs GPIO interface. Of course, care should
be taken about voltage level compatibility. Also, although not strictly 
required, it is strongly advisable to protect the GPIO pins from 
overcurrent situations in some way. The simplest would be to just put
some resistors in series or better yet use a 3-state buffer driver like
the 74HC244. Have a look at http://kolev.info/avrdude-linuxgpio for a more
detailed tutorial about using this programmer type.

Under a Linux installation with direct access to the SPI bus and GPIO
pins, such as would be found on a Raspberry Pi, the ``linuxspi``
programmer type can be used to directly connect to and program a chip
using the built in interfaces on the computer. The requirements to use
this type are that an SPI interface is exposed along with one GPIO
pin. The GPIO serves as the reset output since the Linux SPI drivers
do not hold slave select down when a transfer is not occuring and thus
it cannot be used as the reset pin. A readily available level
translator should be used between the SPI bus/reset GPIO and the chip
to avoid potentially damaging the computer's SPI controller in the
event that the chip is running at 5V and the SPI runs at 3.3V. The
GPIO chosen for reset can be configured in the avrdude configuration
file using the `reset` entry under the linuxspi programmer, or
directly in the port specification. An external pull-up resistor
should be connected between the AVR's reset pin and Vcc. If Vcc is not
the same as the SPI voltage, this should be done on the AVR side of
the level translator to protect the hardware from damage.

On a Raspberry Pi, header J8 provides access to the SPI and GPIO
lines.

Typically, pins 19, 21, and 23 are SPI MOSI, MISO, and SCK, while
pins 24 and 26 would serve as CE outputs. So, close to these pins
is pin 22 as GPIO25 which can be used as /RESET, and pin 25 can
be used as GND.

A typical programming cable would then look like:

======== ========= ==================
 J8 pin   ISP pin   Name             
======== ========= ==================
 21       1         MISO             
 -        2         Vcc - leave open 
 23       3         SCK              
 19       4         MOSI             
 22       5         /RESET           
 25       6         GND              
======== ========= ==================

(Mind the 3.3 V voltage level of the Raspberry Pi!)

The `-P `portname`` option defaults to
``/dev/spidev0.0:/dev/gpiochip0`` for this programmer.

The STK500, JTAG ICE, avr910, and avr109/butterfly use the serial port to communicate with the PC.
The STK600, JTAG ICE mkII/3, AVRISP mkII, USBasp, avrftdi (and derivatives), and USBtinyISP
programmers communicate through the USB, using `libusb` as a
platform abstraction layer.
The avrftdi adds support for the FT2232C/D, FT2232H, and FT4232H devices. These all use 
the MPSSE mode, which has a specific pin mapping. Bit 1 (the lsb of the byte in the config
file) is SCK. Bit 2 is MOSI, and Bit 3 is MISO. Bit 4 usually reset. The 2232C/D parts
are only supported on interface A, but the H parts can be either A or B (specified by the
usbdev config parameter).
The STK500, STK600, JTAG ICE, and avr910 contain on-board logic to control the programming of the target
device.
The avr109 bootloader implements a protocol similar to avr910, but is
actually implemented in the boot area of the target's flash ROM, as
opposed to being an external device.
The fundamental difference between the two types lies in the
protocol used to control the programmer. The avr910 protocol is very
simplistic and can easily be used as the basis for a simple, home made
programmer since the firmware is available online. On the other hand,
the STK500 protocol is more robust and complicated and the firmware is
not openly available.
The JTAG ICE also uses a serial communication protocol which is similar
to the STK500 firmware version 2 one.  However, as the JTAG ICE is
intended to allow on-chip debugging as well as memory programming, the
protocol is more sophisticated.
(The JTAG ICE mkII protocol can also be run on top of USB.)
Only the memory programming functionality of the JTAG ICE is supported
by AVRDUDE.
For the JTAG ICE mkII/3, JTAG, debugWire and ISP mode are supported, provided
it has a firmware revision of at least 4.14 (decimal).
See below for the limitations of debugWire.
For ATxmega devices, the JTAG ICE mkII/3 is supported in PDI mode, provided it
has a revision 1 hardware and firmware version of at least 5.37 (decimal).

The Atmel-ICE (ARM/AVR) is supported (JTAG, PDI for Xmega, debugWIRE, ISP modes).

Atmel's XplainedPro boards, using EDBG protocol (CMSIS-DAP compliant), are
supported by the 'jtag3' programmer type.

Atmel's XplainedMini boards, using mEDBG protocol, are also
supported by the 'jtag3' programmer type.

The AVR Dragon is supported in all modes (ISP, JTAG, PDI, HVSP, PP, debugWire).
When used in JTAG and debugWire mode, the AVR Dragon behaves similar to a
JTAG ICE mkII, so all device-specific comments for that device
will apply as well.
When used in ISP and PDI mode, the AVR Dragon behaves similar to an
AVRISP mkII (or JTAG ICE mkII in ISP mode), so all device-specific
comments will apply there.
In particular, the Dragon starts out with a rather fast ISP clock
frequency, so the `-B `bitclock``
option might be required to achieve a stable ISP communication.
For ATxmega devices, the AVR Dragon is supported in PDI mode, provided it
has a firmware version of at least 6.11 (decimal).

Wiring boards (e.g. Arduino Mega 2560 Rev3) are supported, utilizing
STK500 V2.x protocol, but a simple DTR/RTS toggle to set the boards
into programming mode.  The programmer type is 'wiring'. Note that
the -D option will likely be required in this case, because the
bootloader will rewrite the program memory, but no true chip erase can
be performed.

The Arduino (which is very similar to the STK500 1.x) is supported via
its own programmer type specification 'arduino'.  This programmer works for
the Arduino Uno Rev3.

The BusPirate is a versatile tool that can also be used as an AVR programmer.
A single BusPirate can be connected to up to 3 independent AVRs. See
the section on
*extended parameters*
below for details.

The USBasp ISP and USBtinyISP adapters are also supported, provided AVRDUDE
has been compiled with libusb support.
They both feature simple firmware-only USB implementations, running on
an ATmega8 (or ATmega88), or ATtiny2313, respectively.

The Atmel DFU bootloader is supported in both, FLIP protocol version 1
(AT90USB* and ATmega*U* devices), as well as version 2 (Xmega devices).
See below for some hints about FLIP version 1 protocol behaviour.

The MPLAB(R) PICkit 4 and MPLAB(R) SNAP are supported in ISP, PDI and UPDI mode.
The Curiosity Nano board is supported in UPDI mode. It is dubbed ``PICkit on
Board'', thus the name `pkobn_updi`.

SerialUPDI programmer implementation is based on Microchip's 
*pymcuprog* (`https://github.com/microchip-pic-avr-tools/pymcuprog <https://github.com/microchip-pic-avr-tools/pymcuprog>`_) 
utility, but it also contains some performance improvements included in
Spence Kohde's *DxCore* Arduino core (`https://github.com/SpenceKonde/DxCore <https://github.com/SpenceKonde/DxCore>`_).
In a nutshell, this programmer consists of simple USB->UART adapter, diode 
and couple of resistors. It uses serial connection to provide UPDI interface. 
:ref:`SerialUPDI_programmer` for more details and known issues.

The jtag2updi programmer is supported,
and can program AVRs with a UPDI interface.
Jtag2updi is just a firmware that can be uploaded to an AVR,
which enables it to interface with avrdude using the jtagice mkii protocol
via a serial link (`https://github.com/ElTangas/jtag2updi <https://github.com/ElTangas/jtag2updi>`_).

The Micronucleus bootloader is supported for both protocol version V1
and V2. As the bootloader does not support reading from flash memory,
use the `-V` option to prevent AVRDUDE from verifing the flash memory.
See the section on *extended parameters*
below for Micronucleus specific options.

.. _History_and_Credits:

History and Credits
===================

AVRDUDE was written by Brian S. Dean under the name of AVRPROG to run on
the FreeBSD Operating System.  Brian renamed the software to be called
AVRDUDE when interest grew in a Windows port of the software so that the
name did not conflict with AVRPROG.EXE which is the name of Atmel's
Windows programming software.

The AVRDUDE source now resides in the public CVS repository on
savannah.gnu.org (`http://savannah.gnu.org/projects/avrdude/ <http://savannah.gnu.org/projects/avrdude/>`_),
where it continues to be enhanced and ported to other systems.  In
addition to FreeBSD, AVRDUDE now runs on Linux and Windows.  The
developers behind the porting effort primarily were Ted Roth, Eric
Weddington, and Joerg Wunsch.

And in the spirit of many open source projects, this manual also draws
on the work of others.  The initial revision was composed of parts of
the original Unix manual page written by Joerg Wunsch, the original web
site documentation by Brian Dean, and from the comments describing the
fields in the AVRDUDE configuration file by Brian Dean.  The texi
formatting was modeled after that of the Simulavr documentation by Ted
Roth.

