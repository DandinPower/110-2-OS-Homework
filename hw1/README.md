# HW1 - Program

## Problem

### 2.15

- 編譯執行檔
    
    ```bash
    gcc -o copy copy.c
    ```
    
- 透過strace紀錄執行過程
    
    ```bash
    strace -o trace.txt ./copy data/test.txt data/test2.txt
    ```
    
- 查詢結果
    
    ```
    cat trace.txt
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96.jpg)
    
- 透過strace觀看copy.c使用system call的數量
    
    ```bash
    strace -c ./copy
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%201.jpg)
    

---

### 3.14

- 編譯程式碼
    
    ```c
    gcc -o main main.c
    ```
    
- 運行方式
    
    ```bash
    #正確
    ./main 35
    
    #不正確
    ./main -35
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%202.jpg)
    

---

### 3.15

- 編譯程式碼
    
    ```bash
    gcc main.c -o main -lrt
    ```
    
- 運行程式碼
    
    ```bash
    #正確
    ./main 35
    
    #不正確
    ./main -35
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%203.jpg)
    

---

### 3.20

- 編譯程式碼
    
    ```bash
    gcc -o main main.c
    ```
    
- 運行程式
    
    ```bash
    cat data/test.txt
    cat data/test2.txt
    ./main data/test.txt data/test2.txt
    cat data/test2.txt
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%204.jpg)
    

## Project

### Chap2

### Part 1

- 製作ko檔
    
    ```bash
    sudo make
    sudo insmod simple.ko
    insmod | grep simple
    sudo rmmod simple.ko
    dmesg
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%205.jpg)
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%206.jpg)
    

### Part2

- 製作ko檔
    
    ```bash
    sudo make
    sudo insmod birthday.ko
    insmod | grep birthday
    sudo rmmod birthday.ko
    dmesg
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%207.jpg)
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%208.jpg)
    

---

### Chap3

### Project1

- 編譯程式碼
    
    ```bash
    gcc -o shell shell.c -lrt
    ```
    
- 運行shell
    
    ```bash
    ./shell
    ```
    
- 操作
    1. 輸入指令
        
        ```bash
        osh>pwd
        ```
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%209.jpg)
        
    2. 輸入指令並Concurrency運行
        
        ```bash
        osh>pwd &
        ```
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2010.jpg)
        
    3. 輸入history來查看已經儲存的指令
        
        ```bash
        osh>history
        ```
        
        - 錯誤指令不會記錄
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2011.jpg)
        
        - 最多10個如果超過就會將先前的移除以保留最新的10個
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2012.jpg)
        
    4. 輸入!!來執行最新一次的指令
        
        ```bash
        osh>!!
        ```
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2013.jpg)
        
    5. 輸入!<index>來指定執行history裡面的指令
        
        ```bash
        osh>!0
        ```
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2014.jpg)
        
- 錯誤提示
    1. 輸入錯誤指令
        
        ```bash
        osh>hello world
        ```
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2015.jpg)
        
    2. history沒有儲存指令卻呼叫
        
        ![擷取.JPG](image/%E6%93%B7%E5%8F%96%2016.jpg)