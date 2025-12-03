#include <stdio.h>

int get_max_joltage(char *bank)
{
	int first_digit;
	int second_digit;
	int joltage;
    int max_joltage;
    int i;
	int j;

	max_joltage = 0;
	i = 0;
    while (bank[i])
    {
        j = i + 1;
        while (bank[j])
        {
            first_digit = bank[i] - '0';
            second_digit = bank[j] - '0';
            joltage = first_digit * 10 + second_digit;
            if (joltage > max_joltage)
                max_joltage = joltage;
            j++;
        }
        i++;
    }
    return (max_joltage);
}

int main(int argc, char **argv)
{
    int total;
    int i;
	int joltage;
    
	total = 0;
	i = 1;
    while (i < argc)
    {
        joltage = get_max_joltage(argv[i]);
        total += joltage;
        i++;
    }
    printf("%d\n", total);
    return (0);
}