#include "Inc/Others.h"


bool sensible(__int8 T[M][N], int row, int column)
{
    // centre
    if (row==((M-1)/2) && column==((N-1)/2))
    {
        return true;
    }
    if (row==((M-1)/2) && column==((N-1)/2 + (N+1)%2))
    {
        return true;
    }
    if (row==((M-1)/2 + (M+1)%2) && column==((N-1)/2))
    {
        return true;
    }
    if (row==((M-1)/2 + (M+1)%2) && column==((N-1)/2 + (N+1)%2))
    {
        return true;
    }
    // neighbour
    if (row-1>=0 && T[row-1][column]!=EMPTY) //up
    {
        return true;
    }
    if (row-1>=0 && column+1<N && T[row-1][column+1]!=EMPTY) //up-right
    {
        return true;
    }
    if (column+1<M && T[row][column+1]!=EMPTY) //right
    {
        return true;
    }
    if (row+1<M && column+1<N && T[row+1][column+1]!=EMPTY) //down-right
    {
        return true;
    }
    if (row+1<M && T[row+1][column]!=EMPTY) //down
    {
        return true;
    }
    if (row+1<M && column-1>=0 && T[row+1][column-1]!=EMPTY) // down-left
    {
        return true;
    }
    if (column-1>=0 && T[row][column-1]!=EMPTY) //left
    {
        return true;
    }
    if (row-1>=0 && column-1>=0 && T[row-1][column-1]!=EMPTY) //up-left
    {
        return true;
    }
    // create or block threat
    int flag;
    if (row-(K-1)>=0 && T[row-2][column]!=EMPTY) //up
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row-(i+2)][column] != T[row-(i+3)][column])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (row-(K-1)>=0 && column+(K-1)<N && T[row-2][column+2]!=EMPTY) //up-right
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row-(i+2)][column+(i+2)] != T[row-(i+3)][column+(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (column+(K-1)<M && T[row][column+2]!=EMPTY) //right
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row][column+(i+2)] != T[row][column+(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (row+(K-1)<M && column+(K-1)<N && T[row+2][column+2]!=EMPTY) //down-right
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row+(i+2)][column+(i+2)] != T[row+(i+3)][column+(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (row+(K-1)<M && T[row+2][column]!=EMPTY) //down
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row+(i+2)][column] != T[row+(i+3)][column])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (row+(K-1)<M && column-(K-1)>=0 && T[row+2][column-2]!=EMPTY) // down-left
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row+(i+2)][column-(i+2)] != T[row+(i+3)][column-(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (column-(K-1)>=0 && T[row][column-2]!=EMPTY) //left
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row][column-(i+2)] != T[row][column-(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    if (row-(K-1)>=0 && column-(K-1)>=0 && T[row-2][column-2]!=EMPTY) //up-left
    {
        flag = true;
        for (int i=0; i<(K-1)-2; i++)
        {
            if (T[row-(i+2)][column-(i+2)] != T[row-(i+3)][column-(i+3)])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }
    return false;
}


int usefulness(__int8 T[M][N], int row, int column)
{
    /*if ((row==0 && column==0) || (row==0 && column==M) || (row==N && column==0) || (row==N && column==M))
    {
        return 3;
    }
    if (row==0 || column==0 || row==N || column==M)
    {
        return 3;
    }*/
    return 1;
}


void symetries(bool S[8], __int8 T[M][N])
{
    for (int i=0; i<8; i++)
    {
        S[i] = true;
    }
    if (M == N)
    {
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column]==-T[column][N-1-row] && T[row][column]!=EMPTY)
                {
                    S[NORMAL_90] = false;
                }
            }
        }
    }
    else
    {
        S[NORMAL_90] = false;
    }
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (T[row][column]==-T[M-1-row][N-1-column] && T[row][column]!=EMPTY)
            {
                S[NORMAL_180] = false;
            }
        }
    }
    if (M == N)
    {
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column]==-T[M-1-column][row] && T[row][column]!=EMPTY)
                {
                    S[NORMAL_270] = false;
                }
            }
        }
    }
    else
    {
        S[NORMAL_270] = false;
    }
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (T[row][column]==-T[row][N-1-column] && T[row][column]!=EMPTY)
            {
                S[VERTICALLY] = false;
            }
        }
    }
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (T[row][column]==-T[M-1-row][column] && T[row][column]!=EMPTY)
            {
                S[HORIZONTALLY] = false;
            }
        }
    }
    if (M == N)
    {
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column]==-T[N-1-column][M-1-row] && T[row][column]!=EMPTY)
                {
                    S[DIAGONALLY_UP] = false;
                }

            }
        }
    }
    else
    {
        S[DIAGONALLY_UP] = false;
    }
    if (M == N)
    {
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column]==-T[column][row] && T[row][column]!=EMPTY)
                {
                    S[DIAGONALLY_DOWN] = false;
                }
            }
        }
    }
    else
    {
        S[DIAGONALLY_DOWN] = false;
    }
    return;
}


void make_move(__int8 T[M][N], int x, int y, int &now, int &moves)
{
    T[x][y] = now;
    now = - now;
    moves++;
}