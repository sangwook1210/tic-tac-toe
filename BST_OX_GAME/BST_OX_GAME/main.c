#include "bst.h"

int main() {
    Board* b = malloc(sizeof(Board));   //보드 생성

    for (int i = 0; i < 9; i++) //보드 초기화
        b->board[i] = ' ';

    printBoard(b);  //보드 출력
    int turn = 0;   //플레이어의 차례인지 컴퓨터의 차례인지 결정하는 변수

    while (1) {
        if (turn % 2 == 0) {    //turn을 2로 나눈 나머지가 0이라면 플레이어의 차례
            process(b);
            printBoard(b);
        }

        else {  //아니라면 컴퓨터의 차례
            first_child_node(b);
            printBoard(b);
        }

        if (give_score(b) == 1) {   //give_score가 1이라면 플레이어의 패배
            printf("당신의 패배입니다.\n");
            break;
        }

        else if (give_score(b) == -1) { //give_score가 -1이라면 플레이어의 승리
            printf("축하합니다! 당신의 승리입니다.\n");
            break;
        }

        else if (give_score(b) == 0) {  ////give_score가 0이라면 무승부
            printf("무승부입니다.\n");
            break;
        }
        turn++; //차례 변경
    }
}