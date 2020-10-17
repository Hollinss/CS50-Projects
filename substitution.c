#include <stdio.h>

#include <cs50.h>

#include <string.h>

#include <ctype.h>

void sub(string n, string arr);
bool dup(string arr);

int main(int argc, string argv[]) {
  if (argc != 2) {

    printf("Usage: ./substitution key\n");
    return 1;

  }

  if (strlen(argv[1]) != 26) {

    printf("Key must contain 26 characters.\n");
    return 1;

  }
  int checklen = 0;
  for (int i = 0; i < strlen(argv[1]); i++) {

    if ((argv[1][i] >= 32 && argv[1][i] <= 64) || (argv[1][i] >= 91 && argv[1][i] <= 96) || (argv[1][i] >= 123 && argv[1][i] <= 127)) {
      checklen++;
    }

  }
  if (checklen > 0) {
    printf("Key must contain only alphabetical characters.\n");
    return 1;
  }
  int check = 0;
  if (dup(argv[1]) == true) {
    printf("No duplicates.\n");
    return 1;
  }

  string plaintext = get_string("plaintext: ");
  sub(plaintext, argv[1]);
  printf("\n");
}

void sub(string n, string arr) {

  int sub[26] = {
    0
  };

  printf("ciphertext: ");
  for (int i = 0; i < strlen(n); i++) {
    int plain = toupper(n[i]) - 'A';
    sub[plain]++;
    if (plain < 0 || plain > 25) {
      printf("%c", n[i]);
    } else if (sub[plain] > 0) {

      if (isupper(n[i])) {

        printf("%c", toupper(arr[plain]));

      } else if (islower(n[i])) {
        printf("%c", tolower(arr[plain]));
      }
    }

  }
}

bool dup(string arr) {

  int dup[26] = {
    0
  };
  for (int i = 0; i < strlen(arr); i++) {
    int index = toupper(arr[i]) - 'A';
    dup[index]++;
    if (dup[index] > 1) {
      return true;

    }
  }
  return false;

}