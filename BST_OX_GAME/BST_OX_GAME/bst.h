#pragma once
#define _CRT_SECURE_NO_WARNINGS

//Board ����ü
typedef struct Board {
    char board[9];  //������
    int score;  //����
    struct Board* left;
    struct Board* right;
} Board;

//���忡 ������ ���� ��Ȳ�� ������ִ� �Լ�
void printBoard(Board* b);

//�÷��̾�κ��� ������ ��ġ�� �Է¹޾� ���� �����ϴ� �Լ�
process(Board* b);

//�������� ��Ȳ�� �о� �˸��� ���� ��ȯ�ϴ� �Լ�
int give_score(Board* b);

//������ ���� ��Ȳ�� �����ʰ� ���� �ڽ� ��忡 �����ϴ� �Լ�
void leftright(Board* b);

//��ǻ�Ͱ� ����Ʈ���� �����Ͽ� ���� �����ϴ� �Լ�
int cpu_chacksu(Board* b);

//��ǻ�Ͱ� ������ �� ���� ���ϴ� �Լ�
void first_child_node(Board* b);