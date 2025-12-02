#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_invalid_id(long long num)
{
    char str[32];
    int len;
    int i;
    
    sprintf(str, "%lld", num);
    len = strlen(str);
    if (len % 2 != 0)
        return (0);
       i = 0;
    while (i < len / 2)
    {
        if (str[i] != str[i + len / 2])
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    char *input;
    int i;
    long long start, end, current;
    long long sum;
    
    if (argc != 2)
        return (1);
    
    input = argv[1];
    i = 0;
    sum = 0;
    
    while (input[i])
    {
        start = atoll(&input[i]);
        while (input[i] && input[i] != '-')
            i++;
        if (input[i] == '-')
            i++;
        end = atoll(&input[i]);
        while (input[i] && input[i] != ',')
            i++;
        if (input[i] == ',')
            i++;
        current = start;
        while (current <= end)
        {
            if (is_invalid_id(current))
                sum += current;
            current++;
        }
    }
    printf("%lld\n", sum);
    return (0);
}
