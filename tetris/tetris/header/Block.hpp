#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Random.hpp"

#define MINO_WIDTH 4
#define MINO_HEIGHT 4

/*----------
テトリスミノの形
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
ミノ毎のブロックの配置の設定
----------*/
void define_mino_shape(BLOCK_TYPE mino_shape[MINO_WIDTH][MINO_HEIGHT]) {
	/* 初期化 */
	for (int x = 0; x < MINO_WIDTH; x++) {
		for (int y = 0; y < MINO_HEIGHT; y++) {
			mino_shape[x][y] = EMPTY;
		}
	}
	/* ブロックの配置 */
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
テトリスミノの回転角
----------*/
typedef enum mino_angle {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MINO_ANGLE_MAX,
}MINO_ANGLE;

/*----------
テトリスミノのクラス
----------*/
class MINO {
private:
	/* ブロックの分布 */
	BLOCK_TYPE mino_shape[4][4];
	/* ブロックの角度 */
	MINO_ANGLE mino_angle;
	/* ブロックが落下中かどうか */
	bool falling;
public:
	/* ブロックの x・y 座標 */
	int x, y;

	/*----------
	コンストラクタ
	----------*/
	MINO(int _x, int _y) {
		/* ブロックの座標 */
		x = _x;
		y = _y;
		/* ブロックの角度 */
		mino_angle = UP;
		/* ブロックの形の設定 */
		define_mino_shape(mino_shape);
		/* ブロック落下 */
		falling = true;
	}

	/*----------
	ミノの回転
	----------*/
	void rotate() {
		/* 回転状態の更新 */
		mino_angle = MINO_ANGLE((mino_angle + 1) % MINO_ANGLE_MAX);
		/* 回転前のブロックの記録 */
		BLOCK_TYPE before[4][4];
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				before[x][y] = mino_shape[x][y];
			}
		}
		/* 回転によるブロックの位置の変更 */
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				mino_shape[x][y] = before[-y + MINO_WIDTH - 1][x];
			}
		}
	}

	/*----------
	ミノが対象座標に移動できるか
	----------*/
	bool can_move(FIELD field, int _x, int _y) {
		for (int x = 0; x < MINO_WIDTH; x++) {
			for (int y = 0; y < MINO_HEIGHT; y++) {
				/* フィールド上での x・y座標の計算 */
				int field_x = _x + 1 + x, field_y = _y + y;
				/* ブロックとブロック，ブロックと壁が重ならないか検査 */
				if (0 <= field_x && field_x <= FIELD_WIDTH) {
					if (mino_shape[x][y] == BLOCK && field.get_block_type(field_x, field_y) != EMPTY)
						return false;
				}
			}
		}
		return true;
	}

	/*----------
	フィールドにブロックを追加
	----------*/
	void add(FIELD& field) {
		for (int y, x = 0; x < MINO_WIDTH; x++) {
			for (y = 0; y < MINO_HEIGHT; y++) {
				/* フィールド上での x・y座標の計算 */
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
	落下終了
	----------*/
	bool is_fall() {
		return falling;
	}

	/*----------
	落下終了
	----------*/
	void fall() {
		falling = false;
	}
};

#endif