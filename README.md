# 클라이언트-서버 모델을 이용한 concurrent 파일 서버 구현
## executable file 생성
1. server
<pre>
<code>
gcc server.c -o server
</code>
</pre>

2. client
<pre>
<code>
gcc client.c -o client
</code>
</pre>

## executable file 실행
>두 개의 터미널을 연 후에 server file을 먼저 실행해야 한다.
<pre>
<code>
./server
./client
</code>
</pre>

## client 파일 사용법
### ./client를 통해 실행 후, 한 번 실행 후 종료되므로 ./client를 통해 새 사용자로 실행한다.
1. Enter File Name: 에는 읽고 싶거나, 쓰고 싶은 파일 이름을 입력한다.(30bytes)
2. Enter File Mode[r|w]: 에는 읽고 싶을 때 r, 쓰고 싶을 때 w을 입력한다. 다른 문자를 입력하면 r,w 를 입력할 때 까지 동작한다.(2bytes)
3. r이라면 Enter Bytes to read: (4096bytes)
4. w라면 Enter String: (4096bytes)

## server 파일 사용법
### ./server를 통해 실행 후, ctrl+c로 종료할 때 까지 지속적으로 실행된다.
>읽거나 쓰기를 성공했을 때 서버에도 성공했음을 알리고, read를 실패했을 때 파일 이름이 잘못됐음을 알린다.

## 실행 예
![image](https://user-images.githubusercontent.com/48954288/198447502-815d4875-ed46-43df-9c8f-8c57f0d330d5.png)
