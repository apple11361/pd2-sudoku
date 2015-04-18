#include <iostream>

class Sudoku {
public:
  Sudoku();
  Sudoku(const int init_map[]);
  bool ReadIn();// 讀入數獨題目 
  int Solve();// 解題
  void GiveQuestion();// 出題; 題目輸出到檔案 su_question 和螢幕 
  int getFirstZeroIndex();// 取得第1個空白格的位置 
  int checkR(int index);// 檢查同列有沒有相同的數字, 若有傳回 1
  int checkC(int index);// 檢查同行有沒有相同的數字, 若有傳回 1
  int checkB(int index);// 檢查同宮有沒有相同的數字, 若有傳回 1
  int PrintMap();// 輸出數獨內容到螢幕
  
  // out: Solve() 控制是否輸出結果的變數, ==0 不輸出結果, ==1 輸出結果
  // DigMap() 裡用 Solve() 試求解時, 不必輸出結果 
  int out;// 物件初建立時 out 會設為 1 
  
  static const int sudokuSize = 144;//數獨大小, 總格數 
  static const int mapRC = 12;// 方陣大小, 12 x 12
  static const int rcB = 3;// 每宮的列數或行數
  static const int gridB = rcB * rcB;// 每宮的格數
  static const int HVBlockNum = 4;// 橫向或縱向的宮數
  static const int numB = HVBlockNum * HVBlockNum;// 總宮數, 16 

private:
  int FillNum(int p, int num);// 在位置 p 填入 num, 成功傳回 1, 失敗傳回 0 
  int DigMap();// 數獨題目出題(挖洞法)    
  int push(int *prevPos, int &prevPosP, int index);// 將位置 index 放入堆疊中
  int pop(int *prevPos, int &prevPosP);// 取出堆疊中的上一個位置      
        
  int map[sudokuSize];
};

