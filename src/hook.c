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

      printf("Blocking %i", vkCode);
      if (wParam == WM_KEYDOWN)
      {
          printf(" down\n");
      }
      else if (wParam == WM_KEYUP)
      {
          printf(" up\n");
      }
    }
  }
  return 1;
}

// Reads arguments from argv and populates
// allowedKeys array
void parseConfig(int argc, char *argv[])
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

    // TODO: map more characters
    if (strcmp(param, "space") == 0)
    {
      allowedKeys[keyIndex] = 0x20;
      strcat(mappedString, "space");
    }
    else if (strcmp(param, "c") == 0)
    {
      allowedKeys[keyIndex] = 67;
      strcat(mappedString, "c");
    }
    else if (strcmp(param, "ctrl") == 0)
    {
      allowedKeys[keyIndex] = 0xA2;
      strcat(mappedString, "ctrl");
    }
    else if (strncmp(param, "0x", 2) == 0) // starts with 0x
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
    // TODO: better printing for %c and %s, not both in the same time
    printf("  0x%X - %d - %c - %s\n", key, key, key, mappedString);
  }
}

int runHook() {
  hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
  if (hook == NULL)
  {
    puts("Error: could not initialize keyboard hook");
    return 1;
  }

  while (GetMessage(msg, NULL, 0, 0) > 0)
  {
    // TODO: is this even needed?
    TranslateMessage(msg);
    DispatchMessage(msg);
  }

  return 0;
}