#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <stdlib.h>
using namespace std;

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

/*----------
�u���b�N�̗L��
----------*/
typedef enum block_type {
	WALL,
	BLOCK,
	EMPTY,
}BLOCK_TYPE;

/*----------
�t�B�[���h�N���X
----------*/
class FIELD {
private:
	/* �u���b�N�̏�Ԃ��i�[����z�� */
	BLOCK_TYPE field[FIELD_WIDTH][FIELD_HEIGHT];

	/*----------
	�u���b�N�̕\��
	----------*/
	void display_block(BLOCK_TYPE block) {
		switch (block) {
		case(WALL):
			cout << "��"; break;
		case(BLOCK):
			cout << "��"; break;
		case(EMPTY):
			cout << "�@"; break;
		default:
			cout << "Error Happen!" << endl; exit(0);
		}
	}

public:
	/*----------
	�R���X�g���N�^
	----------*/
	FIELD() {
		/* �t�B�[���h�̏����� */
		for (int x, y = 0; y < FIELD_HEIGHT; y++) {
			for (x = 0; x < FIELD_WIDTH; x++) {
				field[x][y] = WALL;
			}
		}
		for (int x, y = 0; y < FIELD_HEIGHT - 1; y++) {
			for (x = 1; x < FIELD_WIDTH - 1; x++) {
				field[x][y] = EMPTY;
			}
		}
	}

	/*----------
	�t�B�[���h�S�̂̕\��
	----------*/
	void display() {
		/* ��ʂ̃N���A */
		system("cls");
		/* �\�� */
		for (int x, y = 0; y < FIELD_HEIGHT; y++) {
			for (x = 0; x < FIELD_WIDTH; x++) {
				display_block(field[x][y]);
			}
			cout << endl;
		}
	}

	/*----------
	�w����W�̃u���b�N�̎�ނ��擾
	----------*/
	BLOCK_TYPE get_block_type(int x, int y) {
		return field[x][y];
	}

	/*----------
	�t�B�[���h�Ƀu���b�N��ݒu
	----------*/
	void set_block(int x, int y) {
		field[x][y] = BLOCK;
	}

	/*----------
	�u���b�N���P�񑵂������ǂ����̔���C����я���
	----------*/
	void delete_row() {
		for (int y = FIELD_HEIGHT - 2; y >= 0; y--) {
			/* �u���b�N���P�񑵂������ǂ����̔��� */
			bool checker = true;
			for (int x = 1; x < FIELD_WIDTH - 1; x++) {
				if (field[x][y] != BLOCK) {
					checker = false;
					break;
				}
			}
			/* �����Ă����̃u���b�N���폜 */
			if (checker == true) {
				/* �����Ă����̃u���b�N���폜 */
				for (int x = 1; x < FIELD_WIDTH - 1; x++) {
					field[x][y] = EMPTY;
				}
				/* �u���b�N�S�̂��ړ� */
				for (int _y = y - 1; _y > 0; _y--) {
					for (int x = 1; x < FIELD_WIDTH - 1; x++) {
						field[x][_y + 1] = field[x][_y];
					}
				}
				y = FIELD_HEIGHT - 1;
			}
		}
	}
};

#endif