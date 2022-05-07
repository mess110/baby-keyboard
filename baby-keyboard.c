#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// couldn't resist - I had to use macros just because
#define VERSION_STRING "1.0.0"
#define listen(msg)                       \
  while (GetMessage(msg, NULL, 0, 0) > 0) \
  {                                       \
  }
#define convertHexStringToInt(hexString) (int)strtol(hexString, NULL, 16);

HHOOK hook;
LPMSG msg;
int *allowedKeys;
int numberOfArguments;

// The keyboard hook. If we want the key to work, we call CallNextHookEx,
// otherwise we return 1
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
  if (code == HC_ACTION)
  {
    if (wParam == WM_KEYDOWN || wParam == WM_KEYUP)
    {
      int vkCode = ((KBDLLHOOKSTRUCT *)lParam)->vkCode;
      for (int i = 0; i < numberOfArguments; i++)
      {
        if (allowedKeys[i] == vkCode)
        {
          return CallNextHookEx(hook, code, wParam, lParam);
        }
      }
    }
  }
  return 1;
}

void parseArgs(int argc, char *argv[])
{
  if (argc == 1)
  {
    puts("Blocking all keys");
  }
  else
  {
    numberOfArguments = argc - 1;
    allowedKeys = malloc(numberOfArguments);

    puts("Blocking all keys except:");
    for (int i = 1; i < argc; i++)
    {
      allowedKeys[i - 1] = convertHexStringToInt(argv[i]);
      printf("  0x%X - %d\n", allowedKeys[i - 1], allowedKeys[i - 1]);
    }
  }
}

int main(int argc, char *argv[])
{
  // hook the hook
  hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
  if (hook != NULL)
  {
    puts("baby-keyboard.exe");
    printf("Version: %s\n\n", VERSION_STRING);
    puts("The simplest way to disable keyboard buttons!\n");
    puts("To allow specific keys, add them as arguments when running the program.");
    puts("Each argument is a hex int. The corresponding keys can be found here:");
    puts("https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\n");
  }
  else
  {
    puts("Error: could not initialize keyboard hook");
    return 1;
  }

  parseArgs(argc, argv);
  listen(msg);

  puts("Done");
  return 0;
}