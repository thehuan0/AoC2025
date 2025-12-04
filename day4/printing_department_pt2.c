#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_adjacent(int i, int j, char **grid, int rows, int cols)
{
    int nroll;

	nroll = 0;    
    if (i > 0 && j > 0 && grid[i-1][j-1] == '@')
		nroll++;
    if (j > 0 && grid[i][j-1] == '@')
		nroll++;
    if (i < rows-1 && j > 0 && grid[i+1][j-1] == '@')
		nroll++;
    if (i > 0 && grid[i-1][j] == '@')
		nroll++;
    if (i < rows-1 && grid[i+1][j] == '@')
		nroll++;
    if (i > 0 && j < cols-1 && grid[i-1][j+1] == '@')
		nroll++;
    if (j < cols-1 && grid[i][j+1] == '@')
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
    int		cols;
    char	**grid;
    char	**next_grid;
    int		total_removed;
    int		changed;
    
	i = 0;
    j = 0; 
	rows = argc - 1;
    cols = strlen(argv[1]);
    grid = malloc(rows * sizeof(char *));
    next_grid = malloc(rows * sizeof(char *));
	total_removed = 0;
    changed = 1;
	if (argc < 2)
        return (0);
    if (!grid || !next_grid)
        return (0);
    while (i < rows)
    {
        grid[i] = malloc(cols + 1);
        next_grid[i] = malloc(cols + 1);
        strcpy(grid[i], argv[i + 1]);
        strcpy(next_grid[i], argv[i + 1]);
        i++;
    }    
    while (changed == 1)
    {
        changed = 0;
        i = 0;
        while (i < rows)
        {
            strcpy(next_grid[i], grid[i]);
            i++;
        }
        i = 0;
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {
                if (grid[i][j] == '@' && check_adjacent(i, j, grid, rows, cols))
                {
                    next_grid[i][j] = '.';
                    changed = 1;
                }
                j++;
            }
            i++;
        }
        if (changed == 1)
        {
            i = 0;
            while (i < rows)
            {
                j = 0;
                while (j < cols)
                {
                    if (grid[i][j] == '@' && next_grid[i][j] == '.')
                    {
                        total_removed++;
                    }
                    j++;
                }
                strcpy(grid[i], next_grid[i]);
                i++;
            }
        }
    }    
    printf("Total rolls removed: %d\n", total_removed);
    i = 0;
    while (i < rows)
    {
        free(grid[i]);
        free(next_grid[i]);
        i++;
    }
    free(grid);
    free(next_grid);
    return (0);
}
