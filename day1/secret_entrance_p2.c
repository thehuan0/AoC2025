#include <stdio.h>
#include <stdlib.h>

static int ft_atoi(const char *s)
{
    int i;
    int sign;
    long num;

    i = 0;
    sign = 1;
    num = 0;
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-')
    {
        sign = -sign;
        i++;
    }
    else if (s[i] == '+')
        i++;
    while (s[i] >= '0' && s[i] <= '9')
    {
        num = num * 10 + (s[i] - '0');
        i++;
    }
    return ((int)(num * sign));
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int pass;
    int dial;
    int iter;

    i = 1;
    pass = 0;
    dial = 50;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] == 'L')
            {
                j++;
                iter = ft_atoi(&argv[i][j]);
                while (iter > 0)
                {
                    dial--;
                    if (dial < 0)
                        dial = 99;
                    if (dial == 0)
                        pass++;
                    iter--;
                }
                while (argv[i][j] >= '0' && argv[i][j] <= '9')
                    j++;
            }
            else if (argv[i][j] == 'R')
            {
                j++;
                iter = ft_atoi(&argv[i][j]);
                while (iter > 0)
                {
                    dial++;
                    if (dial > 99)
                        dial = 0;
                    if (dial == 0)
                        pass++;
                    iter--;
                }
                while (argv[i][j] >= '0' && argv[i][j] <= '9')
                    j++;
            }
            else
                j++;
        }
        i++;
    }
    printf("%d\n", pass);
    return (0);
}
