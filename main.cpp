#include <iostream>
#include <set>
#include <chrono>
#include <cmath>
#include "Inc/Board.h"
#include "Inc/Others.h"
#include "Inc/Cleaner.h"
#include "Inc/Printer.h"
using namespace std;


set<Board> boards[PARTS];
int moves = 0;
__int8 T[M][N];
bool S[8];
int MAX_DEPTH = M*N;


int calculate(int now, int depth)
{
    int forced = forced_win(T, now);
    if (forced != EMPTY)
    {
        return forced * now * WIN;
    }
    if (!winable(T, depth+moves))
    {
        return TIE;
    }
    if (depth == MAX_DEPTH)
    {
        return UNKNOWN;
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
    int state = LOSE;
    int tmp;
    int my_move = forced_move(T, now);
    if (my_move != -1)
    {
        T[my_move/N][my_move%N] = now;
        tmp = -calculate(-now, depth);
        T[my_move/N][my_move%N] = EMPTY;
        if (tmp == -UNKNOWN)
        {
            tmp = -tmp;
        }
        state = max(tmp, state);
        board.set_state(state);
        boards[my_key].insert(board);
        return state;
    }
    for (int row=0; row<M; row++)
    {
        for (int column=0; column<N; column++)
        {
            if (T[row][column] == EMPTY && sensible(T, row, column))
            {
                T[row][column] = now;
                tmp = -calculate(-now, depth+1);
                T[row][column] = EMPTY;
                if (tmp == -UNKNOWN)
                {
                    tmp = -tmp;
                }
                state = max(tmp, state);
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
                    T[row][column] = now;
                    tmp = -calculate(-now, depth+1);
                    T[row][column] = EMPTY;
                    if (tmp == -UNKNOWN)
                    {
                        tmp = -tmp;
                    }
                    state = max(tmp, state);
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
    board.set_state(state);
    boards[my_key].insert(board);
    return state;
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
                        state = WIN;
                    }
                    else
                    {
                        state = -calculate(-now, 1);
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
    return 0;
}
