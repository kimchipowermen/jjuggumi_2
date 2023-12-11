#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
/*
* �ؾ�����: 1. Ż�� �˰��� �ϼ�( dialog �� ���)
*           2. ���� �������� ���
*           3. q ��� ������
*           4. �Ѹ� ������ ��� ����
*/
#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void sample_init(void);
void move_manual(key_t key);
void move_random(int i, int dir);
void move_tail(int i, int nx, int ny);
void camera(int x);
void observe(int see);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
int px_log[PLAYER_MAX], py_log[PLAYER_MAX], player_rand[PLAYER_MAX];//������ ������ �α�, �÷��̾� �̵�Ȯ��
bool gameover[PLAYER_MAX];
int loop;


int random_move;
int random_x, random_y;

void sample_init(void) {
	map_init(12, 70);
	loop = 1;
	int x, y;
	for (int i = 0; i < n_player; i++) {
		gameover[i] = true;
		y = N_COL - 2;
		// ���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);

		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 300);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}

void camera(int x) {//���� ����
	if (x == 1) {
		for (int i = 4; i < 8; i++) {
			back_buf[i][2] = '#';
		}
	}
	else if (x == 0) {
		for (int i = 4; i < 8; i++) {
			back_buf[i][2] = '@';
		}
	}
}

void move(void) {//������ ���� Ȯ��
	random_move = randint(1, 10);
	if (random_move <= 1) {//������ ����Ȯ�� 10%
		random_x = 0;
		random_y = 0;
	}
	else if (random_move <= 2) {// �Ʒ��� ������ Ȯ��10%
		random_x = 0;
		random_y = 1;
	}
	else if (random_move <= 3) {// ���� �ö� Ȯ��10%
		random_x = 0;
		random_y = -1;
	}
	else {//�������� �̵��� Ȯ�� 70%
		random_x = -1;
		random_y = 0;
	}
}

void observe(int see) {
	if (see = 1) {//���� ������ ������ �Լ�

		for (int i = 1; i < n_player; i++) {//���� ������ ai������
			if (gameover[i] == true && tick % period[i] == 0) {
				move();
				move_random(i, -1);
			}
		}
	}
	else if (see = 0) {//���� ���� ai������
		for (int i = 1; i < n_player; i++) {
			if (gameover[i] == true && player_rand[i] == 1) {
				move();
				move_random(i, -1);
			}
		}
	}
}

int save[PLAYER_MAX];//
void stop(void) {
	for (int i = 0; i < n_player; i++) {
		px_log[i] = px[i];
		py_log[i] = py[i];
	}
}
void stop_chack(void) {//���� ���� �����ϰ�� ��Ƴ��� ����
	for (int i = 0; i < n_player; i++) {
		for (int j = i + 1; j < n_player; j++) {
			if (py_log[i] == py_log[j] && px_log[i] > px_log[j]) {
				save[i] = 0;//���� ���ɼ� ����
				break;
			}
			else {
				save[i] = 1;//���ɼ� ����
			}
		}
	}
	for (int i = 7; i >= 0; i--) {
		if (py_log[8] == py_log[i] && px_log[8] > px_log[i]) {
			save[8] = 0;//���� ���ɼ� ����
			break;
		}
		else {
			save[8] = 1;//���ɼ� ����
		}

	}
}

int dead_player[PLAYER_MAX];
void kill_player(void) {
	for (int i = 0; i < n_player; i++) {
		if (save[i] == 1) {
			if (px[i] != px_log[i] || py[i] != py_log[i]) {
				gameover[i] = false;
				player[i].is_alive = false;
				dead_player[i] = i;
				n_alive--;
			}
		}
	}
}

void move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}

// 0 <= dir < 4�� �ƴϸ� ����
void move_random(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�
	int attempt = 0;

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
	do {
		nx = px[p] + random_y;
		ny = py[p] + random_x;
		attempt++;
		if (attempt > 3) {
			// ��� ���� �õ� �Ŀ��� �̵� ������ ������ ã�� ���ϸ� ��ȯ
			return;
		}
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]�� ���
void move_tail(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void win(void) {
	for (int i = 0; i < n_player; i++) {
		if (px[i] > 4 && px[i] < 8) {
			if (py[i] == 3) {
				char message[50];
				snprintf(message, sizeof(message), "player%d win", i);
				dialog(message, 5);
				winer[i] = 1;
				loop = 0;
			}
		}
		else if (px[i] == 3 || px[i] == 8) {
			if (py[i] == 2) {
				char message[50];
				snprintf(message, sizeof(message), "player%d win", i);
				dialog(message, 5);
				winer[i] = 1;
				loop = 0;
			}
		}
	}
}

void mugung(void) {
	if (tick == 10) {
		gotoxy(N_ROW + 1, 0);
		printf("��");

	}
	else if (tick == 100) {
		gotoxy(N_ROW + 1, 0);
		printf("����");
	}
	else if (tick == 300) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ");
	}
	else if (tick == 600) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ��");
	}
	else if (tick == 1000) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ����");
	}
	else if (tick == 1700) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� ��");
	}
	else if (tick == 2000) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ�");
	}
	else if (tick == 2200) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ���");
	}
	else if (tick == 2300) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ�����");
	}
	else if (tick == 2380) {
		gotoxy(N_ROW + 1, 0);
		printf("����ȭ���� �Ǿ����ϴ�");
		camera(0);
		for (int i = 0; i < n_player; i++) {
			player_rand[i] = randint(1, 10);
		}
	}
	else if (tick == 5380) {
		for (int i = 0; i < n_player; i++) {
			if (player[i].is_alive == false) {
				char message[50];
				snprintf(message, sizeof(message), "player%d dead", i);
				dialog(message, 1);
			}
		}
		for (int i = 0; i < 20; i++) {
			gotoxy(N_ROW + 1, i);
			printf(" ");
			tick = 0;
			camera(1);
		}
	}

}

void mugunghwa(void) {
	sample_init();
	camera(1);

	system("cls");
	display();
	while (loop) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (tick % 20 == 0 && player[0].is_alive == true) {
			if (key == K_QUIT) {
				break;
			}
			else if (key != K_UNDEFINED) {
				move_manual(key);
			}
		}
		mugung();

		if (tick <= 3480) {
			observe(1);
		}
		else if (tick > 3480) {
			observe(0);
			stop_chack();
			kill_player();

		}

		stop();
		//dialog("hello");
		// player 1 ���ʹ� �������� ������(8����)
		if (n_alive == 1) {
			for (int i = 0; i < n_player; i++) {
				if (player[i].is_alive == true) {
					char message[50];
					snprintf(message, sizeof(message), "player %d win", i);
					dialog(message, 4);
					winer[i] = 1;
					loop = 0;
				}
			}
		}

		win();
		display();
		Sleep(10);
		tick += 10;
	}
}