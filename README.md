# baby-keyboard.exe

The simplest way to disable keyboard buttons and allow exceptions!

* blocks keys without disabling the keyboard
* allow specified keys
* super simple to use
* self-contained
* open-source

## Usage

By default, when running with no arguments, it will disable all the keys:

```
./baby-keyboard.exe
```

To allow specific keys, add them as arguments when running the program:

```
./baby_keyboard.exe ctrl space numbers 65 0x66 c
```

To read more about usage:

```
./baby-keyboard.exe help
```

## Build

You need a c compiler and make installed.

```
make build
./baby-keyboard.exe ctrl c
```

Tested on Windows 11, initially built on Windows 10.