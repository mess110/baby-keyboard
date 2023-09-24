#include <stdio.h>
// #include <stdlib.h>
#include <windows.h>

#include "hook.c"

#define VERSION_STRING "1.0.0"

void printHelp()
{
  puts("baby-keyboard.exe");
  printf("Version: %s\n\n", VERSION_STRING);
  puts("The simplest way to disable keyboard buttons!\n");
  puts("By default, when running with no arguments, it will disable all the keys.");
  puts("To allow specific keys, add them as arguments when running the program.");
  puts("Each argument is a hex int, an int or a string shortcut.\n");
  puts("The corresponding hex codes can be found here (the value column):");
  puts("https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\n");
  puts("Example usage: baby-keyboard.exe space 0x21 67\n");
  printf("Sample shortcuts: space, ctrl");
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
  }

  parseConfig(argc, argv);
  return runHook();
}
