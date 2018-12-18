#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmlib2.h"
#include "makefname.c"

void make_filename( char head[], int keta, int num, char fname[] );


int main(void){
        char fname[256];
        int x,y,color;
        int flag;

        //back.ppmの読み込み
        load_color_image(0,"back.ppm");
        //編集用データの用意
        copy_color_image(0,1);

        do {
                printf("20フレームごとの処理を行いたい場合は'0',1フレームごとの処理(透明度変化あり)を行いたい場合は'1'を入力してください。\n");
                scanf("%d",&flag);
        } while(!(flag==0||flag==1));

        printf("画像データ群に対して処理を開始します。\n");


        if(flag==0) {
                for(int i=1; i<=200; i=i+20) {

                        make_filename("org",5,i,fname);
                        load_color_image(2,fname);

                        for(y=0; y<height[1]; y++) {
                                for(x=0; x<width[1]; x++) {
                                        for(color=0; color<3; color++) {
                                                if(abs(image[0][x][y][color]-image[2][x][y][color])>=30) {
                                                        image[1][x][y][0]=image[2][x][y][0];
                                                        image[1][x][y][1]=image[2][x][y][1];
                                                        image[1][x][y][2]=image[2][x][y][2];
                                                        break;
                                                }
                                        }
                                }
                        }
                }
        }
        else if(flag==1) {
                for(int i=1; i<=200; i++) {

                        make_filename("org",5,i,fname);
                        load_color_image(2,fname);

                        for(y=0; y<height[1]; y++) {
                                for(x=0; x<width[1]; x++) {
                                        for(color=0; color<3; color++) {
                                                if(abs(image[0][x][y][color]-image[2][x][y][color])>=30) {
                                                        image[1][x][y][0]=image[0][x][y][0]+(int)((double)(image[2][x][y][0]-image[0][x][y][0])*i/200);
                                                        image[1][x][y][1]=image[0][x][y][1]+(int)((double)(image[2][x][y][1]-image[0][x][y][1])*i/200);
                                                        image[1][x][y][2]=image[0][x][y][2]+(int)((double)(image[2][x][y][2]-image[0][x][y][2])*i/200);
                                                        break;
                                                }
                                        }
                                }
                        }
                }
        }

        save_color_image(1,"human.ppm");

        printf("処理が完了しました。プログラムを終了します。\n");

        return 0;
}
