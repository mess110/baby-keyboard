# baby-keyboard

The simplest way to disable keyboard buttons!

Disable all or allow some keyboard buttons to work so the baby can smash away!

## Features

* super simple
* blocks keys without disabling the keyboard
* allows specified keys
* self-contained
* open-source

## Example usage

To disable all the keys, run `baby-keyboard.exe`

To disable all keys except `spacebar` and `g` run `baby-keyboard.exe 0x20 0x47`.
See [Makefile](Makefile) for more examples.

To allow specific keys, add them as arguments when running the program.
Each argument is a hex int. The corresponding keys can be found
[here](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes).

When you want to re-enable the keyboard buttons, just close the window.

Use Windows shortcuts to save preconfigured allowed keys options for easy access.

## Build

You need a c compiler installed.

```
make build
```

Tested on Windows 10.

## Useful arguments

| Arguments               | Description  |
| ----------------------- | ------------ |
| 0x25 0x26 0x27 0x28     | Arrow keys   |
| 0x57 0x41 0x53 0x44     | WASD         |
| 0x1B                    | Escape       |
| 0x0D                    | Enter        |
| 0x11                    | Control      |
| 0x12                    | Alt          |
| 0x10                    | Shift        |
| 0x20                    | Space        |
