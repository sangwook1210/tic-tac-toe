#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

char user = 'o';    //�÷��̾ ���� ���� o�̴�
char com = 'x';     //��ǻ�Ͱ� ���� ���� x�̴�

//���忡 ������ ���� ��Ȳ�� ������ִ� �Լ�
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

//�÷��̾�κ��� ������ ��ġ�� �Է¹޾� ���� �����ϴ� �Լ�
process(Board* b) {
    int userPos = 0;
    while (1) {
        printf("���� ���� ��ȣ�� �Է����ּ���: ");
        userPos = 0;    //�÷��̾�κ��� ���� ���� ��ȣ�� �Է¹��� ����
        int result = scanf_s("%d", &userPos);

        if (userPos >= 1 && userPos <= 9) { //�÷��̾��� �ùٸ� �Է�
            if (b->board[userPos - 1] == 'o' || b->board[userPos - 1] == 'x') { //�÷��̾ �Է��� ���� �̹� ���� ���� ���
                printf("�װ����� �̹� ���� �ֽ��ϴ�. �ٽ� �Է����ּ���.\n\n");
            }
            else {  //�÷��̾ �Է��� ���� ���� ���� ���
                b->board[userPos - 1] = user;
                break;
            }
        }
        else {  //�÷��̾��� �߸��� �Է�
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n\n");
            rewind(stdin);  //ǥ�� �Է� ���ۿ� ����� ��� ���ڸ� ����
        }
    }
}

//�������� ��Ȳ�� �о� �˸��� ���� ��ȯ�ϴ� �Լ�
int give_score(Board* b) {
    //��ǻ�Ͱ� �� ���� �ϼ������� ��� 1�� ��ȯ
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

    //�÷��̾ �� ���� �ϼ������� ��� -1�� ��ȯ
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

    //�� �̻� �� ���� ��� ��� ��� 0�� ��ȯ
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

    //���� �ǰ����� ���� ���� ��� 2�� ��ȯ
    else
        return 2;
}

//������ ���� ��Ȳ�� �����ʰ� ���� �ڽ� ��忡 �����ϴ� �Լ�
void leftright(Board* b) {
    for (int i = 0; i < 9; i++) {
        b->left->board[i] = b->board[i];
        b->right->board[i] = b->board[i];
    }
}

//��ǻ�Ͱ� ����Ʈ���� �����Ͽ� ���� �����ϴ� �Լ�
int cpu_chacksu(Board* b) {
    srand(time(NULL));
    int random_l = 100, random_r = 100; //���� �ڽ� ��忡�� ���� �ڸ��� ������ �ڽ� ��忡�� ���� �ڸ�
    int cnt = 0;    //���� �� ������ ������ ������ ����

    //���� �� ������ ������ ����
    for (int i = 0; i < 9; i++) {
        if (b->board[i] == ' ')
            cnt++;
    }

    //���� �ڽ� ����� ���� ��� ��ġ�� ���� ������ ����
    while (1) {
        if (cnt == 0)   //�ǿ� �� ������ �ϳ��� ���ٸ�
            break;  //random_l�� �������� �ʴ´�
        else {
            random_l = rand() % 9;  //random_l ����
            if (b->board[random_l] == 'o' || b->board[random_l] == 'x') //���� random_l�� �̹� ���� �ִٸ�
                continue;   //random_l�� �ٽ� �����Ѵ�
            else
                break;
        }
    }

    //������ �ڽ� ����� ���� ��� ��ġ�� ���� ������ ����
    while (1) {
        if (cnt == 0 || cnt == 1)   //�ǿ� �� ������ �ϳ��� ���ų� �ǿ� �� ������ �ϳ��ۿ� ���ٸ�
            break;  //random_r�� �������� �ʴ´�
        else {
            random_r = rand() % 9;  //random_r����
            if (random_r == random_l || b->board[random_r] == 'o' || b->board[random_r] == 'x') //���� random_r�� random_l�� ���ų� random_r�� �̹� ���� �ִٸ�
                continue;   //random_r�� �ٽ� �����Ѵ�
            else
                break;
        }
    }

    //b�� left�� right ���� ����
    b->left = malloc(sizeof(Board));
    b->right = malloc(sizeof(Board));

    //���� ���� �ºΰ� ���� �ʾҴٸ�
    if (give_score(b) == 2) {
        //������� ���� o�� x�� ������ ���� ������ ���� �������� ����Ѵ�.
        int o_num = 0;
        int x_num = 0;
        for (int i = 0; i < 9; i++) {
            if (b->board[i] == 'o')
                o_num++;
            else if (b->board[i] == 'x')
                x_num++;
        }

        //��ǻ�Ͱ� ���� ����
        if (o_num > x_num) {
            //b�� ���� b->left�� b->right�� ����
            leftright(b);

            //random_r�� �������� �ʾҴٸ�
            if (random_r == 100) {
                b->left->board[random_l] = 'x'; //b->left�� ������ random_l ��ġ�� x���� �д�
                cpu_chacksu(b->left);   //cpu_chacksu�� �ٽ� ���� (b->left�� �� �� ���̴�)
            }
            else {
                b->left->board[random_l] = 'x'; //b->left�� ������ random_l ��ġ�� x���� �д�
                b->right->board[random_r] = 'x';    //b->right�� ������ random_r ��ġ�� x���� �д�

                int score_l = cpu_chacksu(b->left); //cpu_chacksu(b->left)���� ��ȯ�� ���� score_l�� ����
                int score_r = cpu_chacksu(b->right);    //cpu_chacksu(b->right)���� ��ȯ�� ���� score_r�� ����

                return score_l + score_r;   //give_score�� 2��� left�� right�� ���ھ ��ģ��
            }
        }

        //�÷��̾��� ���� ��ǻ�Ͱ� ���� ����
        else if (o_num == x_num) {
            //b�� ���� b->left�� b->right�� ����
            leftright(b);

            //random_r�� �������� �ʾҴٸ�
            if (random_r == 100) {
                b->left->board[random_l] = 'o'; //b->left�� ������ random_l ��ġ�� o���� �д�
                cpu_chacksu(b->left); //cpu_chacksu�� �ٽ� ����(b->left�� �� �� ���̴�)
            }
            else {
                b->left->board[random_l] = 'o'; //b->left�� ������ random_l ��ġ�� o���� �д�
                b->right->board[random_r] = 'o';    //b->right�� ������ random_r ��ġ�� o���� �д�


                int score_l = cpu_chacksu(b->left); //cpu_chacksu(b->left)���� ��ȯ�� ���� score_l�� ����
                int score_r = cpu_chacksu(b->right);    //cpu_chacksu(b->right)���� ��ȯ�� ���� score_r�� ����

                return score_l + score_r;   //give_score�� 2��� left�� right�� ���ھ ��ģ��
            }
        }
    }

    //���� �ºΰ� �����������ٸ�
    else {
        b->score = give_score(b);   //score�� 2�� �ƴ϶�� give_score�� score
        return b->score;
    }
}

//��ǻ�Ͱ� ������ �� ���� ���ϴ� �Լ�
void first_child_node(Board* b) {
    srand(time(NULL));
    int random_l = 100, random_r = 100; //���� �ڽ� ��忡�� ���� �ڸ��� ������ �ڽ� ��忡�� ���� �ڸ�
    int cnt = 0;    //���� �� ������ ������ ������ ����
    for (int i = 0; i < 9; i++) {
        if (b->board[i] == ' ')
            cnt++;
    }

    //���� �ڽ� ����� ���� ��� ��ġ�� ���� ������ ����
    while (1) {
        if (cnt == 0)   //�ǿ� �� ������ �ϳ��� ���ٸ�
            break;  //random_l�� �������� �ʴ´�
        else {
            random_l = rand() % 9;  //random_l ����
            if (b->board[random_l] == 'o' || b->board[random_l] == 'x') //���� random_l�� �̹� ���� �ִٸ�
                continue;   //random_l�� �ٽ� �����Ѵ�
            else
                break;
        }
    }

    //������ �ڽ� ����� ���� ��� ��ġ�� ���� ������ ����
    while (1) {
        if (cnt == 0 || cnt == 1)   //�ǿ� �� ������ �ϳ��� ���ų� �ǿ� �� ������ �ϳ��ۿ� ���ٸ�
            break;  //random_r�� �������� �ʴ´�
        else {
            random_r = rand() % 9;  //random_r����
            if (random_r == random_l || b->board[random_r] == 'o' || b->board[random_r] == 'x') //���� random_r�� random_l�� ���ų� random_r�� �̹� ���� �ִٸ�
                continue;   //random_r�� �ٽ� �����Ѵ�
            else
                break;
        }
    }

    //b�� left�� right ���� ����
    b->left = malloc(sizeof(Board));
    b->right = malloc(sizeof(Board));

    //b�� ���� b->left�� b->right�� ����
    leftright(b);

    b->left->board[random_l] = 'x'; //b->left�� ������ random_l ��ġ�� x���� �д�
    b->right->board[random_r] = 'x';    //b->right�� ������ random_r ��ġ�� x���� �д�

    int l_score = cpu_chacksu(b->left);
    int r_score = cpu_chacksu(b->right);

    if (l_score >= r_score) //���� ���� �ڽ� ����� ���ھ��� ������ ���ų� ũ�ٸ�
        b->board[random_l] = 'x';   //���ʿ� �����ߴ� ��Ĵ�� �д�
    else    //���� ������ �ڽ� ����� ���ھ��� ������ ũ�ٸ�
        b->board[random_r] = 'x';   //�����ʿ� �����ߴ� ��Ĵ�� �д�
}