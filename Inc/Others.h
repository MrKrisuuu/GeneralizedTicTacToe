#include "Inc/Board.h"


#ifndef OTHERS_H_INCLUDED
#define OTHERS_H_INCLUDED

int forced_win(__int8 T[M][N], int now);
bool winable(__int8 T[M][N], int moves);
int forced_move(__int8 T[M][N], int now);
bool sensible(__int8 T[M][N], int row, int column);
void symetries(bool S[8], __int8 T[M][N]);
void make_move(__int8 T[M][N], int x, int y, int &now, int &moves);

#endif // OTHERS_H_INCLUDED
