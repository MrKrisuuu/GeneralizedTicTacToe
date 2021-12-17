#include "Inc/Cleaner.h"


void clean_boards_unknown(std::set<Board> boards[PARTS])
{
    for (int i=0; i<PARTS; i++)
    {
        auto it = boards[i].begin();
        while (it != boards[i].end())
        {
            if ((*it).get_state() == UNKNOWN)
            {
                it = boards[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}


void clean_boards_known(std::set<Board> boards[PARTS], __int8 T[M][N])
{
    Board board = Board(T, NORMAL);
    for (int i=0; i<PARTS; i++)
    {
        auto it = boards[i].begin();
        while (it != boards[i].end())
        {
            if (!board.in(*it))
            {
                it = boards[i].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}
