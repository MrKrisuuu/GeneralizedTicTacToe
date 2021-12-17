#include "Inc/Board.h"


unsigned long long int Board::powers[SIZE];


int Board::getter(int row, int column) const
{
    return ((T[(N*row+column)>>2]>>(((N*row+column)&3)<<1))&3)-1;
}


Board::Board(__int8 other[M][N], int mode)
{
    for (int element=0; element<SIZE; element++)
    {
        this->T[element] = 0;
    }
    switch (mode)
    {
    case NORMAL:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[row][column]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case NORMAL_90:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[column][N-1-row]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case NORMAL_180:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[M-1-row][N-1-column]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case NORMAL_270:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[N-1-column][row]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case VERTICALLY:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[row][N-1-column]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case HORIZONTALLY:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[M-1-row][column]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case DIAGONALLY_UP:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[N-1-column][M-1-row]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    case DIAGONALLY_DOWN:
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                this->T[(N*row+column)/4] += (other[column][row]+1)<<(2*((N*row+column)%4));
            }
        }
        break;
    }
}


int Board::check()
{
    int i;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (getter(row, column) != EMPTY)
            {
                // row
                if (column+K <= N)
                {
                    for (i=1; i<K; i++)
                    {
                        if (this->getter(row, column) != this->getter(row, column+i))
                        {
                            break;
                        }
                    }
                    if (i == K)
                    {
                        return this->getter(row, column);
                    }
                }

                // column
                if (row+K <= M)
                {
                    for (i=1; i<K; i++)
                    {
                        if (this->getter(row, column) != this->getter(row+i, column))
                        {
                            break;
                        }
                    }
                    if (i == K)
                    {
                        return this->getter(row, column);
                    }
                }
                // diagonal right
                if (row+K <= M && column+K <= N)
                {
                    for (i=1; i<K; i++)
                    {
                        if (this->getter(row, column) != this->getter(row+i, column+i))
                        {
                            break;
                        }
                    }
                    if (i == K)
                    {
                        return this->getter(row, column);
                    }
                }

                // diagonal left
                if (row+K <= M && column+1 >= K)
                {
                    for (i=1; i<K; i++)
                    {
                        if (this->getter(row, column) != this->getter(row+i, column-i))
                        {
                            break;
                        }
                    }
                    if (i == K)
                    {
                        return this->getter(row, column);
                    }
                }
            }
        }
    }
    return EMPTY;
}


void Board::set_state(int state)
{
    this->state = state;
}


int Board::get_state() const
{
    return this->state;
}


int Board::get_key()
{
    unsigned long long int my_key = 0;
    unsigned long long int* power = powers;
    for (int element=0; element<SIZE; element++)
    {
        my_key += this->T[element] * (*power);
        power++;
    }
    return my_key%PARTS;
}


bool Board::operator<(const Board& other) const
{
    //return this->key < other.key;
    for (int element=0; element<SIZE; element++)
    {
        if (this->T[element] != other.T[element])
        {
            return this->T[element] < other.T[element];
        }
    }
    return false;
}


void Board::print()
{
    std::cout << std::endl;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            switch(this->getter(row, column))
            {
            case CROSS:
                std::cout << "X ";
                break;
            case CIRCLE:
                std::cout << "O ";
                break;
            case EMPTY:
                std::cout << "_ ";
                break;
            default:
                std::cout << "E " << this->getter(row, column);

            }
        }
        std::cout << std::endl;
    }
}


bool Board::in(Board other)
{
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (this->getter(row, column) != EMPTY)
            {
                if (this->getter(row, column) != other.getter(row, column))
                {
                    return false;
                }
            }
        }
    }
    return true;
}





