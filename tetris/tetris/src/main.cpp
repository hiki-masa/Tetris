#include <time.h>
#include <conio.h>
#include "../header/Field.hpp"
#include "../header/Block.hpp"

/* �~�m�̏o���n�_ */
#define mino_start_x 5
#define mino_start_y 0

int main() {
	/* ��v�t�B�[���h�̍쐬 */
	FIELD Field;
	/* ���Ԃ̋L�^ */
	time_t now_time = time(NULL);
	/* �Q�[���I�[�o�[���� */
	bool game_over = true;
	while (game_over) {
		/* �~�m�̍쐬 */
		MINO Mino(mino_start_x, mino_start_y);

		while (Mino.is_fall()) {
			/* �L�[�{�[�h����̏��� */
			if (_kbhit()) {
				/* �\���p�t�B�[���h�̍쐬 */
				FIELD Display = Field;

				/* ���̓R�}���h���Ƃ̏��� */
				switch (_getch()) {
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('w'):
				case(0x48):
					break;
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('a'):
				case(0x4b):
					if (Mino.can_move(Display, Mino.x - 1, Mino.y))
						Mino.x--;
					break;
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('d'):
				case(0x4d):
					if (Mino.can_move(Display, Mino.x + 1, Mino.y))
						Mino.x++;
					break;
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('s'):
				case(0x50):
					if (Mino.can_move(Display, Mino.x, Mino.y + 1))
						Mino.y++;
					break;
					/* �uspace�v�������ꂽ�ꍇ�̏��� */
				case(0x20):
					MINO rotate = Mino;
					rotate.rotate();
					if (rotate.can_move(Display, rotate.x, rotate.y))
						Mino.rotate();
					break;
				}
				/* ����̔��f����ѕ\�� */
				Mino.add(Display);
				Display.display();
			}
			/* 1�b�o�� */
			if (now_time != time(NULL)) {
				/* ���Ԃ̍X�V */
				now_time = time(NULL);
				/* �\���p�t�B�[���h�̍쐬 */
				FIELD Display = Field;
				/* �����ł���ꍇ */
				if (Mino.can_move(Display, Mino.x, Mino.y + 1)) {
					/* �~�m�̗��� */
					Mino.y++;
					/* ���ʂ̔��f����ѕ\�� */
					Mino.add(Display);
					Display.display();
				}
				/* �����o���Ȃ��ꍇ */
				else {
					if (Mino.y == mino_start_y) {
						game_over = false;
					}
					/* ����������̏㏑�� */
					Mino.fall();
					/* �~�m���t�B�[���h�ɒǉ� */
					Mino.add(Field);
					/* ��̊m�F */
					Field.delete_row();
				}
			}
		}
	}
	cout << "Game Over" << endl;
}