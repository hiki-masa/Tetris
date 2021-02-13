#include <time.h>
#include <conio.h>
#include "../header/Field.hpp"
#include "../header/Block.hpp"

/* ミノの出現地点 */
#define mino_start_x 5
#define mino_start_y 0

int main() {
	/* 主要フィールドの作成 */
	FIELD Field;
	/* 時間の記録 */
	time_t now_time = time(NULL);
	/* ゲームオーバー判定 */
	bool game_over = true;
	/* ミノの作成 */
	MINO Falling_Mino(mino_start_x, mino_start_y);
	while (game_over) {
		/* 次のミノの作成 */
		MINO Next_Mino(mino_start_x, mino_start_y);

		while (Falling_Mino.is_fall()) {
			/* キーボード操作の処理 */
			if (_kbhit()) {
				/* 表示用フィールドの作成 */
				FIELD Display = Field;

				/* 入力コマンドごとの処理 */
				switch (_getch()) {
					/* 「↑」を押された場合の処理 */
				case('w'):
				case(0x48):
					break;
					/* 「←」を押された場合の処理 */
				case('a'):
				case(0x4b):
					if (Falling_Mino.can_move(Display, Falling_Mino.x - 1, Falling_Mino.y))
						Falling_Mino.x--;
					break;
					/* 「→」を押された場合の処理 */
				case('d'):
				case(0x4d):
					if (Falling_Mino.can_move(Display, Falling_Mino.x + 1, Falling_Mino.y))
						Falling_Mino.x++;
					break;
					/* 「↓」を押された場合の処理 */
				case('s'):
				case(0x50):
					if (Falling_Mino.can_move(Display, Falling_Mino.x, Falling_Mino.y + 1))
						Falling_Mino.y++;
					break;
					/* 「space」を押された場合の処理 */
				case(0x20):
					MINO rotate = Falling_Mino;
					rotate.rotate();
					if (rotate.can_move(Display, rotate.x, rotate.y))
						Falling_Mino.rotate();
					break;
				}
				/* 操作の反映 */
				Falling_Mino.add(Display);
				/* フィールド，次のミノの表示 */
				Display.display_field();
				Next_Mino.display_mino("Next");
			}
			/* 1秒経過 */
			if (now_time != time(NULL)) {
				/* 時間の更新 */
				now_time = time(NULL);
				/* 表示用フィールドの作成 */
				FIELD Display = Field;
				/* 落下できる場合 */
				if (Falling_Mino.can_move(Display, Falling_Mino.x, Falling_Mino.y + 1)) {
					/* ミノの落下 */
					Falling_Mino.y++;
					/* 結果の反映 */
					Falling_Mino.add(Display);
					/* フィールド，次のミノの表示 */
					Display.display_field();
					Next_Mino.display_mino("Next");
				}
				/* 落下出来ない場合 */
				else {
					if (Falling_Mino.y == mino_start_y) {
						game_over = false;
					}
					/* 落下中判定の上書き */
					Falling_Mino.fall();
					/* ミノをフィールドに追加 */
					Falling_Mino.add(Field);
					/* 列の確認 */
					Field.delete_row();
				}
			}
		}

		/* 次のミノを落下対象に変更 */
		Falling_Mino = Next_Mino;
	}
	cout << "Game Over" << endl;
}