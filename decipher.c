#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
  //Timer

  clock_t begin = clock();

  //Read Keys from file
  FILE *reader;
  reader = fopen("key.txt", "r");
  char keys[30];
  while (!feof(reader))
  {
    fgets(keys, 30, reader);
    fflush(stdin);
  }
  fclose(reader);
  //Pointer of Keys
  char *keyPtr = &keys[0];

  //Read Encoded Text
  unsigned char ectext[500];
  reader = fopen("encodedText.txt", "r");

  while (!feof(reader))
  {
    fgets(ectext, 500, reader);
    fflush(stdin);
    //Decode here:
    //Store
    short int num[500];
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
    //free(numptr);
  }
  fclose(reader);
  printf("\n");
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Deciphering Time: %f\n", time_spent);
  return 0;
}
