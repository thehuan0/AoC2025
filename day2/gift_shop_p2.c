#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_invalid_id(long long num)
{
    char str[32];
    int len;
    int pattern_len;
    int i;
    int valid_pattern;
    
    sprintf(str, "%lld", num);
    len = strlen(str);
    pattern_len = 1;
    while (pattern_len <= len / 2)
    {
        if (len % pattern_len == 0)
        {
            valid_pattern = 1;
            i = pattern_len;
            while (i < len)
            {
                if (str[i] != str[i % pattern_len])
                {
                    valid_pattern = 0;
                    break;
                }
                i++;
            }
            
            if (valid_pattern)
                return (1);
        }
        pattern_len++;
    }
    return (0);
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
