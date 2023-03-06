#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10 // size : board of size by size 
#define numberBomb 12 // max : size * size - 1

int randomGenerator()
{
    int randomnumber;
    randomnumber = rand() % size;
    return(randomnumber);
}

void createTable(char grid[size][size])
{
    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            grid[j][i] = '0';
        }
    }

    int testBomb;
    int x, y;


    for (int b = 0; b < numberBomb; ++b)
    {
        testBomb = 0;

        while (testBomb == 0) {

            x = randomGenerator();
            y = randomGenerator();

            if (grid[x][y] == '0') {
                testBomb = 1;
            }
        }
        grid[x][y] = 'X';
    }
}

void createMask(char gridMask[size][size])
{
    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            gridMask[j][i] = '.';
        }
    }
}

void bombNearby(char grid[size][size])
{
    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            int count = 0;
            char countChar;
            if (grid[j][i] == '0') {

                if (grid[j - 1][i] == 'X') {
                    count = ++count;
                }
                if (grid[j + 1][i] == 'X') {
                    count = ++count;
                }

                if (i != 0) {
                    if (grid[j][i - 1] == 'X') {
                        count = ++count;
                    }
                    if (grid[j - 1][i - 1] == 'X') {
                        count = ++count;
                    }
                    if (grid[j + 1][i - 1] == 'X') {
                        count = ++count;
                    }
                }

                if (i != size - 1) {
                    if (grid[j][i + 1] == 'X') {
                        count = ++count;
                    }
                    if (grid[j - 1][i + 1] == 'X') {
                        count = ++count;
                    }
                    if (grid[j + 1][i + 1] == 'X') {
                        count = ++count;
                    }
                }

                // converion count en char ASCII

                grid[j][i] = (char)(count + 48);

            }
        }
    }
}

void showTable(char grid[size][size])
{
    printf("    0 1 2 3 4 5 6 7 8 9 \n \n");
    for (int j = 0; j < size; ++j)
    {
        printf("%d   ", j);
        for (int i = 0; i < size; ++i)
        {
            printf("%c", grid[j][i]);
            printf(" ");
        }
        printf("\n");
    }
}

void explosion0(char grid[size][size], char gridMask[size][size], int inputRow, int inputCol)
{
    int j = inputRow;
    int i = inputCol;

    if (grid[j - 1][i] == '0') {
        gridMask[j - 1][i] = '0';
        grid[j - 1][i] = ' ';
        explosion0(grid, gridMask, j - 1, i);
    }

    if (grid[j - 1][i] != ' ' && grid[j - 1][i] != '0') {
        gridMask[j - 1][i] = grid[j - 1][i];
    }

    if (grid[j + 1][i] == '0') {
        gridMask[j + 1][i] = '0';
        explosion0(grid, gridMask, j + 1, i);
        grid[j + 1][i] = ' ';

    }

    if (grid[j + 1][i] != ' ' && grid[j + 1][i] != '0') {
        gridMask[j + 1][i] = grid[j + 1][i];
    }

    if (i != 0) {
        if (grid[j][i - 1] == '0') {
            gridMask[j][i - 1] = '0';
            grid[j][i - 1] = ' ';
            explosion0(grid, gridMask, j, i - 1);
        }

        if (grid[j][i - 1] != ' ' && grid[j][i - 1] != '0') {
            gridMask[j][i - 1] = grid[j][i - 1];
        }

        if (grid[j - 1][i - 1] == '0') {
            gridMask[j - 1][i - 1] = '0';
            grid[j - 1][i - 1] = ' ';
            explosion0(grid, gridMask, j - 1, i - 1);
        }

        if (grid[j - 1][i - 1] != ' ' && grid[j - 1][i - 1] != '0') {
            gridMask[j - 1][i - 1] = grid[j - 1][i - 1];
        }

        if (grid[j + 1][i - 1] == '0') {
            gridMask[j + 1][i - 1] = '0';
            grid[j + 1][i - 1] = ' ';
            explosion0(grid, gridMask, j + 1, i - 1);
        }

        if (grid[j + 1][i - 1] != ' ' && grid[j + 1][i - 1] != '0') {
            gridMask[j + 1][i - 1] = grid[j + 1][i - 1];
        }

    }

    if (i != size - 1) {
        if (grid[j][i + 1] == '0') {
            gridMask[j][i + 1] = '0';
            grid[j][i + 1] = ' ';
            explosion0(grid, gridMask, j, i + 1);
        }

        if (grid[j][i + 1] != ' ' && grid[j][i + 1] != '0') {
            gridMask[j][i + 1] = grid[j][i + 1];
        }

        if (grid[j - 1][i + 1] == '0') {
            gridMask[j - 1][i + 1] = '0';
            grid[j - 1][i + 1] = ' ';
            explosion0(grid, gridMask, j - 1, i + 1);
        }

        if (grid[j - 1][i + 1] != ' ' && grid[j - 1][i + 1] != '0') {
            gridMask[j - 1][i + 1] = grid[j - 1][i + 1];
        }

        if (grid[j + 1][i + 1] == '0') {
            gridMask[j + 1][i + 1] = '0';
            grid[j + 1][i + 1] = ' ';
            explosion0(grid, gridMask, j + 1, i + 1);
        }

        if (grid[j + 1][i + 1] != ' ' && grid[j + 1][i + 1] != '0') {
            gridMask[j + 1][i + 1] = grid[j + 1][i + 1];
        }

    }


}


int testWin(char grid[size][size], char gridMask[size][size])
{
    int win = 0;
    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {

            if (gridMask[j][i] == '.') {
                if (grid[j][i] != 'X') {
                    return(win);
                }
            }

            if (gridMask[j][i] == 'F') {
                if (grid[j][i] != 'X') {
                    return(win);
                }
            }

        }
    }
    win = 1;
    return(win);
}


int main()
{
    srand(time(NULL));
    int inputRow;
    int inputCol;
    int flagDig;

    char grid[size][size];
    char gridMask[size][size];
    createTable(grid);
    createMask(gridMask);
    bombNearby(grid);

    printf("Start of Minesweeper ! \n \n");
    int stopWhile = 0;
    int test;
    int testRow;
    int testCol;

    showTable(gridMask);

    while (stopWhile == 0) {

        test = 0;
        testRow = 0;
        testCol = 0;

        while (test == 0) {

            printf("\n Enter the number of a row : ");
            scanf_s("%d", &inputRow);

            printf("\n Enter the number of a column : ");
            scanf_s("%d", &inputCol);

            if ((inputCol < 0) || (inputCol > size - 1)) {
                testCol = 0;
            }
            else {
                testRow = 1;
            }
            if ((inputRow < 0) || (inputRow > size - 1)) {
                testRow = 0;
            }
            else {
                testCol = 1;
            }
            if (testRow == 1 && testCol == 1) {
                if (gridMask[inputRow][inputCol] == '.' || gridMask[inputRow][inputCol] == 'F') {
                    test = 1;
                }
            }
            else {
                printf("Strike not possible, try again");
            }

            printf_s("\n Dig or Place a Flag ( 0 to dig / 1 to Flag ) : ");
            scanf_s("%d", &flagDig);
        }

        system("CLS");

        if (flagDig == 0) {

            gridMask[inputRow][inputCol] = grid[inputRow][inputCol];

            if (grid[inputRow][inputCol] == '0')
            {
                explosion0(grid, gridMask, inputRow, inputCol);
            }

            if (gridMask[inputRow][inputCol] == 'X') {
                showTable(gridMask);
                printf("\n You discovered a bomb, end of the game  \n");
                break;
            }
            else {
                printf("\n \n");
            }
        }

        else if (flagDig == 1) {
            if (gridMask[inputRow][inputCol] == '.') {
                gridMask[inputRow][inputCol] = 'F';
                printf("\n Placed flag at row : %d and col : %d \n \n", inputRow, inputCol);
            }
            else if (gridMask[inputRow][inputCol] == 'F') {
                gridMask[inputRow][inputCol] = '.';
                printf("\n Removed flag at row : %d and col : %d \n \n", inputRow, inputCol);
            }
        }

        showTable(gridMask);
        printf("\n Played at row : %d and col : %d \n \n", inputRow, inputCol);

        if (testWin(grid, gridMask) == 1) {
            printf("\n You have won !");
            break;
        }
    }
}
