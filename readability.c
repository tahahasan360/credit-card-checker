#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");
    int words = 1;
    int sentences = 0;
    int letters = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (((s[i] >= 'a') && (s[i] <= 'z')) || ((s[i] >= 'A') && (s[i] <= 'Z')))
        {
            letters ++;
        }
        else if (s[i] == ' ')
        {
            words++;
        }
        else if ((s[i] == '?') || (s[i] == '!') || (s[i] == '.'))
        {
            sentences++;
        }
    }

    int index = round(0.0588 * (((float) letters / words) * 100) - 0.296 * (((float) sentences / words) * 100) - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
