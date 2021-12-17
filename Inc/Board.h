#include <iostream>
#include <stdint.h>


#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

const int M = 4;
const int N = 4;
const int K = 4;
const int ACCURATE = true;

const int PARTS = 1<<20;
const int SIZE = (M*N-1)/4+1;

const int CROSS = 1;
const int EMPTY = 0;
const int CIRCLE = -1;

const int WIN = 3;
const int UNKNOWN = 2;
const int TIE = 0;
const int LOSE = -3;

const int NORMAL = 0;
const int NORMAL_90 = 1;
const int NORMAL_180 = 2;
const int NORMAL_270 = 3;
const int VERTICALLY = 4;
const int HORIZONTALLY = 5;
const int DIAGONALLY_UP = 6;
const int DIAGONALLY_DOWN = 7;


class Board
{
    unsigned __int8 T[SIZE];
    __int8 state;
    int getter(int row, int column) const;
public:
    static unsigned long long int powers[SIZE];
    Board(__int8 other[M][N], int mode);
    int check();
    void set_state(int state);
    int get_state() const;
    int get_key();
    bool operator<(const Board& other) const;
    void print();
    bool in(Board other);
};

#endif // BOARD_H_INCLUDED
