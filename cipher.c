#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
  //Timer
  clock_t begin = clock();

  int STR_LEN;
  //Read Keys from file
  FILE *reader;
  reader = fopen("key.txt", "r");
  char keys[9];
  while (!feof(reader))
  {
    fgets(keys, 9, reader);
  }
  fclose(reader);

  //Pointer of Keys
  char *keyPtr = &keys;

  //Read Plain Text
  unsigned char pltext[500];

  reader = fopen("dummy.txt", "r");
  remove("encodedText.txt");

  while (!feof(reader))
  {
    fgets(pltext, 500, reader);
    fflush(stdin);
    STR_LEN = StringLength(pltext);
    unsigned char *result = "";
    //Padding last line
    if (feof(reader))
    {
      pltext[StringLength(pltext)] = ' ';
      STR_LEN++;
    }

    result = encode(pltext, STR_LEN, keyPtr);

    FILE *reader1 = fopen("encodedText.txt", "ab+");

    for (int i = 0; i < STR_LEN; i++)
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

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Ciphering Time: %f\n", time_spent);
  return 0;
}
