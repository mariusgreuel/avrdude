# AVRDUDE for Windows

[![Build Status](https://github.com/mariusgreuel/avrdude/actions/workflows/build_cmake.yml/badge.svg?branch=windows)](https://github.com/mariusgreuel/avrdude/actions/workflows/build_cmake.yml)

This is a fork of AVRDUDE 6.4 from <https://github.com/avrdudes/avrdude>.

The purpose of this fork is to add better support for Windows to bring it on par with the Linux version of AVRDUDE.

Noteable changes include:

- [Support Atmel AVR programmers out of the box](#support-atmel-avr-programmers-out-of-the-box)
- [Support Micronucleus bootloader](#support-micronucleus-bootloader)
- [Support Teensy HalfKay bootloader](#support-teensy-halfkay-bootloader)
- [Support COM port discovery via USB VID/PID](#support-com-port-discovery-via-usb-vidpid)
- [Support Arduino Leonardo bootloader auto-reset](#support-arduino-leonardo-bootloader-auto-reset)
- [Support WinUSB devices via custom libusb](#support-winusb-devices-via-custom-libusb)
- [Support FTDI devices via custom libftdi](#support-ftdi-devices-via-custom-libftdi)
- [Support HID devices via libhidapi](#support-hid-devices-via-libhidapi)
- [Support Visual Studio](#support-visual-studio)
- [Miscellaneous bug-fixes and patches](#miscellaneous-bug-fixes-and-patches)

The original AVRDUDE project homepage can be found here <https://savannah.nongnu.org/projects/avrdude>.

## Download

To get the latest version of **AVRDUDE for Windows**, go to the [releases folder](https://github.com/mariusgreuel/avrdude/releases):

<https://github.com/mariusgreuel/avrdude/releases>

## Feature Details

### Support Atmel AVR programmers out of the box

This build contains support for Atmel AVR programmers, such as

- [Atmel-ICE](https://www.microchip.com/DevelopmentTools/ProductDetails/ATATMEL-ICE) (Part Number: ATATMEL-ICE)
- [Atmel AVRISP mkII](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/ATAVRISP2) (Part Number: ATAVRISP2)

This build does not rely on **libusb** drivers. Instead the default Atmel drivers can be used, allowing you to use AVRDUDE and Atmel Studio 7 side-by-side, without switching drivers.

If you previously changed the driver of your programmer to libusb, you should use **Windows Device Manager** to uninstall the device, and then reinstall using the default Windows drivers.

### Support Micronucleus bootloader

This build adds support for the [Micronucleus bootloader](https://github.com/micronucleus/micronucleus), so you do no longer need a separate command-line utility when working with devices that use the Micronucleus bootloader.

The Micronucleus bootloader is typically used on small ATtiny boards, such as **Digispark** (ATtiny85), **Digispark Pro** (ATtiny167), and the respective clones.
By default, it uses the USB VID/PID **16D0:0753** (MCS Digistump).

Since this bootloader is optimized for size, it implements writing to flash memory only.
As it does not support reading, you need to use the **-V** option to prevent AVRDUDE from verifing the flash memory. To have AVRDUDE wait for the device to be connected, use the extended option '-x wait'.

#### Example: Flashing a Micronucleus bootloader device

```console
avrdude -c micronucleus -p t85 -x wait -V -U flash:w:main.hex:i
```

### Support Teensy HalfKay bootloader

This build adds support for the [Teensy HalfKay bootloader](https://www.pjrc.com/teensy/halfkay_protocol.html), so you do no longer need a the Teensy Loader tool when working with Teensy devices.

Since this bootloader is optimized for size, it implements writing to flash memory only.
As it does not support reading, you need to use the **-V** option to prevent AVRDUDE from verifing the flash memory. To have AVRDUDE wait for the device to be connected, use the extended option '-x wait'.

Supported devices are:

- Teensy 1.0 (AT90USB162)
- Teensy 2.0 (ATmega32U4)
- Teensy++ 1.0 (AT90USB646)
- Teensy++ 2.0 (AT90USB1286)

#### Example: Flashing a Teensy 2.0 device

```console
avrdude -c teensy -p m32u4 -x wait -V -U flash:w:main.hex:i
```

### Support COM port discovery via USB VID/PID

Most Arduino boards use a USB-based virtual COM port, which is connected to some sort of bootloader. Since COM port numbers (COM1, COM2, ...) are determined by Windows, you first need to use Windows device manager to figure out the COM port before you can use AVRDUDE to flash the board. Alternatively, you may use Windows device manager to assign a COM port of your choice to the USB device. Additionally, the COM port of your Arduino board may change over time, for instance if you plug the device in a different USB port.

To simplify the discovery of your Arduino board, I provided the possibility to specify the USB vendor and product ID instead of the COM port.

For instance, to connect to an Arduino Leonardo, use the following command:

```console
avrdude -c avr109 -P usb:2341:0036 -p m32u4
```

Since the USB vendor and device ID **2341:0036** is the identical for all Leonardo boards, the command above will work regardless of which COM port was actually assigned to your board.

Note that can cannot use this method if you have more than one device of the same type (i.e. that share the same USB VID/PID) plugged into your computer. Also, some devices ship various versions of firmwares using different VID/PID.

To figure out the USB VID and PID, you may use **Windows devices manager** (see the **Hardware IDs** of the **Details tab** of the USB device), or look it up in the official list of Arduino devices:
<https://github.com/arduino/ArduinoCore-avr/blob/master/boards.txt>

USB VID/PID pairs for some popular boards and the respective commands are:

- Arduino Uno Rev 3: **2A03:0043** -> `avrdude -c arduino -P usb:2A03:0043 -p m328p`
- Arduino Micro: **2341:0037** -> `avrdude -c avr109 -P usb:2341:0037 -p m32u4`
- Arduino Leonardo: **2341:0036** -> `avrdude -c avr109 -P usb:2341:0036 -p m32u4`
- Sparkfun Pro Micro (5V): **1B4F:9205** -> `avrdude -c avr109 -P usb:1B4F:9205 -p m32u4`
- Sparkfun Pro Micro (3.3V): **1B4F:9203** -> `avrdude -c avr109 -P usb:1B4F:9203 -p m32u4`
- Adafruit Circuit Playground: **239A:0011** -> `avrdude -c avr109 -P usb:239A:0011 -p m32u4`

### Support Arduino Leonardo bootloader auto-reset

Before any Arduino board may be flashed via the bootloader, you need to kick it into bootloader mode first. This can done manually by pressing the reset button, or automatically via an special auto-reset mechanism: For boards with a USB to serial converter chip (such as Arduino Uno or Nano), the tool needs to pull the DTR signal to low, which will briefly pull the RESET pin of the microcontroller to low. For boards with a direct USB connection (such as Arduino Leonardo or Micro), the sketch typically implements a serial port via a USB composite device with a virtual COM port. To perform the auto-reset, the sketch implements a hack that resets the device into bootloader mode when the COM port is opened with a baudrate of 1200bps. To make matters even more complicated, the bootloader COM port has a different USB VID:PID pair than the sketch COM port, which causes the COM port to change while performing the reset.

To simplify the process of auto-resetting the board, this version will auto-reset the device when AVRDUDE detects that the device is running in sketch mode. Note that the sketch is required to implement a USB composite device with a virtual COM port with a matching USB VID:PID, which is implemented in the Arduino core software.

### Support WinUSB devices via custom libusb

Since AVRDUDE originated from Unix, the USB support in AVRDUDE is built upon the Unix-based USB library [libusb](https://sourceforge.net/projects/libusb/). In order to support Windows, libusb has been ported to Windows [libusb-win32](https://sourceforge.net/projects/libusb-win32/).

The downside of using libusb-win32 is that it requires the user to manually install a kernel-mode driver (libusb0.sys or libusbk.sys)  instead of the manufacturer supplied Windows driver. There are several hacks to accomplish this, such as the [Zadig driver installation utility](https://zadig.akeo.ie/), which installs a self-signed root certificate in the Windows driver store due to the lack of proper driver installation packages.

This build contains a custom library called **libwinusb**, which implements a sub-set of the libusb-win32 API. The libwinusb implementation supports both the **winusb.sys** driver, and the **libusb0.sys** driver as well. This patch has a number of advantages, such as

- Many USB devices that ship with WinUSB drivers, such as Atmel programmer, will run out of the box.
- Works with both WinUSB and libusb: You can use either Windows built-in WinUSB driver to access your USB devices, or keep using the libusb drivers if you have them installed already.
- No static dependency to libusb0.dll: You cannot run the original version AVRDUDE, unless you previously installed libusb. On systems where libusb is not installed, this build eliminates the error "The code execution cannot proceed because libusb0.dll was not found. Reinstalling the program may fix this problem".

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

The build instructions have been moved here:\
<https://github.com/avrdudes/avrdude/wiki>

### Building AVRDUDE for Windows using MSVC

#### Windows Prerequisites

In order to build AVRDUDE on Windows, you need:

- Flex and Bison installed, for instance via [Chocolatey](https://chocolatey.org/)
- Microsoft Visual Studio 2019 with **Desktop development with C++** and **CMake** enabled

#### Windows Build Instructions

To build AVRDUDE on Windows, do the following:

- `git clone --branch windows https://github.com/mariusgreuel/avrdude`
- Open the folder **avrdude** using the menu item **File->Open->Folder**
- Build the project using the menu item **Build->Build All**

### Linux udev rules

If you intent to use either the Micronucleus or Teensy bootloader, you should edit the udev rules so that you can run AVRDUDE without root.

For instance, if you are on Ubuntu and you installed the avrdude package, you would edit `/lib/udev/rules.d/60-avrdude.rules` and add the following rules:

```console
# Micronucleus Bootloader
SUBSYSTEM=="usb", ATTR{idVendor}=="16d0", ATTR{idProduct}=="0753", TAG+="uaccess"
# Teensy Bootloader
SUBSYSTEM=="usb", ATTR{idVendor}=="16c0", ATTR{idProduct}=="0478", TAG+="uaccess"
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

