#include "Inc/Board.h"


#ifndef TICTACTOE_STATES_H
#define TICTACTOE_STATES_H

int forced_win(__int8 T[M][N], int now);
bool winable(__int8 T[M][N], int moves);

#endif //TICTACTOE_STATES_H
