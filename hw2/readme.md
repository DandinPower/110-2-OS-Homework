# HW2 Program

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
    
    [110-2-OS-Homework/hw2 at main · DandinPower/110-2-OS-Homework](https://github.com/DandinPower/110-2-OS-Homework/tree/main/hw2)
    

## Problem

### 4.17

- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread -lm
    ```
    
- 執行程式
    
    ```bash
    ./main
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96.jpg)
    

### 4.21

- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread
    ```
    
- 執行程式
    
    ```bash
    ./main <輸出長度>
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%201.jpg)
    

### 6.33

- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread -lm
    ```
    
- 執行程式
    
    ```bash
    ./main
    ```
    
- 正確輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%202.jpg)
    
- 如果沒加上mutex lock 就可能會發生沒有正確加到導致結果變低
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%203.jpg)
    

## Project

### Chap4

- 這邊選擇做Project2 Multithreaded sorting application
- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread 
    ```
    
- 執行程式
    
    ```bash
    ./main
    ```
    
- 使用方法
    - 先輸入待排序的list長度
    
    ```bash
    input list length:<長度>
    ```
    
    - 接下來輸入list
    
    ```bash
    5 1 19 6 87 10 3 55 21 30 100
    ```
    
- 兩個thread在各自排序完各自sublist後為確認有先完成才跑第3個thread因此會delay 1秒鐘
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%204.jpg)
    

### Chap6

- 這邊選擇做Project1 The Sleeping Teaching Assistant
- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread 
    ```
    
- 執行程式碼
    
    ```bash
    ./main
    ```
    
- 輸出說明
    
    ```
    Ta is sleeping  //當Ta在睡覺時
    Ta is wake up  //有student叫醒Ta時
    Ta Starting help students who sits in [編號]chair...  //Ta開始教學剛剛坐在[編號]上的人
    Ta Ask students leave //Ta教學完畢叫學生離開
    ```
    
    ```
    Student [編號] needs help  //學生需要幫忙
    Student [編號] Sits in [椅子編號]chair waiting Ta //學生坐在[椅子編號]等Ta
    Student [編號] into office getting help with Ta  //學生開始被Ta教學
    Student [編號] Leaving office... //教學完畢學生離開
    Student [編號] come again later //學生因為椅子滿了因此先離開了
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%205.jpg)