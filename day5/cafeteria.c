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

static int	ft_is_in_range(long long id, t_range *ranges, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (id >= ranges[i].start && id <= ranges[i].end)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_parse_ranges(t_range **ranges, char *line, int *count)
{
	char	*dash;
	t_range	*temp;

	dash = strchr(line, '-');
	if (!dash)
		return (0);
	*dash = '\0';
	if (*count % 100 == 0)
	{
		temp = malloc(sizeof(t_range) * (*count + 101));
		if (!temp)
			return (0);
		if (*ranges)
		{
			memcpy(temp, *ranges, sizeof(t_range) * *count);
			free(*ranges);
		}
		*ranges = temp;
	}
	(*ranges)[*count].start = atoll(line);
	(*ranges)[*count].end = atoll(dash + 1);
	(*count)++;
	return (1);
}

static int	ft_check_id(char *line, t_range *ranges, int range_count)
{
	long long	id;

	if (!line || !line[0])
		return (0);
	id = atoll(line);
	return (ft_is_in_range(id, ranges, range_count));
}

static int	ft_process_file(int fd, t_range **ranges, int *range_count)
{
	char	*line;
	int		section;
	int		fresh;

	section = 0;
	fresh = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			section = 1;
			free(line);
			continue ;
		}
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (section == 0)
			ft_parse_ranges(ranges, line, range_count);
		else
			fresh += ft_check_id(line, *ranges, *range_count);
		free(line);
	}
	return (fresh);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			fresh_count;
	int			range_count;
	t_range		*ranges;

	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	ranges = NULL;
	range_count = 0;
	fresh_count = ft_process_file(fd, &ranges, &range_count);
	close(fd);
	if (ranges)
		free(ranges);
	printf("%d\n", fresh_count);
	return (0);
}
