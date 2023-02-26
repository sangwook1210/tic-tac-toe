#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

char user = 'o';    //플레이어가 놓을 돌은 o이다
char com = 'x';     //컴퓨터가 놓을 돌은 x이다

//보드에 돌들이 놓인 상황을 출력해주는 함수
void printBoard(Board* b) {
    for (int i = 0; i < 9; i++)
        if (i % 3 == 2) {
            printf("%c\n", b->board[i]);
            if (i != 8) {
                printf("-----");
            }
            printf("\n");
        }
        else
            printf("%c|", b->board[i]);
}

//플레이어로부터 착수할 위치를 입력받아 돌을 착수하는 함수
process(Board* b) {
    int userPos = 0;
    while (1) {
        printf("놓을 곳의 번호를 입력해주세요: ");
        userPos = 0;    //플레이어로부터 놓을 곳의 번호를 입력받을 변수
        int result = scanf_s("%d", &userPos);

        if (userPos >= 1 && userPos <= 9) { //플레이어의 올바른 입력
            if (b->board[userPos - 1] == 'o' || b->board[userPos - 1] == 'x') { //플레이어가 입력한 곳에 이미 돌이 있을 경우
                printf("그곳에는 이미 돌이 있습니다. 다시 입력해주세요.\n\n");
            }
            else {  //플레이어가 입력한 곳에 돌이 없을 경우
                b->board[userPos - 1] = user;
                break;
            }
        }
        else {  //플레이어의 잘못된 입력
            printf("잘못된 입력입니다. 다시 입력해주세요.\n\n");
            rewind(stdin);  //표준 입력 버퍼에 저장된 모든 문자를 제거
        }
    }
}

//보드판의 상황을 읽어 알맞은 값을 반환하는 함수
int give_score(Board* b) {
    //컴퓨터가 한 줄을 완성시켰을 경우 1을 봔환
    if ((b->board[0] == 'x' && b->board[1] == 'x' && b->board[2] == 'x') ||
        (b->board[3] == 'x' && b->board[4] == 'x' && b->board[5] == 'x') ||
        (b->board[6] == 'x' && b->board[7] == 'x' && b->board[8] == 'x') ||
        (b->board[0] == 'x' && b->board[3] == 'x' && b->board[6] == 'x') ||
        (b->board[1] == 'x' && b->board[4] == 'x' && b->board[7] == 'x') ||
        (b->board[2] == 'x' && b->board[5] == 'x' && b->board[8] == 'x') ||
        (b->board[0] == 'x' && b->board[4] == 'x' && b->board[8] == 'x') ||
        (b->board[2] == 'x' && b->board[4] == 'x' && b->board[6] == 'x')) {
        return 1;
    }

    //플레이어가 한 줄을 완성시켰을 경우 -1을 반환
    else if ((b->board[0] == 'o' && b->board[1] == 'o' && b->board[2] == 'o') ||
        (b->board[3] == 'o' && b->board[4] == 'o' && b->board[5] == 'o') ||
        (b->board[6] == 'o' && b->board[7] == 'o' && b->board[8] == 'o') ||
        (b->board[0] == 'o' && b->board[3] == 'o' && b->board[6] == 'o') ||
        (b->board[1] == 'o' && b->board[4] == 'o' && b->board[7] == 'o') ||
        (b->board[2] == 'o' && b->board[5] == 'o' && b->board[8] == 'o') ||
        (b->board[0] == 'o' && b->board[4] == 'o' && b->board[8] == 'o') ||
        (b->board[2] == 'o' && b->board[4] == 'o' && b->board[6] == 'o')) {
        return -1;
    }

    //더 이상 둘 곳이 없어서 비긴 경우 0을 반환
    else if ((b->board[0] == 'x' || b->board[0] == 'o') &&
        (b->board[1] == 'x' || b->board[1] == 'o') &&
        (b->board[2] == 'x' || b->board[2] == 'o') &&
        (b->board[3] == 'x' || b->board[3] == 'o') &&
        (b->board[4] == 'x' || b->board[4] == 'o') &&
        (b->board[5] == 'x' || b->board[5] == 'o') &&
        (b->board[6] == 'x' || b->board[6] == 'o') &&
        (b->board[7] == 'x' || b->board[7] == 'o') &&
        (b->board[8] == 'x' || b->board[8] == 'o')) {
        return 0;
    }

    //아직 판가름이 나지 않은 경우 2를 반환
    else
        return 2;
}

//보드의 현재 상황을 오른쪽과 왼쪽 자식 노드에 복사하는 함수
void leftright(Board* b) {
    for (int i = 0; i < 9; i++) {
        b->left->board[i] = b->board[i];
        b->right->board[i] = b->board[i];
    }
}

//컴퓨터가 이진트리를 생성하여 돌을 착수하는 함수
int cpu_chacksu(Board* b) {
    srand(time(NULL));
    int random_l = 100, random_r = 100; //왼쪽 자식 노드에서 놓을 자리와 오른쪽 자식 노드에서 놓을 자리
    int cnt = 0;    //판의 빈 공간의 개수를 저장할 변수

    //판의 빈 공간의 개수를 센다
    for (int i = 0; i < 9; i++) {
        if (b->board[i] == ' ')
            cnt++;
    }

    //왼쪽 자식 노드의 판의 어느 위치에 돌이 놓일지 설정
    while (1) {
        if (cnt == 0)   //판에 빈 공간이 하나도 없다면
            break;  //random_l을 설정하지 않는다
        else {
            random_l = rand() % 9;  //random_l 설정
            if (b->board[random_l] == 'o' || b->board[random_l] == 'x') //정한 random_l에 이미 돌이 있다면
                continue;   //random_l을 다시 설정한다
            else
                break;
        }
    }

    //오른쪽 자식 노드의 판의 어느 위치에 돌이 놓일지 설정
    while (1) {
        if (cnt == 0 || cnt == 1)   //판에 빈 공간이 하나도 없거나 판에 빈 공간이 하나밖에 없다면
            break;  //random_r을 설정하지 않는다
        else {
            random_r = rand() % 9;  //random_r설정
            if (random_r == random_l || b->board[random_r] == 'o' || b->board[random_r] == 'x') //정한 random_r이 random_l과 같거나 random_r에 이미 돌이 있다면
                continue;   //random_r을 다시 설정한다
            else
                break;
        }
    }

    //b의 left와 right 보드 생성
    b->left = malloc(sizeof(Board));
    b->right = malloc(sizeof(Board));

    //만약 아직 승부가 나지 않았다면
    if (give_score(b) == 2) {
        //현재까지 놓인 o와 x의 개수를 세어 무엇을 놓을 차례인지 계산한다.
        int o_num = 0;
        int x_num = 0;
        for (int i = 0; i < 9; i++) {
            if (b->board[i] == 'o')
                o_num++;
            else if (b->board[i] == 'x')
                x_num++;
        }

        //컴퓨터가 놓은 차례
        if (o_num > x_num) {
            //b의 판을 b->left와 b->right에 복사
            leftright(b);

            //random_r이 설정되지 않았다면
            if (random_r == 100) {
                b->left->board[random_l] = 'x'; //b->left의 보드의 random_l 위치에 x돌을 둔다
                cpu_chacksu(b->left);   //cpu_chacksu를 다시 실행 (b->left는 꽉 찬 판이다)
            }
            else {
                b->left->board[random_l] = 'x'; //b->left의 보드의 random_l 위치에 x돌을 둔다
                b->right->board[random_r] = 'x';    //b->right의 보드의 random_r 위치에 x돌을 둔다

                int score_l = cpu_chacksu(b->left); //cpu_chacksu(b->left)에서 반환된 값을 score_l에 저장
                int score_r = cpu_chacksu(b->right);    //cpu_chacksu(b->right)에서 반환된 값을 score_r에 저장

                return score_l + score_r;   //give_score가 2라면 left와 right의 스코어를 합친다
            }
        }

        //플레이어의 돌을 컴퓨터가 놓을 차례
        else if (o_num == x_num) {
            //b의 판을 b->left와 b->right에 복사
            leftright(b);

            //random_r이 설정되지 않았다면
            if (random_r == 100) {
                b->left->board[random_l] = 'o'; //b->left의 보드의 random_l 위치에 o돌을 둔다
                cpu_chacksu(b->left); //cpu_chacksu를 다시 실행(b->left는 꽉 찬 판이다)
            }
            else {
                b->left->board[random_l] = 'o'; //b->left의 보드의 random_l 위치에 o돌을 둔다
                b->right->board[random_r] = 'o';    //b->right의 보드의 random_r 위치에 o돌을 둔다


                int score_l = cpu_chacksu(b->left); //cpu_chacksu(b->left)에서 반환된 값을 score_l에 저장
                int score_r = cpu_chacksu(b->right);    //cpu_chacksu(b->right)에서 반환된 값을 score_r에 저장

                return score_l + score_r;   //give_score가 2라면 left와 right의 스코어를 합친다
            }
        }
    }

    //만약 승부가 결정지어졌다면
    else {
        b->score = give_score(b);   //score가 2가 아니라면 give_score가 score
        return b->score;
    }
}

//컴퓨터가 실제로 둘 수를 정하는 함수
void first_child_node(Board* b) {
    srand(time(NULL));
    int random_l = 100, random_r = 100; //왼쪽 자식 노드에서 놓을 자리와 오른쪽 자식 노드에서 놓을 자리
    int cnt = 0;    //판의 빈 공간의 개수를 저장할 변수
    for (int i = 0; i < 9; i++) {
        if (b->board[i] == ' ')
            cnt++;
    }

    //왼쪽 자식 노드의 판의 어느 위치에 돌이 놓일지 설정
    while (1) {
        if (cnt == 0)   //판에 빈 공간이 하나도 없다면
            break;  //random_l을 설정하지 않는다
        else {
            random_l = rand() % 9;  //random_l 설정
            if (b->board[random_l] == 'o' || b->board[random_l] == 'x') //정한 random_l에 이미 돌이 있다면
                continue;   //random_l을 다시 설정한다
            else
                break;
        }
    }

    //오른쪽 자식 노드의 판의 어느 위치에 돌이 놓일지 설정
    while (1) {
        if (cnt == 0 || cnt == 1)   //판에 빈 공간이 하나도 없거나 판에 빈 공간이 하나밖에 없다면
            break;  //random_r을 설정하지 않는다
        else {
            random_r = rand() % 9;  //random_r설정
            if (random_r == random_l || b->board[random_r] == 'o' || b->board[random_r] == 'x') //정한 random_r이 random_l과 같거나 random_r에 이미 돌이 있다면
                continue;   //random_r을 다시 설정한다
            else
                break;
        }
    }

    //b의 left와 right 보드 생성
    b->left = malloc(sizeof(Board));
    b->right = malloc(sizeof(Board));

    //b의 판을 b->left와 b->right에 복사
    leftright(b);

    b->left->board[random_l] = 'x'; //b->left의 보드의 random_l 위치에 x돌을 둔다
    b->right->board[random_r] = 'x';    //b->right의 보드의 random_r 위치에 x돌을 둔다

    int l_score = cpu_chacksu(b->left);
    int r_score = cpu_chacksu(b->right);

    if (l_score >= r_score) //만약 왼쪽 자식 노드의 스코어의 총합이 같거나 크다면
        b->board[random_l] = 'x';   //왼쪽에 착수했던 방식대로 둔다
    else    //만약 오른쪽 자식 노드의 스코어의 총합이 크다면
        b->board[random_r] = 'x';   //오른쪽에 착수했던 방식대로 둔다
}