#include <stdio.h>
// #include <stdlib.h>
#include <windows.h>

#include "hook.c"

#define VERSION_STRING "1.0.0"

void printHelp()
{
  puts("baby-keyboard.exe");
  printf("Version: %s\n\n", VERSION_STRING);
  puts("The simplest way to disable keyboard buttons and allow exceptions!\n");
  puts("By default, when running with no arguments, it will disable all the keys:\n");
  puts("  ./baby-keyboard.exe\n");
  puts("To allow specific keys, add them as arguments when running the program:\n");
  puts("  ./baby_keyboard.exe ctrl space numbers 65 0x66 c\n");
  puts("Each argument can be a hex number, an int or a string shortcut.\n");
  puts("The corresponding hex number can be found here (the value column):");
  puts("https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\n");
  puts("int arguments are converted to char (will allow A key):");
  puts("  ./baby-keyboard.exe 65\n");
  puts("String shortcuts are: a to z (each letter), 0 to 9 (each number),");
  puts("letters, numbers, arrow-keys, arrow-left, arrow-up, arrow-right, arrow-down");
  printf("space, enter, tab, ctrl, alt");
}

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    char *param = argv[1];
    if (strcmp(param, "help") == 0)
    {
      printHelp();
      return 0;
    }
    if (strcmp(param, "version") == 0)
    {
      printf("%s", VERSION_STRING);
      return 0;
    }
  }

  parseConfig(argc, argv);
  return runHook();
}
