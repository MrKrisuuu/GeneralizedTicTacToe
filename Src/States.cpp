#include "Inc/States.h"


int forced_win(__int8 T[M][N], int now)
{
    int crosses;
    int empties;
    int circles;
    int wins = 0;
    int x_empty;
    int y_empty;
    int x = -1;
    int y = -1;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            // row
            if (column+K <= N)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i = 0; i < K; i++)
                {
                    switch (T[row][column + i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            x_empty = row;
                            y_empty = column + i;
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (empties==2 || (crosses>0 && circles>0))
                    {
                        break;
                    }
                }
                if (crosses == K-1 && empties == 1)
                {
                    if (now == CROSS)
                    {
                        return CROSS;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
                else if (circles == K-1 && empties == 1)
                {
                    if (now == CIRCLE)
                    {
                        return CIRCLE;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
            }
            // column
            if (row+K <= M)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            x_empty = row+i;
                            y_empty = column;
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (empties==2 || (crosses>0 && circles>0))
                    {
                        break;
                    }
                }
                if (crosses == K-1 && empties == 1)
                {
                    if (now == CROSS)
                    {
                        return CROSS;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
                else if (circles == K-1 && empties == 1)
                {
                    if (now == CIRCLE)
                    {
                        return CIRCLE;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
            }
            // diagonal right
            if (row+K <= M && column+K <= N)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column+i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            x_empty = row+i;
                            y_empty = column+i;
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (empties==2 || (crosses>0 && circles>0))
                    {
                        break;
                    }
                }
                if (crosses == K-1 && empties == 1)
                {
                    if (now == CROSS)
                    {
                        return CROSS;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
                else if (circles == K-1 && empties == 1)
                {
                    if (now == CIRCLE)
                    {
                        return CIRCLE;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
            }
            // diagonal left
            if (row+K <= M && column+1 >= K)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column-i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            x_empty = row+i;
                            y_empty = column-i;
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (empties==2 || (crosses>0 && circles>0))
                    {
                        break;
                    }
                }
                if (crosses == K-1 && empties == 1)
                {
                    if (now == CROSS)
                    {
                        return CROSS;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
                else if (circles == K-1 && empties == 1)
                {
                    if (now == CIRCLE)
                    {
                        return CIRCLE;
                    }
                    if (x != x_empty && y != y_empty)
                    {
                        wins++;
                        x = x_empty;
                        y = y_empty;
                    }
                }
            }
        }
    }
    if (wins>=2)
    {
        return -now;
    }
    return EMPTY;
}


bool winable(__int8 T[M][N], int moves)
{
    int CROSS_moves = (M*N+1)/2 - (moves+1)/2;
    int CIRCLE_moves = (M*N)/2 - (moves)/2;
    int crosses;
    int empties;
    int circles;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            // row
            if (column+K <= N)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row][column+i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (crosses>0 && circles>0)
                    {
                        break;
                    }
                }
                if (crosses+empties == K)
                {
                    if (empties <= CROSS_moves)
                    {
                        return true;
                    }
                }
                if (circles+empties == K)
                {
                    if (empties <= CIRCLE_moves)
                    {
                        return true;
                    }
                }
            }
            // column
            if (row+K <= M)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (crosses>0 && circles>0)
                    {
                        break;
                    }
                }
                if (crosses+empties == K)
                {
                    if (empties <= CROSS_moves)
                    {
                        return true;
                    }
                }
                if (circles+empties == K)
                {
                    if (empties <= CIRCLE_moves)
                    {
                        return true;
                    }
                }
            }
            // diagonal right
            if (row+K <= M && column+K <= N)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column+i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (crosses>0 && circles>0)
                    {
                        break;
                    }
                }
                if (crosses+empties == K)
                {
                    if (empties <= CROSS_moves)
                    {
                        return true;
                    }
                }
                if (circles+empties == K)
                {
                    if (empties <= CIRCLE_moves)
                    {
                        return true;
                    }
                }
            }
            // diagonal left
            if (row+K <= M && column+1 >= K)
            {
                crosses = 0;
                empties = 0;
                circles = 0;
                for (int i=0; i<K; i++)
                {
                    switch (T[row+i][column-i])
                    {
                        case CROSS:
                            crosses++;
                            break;
                        case EMPTY:
                            empties++;
                            break;
                        case CIRCLE:
                            circles++;
                            break;
                    }
                    if (crosses>0 && circles>0)
                    {
                        break;
                    }
                }
                if (crosses+empties == K)
                {
                    if (empties <= CROSS_moves)
                    {
                        return true;
                    }
                }
                if (circles+empties == K)
                {
                    if (empties <= CIRCLE_moves)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


