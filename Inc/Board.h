#include <iostream>
#include <stdint.h>
#include "Parameters.h"


#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


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
