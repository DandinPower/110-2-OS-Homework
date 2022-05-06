# HW3 Program

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

### 7.17

- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread 
    ```
    
- 執行程式
    
    ```bash
    ./main
    ```
    
- 輸出結果
    - 會確保不會同時有south跟north的人上橋
    - 如果是同一邊的話則可以正常上橋
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96.jpg)
    

### 8.25

- 編譯程式碼
    
    ```bash
    gcc -o main main.c
    ```
    
- 執行程式
    
    ```bash
    ./main <virtual address>
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%201.jpg)
    

### 9.26

- 編譯程式碼
    
    ```bash
    gcc -o main main.c
    ```
    
- 執行程式
    
    ```bash
    ./main <frameNums>
    ```
    
    - frameNums 為frame的個數
- 輸出說明
    1. 先根據handwrite 9.8的題目當測資
    2. 再隨機產生一組測資
- 輸出結果
    - handwrite 9.8
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%202.jpg)
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%203.jpg)
    
    - Random generate
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%204.jpg)
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%205.jpg)
    

## Project

### Chap7

- 專案說明
    1. 選用了5個customers,以及4種resources
    2. 先透過argv宣告好resources的available
    3. maximum會根據available來隨機產生(每個max都不會超過available)
    4. create 5個customer thread來不斷request resources並且在need 都為0後release所有resource
    5. 當全部的need都配置完後及結束程式
- 輸出說明
    1. request resource時
        - request的值為根據該customer的need來隨機產生
            
            ```
            [編號]customer is request: <1> <2> <3> <4>
            ```
            
        - 如果成功的話
            
            ```
            Sequence: [找出符合safe state的執行順序] Request is accept!
            ```
            
        - 如果失敗的話
            
            ```
            Sequence: -1 Request is Reject and wait for resource because can't find valid sequence,so it's in unsafe state.
            ```
            
    2. 當都配置完後release all
        
        ```
        [編號]customer is finish!
        [編號]customer release all!
        ```
        
    3. 每當available,maximum,allocation,need有更新時都會輸出一次目前的狀態
        
        ```
        Available:
        3 1 6 0 
        
        Maximum:
        8 9 7 2 
        7 5 3 7 
        6 2 4 2 
        3 5 8 1 
        6 5 8 0 
        
        Allocation:
        5 8 1 2 
        0 0 1 5 
        0 0 0 0 
        0 0 0 0 
        2 0 0 0 
        
        Need:
        3 1 6 0 
        7 5 2 2 
        0 0 0 0 
        3 5 8 1 
        4 5 8 0
        ```
        
- 編譯程式碼
    
    ```bash
    gcc -o main main.c -lpthread
    ```
    
- 執行程式
    
    ```bash
    ./main <available0> <available1> <available2> <available3>
    ```
    
- 輸出結果
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%206.jpg)
    
    - 此為最終的結束狀態 → 上面省略

### Chap9

- 專案說明
    - 採用了3個檔案
        - addresses.txt 為測資1000筆
        - output.txt 為紀錄output輸出
        - BACKING_STORE.bin 為長度為65536長度的memory資料
    - 在執行的時候透過指定argv來把以上3個檔案的路徑輸入進去
- 輸出說明
    - 輸出每一行的logical address,physical address,還有對應的value
    - 輸出測資的筆數
    - 輸出TLB hits的個數以及比例
    - 輸出Page faults的個數以及比例
- 編譯程式碼
    
    ```bash
    gcc -o main main.c
    ```
    
- 執行程式碼
    
    ```bash
    ./main BACKING_STORE.bin addresses.txt output.txt
    ```
    
- 輸出結果
    
    ```bash
    cat output.txt
    ```
    
    ![擷取.JPG](image/%E6%93%B7%E5%8F%96%207.jpg)
    
    - 以上省略