/* USER: user176.36pdp
LANG: C
TASK: olivetrees */

#include <stdio.h>
#include <stdlib.h>
void show(int **grid, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    FILE *inputFile = fopen("olivetrees.in", "r");
    FILE *outputFile = fopen("olivetrees.out", "w");

    int N, M;
    fscanf(inputFile, "%d %d", &N, &M);

    int total_area = N * M;
    int available_area = N * M;

    int **grid = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        grid[i] = malloc(M * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            grid[i][j] = 0;
        }
    }

    int *empty_per_col = malloc(M * sizeof(int));
    for (int i = 0; i < M; i++)
    {
        int d = 0;
        fscanf(inputFile, " %d", &d);
        available_area -= d;
        empty_per_col[i] = N - d;
        if (d > 0)
        {
            for (int j = N - 1; j >= N - d; j--)
            {
                grid[j][i] = 1;
            }
        }
    }
    if (available_area == 0)
    {
        fprintf(outputFile, "%d", 0);
        return 0;
    }
    if (available_area == total_area)
    {
        fprintf(outputFile, "%d", total_area);
        return 0;
    }
    show(grid,N,M);
    int max_area = 0;
    int cur_area = 0;

    for (int i = 0; i < M; i++)
    {
        cur_area = empty_per_col[i];
        if (i == M - 1)
        {
            for (int x = -1; x >= -i; x--)
            {
                if (empty_per_col[i] <= empty_per_col[i + x])
                {
                    cur_area += empty_per_col[i];
                }
                else
                {
                    break;
                }
            }
            if (cur_area > max_area)
            {
                max_area = cur_area;
            }
            cur_area = 0;
        }
        for (int z = 1; z < M - i; z++)
        {
            if (empty_per_col[i] <= empty_per_col[i + z])
            {
                cur_area += empty_per_col[i];
            }

            else
            {
                for (int x = -1; x >= -i; x--)
                {
                    if (empty_per_col[i] <= empty_per_col[i + x])
                    {
                        cur_area += empty_per_col[i];
                    }
                    else
                    {
                        break;
                    }
                }

                if (cur_area > max_area)
                {
                    max_area = cur_area;
                }
                cur_area = 0;
                break;
            }

            if (z == M - i - 1)
            {
                if (i > 0)
                {
                    for (int x = -1; x >= -i; x--)
                    {
                        if (empty_per_col[i] <= empty_per_col[i + x])
                        {
                            cur_area += empty_per_col[i];
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (cur_area > max_area)
                    {
                        max_area = cur_area;
                    }
                }
            }
        }
    }
    if (max_area != 0)
    {
        fprintf(outputFile, "%d", max_area);
    }
    for (int i = 0; i < N; i++)
    {
        free(grid[i]);
    }
    free(grid);
    return 0;
}