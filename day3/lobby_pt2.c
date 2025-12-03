#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long long	get_max_joltage_part2(char *bank)
{
	int			len;
	int			positions_needed;
	int			positions_left;
	int			best_pos;
	int			best_digit;
	int			current_pos;
	int			j;
	int			digit;
	long long	joltage;

	len = ft_strlen(bank);
	joltage = 0;
	current_pos = 0;
	positions_needed = 12;
	
	while (positions_needed > 0)
	{
		positions_left = len - current_pos;
		best_digit = -1;
		best_pos = current_pos;
		j = current_pos;
		while (j <= len - positions_needed)
		{
			digit = bank[j] - '0';
			if (digit > best_digit)
			{
				best_digit = digit;
				best_pos = j;
			}
			j++;
		}
		joltage = joltage * 10 + best_digit;
		current_pos = best_pos + 1;
		positions_needed--;
	}
	return (joltage);
}

int	main(int argc, char **argv)
{
	long long	total;
	long long	joltage;
	int			i;

	total = 0;
	i = 1;
	while (i < argc)
	{
		joltage = get_max_joltage_part2(argv[i]);
		total += joltage;
		i++;
	}
	printf("%lld\n", total);
	return (0);
}
