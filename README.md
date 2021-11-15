# PicoScreenTerminal
This is some utility functions/classes for having a nice way to communicate with a pico board RP2040

## How to build
First follow the "Quick-start your own project" in [pico-sdk](https://github.com/raspberrypi/pico-sdk).
(Without the need to create a CMakeLists.txt)

Then you can simply build the project like this :
```
mkdir build
cd build
cmake .. -DPICO_SDK_PATH="(YOUR PATH TO THE PICO-SDK)\pico-sdk"
```

## The demo
For demonstration purpose, a snake as been made to be played when pluging the pico RP2040.
You need a software that enable communication with the RP2040 like *Tera Term* for Windows.

You can use the following command in the *terminal* on Mac (use Tab to complete the usbmodem number) :
```
screen /dev/tty.usbmodem(something)
```
