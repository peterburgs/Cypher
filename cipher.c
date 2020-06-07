#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern unsigned char *encode();

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

  //Read Plain Text
  unsigned char pltext[255];
  reader = fopen("dummy.txt", "r");
  while (!feof(reader))
  {
    fgets(pltext, 255, reader);
    fflush(stdin);

    unsigned char *result = "";
    //Encode here:
    // if(StringLength(pltext)%2==1)
    // {
    //     pltext[StringLength(pltext)]=" ";
    //     pltext[StringLength(pltext)+1]="\n";
    // }
    result = encode(pltext, StringLength(pltext), keyPtr);
    FILE *reader1 = fopen("encodedText.txt", "ab+");

    for (int i = 0; i < StringLength(pltext); i++)
    {
      fprintf(reader1, "%02x", *(result + i));
    }
    if (pltext[0] != '\0' && !feof(reader))
    {
      fprintf(reader1, "\n");
    }
    fclose(reader1);
  }
  fclose(reader);

  return 0;
}
