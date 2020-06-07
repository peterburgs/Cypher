#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern unsigned char *decode();

int StringLength(char *s)
{
  int i = 0;

  while (s[i] != '\0')
  {
    i++;
  }
  return i;
}
int main()
{
  //Read Keys from file
  FILE *reader;
  reader = fopen("key.txt", "r");
  char keys[30];
  while (!feof(reader))
  {
    fgets(keys, 30, reader);
  }
  fclose(reader);
  //Pointer of Keys
  char *keyPtr = &keys;

  //Read Encoded Text
  unsigned char ectext[255];
  reader = fopen("encodedText.txt", "r");
  while (!feof(reader))
  {
    fgets(ectext, 255, reader);

    //Decode here:
    //Store
    int length = sizeof(ectext) / sizeof(ectext[0]);
    fflush(stdin);

    short int num[255];
    int *numptr = &num;
    int j = 0;
    int i;

    for (i = 0; i < StringLength(ectext); i += 4)
    {
      char shortArr[5];
      shortArr[0] = ectext[i];
      shortArr[1] = ectext[i + 1];
      shortArr[2] = ectext[i + 2];
      shortArr[3] = ectext[i + 3];
      sscanf(shortArr, "%x", &num[j]);
      fflush(stdin);
      j++;
    }
    unsigned char *result = decode(numptr, i / 2, keyPtr);
    printf("%s", result);
    if (result[StringLength(result) - 1] != '\n' && !feof(reader))
    {
      printf("\n");
    }
  }
  fclose(reader);

  return 0;
}
