#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_adjacent(int i, int j, char **grid, int rows)
{
	int		nroll = 0;
	int		cols;
	
	cols = strlen(grid[0]);
	nroll = 0;
	if (i > 0 && j > 0 && grid[i-1][j-1] == '@')
		nroll++;
	if (i > 0 && grid[i-1][j] == '@')
		nroll++;
	if (i > 0 && j < cols-1 && grid[i-1][j+1] == '@')
		nroll++;
	if (j > 0 && grid[i][j-1] == '@')
		nroll++;
	if (j < cols-1 && grid[i][j+1] == '@')
		nroll++;
	if (i < rows-1 && j > 0 && grid[i+1][j-1] == '@')
		nroll++;
	if (i < rows-1 && grid[i+1][j] == '@')
		nroll++;
	if (i < rows-1 && j < cols-1 && grid[i+1][j+1] == '@')
		nroll++;
	return (nroll < 4);
}

int main(int argc, char **argv)
{
	int		i;
	int		j;
	int		rows;
	char	**grid;
	int		accessible_rolls;

	i = 0;
	j = 0;
	rows = 0;
	grid = NULL;
	accessible_rolls = 0;
	if (argc < 2)
		return(0);
	rows = argc - 1;
	grid = malloc(rows * sizeof(char *));
	if (!grid)
		return (0);
	while (i < rows)
	{
		grid[i] = malloc(strlen(argv[i + 1]) + 1);
		if (!grid[i])
			return (0);
		strcpy(grid[i], argv[i + 1]);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[i][j] == '@')
			{
				if (check_adjacent(i, j, grid, rows))
					accessible_rolls++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	printf("Available rolls: %d\n", accessible_rolls);
	return (0);
}