#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Random.hpp"

#define MINO_WIDTH 4
#define MINO_HEIGHT 4

/*----------
�e�g���X�~�m�̌`
----------*/
typedef enum mino_type {
	I,
	O,
	S,
	Z,
	J,
	L,
	T,
	MINO_TYPE_MAX,
}MINO_TYPE;

/*----------
�~�m���̃u���b�N�̔z�u�̐ݒ�
----------*/
void define_mino_shape(BLOCK_TYPE mino_shape[MINO_WIDTH][MINO_HEIGHT]) {
	/* ������ */
	for (int x = 0; x < MINO_WIDTH; x++) {
		for (int y = 0; y < MINO_HEIGHT; y++) {
			mino_shape[x][y] = EMPTY;
		}
	}
	/* �u���b�N�̔z�u */
	int mino_type = int(rnd() * (MINO_TYPE_MAX - 1e-6));
	switch (mino_type) {
	case(I):
		mino_shape[0][0] = BLOCK;
		mino_shape[0][1] = BLOCK;
		mino_shape[0][2] = BLOCK;
		mino_shape[0][3] = BLOCK;
		break;
	case(O):
		mino_shape[0][0] = BLOCK;
		mino_shape[1][0] = BLOCK;
		mino_shape[0][1] = BLOCK;
		mino_shape[1][1] = BLOCK;
		break;
	case(S):
		mino_shape[1][0] = BLOCK;
		mino_shape[2][0] = BLOCK;
		mino_shape[0][1] = BLOCK;
		mino_shape[1][1] = BLOCK;
		break;
	case(Z):
		mino_shape[0][0] = BLOCK;
		mino_shape[1][0] = BLOCK;
		mino_shape[1][1] = BLOCK;
		mino_shape[2][1] = BLOCK;
		break;
	case(J):
		mino_shape[1][0] = BLOCK; 
		mino_shape[1][1] = BLOCK; 
		mino_shape[0][2] = BLOCK; 
		mino_shape[1][2] = BLOCK; 
		break;
	case(L):
		mino_shape[0][0] = BLOCK;
		mino_shape[0][1] = BLOCK;
		mino_shape[0][2] = BLOCK;
		mino_shape[1][2] = BLOCK;
		break;
	case(T):
		mino_shape[1][0] = BLOCK;
		mino_shape[0][1] = BLOCK;
		mino_shape[1][1] = BLOCK;
		mino_shape[2][1] = BLOCK;
		break;
	default:
		cout << "Error Happen!" << endl;
		exit(0);
	}
}

/*----------
�e�g���X�~�m�̉�]�p
----------*/
typedef enum mino_angle {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MINO_ANGLE_MAX,
}MINO_ANGLE;

/*----------
�e�g���X�~�m�̃N���X
----------*/
class MINO {
private:
	/* �u���b�N�̕��z */
	BLOCK_TYPE mino_shape[4][4];
	/* �u���b�N�̊p�x */
	MINO_ANGLE mino_angle;
	/* �u���b�N�����������ǂ��� */
	bool falling;
public:
	/* �u���b�N�� x�Ey ���W */
	int x, y;

	/*----------
	�R���X�g���N�^
	----------*/
	MINO(int _x, int _y) {
		/* �u���b�N�̍��W */
		x = _x;
		y = _y;
		/* �u���b�N�̊p�x */
		mino_angle = UP;
		/* �u���b�N�̌`�̐ݒ� */
		define_mino_shape(mino_shape);
		/* �u���b�N���� */
		falling = true;
	}

	/*----------
	�~�m�̉�]
	----------*/
	void rotate() {
		/* ��]��Ԃ̍X�V */
		mino_angle = MINO_ANGLE((mino_angle + 1) % MINO_ANGLE_MAX);
		/* ��]�O�̃u���b�N�̋L�^ */
		BLOCK_TYPE before[4][4];
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				before[x][y] = mino_shape[x][y];
			}
		}
		/* ��]�ɂ��u���b�N�̈ʒu�̕ύX */
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				mino_shape[x][y] = before[-y + MINO_WIDTH - 1][x];
			}
		}
	}

	/*----------
	�~�m���Ώۍ��W�Ɉړ��ł��邩
	----------*/
	bool can_move(FIELD field, int _x, int _y) {
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				/* �t�B�[���h��ł� x�Ey���W�̌v�Z */
				int field_x = _x + 1 + x, field_y = _y + y;
				/* �u���b�N�ƃu���b�N�C�u���b�N�ƕǂ��d�Ȃ�Ȃ������� */
				if (0 <= field_x && field_x <= FIELD_WIDTH) {
					if (mino_shape[x][y] == BLOCK && field.get_block_type(field_x, field_y) != EMPTY)
						return false;
				}
			}
		}
		return true;
	}

	/*----------
	�t�B�[���h�Ƀu���b�N��ǉ�
	----------*/
	void add(FIELD& field) {
		for (int y, x = 0; x < MINO_WIDTH; x++) {
			for (y = 0; y < MINO_HEIGHT; y++) {
				/* �t�B�[���h��ł� x�Ey���W�̌v�Z */
				int field_x = this->x + 1 + x, field_y = this->y + y;
				if (0 <= field_x && field_x < FIELD_WIDTH) {
					if (mino_shape[x][y] == BLOCK) {
						field.set_block(field_x, field_y);
					}
				}
			}
		}
	}

	/*----------
	�����I��
	----------*/
	bool is_fall() {
		return falling;
	}

	/*----------
	�����I��
	----------*/
	void fall() {
		falling = false;
	}
};

#endif