#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmlib2.h"
#include "makefname.c"

void make_filename( char head[], int keta, int num, char fname[] );


int main(void){
        char fname[256];
        int x,y,color;

        //back.ppmの読み込み
        load_color_image(0,"back.ppm");
        printf("画像データ群に対して処理を開始します。\n");

        for(int i=1; i<=200; i++) {

                make_filename("org",5,i,fname);
                load_color_image(1,fname);

                for(y=0; y<height[1]; y++) {
                        for(x=0; x<width[1]; x++) {
                                for(color=0; color<3; color++) {
                                        if(abs(image[0][x][y][color]-image[1][x][y][color])>=30) {
                                                break;
                                        }
                                        if(color==2) {
                                                image[1][x][y][0]=255;
                                                image[1][x][y][1]=255;
                                                image[1][x][y][2]=255;
                                        }
                                }
                        }
                }

                make_filename("out",5,i,fname);
                save_color_image(1,fname);
        }

        printf("処理が完了しました。プログラムを終了します。\n");

        return 0;
}
