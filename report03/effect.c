#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmlib2.h"
#include "makefname.c"

void make_filename( char head[], int keta, int num, char fname[] );


int main(void){
        char fname[256];
        int x,y,color;

        printf("画像データ群に対して処理を開始します。\n");

        for(int i=1; i<=200; i++) {

                make_filename("org",5,i,fname);
                load_color_image(0,fname);

                for(y=0; y<height[0]; y++) {
                        for(x=0; x<width[0]; x++) {
                                for(color=0; color<3; color++) {
                                        image[0][x][y][0]=(image[0][x][y][0]/64)*64;
                                        image[0][x][y][1]=(image[0][x][y][1]/64)*64;
                                        image[0][x][y][2]=(image[0][x][y][2]/64)*64;
                                }
                        }
                }

                make_filename("out_effect",5,i,fname);
                save_color_image(0,fname);
        }

        printf("処理が完了しました。プログラムを終了します。\n");

        return 0;
}
