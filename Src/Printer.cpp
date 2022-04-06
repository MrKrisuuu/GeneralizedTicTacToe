#include "Inc/Printer.h"


void print_boards(std::set<Board> boards[PARTS])
{
    long long int all_boards = 0;
    long long int unknown_boards = 0;
    for (int i=0; i<PARTS; i++)
    {
        all_boards += boards[i].size();
        //cout << i+1 << "==" << boards[i].size() << endl;
        for_each(boards[i].begin(), boards[i].end(), [&unknown_boards](auto it)
        {
            if (it.get_state() == UNKNOWN || it.get_state() == -UNKNOWN) unknown_boards++;
        });
    }
    std::cout << "Boards remembered: " << all_boards << std::endl;
    double percent;
    if (all_boards)
    {
        percent = (10000*(all_boards - unknown_boards)/all_boards)/100.0;
    }
    else
    {
        percent = 100;
    }
    std::cout << "Known boards: " << all_boards - unknown_boards << " (" << percent << "%)" << std::endl;
    std::cout << "Unknown boards: " << unknown_boards << std::endl;
    return;
}
