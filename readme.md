# AVRDUDE for Windows

[![Build Status](https://travis-ci.com/mariusgreuel/avrdude.svg?branch=windows)](https://travis-ci.com/mariusgreuel/avrdude)

This is a fork of AVRDUDE 6.3 from <https://www.nongnu.org/avrdude/>.

The purpose of this fork is to add better support for Windows to bring it on par with the Linux version of AVRDUDE.

Noteable changes include:

- Support Atmel AVR programmers out of the box
- Support Micronucleus bootloader
- Support Teensy HalfKay bootloader
- Support COM port discovery via USB VID/PID
- Support Arduino Leonardo bootloader auto-reset
- Support WinUSB devices via custom libusb
- Support FTDI devices via custom libftdi
- Support HID devices via libhidapi
- Support Visual Studio
- Miscellaneous bug-fixes and patches

## Download

To get the latest version of **AVRDUDE for Windows**, go to the [releases folder](https://github.com/mariusgreuel/avrdude/releases):

<https://github.com/mariusgreuel/avrdude/releases>

## Feature Details

### Support Atmel AVR programmers out of the box

This build contains support for Atmel AVR programmers, such as

- [Atmel-ICE](https://www.microchip.com/DevelopmentTools/ProductDetails/ATATMEL-ICE) (Part Number: ATATMEL-ICE)
- [Atmel AVRISP mkII](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/ATAVRISP2) (Part Number: ATAVRISP2)

This build does not rely on **libusb** drivers. Instead the default Atmel drivers are used, allowing you to use AVRDUDE and Atmel Studio 7 side-by-side, without switch drivers.

If you previously changed the driver of your programmer to libusb, you should use **Windows Device Manager** to uninstall the device, and then reinstall using the default Windows drivers.

### Support Micronucleus bootloader

This build adds support for the [Micronucleus bootloader](https://github.com/micronucleus/micronucleus), so you do no longer need a separate command-line utility when working with devices that use the Micronucleus bootloader.

The Micronucleus bootloader is typically used on small ATtiny boards, such as **Digispark** (ATtiny85), **Digispark Pro** (ATtiny167), and the respective clones.
By default, it uses the USB VID/PID **16D0:0753** (MCS Digistump).

Since this bootloader is optimized for size, it implements writing to flash memory only.
As it does not support reading, use the -V option to prevent AVRDUDE from verifing the flash memory. To have AVRDUDE wait for the device to be connected, use the extended option '-x wait'.

#### Example: Flashing a Micronucleus bootloader device

```bash
avrdude -c micronucleus -p t85 -x wait -V -U flash:w:main.hex:i
```

### Support Teensy HalfKay bootloader

This build adds support for the [Teensy HalfKay bootloader](https://www.pjrc.com/teensy/halfkay_protocol.html), so you do no longer need a the Teensy Loader tool when working with Teensy devices.

Since this bootloader is optimized for size, it implements writing to flash memory only.
As it does not support reading, use the -V option to prevent AVRDUDE from verifing the flash memory. To have AVRDUDE wait for the device to be connected, use the extended option '-x wait'.

Supported devices are:

- Teensy 1.0 (AT90USB162)
- Teensy 2.0 (ATmega32U4)
- Teensy++ 1.0 (AT90USB646)
- Teensy++ 2.0 (AT90USB1286)

#### Example: Flashing a Teensy 2.0 device

```bash
avrdude -c teensy -p m32u4 -x wait -V -U flash:w:main.hex:i
```

### Support COM port discovery via USB VID/PID

Most Arduino boards include a USB based virtual COM port, which is connected to some sort of bootloader. Since COM port numbers (COM1, COM2, ...) are determined by Windows, you first need to use Windows device manager to figure out the COM port before you can use AVRDUDE to flash the board. Alternatively, you may use Windows device manager to assign a COM port of your choice to the USB device.

However, the COM port of your Arduino board may change over time, for instance if you plug the device in a different USB port. Instead of specifing a COM port, I provided the possibility to specify the USB vendor and product ID.

Note that can cannot use this method if you have more than one device of the same type (i.e. that share the same USB VID/PID) plugged into your computer. Also, some devices ship various versions of firmwares using different VID/PID.

To figure out the USB VID and PID, you may use **Windows devices manager** (see the **Hardware IDs** of the **Details tab** of the USB device), or look it up in the official list of Arduino devices:
<https://github.com/arduino/ArduinoCore-avr/blob/master/boards.txt>

USB VID/PID pairs for popular boards are:

- Arduino Micro: **2341:0037**
- Arduino Leonardo: **2341:0036**
- Sparkfun Pro Micro (5V): **1B4F:9205**
- Sparkfun Pro Micro (3.3V): **1B4F:9203**
- Adafruit Circuit Playground: **239A:0011**

#### Example: Using the '-P' option with a USB PID:VID pair

For instance, to flash an Arduino Leonardo, you may use the following command:

```bash
avrdude -c avr109 -P usb:2341:0036 -p m32u4 -U flash:w:main.hex:i
```

### Support Arduino Leonardo bootloader auto-reset

Before any Arduino board may be flashed via the bootloader, you need to kick it into bootloader mode first. This can done manually by pressing the reset button, or automatically via an special auto-reset mechanism: For boards with a USB to serial converter chip (such as Arduino Uno or Nano), you need to pull the DTR signal to low, which will briefly pull the RESET pin of the microcontroller to low. For boards with a direct USB connection (such as Arduino Leonardo or Micro), the sketch typically implements a serial port via a USB composite device with a virtual COM port. In the latter case, the sketch implements a hack that resets the device into bootloader mode when the COM port is opened with a baudrate of 1200bps. To make matters even more complicated, the bootloader COM port has a different USB VID:PID pair than the sketch COM port, which causes the COM port to change, too.

To simplify the process of auto-resetting the board, this version will auto-reset the device when AVRDUDE detects that the device is running in sketch mode. Note that the sketch is required to implement a USB composite device with a virtual COM port with a matching USB VID:PID, which is implemented in the Arduino core software.

### Support WinUSB devices via custom libusb

Since AVRDUDE originated from Unix, the USB support in AVRDUDE is built upon the Unix-based USB library [libusb](https://sourceforge.net/projects/libusb/). In order to support Windows, libusb has been ported to Windows [libusb-win32](https://sourceforge.net/projects/libusb-win32/).

The downside of using libusb-win32 is that it requires the user to manually install a kernel-mode driver (libusb0.sys or libusbk.sys)  instead of the manufacturer supplied Windows driver. There are several hacks to accomplish this, such as the [Zadig driver installation utility](https://zadig.akeo.ie/), which installs a self-signed root certificate in the Windows driver store due to the lack of proper driver installation packages.

This build contains a custom library called **libwinusb**, which implements a sub-set of the libusb-win32 API. The libwinusb implementation supports both the **winusb.sys** driver, and the **libusb0.sys** driver as well. This patch has a number of advantages, such as

- Many USB devices that ship with WinUSB drivers, such as Atmel programmer, will run out of the box.
- Works with both WinUSB and libusb: You can use either Windows built-in WinUSB driver to access your USB devices, or keep using the libusb drivers if you have them installed already.
- No static dependency to libusb0.dll: You cannot run AVRDUDE, unless you previously installed libusb. This eliminates the error "The code execution cannot proceed because libusb0.dll was not found. Reinstalling the program may fix this problem".

#### Microsoft OS descriptors and firmware examples

Windows provides a mechanism to automatically load the built-in WinUSB driver without providing a driver installation package (INF file). The automatic WinUSB driver installation is triggered via a special [Microsoft OS descriptor](https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors) that must be present in the firmware of the USB device.

To demonstrate how this works, I added Microsoft OS descriptors to the following projects:

- **USBasp** - USB programmer for Atmel AVR controllers: <https://github.com/mariusgreuel/USBasp>

- **FabISP** a.k.a **USBtinyISP** - A fab-able in-system programmer: <https://github.com/mariusgreuel/FabISP>

- **Micronucleus** - ATtiny USB bootloader with a strong emphasis on bootloader compactness: <https://github.com/mariusgreuel/micronucleus>

### Support FTDI devices via custom libftdi

In order to support FTDI devices, AVRDUDE uses the Unix-based library [libftdi1](https://www.intra2net.com/en/developer/libftdi/). Similar to libusb, the libftdi1 library does not play nice on Windows: On Windows, FTDI devices load the manufacturer supplied driver via plug-and-play. The FTDI drivers implement an API via the FTDI D2XX DLLs. However, libftdi1 cannot use the D2XX interface, so it will not work with the plug-and-play drivers.

This build contains a patches library of **libftdi**. The patches load the D2XX DLLs to support FTDI devices, so FTDI devices will just work.

### Support HID devices via libhidapi

This build include the WIN32 version of libhidapi, and some patches, to allow HID devices to work out of the box.

### Support Visual Studio

This build adds support for **Microsoft Visual Studio**. Building AVRDUDE with Microsoft Visual C/C++ will give you the best user and debugging experience while working on Windows.

### Miscellaneous bug-fixes and patches

- This build fixes [bug #54159: Buffer overflow in usbtiny.c](http://savannah.nongnu.org/bugs/?54159), which causes AVRDUDE to crash when using the USBtiny programmer.

- Support new microcontroller: ATtiny167

## Releases

You can find the latest releases of **AVRDUDE for Windows** here:

<https://github.com/mariusgreuel/avrdude/releases>

## Users manual

You can find the original users manual (does not contain AVRDUDE for Windows extras) of AVRDUDE here:

<https://www.nongnu.org/avrdude/user-manual/avrdude.html>

## Build

### Building AVRDUDE for Windows

#### Windows Prerequisites

In order to build AVRDUDE on Windows, you need:

- Microsoft Visual Studio 2019 with 'Desktop development with C++' enabled

#### Windows Build Instructions

To build AVRDUDE on Windows, do the following:

- `git clone --branch windows https://github.com/mariusgreuel/avrdude`
- Open the solution `avrdude.sln` and build the project.

Note: The folder `msvc\generated` includes pre-built files from the AVRDUDE configure and grammar generation.

### Building AVRDUDE for Linux

Note that the AVRDUDE for Linux version does not contain all extra Windows features. The features that have been added to the stock version of AVRDUDE include:

- Support Micronucleus bootloader
- Support Teensy HalfKay bootloader

#### Linux Prerequisites

In order to build AVRDUDE on Linux, you need to install the following packages:

```bash
sudo apt install git make gcc automake libtool flex bison libelf-dev libusb-dev libftdi1-dev libhidapi-dev
```

#### Linux Build Instructions

To build AVRDUDE on Linux, run the following commands:

```bash
git clone --branch linux https://github.com/mariusgreuel/avrdude
cd avrdude
./bootstrap
./configure
make
```

To install a local build of AVRDUDE on your system, run the following command:

```bash
sudo make install
```

## Troubleshooting Tips & Tricks

### Atmel DFU Device driver broken

The current version of the Atmel DFU drivers that are distributed via the Windows Update are goofed up (@Atmel: It might have something to do with the fact that you commented out the CopyFiles sections!).
Symptoms are:

- You cannot use AVRDUDE to connect to an Atmel DFU device, and you get the error message "No matching USB device found".
- When installing the drivers via Windows Update, you get the error message "Windows encountered a problem installing the drivers for your device" and "A service installation section in this INF is invalid."
- In Windows Device Manager, the Atmel DFU device shows up as an unknown device.

You should use an older driver package that does not contain this bug.

### Outdated libusb0 driver

The most current version of libusb0.sys is 1.2.6.0, signed on 12/17/2012 by Travis Lee Robinson. If you are using an older version (check with Windows Device Manager), you may not be able to connect to your USB devices using the libusb0 driver.

## License

AVRDUDE is licensed under the GNU GPLv2.
