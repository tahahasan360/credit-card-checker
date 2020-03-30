#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
    //ensures exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    
    //ensures input only alphabetic characters
    int keylength = strlen(argv[1]);
    //rejects non-alphabetic and repeated characters (no double-checking)
    for (int i = 0; i < keylength; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must contain only alphabetic characters.\n");
            exit(1);
        }
    }
    
    //implements Vigenere encryption
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        int key = (int) toupper(argv[1][i % keylength;]) - 65;
        if (isalpha(plaintext[i]) != 0)
        {
            if (isupper(plaintext[i]) != 0)
            {
                if ((plaintext[i] + key) > 92)
                {
                    printf("%c", plaintext[i] + key - 26);
                }
                else
                {
                    printf("%c", plaintext[i] + key);
                }
            }
            else
            {
                if ((plaintext[i] + key) > 122)
                {
                    printf("%c", plaintext[i] + key - 26);
                }
                else
                {
                    printf("%c", plaintext[i] + key);
                }
            }
        }
        else
        {
            printf ("%c", plaintext[i]);
        }
    }
    printf("\n");
}
