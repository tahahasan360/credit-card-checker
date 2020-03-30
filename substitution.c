#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const int alphabetlength = 26;

int main(int argc, string argv[])
{
    //does not run if no or more than one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    
    //rejects keys longer or shorter than alphabetlength
    if (strlen(argv[1]) != alphabetlength)
    {
        printf("Key must contain %i characters.\n", alphabetlength);
        exit(1);
    }
    
    //rejects non-alphabetic and repeated characters (no double-checking)
    for (int i = 0; i < alphabetlength; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must contain only alphabetic characters.\n");
            exit(1);
        }
        
        for (int j = 0; j < alphabetlength - i; j++)
        {
            if ((argv[1][i] == argv[1][alphabetlength - 1 - j]) && (i != alphabetlength - 1 - j))
            {
                printf("Key must not contain repeated characters.\n");
                exit(1);
            }
        }
    }
    
    //applies substitution cipher
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        int upper = 0;
        if (isalpha(plaintext[i]) != 0)
        {
            if (isupper(plaintext[i]) != 0)
            {
                upper++;
            }
            int n = (int)(toupper(plaintext[i])) - 65;
            char out = argv[1][n];
            if (upper == 0)
            {
                printf("%c", tolower(out));
            }
            else 
            {
                printf("%c", toupper(out));
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
