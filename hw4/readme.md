# HW4 Program

## Team組員

| 資工三 108590017 林銘政 | 課本範例查詢與環境架設 |
| --- | --- |
| 資工三 108590043 李永祺 | 虛擬機測試操作 |
| 資工三 108590045 廖永誠  | 程式碼邏輯撰寫 |

## Environment

- 使用Ubuntu20.04.1
- 需有以下兩個套件
    
    ```bash
    sudo apt-get install make
    sudo apt-get install flex
    ```
    
- Github地址
    
    [110-2-OS-Homework/hw3 at main · DandinPower/110-2-OS-Homework](https://github.com/DandinPower/110-2-OS-Homework/tree/main/hw3)
    

## Problem

### 11.13

- 打開並查看file1.txt
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96.jpg)
    
    - 可以觀察到file1.txt的inode為2367640
- 透過指令創建hard link 到file2.txt
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%201.jpg)
    
    - 可以看到一個file2.txt出現並且inode跟file1.txt一模一樣, 且兩者的內容也一樣
- 修改 file2.txt
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%202.jpg)
    
    - 可以觀察到修改file2.txt後file1.txt也會被同步修改
- strace rm file2.txt
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%203.jpg)
    
    - 在刪除file2.txt後file1.txt仍會保留
- create a soft link
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%204.jpg)
    
    - 觀察到在創建soft link到file4.txt後, 出現了一個內容跟file3.txt一樣但inode編號不一樣的file4.txt
- edit file4.txt
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%205.jpg)
    
    - 嘗試修改file4.txt後可以觀察到file3.txt也被同步修改
- delete file3.txt and try to edit file4
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%206.jpg)
    
    - 可以觀察到在刪除file3後file4就變成空的, 而當我嘗試去修改file4.txt後file3.txt又變回來了並且內容跟剛修改完的file4.txt內容一樣

### 12.16

- 編譯程式碼
    
    ```bash
    gcc -o main main.c
    ```
    
- 執行程式
    
    ```bash
    ./main <disk head>
    ```
    
    - disk head 為初始位置
- 輸出說明
    1. 根據順序依序輸出FCFS, SSTF, SCAN, CSCAN的結果
    2. 每一種演算法會先輸出移動順序再輸出移動總和
- 使用一組測資為
    
    ```
    0 ~ 4999
    2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681
    head : 2150
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%207.jpg)