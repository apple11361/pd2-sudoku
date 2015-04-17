#include <cstdlib>
#include <vector>
#include <iostream>
#include "Sudoku.h"

using namespace std;


int main()
{
    Sudoku sd;
    
    sd.ReadIn();
    sd.Solve();
    
    return 0;
}    


