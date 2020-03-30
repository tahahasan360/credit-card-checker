#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

long power(int);
int digitl(long, int);
int digitr(long, int);
int digits(long);

int main(void)
{
    long num = get_long("Number: ");
    int digits;
    if (num < power(12) || num > power(16) - 1)
    {
        printf("INVALID\n");
        exit(0);
    }


    int x = 0;
    int y = 0;
    for (int i = 0; i < 9; i++)
    {
        x = x + digitr(2 * digitr(num, 2 * i), 1) + digitr(2 * digitr(num, 2 * i), 2);
        y = y + digitr(num, (2 * i) + 1);
    }
    if ((x + y) % 10 == 0)
    {
        if ((digitl(num, 1) == 3) && ((digitl(num, 2) == 4) || (digitl(num, 2)
                                          == 7)))
        {
            printf("AMEX\n");
            exit(0);
        }
        if ((digitl(num, 1) == 5) && ((digitl(num, 2) == 1) || (digitl(num, 2)
                                          == 2) || (digitl(num, 2) == 3) || (digitl(num,
                                                  2) == 4) || (digitl(num, 2) ==
                                                          5)))
        {
            printf("MASTERCARD\n");
            exit(0);
        }
        if (digitl(num, 1) == 4)
        {
            printf("VISA\n");
            exit(0);
        }
        else
        {
            printf("CREDIT CARD CODE NOT DETECTED\n");
            exit(0);
        }
    }
    else
    {
        printf("INVALID\n");
        exit(0);
    }
}




//gives 10 to the power n
long power(int n)
{
    long x = 1;
    for (int i = 0; i < n; i++)
    {
        x = x * 10;
    }
    return x;
}

// gives the dth digit of n, counting from the right i.e. the 3rd digit of 123456 is 4
int digitr(long n, int d)
{
    int r = ((n % power(d)) - (n % power(d - 1))) / power(d - 1);
    return r;
}

// gives the dth digit of n, counting from the left i.e. the 3rd digit of 123456 is 3
int digitl(long n, int d)
{
    int r = (((n % power(digits(n) - d + 1)) - (n % power(digits(n) - d))) / power(digits(n) - d));
    return r;
}

//counts the number of digits of n
int digits (long n)
{
    int counter = 0;
    while (n>0)
    {
        n -= power(counter) * digitr (n, counter + 1 );
        counter++;
    }
    return counter;
}
