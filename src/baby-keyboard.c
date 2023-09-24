#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "cli.c"
// #include "hook.c"

#define listen(msg)                       \
  while (GetMessage(msg, NULL, 0, 0) > 0) \
  {                                       \
  }

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
      printf("Blocking %i\n", vkCode);
    }
  }
  return 1;
}

// Reads arguments from argv and populates
// allowedKeys array
void parseArgs(int argc, char *argv[])
{
  if (argc == 1)
  {
    puts("Blocking all keys");
    return;
  }

  numberOfArguments = argc - 1;
  allowedKeys = malloc(numberOfArguments);

  puts("Blocking all keys except:");
  for (int i = 1; i < argc; i++)
  {

    int keyIndex = i - 1;

    char *param = argv[i];
    char mappedString[64] = "";


    if (strcmp(param, "space") == 0)
    {
      allowedKeys[keyIndex] = 0x20;
      strcat(mappedString, "space");
    }
    else if (strcmp(param, "ctrl") == 0)
    {
      allowedKeys[keyIndex] = 0x11;
      strcat(mappedString, "ctrl");
    }
    else if (strcmp(param, "0x") == 0)
    {
      // support for hex params like 0x12
      // converts from hexadecimal char[] to int
      allowedKeys[keyIndex] = (int)strtol(argv[i], NULL, 16);
    }
    else
    {
      // support for int
      // converts char[] to int
      allowedKeys[keyIndex] = atoi(argv[i]);
    }

    int key = allowedKeys[keyIndex];
    printf("  0x%X - %d - %c - %s\n", key, key, key, mappedString);
  }
}

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    char *param2 = argv[1];
    if (strcmp(param2, "help") == 0)
    {
      printHelp();
      return 0;
    }
  }

  // hook the hook
  hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
  if (hook == NULL)
  {
    puts("Error: could not initialize keyboard hook");
    return 1;
  }

  parseArgs(argc, argv);
  listen(msg);

  puts("Done");
  return 0;
}