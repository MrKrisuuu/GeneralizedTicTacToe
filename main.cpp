#include <iostream>
#include <set>
#include <chrono>
#include <cmath>
#include "Inc/Board.h"
#include "Inc/Others.h"
#include "Inc/Cleaner.h"
#include "Inc/Printer.h"
#include "Inc/States.h"
using namespace std;


set<Board> boards[PARTS];
int moves = 0;
__int8 T[M][N];
bool S[8];
int MAX_DEPTH = M*N;


/// 3 == win for CROSS
/// 1 == unknown for CROSS
/// 0 == TIE
/// -1 == unknown for CIRCLE
/// -3 == win for CIRCLE
int calculate(int now, int depth, int alpha, int beta)
{
    int forced = forced_win(T, now);
    if (forced != EMPTY)
    {
        return forced * WIN;
    }
    if (!winable(T, depth+moves))
    {
        return TIE;
    }
    if (depth >= MAX_DEPTH)
    {
        return -now * UNKNOWN;
    }
    Board board = Board(T, NORMAL);
    int my_key = board.get_key();
    auto searcher = boards[my_key].find(board);
    if (searcher != boards[my_key].end())
    {
        return (*searcher).get_state();
    }
    for (int mode=NORMAL+1; mode<=DIAGONALLY_DOWN; mode++)
    {
        if (S[mode])
        {
            Board board_check = Board(T, mode);
            int my_key_check = board_check.get_key();
            auto searcher = boards[my_key_check].find(board_check);
            if (searcher != boards[my_key_check].end())
            {
                return (*searcher).get_state();
            }
        }
    }
    int tmp;
    if (now == CROSS){ // CROSS
        int state = MINF;
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column] == EMPTY && sensible(T, row, column))
                {
                    T[row][column] = CROSS;
                    tmp = calculate(CIRCLE, depth+1, alpha, beta);
                    T[row][column] = EMPTY;
                    state = max(tmp, state);
                    if (state != UNKNOWN)
                    {
                        alpha = max(alpha, state);
                    }
                    if (beta<=alpha && AB)
                    {
                        board.set_state(state);
                        boards[my_key].insert(board);
                        return state;
                    }
                    if (state == WIN)
                    {
                        board.set_state(state);
                        boards[my_key].insert(board);
                        return state;
                    }
                }
            }
        }
        if (state != UNKNOWN && ACCURATE)
        {
            for (int row=0; row<M; row++)
            {
                for (int column=0; column<N; column++)
                {
                    if (T[row][column] == EMPTY && !sensible(T, row, column))
                    {
                        T[row][column] = CROSS;
                        tmp = calculate(CIRCLE, depth+1, alpha, beta);
                        T[row][column] = EMPTY;
                        state = max(tmp, state);
                        if (state != UNKNOWN)
                        {
                            alpha = max(alpha, state);
                        }
                        if (beta<=alpha && AB)
                        {
                            board.set_state(state);
                            boards[my_key].insert(board);
                            return state;
                        }
                        if (state == WIN)
                        {
                            board.set_state(state);
                            boards[my_key].insert(board);
                            return state;
                        }
                    }
                }
            }
        }
        if (state == UNKNOWN)
        {
            state = -state;
        }
        board.set_state(state);
        boards[my_key].insert(board);
        return state;
    }else{ // CIRCLE
        int state = PINF;
        for (int row=0; row<M; row++)
        {
            for (int column=0; column<N; column++)
            {
                if (T[row][column] == EMPTY && sensible(T, row, column))
                {
                    T[row][column] = CIRCLE;
                    tmp = calculate(CROSS, depth+1, alpha, beta);
                    T[row][column] = EMPTY;
                    state = min(tmp, state);
                    if (state != -UNKNOWN)
                    {
                        beta = min(beta, state);
                    }
                    if (beta<=alpha && AB)
                    {
                        board.set_state(state);
                        boards[my_key].insert(board);
                        return state;
                    }
                    if (state == LOSE)
                    {
                        board.set_state(state);
                        boards[my_key].insert(board);
                        return state;
                    }
                }
            }
        }
        if (state != -UNKNOWN && ACCURATE)
        {
            for (int row=0; row<M; row++)
            {
                for (int column=0; column<N; column++)
                {
                    if (T[row][column] == EMPTY && !sensible(T, row, column))
                    {
                        T[row][column] = CIRCLE;
                        tmp = calculate(CROSS, depth+1, alpha, beta);
                        T[row][column] = EMPTY;
                        state = min(tmp, state);
                        if (state != -UNKNOWN)
                        {
                            beta = min(beta, state);
                        }
                        if (beta<=alpha && AB)
                        {
                            board.set_state(state);
                            boards[my_key].insert(board);
                            return state;
                        }
                        if (state == LOSE)
                        {
                            board.set_state(state);
                            boards[my_key].insert(board);
                            return state;
                        }
                    }
                }
            }
        }
        if (state == -UNKNOWN)
        {
            state = -state;
        }
        board.set_state(state);
        boards[my_key].insert(board);
        return state;
    }
}

bool print_state(int now)
{
    bool done = true;
    symetries(S, T);
    int state;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (T[row][column] == EMPTY)
            {
                if(!EVERY_MOVE && !sensible(T, row, column))
                {
                    cout << "L ";
                }
                else
                {
                    symetries(S, T);
                    T[row][column] = now;
                    if (Board(T, NORMAL).check() != EMPTY)
                    {
                        state = WIN * now;
                    }
                    else
                    {
                        state = calculate(-now, 1, MINF, PINF);
                    }
                    if (now == CIRCLE)
                    {
                        state = -state;
                    }
                    if (state == -UNKNOWN)
                    {
                        state = UNKNOWN;
                    }
                    switch (state)
                    {
                    case WIN:
                        cout << "W ";
                        break;
                    case UNKNOWN:
                        cout << "? ";
                        done = false;
                        break;
                    case TIE:
                        cout << "T ";
                        break;
                    case LOSE:
                        cout << "L ";
                        break;
                    default:
                        cout << "E ";
                    }
                    T[row][column] = EMPTY;
                }
            }
            else
            {
                switch (T[row][column])
                {
                case CROSS:
                    cout << "X ";
                    break;
                case CIRCLE:
                    cout << "O ";
                    break;
                default:
                    cout << "E ";
                }
            }
        }
        cout << endl;
    }
    return done;
}


int main()
{
    cout << "Size of Board: " << sizeof(Board) << endl;
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            T[row][column] = EMPTY;
        }
    }
    int now = CROSS;
    int x, y;
    Board::powers[0] = 1;
    for(int i=1; i<SIZE; i++)
    {
        Board::powers[i] = 256*Board::powers[i-1];
        Board::powers[i] %= PARTS;
    }
    string deep;
    bool done;
    while (moves < M*N && Board(T, NORMAL).check() == EMPTY)
    {
        for(int i=1; i<M*N+1 - moves; i++)
        {
            MAX_DEPTH = i;
            cout << "Depth: " << MAX_DEPTH << " (" << MAX_DEPTH+moves << "/" << M*N << ")" << endl;
            auto begin = chrono::high_resolution_clock::now();
            done = print_state(now);
            auto end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
            float time = ((int)(elapsed.count() * 1e-6)) * 1e-3;
            cout << "Time: " << time << " seconds" << endl;
            print_boards(boards);
            if (done)
            {
                cout << endl;
                clean_boards_unknown(boards);
                break;
            }
            clean_boards_unknown(boards);
            cout << endl;
            deep = " ";
            if (time > 0.5)
            {
                while (deep != "Y" && deep != "N")
                {
                    cout << "Continue?: ";
                    cin >> deep;
                }
                if (deep == "N")
                {
                    break;
                }
            }
        }
        cout << "Move: ";
        cin >> x >> y;
        make_move(T, x, y, now, moves);
        clean_boards_known(boards, T);
    }
    cout << "END!" << endl;
    Board(T, NORMAL).print();
    return 0;
}
/*
1 2
2 3
1 3
1 4
3 2
2 2
1 0
1 1
2 1
4 3
3 0
0 3
2 0
0 0
3 1
 */