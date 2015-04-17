#include <cstdlib>
#include <vector>
#include <iostream>
#include "Sudoku.h"

using namespace std;


int main()
{
    Sudoku apple;
    
    apple.ReadIn();
    apple.Solve();
    
    return 0;
}    


