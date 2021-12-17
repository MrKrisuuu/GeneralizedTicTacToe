#include "Inc/Board.h"
#include <set>


#ifndef CLEANER_H_INCLUDED
#define CLEANER_H_INCLUDED

void clean_boards_unknown(std::set<Board> boards[PARTS]);
void clean_boards_known(std::set<Board> boards[PARTS], __int8 T[M][N]);

#endif // CLEANER_H_INCLUDED
