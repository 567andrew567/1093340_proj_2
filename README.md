# 1093340_proj_2

## 編譯及執行方式
將cpp檔及test_data資料夾放在同個資料夾底下
### 測試環境
    電腦環境:windows11
    編譯器:g++ (MinGW.org GCC-6.3.0-1) 6.3.0
### 編譯
g++ -g 1093340_proj_2.cpp -o 1093340_proj_2
### 執行
1093340_proj_2 測資路徑 entry數量\
example:1093340_proj_2 test_data/test1.txt 2
###錯誤說明
* argv error\
代表參數數量有問題
* open file error\
代表測資路徑有誤
* entry error\
代表設定entry有問題，只能為2的次方
* error!!!instruction not found\
代表輸入有無法執行的instruction

## 測資說明
測資共有三分，接放置於**test_data**資料夾中，分別為:
* **test.txt**\
為老師網頁上的範例測資，有li、bed、bne、add、addi、andi，
* **test1.txt**\
為簡單範例，只有li、beq及addi
* **test2.txt**\
為自製測資，有li、beq、bne、add、addi，

## 執行結果
以test_data/test1.txt為例，entry數量設定為2個
```
entrys : 2
---------------------------------------------------------
read file:
0x110           li R1,16;  //R1=16
0x114           li R2,0; //R2=0
        LoopI:
0x118           beq R1,R2,EndLoopI; //R1==R2 EndLoopI
0x11C           addi R2,R2,1; //R2+=1
0x120   beq R0,R0,LoopI; //Go back to LoopI
        EndLoopI:
---------------------------------------------------------
instruction:
li R1,16
li R2,0
LoopI
beq R1,R2,EndLoopI
addi R2,R2,1
beq R0,R0,LoopI
EndLoopI
---------------------------------------------------------
label:
EndLoopI 6
LoopI 2
---------------------------------------------------------
run code:
li R1 16
use entry: 0
entry: 0 (000, SN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
li R2 0
use entry: 1
entry: 0 (000, SN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
LoopI
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (000, SN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (000, SN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (000, SN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N T wrong misprediction: 1
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (001, WN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 1
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, SN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N T wrong misprediction: 2
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, WN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 2
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, WN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, WN, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N T wrong misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, WT, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, WT, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, WT, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 3
---------------------------------------------------------
addi R2 R2 1
use entry: 1
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N N correct misprediction: 0
---------------------------------------------------------
beq R0 R0 LoopI
use entry: 0
entry: 0 (010, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
T T correct misprediction: 3
---------------------------------------------------------
beq R1 R2 EndLoopI
use entry: 0
entry: 0 (101, WN, SN, ST, SN, SN, SN, SN, SN)
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN)
N T wrong misprediction: 4
---------------------------------------------------------
done
predictors:
entry: 0 (011, WN, SN, ST, SN, SN, WN, SN, SN) misprediction: 4
entry: 1 (000, SN, SN, SN, SN, SN, SN, SN, SN) misprediction: 0
registers:
R0 : 0
R1 : 16
R2 : 16
R3 : 0
R4 : 0
R5 : 0
R6 : 0
R7 : 0
R8 : 0
R9 : 0
R10 : 0
R11 : 0
R12 : 0
R13 : 0
R14 : 0
R15 : 0
R16 : 0
R17 : 0
R18 : 0
R19 : 0
R20 : 0
R21 : 0
R22 : 0
R23 : 0
R24 : 0
R25 : 0
R26 : 0
R27 : 0
R28 : 0
R29 : 0
R30 : 0
R31 : 0

```
輸出以虛線分割，第一格為entry數量，第二格為輸入測資，第三格為整份code(處理完成的)，第四格為所有label及他們的位置，
接下來為每次執行一行code的結果，最後會輸出，每個predictor及register的狀態
