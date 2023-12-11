#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10
#define ITEM_MAX		10

int winer[PLAYER_MAX];
// �⺻�� true, Ż���ϸ� false
int n_player, n_alive;
int tick;  // �ð�


typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
} ITEM;

ITEM item[ITEM_MAX];
typedef struct {
	int id;
	char name[100];
	//�ɷ�ġ: ����, ��, ���¹̳�
	int intel, str, stamina;

	//���� ����
	bool is_alive;
	bool hasitem;
	ITEM item;
} PLAYER;

PLAYER player[PLAYER_MAX];


// �̴ϰ���
//void sample(void);
void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif