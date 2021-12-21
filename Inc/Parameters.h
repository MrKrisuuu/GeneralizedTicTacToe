#ifndef TICTACTOE_PARAMETERS_H
#define TICTACTOE_PARAMETERS_H

/// to change
const int M = 5;
const int N = 6;
const int K = 4;
const bool ACCURATE = false;
const bool EVERY_MOVE = true;

const int PARTS = 1<<20;
const int SIZE = (M*N-1)/4+1;


/// not to change
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



#endif //TICTACTOE_PARAMETERS_H