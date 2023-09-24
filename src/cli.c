// couldn't resist - I had to use macros just because
#define VERSION_STRING "1.0.0"

void printHelp()
{
  puts("baby-keyboard.exe");
  printf("Version: %s\n\n", VERSION_STRING);
  puts("The simplest way to disable keyboard buttons!\n");
  puts("To allow specific keys, add them as arguments when running the program.");
  puts("Each argument is a hex int. The corresponding keys can be found here (the value column):");
  puts("https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\n");
  puts("Example usage: baby-keyboard.exe space 0x21\n");
  puts("Shortcuts: space, ctrl\n");
}
