#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <stdlib.h>
using namespace std;

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

/*----------
ブロックの有無
----------*/
typedef enum block_type {
	WALL,
	BLOCK,
	EMPTY,
}BLOCK_TYPE;

/*----------
フィールドクラス
----------*/
class FIELD {
private:
	/* ブロックの状態を格納する配列 */
	BLOCK_TYPE field[FIELD_WIDTH][FIELD_HEIGHT];

	/*----------
	ブロックの表示
	----------*/
	void display_block(BLOCK_TYPE block) {
		switch (block) {
		case(WALL):
			cout << "■"; break;
		case(BLOCK):
			cout << "□"; break;
		case(EMPTY):
			cout << "　"; break;
		default:
			cout << "Error Happen!" << endl; exit(0);
		}
	}

public:
	/*----------
	コンストラクタ
	----------*/
	FIELD() {
		/* フィールドの初期化 */
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
	フィールド全体の表示
	----------*/
	void display() {
		/* 画面のクリア */
		system("cls");
		/* 表示 */
		for (int x, y = 0; y < FIELD_HEIGHT; y++) {
			for (x = 0; x < FIELD_WIDTH; x++) {
				display_block(field[x][y]);
			}
			cout << endl;
		}
	}

	/*----------
	指定座標のブロックの種類を取得
	----------*/
	BLOCK_TYPE get_block_type(int x, int y) {
		return field[x][y];
	}

	/*----------
	フィールドにブロックを設置
	----------*/
	void set_block(int x, int y) {
		field[x][y] = BLOCK;
	}

	/*----------
	ブロックが１列揃ったかどうかの判定，および処理
	----------*/
	void delete_row() {
		for (int y = FIELD_HEIGHT - 2; y >= 0; y--) {
			/* ブロックが１列揃ったかどうかの判定 */
			bool checker = true;
			for (int x = 1; x < FIELD_WIDTH - 1; x++) {
				if (field[x][y] != BLOCK) {
					checker = false;
					break;
				}
			}
			/* 揃っている列のブロックを削除 */
			if (checker == true) {
				/* 揃っている列のブロックを削除 */
				for (int x = 1; x < FIELD_WIDTH - 1; x++) {
					field[x][y] = EMPTY;
				}
				/* ブロック全体を移動 */
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