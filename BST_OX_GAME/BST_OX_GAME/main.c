#include "bst.h"

int main() {
    Board* b = malloc(sizeof(Board));   //���� ����

    for (int i = 0; i < 9; i++) //���� �ʱ�ȭ
        b->board[i] = ' ';

    printBoard(b);  //���� ���
    int turn = 0;   //�÷��̾��� �������� ��ǻ���� �������� �����ϴ� ����

    while (1) {
        if (turn % 2 == 0) {    //turn�� 2�� ���� �������� 0�̶�� �÷��̾��� ����
            process(b);
            printBoard(b);
        }

        else {  //�ƴ϶�� ��ǻ���� ����
            first_child_node(b);
            printBoard(b);
        }

        if (give_score(b) == 1) {   //give_score�� 1�̶�� �÷��̾��� �й�
            printf("����� �й��Դϴ�.\n");
            break;
        }

        else if (give_score(b) == -1) { //give_score�� -1�̶�� �÷��̾��� �¸�
            printf("�����մϴ�! ����� �¸��Դϴ�.\n");
            break;
        }

        else if (give_score(b) == 0) {  ////give_score�� 0�̶�� ���º�
            printf("���º��Դϴ�.\n");
            break;
        }
        turn++; //���� ����
    }
}