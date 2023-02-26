#pragma once
#define _CRT_SECURE_NO_WARNINGS

//Board 구조체
typedef struct Board {
    char board[9];  //보드판
    int score;  //점수
    struct Board* left;
    struct Board* right;
} Board;

//보드에 돌들이 놓인 상황을 출력해주는 함수
void printBoard(Board* b);

//플레이어로부터 착수할 위치를 입력받아 돌을 착수하는 함수
process(Board* b);

//보드판의 상황을 읽어 알맞은 값을 반환하는 함수
int give_score(Board* b);

//보드의 현재 상황을 오른쪽과 왼쪽 자식 노드에 복사하는 함수
void leftright(Board* b);

//컴퓨터가 이진트리를 생성하여 돌을 착수하는 함수
int cpu_chacksu(Board* b);

//컴퓨터가 실제로 둘 수를 정하는 함수
void first_child_node(Board* b);