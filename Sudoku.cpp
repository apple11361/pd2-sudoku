#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Sudoku.h"

using namespace std;


Sudoku::Sudoku()
{
    out = 1;// 啟用 Solve() 的輸出 
    for(int i=0; i<sudokuSize; ++i)
        map[i] = 0;
}



Sudoku::Sudoku(const int init_map[])
{
    out = 1;// 啟用 Solve() 的輸出
    for(int i=0; i<sudokuSize; ++i)
        map[i] = init_map[i];
}



bool Sudoku::ReadIn()// 讀入數獨題目 
{
    int num;
    
    
        
    for(int i=0; i<sudokuSize; ++i) cin >> map[i];
    

}     







