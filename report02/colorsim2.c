// colorsim.c（このプログラムの名前)
#include <stdio.h>   // 標準入出力ヘッダのインクルード
#include "ppmlib.h"  // ppmファイル用ヘッダのインクルード
#include "label.h"   // ラベリング用ヘッダのインクルード

#define RMIN 0.0001   // 領域面積の下限(=0.01%)
#define RMAX 0.3    // 領域面積の上限(=30%)

int main(void)
{
        int x,y; // 座標用の制御変数
        int number; // 孤立領域の総数
        int add_hsv[3];// 加える値(配列に変更)
        int i;   // ラベル用の制御変数
        int area; // 領域の面積
        int count; // 最終的に残った領域の総数
        int xmin,ymin,xmax,ymax;  // ラベルの領域
        double ratio; // 面積率
        int color; // 作業変数

        printf("==== カラーシミュレーター =====\n");
        printf("原画像(ppm(バイナリ)形式)を読み込みます\n");
        load_color_image(0,""); // ファイル → 画像No.0 への読み込み
        copy_color_image(0,1); // 画像No.0 → 画像No.1 へコピー


        int max;
        int min;
        int max_num;
        int c;
        int a,b;





        // 処理１：画像No.1 の目標の色の画素を青色で抽出します
        printf("\n処理１：目標の色の画素を青色で抽出します．\n");
        // ********************************************************************
        // ここに，画像No.1の画素の色が，原画像(No.0)の色変更対象領域なら青（R=
        // G=0,B=255），そうでないなら白（R=G=B=255）にする処理を書いて下さい．
        // 条件式は対象とする原画像に依存します．つまり，ここでの選別は，自分で
        // 選んだ原画像だけに有効で，他の画像には使えないもので良いです．
        // ********************************************************************

        for(y=0; y<height[0]; y++) {
                for(x=0; x<width[0]; x++) {
                        if(((image[0][x][y][0]>140) && (image[0][x][y][1]<60) && (image[0][x][y][2]<60)) /* || ((image[0][x][y][0]>100) && (image[0][x][y][1]<50) && (image[0][x][y][2]<50))*/) {
                                image[1][x][y][0]=0;
                                image[1][x][y][1]=0;
                                image[1][x][y][2]=255;
                        }else{
                                image[1][x][y][0]=255;
                                image[1][x][y][1]=255;
                                image[1][x][y][2]=255;
                        }
                }
        }



        printf("原画像の目標色の画素を青色にした画像を mask1.ppm で保存します．\n");
        save_color_image( 1, "mask1.ppm" );

        // 処理２：ラベリング
        printf("\n処理２：目標色の領域のラベリングを行ないます．\n");
        printf("ラベリング中です．個数が多いと時間がかかります...\n");
        // ********************************************************************
        // 関数 labeling( ) を使って，画像No.1 を背景画素の色を白（R=G=B=255)と
        // してラべリングを行ない，孤立領域の総数を変数 number に代入する記述を
        // 補って下さい．たった１行だけです．
        // ********************************************************************

        number=labeling(1,255,255,255);

        printf("終了しました．孤立領域の総数＝%d個\n",number);
        if ( number == 0 ) {
                printf("該当する領域がないので終了します．\n");
                exit(1);
        }



        // 処理３：面積で選別する
        printf("\n処理３：目標色の領域の面積で選別します．\n");
        printf("面積が範囲外のものは白画素にします.\n");
        count = number;
        // ラベル=1 から number までを調べる
        for(i=1; i<=number; i++) {
                // ****************************************************************
                // まず，ラベル i の領域の面積 area を求めましょう．
                // その際，同時にその領域の x, y の範囲（xmin,ymin)<--->(xmax,ymax)
                // も求めておきましょう（後の走査を高速化するためです）．ここで，
                // (xmin,ymin)：ラベル i の領域の左上の座標
                // (xmax,ymax)：ラベル i の領域の右下の座標
                // 次に面積率 ratio を求めましょう．ここでの面積率とは，area を画像
                // 全体の面積で割ったものです．すなわち，0.0～1.0の実数値になります．
                // 次にその ratio の値の範囲（プログラムの冒頭の define文で定義され
                // ています．この例では 1%以上30%以下です）ではない画素を白にします．
                // この処理は既に次に書かれていますので作らなくて結構です．
                // ****************************************************************

                //それぞれの変数を初期化
                xmin=width[1]-1;
                xmax=0;
                ymin=height[1];
                ymax=0;
                area=0;

                for(y=0; y<height[1]; y++) {
                        for(x=0; x<width[1]; x++) {
                                if(label[x][y]==i) {
                                        if(x<xmin) {
                                                xmin=x;
                                        }
                                        if(x>xmax) {
                                                xmax=x;
                                        }
                                        if(y<ymin) {
                                                ymin=y;
                                        }
                                        if(y>ymax) {
                                                ymax=y;
                                        }

                                        area++;

                                }
                        }
                }

                ratio=((double)area/((double)width[1]*(double)height[1]));

                if (( ratio < RMIN || ratio > RMAX ) || ymax<550) {//この後ろの条件は赤が口紅にも反応してしまい、面積での区別はできなかったので、位置で区別するためのものである
                        // 面積が該当しない場合は青画素を白画素へ変更する
                        count--;
                        for(y=ymin; y<=ymax; y++) {
                                for(x=xmin; x<=xmax; x++) {
                                        if ( label[x][y] == i ) {
                                                // 白画素へ変更する
                                                image[1][x][y][0] = 255;
                                                image[1][x][y][1] = 255;
                                                image[1][x][y][2] = 255;
                                        }
                                }
                        }
                }
        }
        printf("終了しました．該当した孤立領域の総数＝%d個\n",count);
        if ( count > 0 ) {
                printf("該当領域を青色にした画像を mask2.ppm で保存します．\n");
                save_color_image( 1, "mask2.ppm" );
        } else {
                printf("該当する領域が残らなかったので終了します．\n");
                exit(1);
        }


        //rgb→hsv
        for(y=0; y<height[0]; y++) {
                for(x=0; x<width[0]; x++) {
                        max=0;
                        min=255;
                        max_num=-1;
                        for(int j=0; j<3; j++) {
                                if(max<image[0][x][y][j]) {
                                        max=image[0][x][y][j];
                                        max_num=j;
                                }
                                if(min>image[0][x][y][j]) {
                                        min=image[0][x][y][j];
                                }
                        }
                        hsv[0][x][y][2]=max;
                        if(max==0) {
                                hsv[0][x][y][0]=0;
                                hsv[0][x][y][1]=0;
                        }
                        else{
                                hsv[0][x][y][1]=(int)(255*((double)(max-min)/max));
                                if(max==min) {
                                        hsv[0][x][y][0]=0;
                                }
                                else {
                                        if(max_num==0) {
                                                c=0;
                                                a=1;
                                                b=2;
                                        }
                                        else if(max_num==1) {
                                                c=120;
                                                a=2;
                                                b=0;
                                        }
                                        else if(max_num==2) {
                                                c=240;
                                                a=0;
                                                b=1;
                                        }
                                        hsv[0][x][y][0]=(int)(60*((double)(image[0][x][y][a]-image[0][x][y][b])/(max-min))+c);
                                        if(hsv[0][x][y][0]<0) {
                                                hsv[0][x][y][0]+=360;
                                        }
                                }
                        }
                }
        }





        // 処理４：色の変更
        printf("\n処理４：該当領域の色を変更します．\n");

           printf("Hue(色相)   のシフト量 [-100,100] = ");  scanf("%d",&add_hsv[0]);
           printf("Saturation(彩度) のシフト量 [-100,100] = ");  scanf("%d",&add_hsv[1]);
           printf("Value(明度)  のシフト量 [-100,100] = ");  scanf("%d",&add_hsv[2]);



        // ********************************************************************
        // 原画像（No.0）をラスタ走査し，対応するNo.1の画素が青のときだけ，No.0
        // の画素の色に上記のシフト量を加えます．0より小さくなってしまったら 0,
        // 255 より大きくなったら 255 にすることをお忘れなく．
        // これによって，最終的な出力画像が No.0 に作られます．
        // ********************************************************************


        for(y=0; y<height[0]; y++) {
                for(x=0; x<width[0]; x++) {
                        if(image[1][x][y][0]==0) {//これだけで青か白かの判定は可能である

                                for(color=0; color<3; color++) {
                                        if(hsv[0][x][y][color]+add_hsv[color]<0) {
                                                hsv[0][x][y][color]=0;
                                        }
                                        else if(color==0 && hsv[0][x][y][color]+add_hsv[color]>360) {
                                                hsv[0][x][y][color]=360;
                                        }
                                        else if(color!=0 && hsv[0][x][y][color]+add_hsv[color]>255) {
                                                hsv[0][x][y][color]=255;
                                        }
                                        else{
                                                hsv[0][x][y][color]=hsv[0][x][y][color]+add_hsv[color];
                                        }
                                }
                        }
                }
        }



        //hsv→rgb
        for(y=0; y<height[0]; y++) {
                for(x=0; x<width[0]; x++) {
                        max=hsv[0][x][y][2];
                        min=(int)(max-(((double)hsv[0][x][y][1]/255)*max));
                        if(hsv[0][x][y][0]<=60){
                                image[0][x][y][0]=max;
                                image[0][x][y][1]=(int)(((double)hsv[0][x][y][0]/60)*(max-min)+min);
                                image[0][x][y][2]=min;
                        }
                        else if(hsv[0][x][y][0]>60 && hsv[0][x][y][0]<=120){
                                image[0][x][y][0]=(int)((((double)(120-hsv[0][x][y][0])/60)*(max-min)+min));
                                image[0][x][y][1]=max;
                                image[0][x][y][2]=min;
                        }
                        else if(hsv[0][x][y][0]>120 && hsv[0][x][y][0]<=180){
                                image[0][x][y][0]=min;
                                image[0][x][y][1]=max;
                                image[0][x][y][2]=(int)(((double)(hsv[0][x][y][0]-120)/60)*(max-min)+min);
                        }
                        else if(hsv[0][x][y][0]>180 && hsv[0][x][y][0]<=240){
                                image[0][x][y][0]=min;
                                image[0][x][y][1]=(int)(((double)(240-hsv[0][x][y][0])/60)*(max-min)+min);
                                image[0][x][y][2]=max;
                        }
                        else if(hsv[0][x][y][0]>240 && hsv[0][x][y][0]<=300){
                                image[0][x][y][0]=(int)(((double)(hsv[0][x][y][0]-240)/60)*(max-min)+min);
                                image[0][x][y][1]=min;
                                image[0][x][y][2]=max;
                        }
                        else if(hsv[0][x][y][0]>300 && hsv[0][x][y][0]<=360){
                                image[0][x][y][0]=max;
                                image[0][x][y][1]=min;
                                image[0][x][y][2]=(int)(((double)(360-hsv[0][x][y][0])/60)*(max-min)+min);
                        }

                }
        }


        printf("色を変更した画像を保存します．\n");
        save_color_image( 0,"");


        return 0; // 正常終了を示す値をシステムに返します
}
