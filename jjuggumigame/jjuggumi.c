// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

const int DIALOG_DURATION_SEC = 4;
int jjuggumi_init(void);

void dialog_1(const char message[]) {
	int remainingTime = DIALOG_DURATION_SEC;
	while (remainingTime >= 0) {
		system("cls");
		printf("%s\n", message);
		printf("Time remaining: %d seconds\n", remainingTime);
		Sleep(1000);
		remainingTime--;
	}
}

int intro() {
	printf(
		"    _         _           _    _                                               _  \n"
		"   (_)       (_)         | |  | |                                             | | \n"
		"    _   ___   _  _ __    | |_ | |__    ___       _ __   __ _  _ __ ___  ___   | | \n"
		"   | | / _ \\  | || '_ \\    | __|| '_ \\   /          |/ _` || '_ ` _\\ / _          | | \n"
		"   | || (_) || || | | |  |   |_ | | | ||__/      |(_| || (_| || | | | |||__/  |_|\n"
		"   | |  \\___/ |_||_| |_|    \\__||_| |_|  \\___|       \\__,||\\__,_||_| |_| |_|  \\__|  (_)\n"
		"  _/ |                                            __/ |                           \n"
		"  |__/                                           |___/                            \n"
	);
	Sleep(700);

	dialog("Welcome to the game! Enjoy the game to your heart's content!");

	return 0;
}


// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));
	gotoxy(10, 0);
	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i].is_alive = true;
		winer[i] = 0;
	}
	return 0;
}
void ending(void) {
	for (int i = 0; i < n_player; i++) {
		if (winer[i] == 1)
		{
			system("cls");
			printf("����ڴ� player%d �Դϴ�", i);

		}
	}

}



int main(void) {
	intro();
	jjuggumi_init();
	//sample();
	mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}