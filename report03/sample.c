// sample.c（このプログラムの名前）
#include<stdio.h>      // 標準入出力ヘッダのインクルード
#include"ppmlib2.h"    // 画面表示部をカットした ppmlib.h
#include"makefname.c"  // 連番ファイル名の作成

//関数のプロトタイプ宣言（makefname.c中の関数）
void make_filename( char head[], int keta, int num, char fname[] );

// main関数の始まり
int main(void)
{
    int i;              // i:入力ファイル番号
    char fname[256];    // ファイル名用配列（入出力兼用）
    int x,y,col;        // 制御変数

    printf("原画像のフレーム org00001.ppm～org00010.ppm を反転させます\n");
    for(i=1;i<=10;i++){
        // 連番のファイル名を生成（org00001.ppm～org00010.ppm）
        make_filename( "org", 5, i, fname );   // 5:数字の桁数
        // 画像をNo.0に読み込む
        load_color_image( 0, fname );
        // 画像を反転させる
        for(y=0;y<height[0];y++){
            for(x=0;x<width[0];x++){
                for(col=0;col<3;col++){
                    image[0][x][y][col] = 255 - image[0][x][y][col];
                }
            }
        }
        // 出力ファイル名（out00001.ppm～out00010.ppm）を作る
        make_filename( "out", 5, i, fname );
        // 画像の保存
        save_color_image( 0, fname );
    }
    printf("結果画像を out00001.ppm～out00010.ppm で出力しました\n");
    return 0;  // プログラムの正常終了
}
