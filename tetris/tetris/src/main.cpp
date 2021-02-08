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
	while (game_over) {
		/* ミノの作成 */
		MINO Mino(mino_start_x, mino_start_y);

		while (Mino.is_fall()) {
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
					if (Mino.can_move(Display, Mino.x - 1, Mino.y))
						Mino.x--;
					break;
					/* 「→」を押された場合の処理 */
				case('d'):
				case(0x4d):
					if (Mino.can_move(Display, Mino.x + 1, Mino.y))
						Mino.x++;
					break;
					/* 「↓」を押された場合の処理 */
				case('s'):
				case(0x50):
					if (Mino.can_move(Display, Mino.x, Mino.y + 1))
						Mino.y++;
					break;
					/* 「space」を押された場合の処理 */
				case(0x20):
					MINO rotate = Mino;
					rotate.rotate();
					if (rotate.can_move(Display, rotate.x, rotate.y))
						Mino.rotate();
					break;
				}
				/* 操作の反映および表示 */
				Mino.add(Display);
				Display.display();
			}
			/* 1秒経過 */
			if (now_time != time(NULL)) {
				/* 時間の更新 */
				now_time = time(NULL);
				/* 表示用フィールドの作成 */
				FIELD Display = Field;
				/* 落下できる場合 */
				if (Mino.can_move(Display, Mino.x, Mino.y + 1)) {
					/* ミノの落下 */
					Mino.y++;
					/* 結果の反映および表示 */
					Mino.add(Display);
					Display.display();
				}
				/* 落下出来ない場合 */
				else {
					if (Mino.y == mino_start_y) {
						game_over = false;
					}
					/* 落下中判定の上書き */
					Mino.fall();
					/* ミノをフィールドに追加 */
					Mino.add(Field);
					/* 列の確認 */
					Field.delete_row();
				}
			}
		}
	}
	cout << "Game Over" << endl;
}