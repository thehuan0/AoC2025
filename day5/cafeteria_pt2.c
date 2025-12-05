#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_range
{
	long long	start;
	long long	end;
}	t_range;

static void	ft_parse_line(char *line, t_range *range, int idx)
{
	char	*dash;
	char	temp;

	dash = strchr(line, '-');
	if (!dash)
		return ;
	temp = *dash;
	*dash = '\0';
	range[idx].start = atoll(line);
	range[idx].end = atoll(dash + 1);
	*dash = temp;
}

static void	ft_sort_ranges(t_range *range, int count)
{
	int			i;
	int			j;
	t_range		temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (range[j].start > range[j + 1].start)
			{
				temp = range[j];
				range[j] = range[j + 1];
				range[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static long long	ft_count_unique(t_range *range, int count)
{
	int			i;
	long long	total;
	long long	start;
	long long	end;

	if (count == 0)
		return (0);
	ft_sort_ranges(range, count);
	total = 0;
	start = range[0].start;
	end = range[0].end;
	i = 1;
	while (i < count)
	{
		if (range[i].start <= end + 1)
		{
			if (range[i].end > end)
				end = range[i].end;
		}
		else
		{
			total += (end - start + 1);
			start = range[i].start;
			end = range[i].end;
		}
		i++;
	}
	total += (end - start + 1);
	return (total);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_range		range[1000];
	int			count;
	long long	total;

	if (argc != 2)
		return (printf("Usage: %s <file>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		ft_parse_line(line, range, count);
		count++;
		free(line);
	}
	close(fd);
	total = ft_count_unique(range, count);
	printf("%lld\n", total);
	return (0);
}
