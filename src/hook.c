HHOOK hook;
LPMSG msg;
int *allowedKeys = NULL;
int numberOfArguments = 0;

#define ifParamIs(name, value) \
    if (strcmp(param, name) == 0) \
    { \
      allowedKeys[keyIndex] = value; \
      strcat(mappedString, name); \
    }

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

      printf("Blocking %i %c", vkCode, vkCode);
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
  allowedKeys = (int *)malloc(numberOfArguments * sizeof(int));
  if (allowedKeys == NULL)
  {
    perror("Memory allocation failed");
    // TODO: exit the program
  }
  // printf("%i\n", numberOfArguments);

  puts("Blocking all keys except:");
  int extras = 0;
  for (int i = 1; i < argc; i++)
  {
    int keyIndex = i - 1 + extras;
    char *param = argv[i];
    char mappedString[64] = "";

    // TODO: map more characters
    ifParamIs("space", 0x20)
    else ifParamIs("enter", 13)
    else ifParamIs("tab", 9)
    else ifParamIs("ctrl", 162) // TODO: add all ctrl buttons
    else ifParamIs("alt", 164) // TODO: add all alt buttons
    else ifParamIs("0", 48)
    else ifParamIs("1", 49)
    else ifParamIs("2", 50)
    else ifParamIs("3", 51)
    else ifParamIs("4", 52)
    else ifParamIs("5", 53)
    else ifParamIs("6", 54)
    else ifParamIs("7", 55)
    else ifParamIs("8", 56)
    else ifParamIs("9", 57)
    else if (strcmp(param, "numbers") == 0)
    {
      allowedKeys[keyIndex] = 48; // add 0

      for (int j = 49; j <= 57; j++) {
        numberOfArguments++;
        allowedKeys = (int *)realloc(allowedKeys, numberOfArguments * sizeof(int));
        allowedKeys[keyIndex + j - 48] = j;
        extras++;
      }
    }
    else ifParamIs("a", 65)
    else ifParamIs("b", 66)
    else ifParamIs("c", 67)
    else ifParamIs("d", 68)
    else ifParamIs("e", 69)
    else ifParamIs("f", 70)
    else ifParamIs("g", 71)
    else ifParamIs("h", 72)
    else ifParamIs("i", 73)
    else ifParamIs("j", 74)
    else ifParamIs("k", 75)
    else ifParamIs("l", 76)
    else ifParamIs("m", 77)
    else ifParamIs("n", 78)
    else ifParamIs("o", 79)
    else ifParamIs("p", 80)
    else ifParamIs("q", 81)
    else ifParamIs("r", 82)
    else ifParamIs("s", 83)
    else ifParamIs("t", 84)
    else ifParamIs("u", 85)
    else ifParamIs("v", 86)
    else ifParamIs("w", 87)
    else ifParamIs("x", 88)
    else ifParamIs("y", 89)
    else ifParamIs("z", 90)
    else if (strcmp(param, "letters") == 0)
    {
      allowedKeys[keyIndex] = 65; // add A

      for (int j = 66; j <= 90; j++) {
        numberOfArguments++;
        allowedKeys = (int *)realloc(allowedKeys, numberOfArguments * sizeof(int));
        allowedKeys[keyIndex + j - 65] = j;
        extras++;
      }
    }
    else ifParamIs("arrow-left", 37)
    else ifParamIs("arrow-up", 38)
    else ifParamIs("arrow-right", 39)
    else ifParamIs("arrow-down", 40)
    else if (strcmp(param, "arrow-keys") == 0)
    {
      numberOfArguments += 3; // one added by default
      allowedKeys = (int *)realloc(allowedKeys, numberOfArguments * sizeof(int));

      allowedKeys[keyIndex] = 37; // left arrow
      allowedKeys[keyIndex + 1] = 38; // up arrow
      allowedKeys[keyIndex + 2] = 39; // right arrow
      allowedKeys[keyIndex + 3] = 40; // down arrow

      extras += 3;
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

    if (allowedKeys[keyIndex] == 0)
    {
      printf("  %s: uknown key\n", param);
    }
    else
    {
      int key = allowedKeys[keyIndex];
      // TODO: better printing for %c and %s, not both in the same time
      printf("  %s: 0x%X - %d - %c - %s\n", param, key, key, key, mappedString);
    }
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