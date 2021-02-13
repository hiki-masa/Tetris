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
	/* �~�m�̍쐬 */
	MINO Falling_Mino(mino_start_x, mino_start_y);
	while (game_over) {
		/* ���̃~�m�̍쐬 */
		MINO Next_Mino(mino_start_x, mino_start_y);

		while (Falling_Mino.is_fall()) {
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
					if (Falling_Mino.can_move(Display, Falling_Mino.x - 1, Falling_Mino.y))
						Falling_Mino.x--;
					break;
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('d'):
				case(0x4d):
					if (Falling_Mino.can_move(Display, Falling_Mino.x + 1, Falling_Mino.y))
						Falling_Mino.x++;
					break;
					/* �u���v�������ꂽ�ꍇ�̏��� */
				case('s'):
				case(0x50):
					if (Falling_Mino.can_move(Display, Falling_Mino.x, Falling_Mino.y + 1))
						Falling_Mino.y++;
					break;
					/* �uspace�v�������ꂽ�ꍇ�̏��� */
				case(0x20):
					MINO rotate = Falling_Mino;
					rotate.rotate();
					if (rotate.can_move(Display, rotate.x, rotate.y))
						Falling_Mino.rotate();
					break;
				}
				/* ����̔��f */
				Falling_Mino.add(Display);
				/* �t�B�[���h�C���̃~�m�̕\�� */
				Display.display_field();
				Next_Mino.display_mino("Next");
			}
			/* 1�b�o�� */
			if (now_time != time(NULL)) {
				/* ���Ԃ̍X�V */
				now_time = time(NULL);
				/* �\���p�t�B�[���h�̍쐬 */
				FIELD Display = Field;
				/* �����ł���ꍇ */
				if (Falling_Mino.can_move(Display, Falling_Mino.x, Falling_Mino.y + 1)) {
					/* �~�m�̗��� */
					Falling_Mino.y++;
					/* ���ʂ̔��f */
					Falling_Mino.add(Display);
					/* �t�B�[���h�C���̃~�m�̕\�� */
					Display.display_field();
					Next_Mino.display_mino("Next");
				}
				/* �����o���Ȃ��ꍇ */
				else {
					if (Falling_Mino.y == mino_start_y) {
						game_over = false;
					}
					/* ����������̏㏑�� */
					Falling_Mino.fall();
					/* �~�m���t�B�[���h�ɒǉ� */
					Falling_Mino.add(Field);
					/* ��̊m�F */
					Field.delete_row();
				}
			}
		}

		/* ���̃~�m�𗎉��ΏۂɕύX */
		Falling_Mino = Next_Mino;
	}
	cout << "Game Over" << endl;
}