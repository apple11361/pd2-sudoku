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


int Sudoku::Solve()// 解題; out==0 不輸出結果, out==1 輸出結果
{
    int board[150];// 保存完成解題後的數獨內容, 否則在求第2解時, 如果無第2解, 會把已得的第1解又填回空白
    int prevPos[150];// 存放上一次填數位置的stack 
    int prevPosP = 0;//  prevPos[] stack 的指標
    int ansNum;// 答案的數目 
    int index;// map[] index
     
    ansNum = 0;
    index = getFirstZeroIndex();    
    
    do
    {
        map[index]++;// 將本位置數字加 1
      
        if(map[index] > gridB)// 如果本位置的數字已大於 9 時, 表示本位置填數失敗, 回到上一個位置繼續測試
        {
            map[index] = 0;
            index = pop(prevPos, prevPosP);
        }
        else
        {
            if(checkR(index)==0 && checkC(index)==0 && checkB(index)==0)// 如果同列、行、宮都沒有相同的數字，則到下一個空白處繼續
            {
                push(prevPos, prevPosP, index);// 將目前填數位置存入stack 
                index = getFirstZeroIndex();
                if(index==-1)
                {
                    for(int i=0; i<sudokuSize; i++)
                    {
                        board[i] = map[i];
                    }
                    
                    ansNum++;
                    index = pop(prevPos, prevPosP);
                }
            }
        }
    }while(index>=0 && ansNum<2);
    
    if(out>0)// 如果 out>0, 輸出結果 
    {
        if(ansNum==0)
        {
            cout << '0' << endl;
        }
        else
        {
            if(ansNum==1)
            {
                for(int i=0; i<sudokuSize; i++)
                {
                    map[i] = board[i];
                }

                cout << '1' << endl;
                PrintMap();
            }
            else
               cout << '2' << endl;
        } 
    }
    
    return ansNum;      
}  



void Sudoku::GiveQuestion()
{
    int i, j, rnd, flag, temp, repeat;
    int locB[20];// 各宮的起點
    int posB[10];// 宮內格子位置的增值 
    int dark[5];// 4個黑色區塊的宮格
    
    srand(time(NULL));
    
    for(int block=0; block<numB; block++)// 計算各宮的起點
    {
        locB[block] = block/HVBlockNum*rcB*mapRC + block%HVBlockNum*rcB;
    }
    
    for(i=0; i<gridB; i++)// 計算宮內格子位置的增值 
    {
        posB[i] =(i/rcB)*mapRC + (i%rcB);
    }   
     
    for(i=0; i<4; i++) dark[i] = -1;
    
    for(i=0; i<4; i++)// 隨機產生4個宮行位置不相同的黑色區塊
    {
        rnd = rand()%4;
        flag = 0;
        
        for(j=0; j<i; j++)
        {
            if(rnd==dark[j])// 宮行位置重複 
            {
                flag = 1;
            }    
        }    
        
        if(flag)// 如果重複, 重來 
        {
            i--;
        }
        else
        {
            dark[i] = rnd;
        }
    }
    
    for(int i=0; i<sudokuSize; i++) map[i] = 0;// 數獨內容歸零 
    
    for(i=0; i<4; i++)// 4個黑色區塊填入-1
    {
        dark[i] = i * HVBlockNum + dark[i];// dark 原來存的是各宮格列的黑色區塊之宮行位置, 需轉換成實際的宮數 
        
        for(j=0; j<gridB; j++)// 黑色區塊裡的格子填入-1 
        {
            map[locB[dark[i]] + posB[j]] = -1; 
        }
    }
    
    
                
    for(int num=1; num<=gridB; num++)// 產生完整數獨盤面, 從 1 填到 9 
    {
        repeat = 0;
        
        for(int block=0; block<numB; block++)// 各宮嘗試填入數字 num 
        {
            if(block!=dark[0] && block!=dark[1] && block!=dark[2] && block!=dark[3])
            {
                for(i=0; i<gridB; i++)// 打亂宮格內順序
                {
                    rnd = rand()%gridB;
                    temp = posB[i];
                    posB[i] = posB[rnd];
                    posB[rnd] = temp;
                }
                
                while(--i>=0 && !FillNum(locB[block]+posB[i], num));// 填入數字, 成功則離開; 如果失敗, 填宮格內下個位置, 直到 i<0 
                
                if (i<0)// 填入失敗, 還原所填數字
                {  
                    for(int p=0; p<sudokuSize; p++)
                       if(map[p]==num) map[p]=0;           
                    block = -1;   // 重來, 讓block從0開始
                    if(++repeat>mapRC) break; // 若重來次數過多, 跳離 
                }
            }
        }   
         
        if(repeat>mapRC && num>=2)// 若重來次數過多, 而且目前所填數字 num>=2 則先還原前一數字, 然後退回前一數字重填 
        {
            num--;
            for(int p=0; p<sudokuSize; p++)// 還原前一數字
               if(map[p]==num) map[p]=0; 
            num--;// 退回前一數字(因為回到迴圈開頭會加 1, 所以這裡先減 1) 
        }   
    }
    
    DigMap();// 數獨題目出題(挖洞法)
    

    
    PrintMap();
} 



int Sudoku::FillNum(int p, int num)// 在位置 p 填入 num, 成功傳回 1, 失敗傳回 0 
{
    int flag;
    
    if(map[p]!=0) return 0;
    map[p] = num;
    flag = checkR(p);// 檢查同列有沒有相同的數字
    if(!flag) flag = checkC(p);// 檢查同行有沒有相同的數字
    if(flag)
    {
         map[p] = 0;
         return 0;
    }

    return 1;  
}   



int Sudoku::DigMap()// 數獨題目出題(挖洞法)
{
    int i, rnd, d, d2, temp, ansNum;
    int keep1, keep2;// 待挖位置所存內容的暫存器 
    int effGrid[150];// 有效格子的位置 
    int dig[150];// 挖洞順序 
    int board[150];// 存放題目內容 
    int digNum = (sudokuSize-36+1)/2;// 要挖洞的數目; 因為是對稱挖洞, 一次挖2個位置, 所以只需一半有效格數的挖洞次數
    
    out = 0;// 取消 Solve() 的輸出
    
    d = 0;
    for(i=0; i<sudokuSize; i++)
    {
        board[i] = map[i];
        
        if(board[i]!=-1)// 有效的格子
        {
            effGrid[d] = i;// 把格子的位置存在 effGrid 陣列中 
            d++;
        }
    }   
    
    for(i=0; i<digNum; i++) dig[i] = i;// 挖洞順序
    
    for(i=0; i<digNum; i++)// 打亂挖洞順序
    {
        rnd = rand()%digNum;
        temp = dig[rnd];
        dig[rnd] = dig[i];
        dig[i] = temp;
    }   
       
    for(d=0; d<digNum; d++)
    {
        ansNum = 0;
        keep2 = -1;
        d2 = sudokuSize - 36 - dig[d] - 1;
        keep1 = board[effGrid[dig[d]]];
        board[effGrid[dig[d]]] = 0;// 挖洞
        
        if(d2!=dig[d])
        {
            keep2 = board[effGrid[d2]];
            board[effGrid[d2]] = 0;// 對稱挖洞
        }
        
        for(i=0; i<sudokuSize; i++) map[i] = board[i];// 將挖洞後的題目內容存入 map[] 中 
        
        
        ansNum = Solve();// 解題 
        
        if(ansNum>1)// 有多重解, 挖洞需填回
        {
            board[effGrid[dig[d]]] = keep1;
            if(keep2>0) board[effGrid[d2]] = keep2;
        }
    } 
    
    for(i=0; i<sudokuSize; i++)// 剛剛試求解過程 map[]內容已變更, 所以需把存在 board[] 的最終結果存回 map[]  
    {
        map[i] = board[i];   
    }
    
    out = 1;// 恢復 Solve() 的輸出 
    
    return 1;
}



int Sudoku::getFirstZeroIndex()// 取得第1個空白格的位置
{
    for(int i=0;i<sudokuSize;++i)
       if(map[i] == 0)
          return i;
    return -1;
}



int Sudoku::checkR(int index)// 檢查同列有沒有相同的數字, 若有傳回 1
{
    int flag = 0, i, index1, startR;
    startR = index/mapRC * mapRC;// 列位置的起點
    
    for(i=0; i<mapRC; i++)
    {
        index1 = startR + i;// 同列裡第i行的位置 
        if(index!=index1 && map[index]==map[index1]) flag++;
    }    
    
    return(flag);
}    



int Sudoku::checkC(int index)// 檢查同行有沒有相同的數字, 若有傳回 1
{
    int flag = 0, i, index1, startC;
    startC = index % mapRC;// 行位置的起點
    
     for(i=0; i<mapRC; i++)
    {
        index1 = startC + i*mapRC;// 同行裡第i列的位置 
        if(index!=index1 && map[index]==map[index1]) flag++;
    }
    
    return(flag);
}   



int Sudoku::checkB(int index)// 檢查同宮有沒有相同的數字, 若有傳回 1
{
    int flag = 0, i, index1, startB;
    startB = ((index/mapRC)/rcB)*mapRC*rcB + ((index%mapRC)/rcB)*rcB;// 宮位置的起點
    
    for(i=0; i<gridB; i++)
    {
        index1= startB + (i/rcB)*mapRC+(i%rcB);// 同宮裡的第i格 
        //printf("sudoku[%d] = %d   sudoku[%d] = %d\n", sp, sudoku[sp], sp1, sudoku[sp1]);
        //system("pause");
        if(index!=index1 && map[index]==map[index1]) flag++;
    }    
    return(flag);
}
 


int Sudoku::push(int *prevPos, int &prevPosP, int index)// 將位置 index 放入堆疊中
{
    prevPos[prevPosP++] = index;
}



int Sudoku::pop(int *prevPos, int &prevPosP)// 取出堆疊中的上一個位置
{
    if(prevPosP<=0) return(-1); 
    else return(prevPos[--prevPosP]);
}



int Sudoku::PrintMap()// 輸出數獨內容到螢幕
{
    for(int i=0; i<sudokuSize; i++)
    {
        cout << map[i] << " ";
        
        if(i%12==11)
           cout << endl;
    }
}






