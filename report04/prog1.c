#include<stdio.h>
#include "wavelib.h"


int main(void){
    struct RIFF RIFF1, RIFF2;  /* RIFFチャンク用構造体変数 */
    struct fmt  fmt1, fmt2;    /* fmt チャンク用構造体変数 */
    struct data data1, data2;  /* dataチャンク用構造体変数 */
    double alpha;              /* 時間軸方向の短縮係数     */
    int newsize, i, n;         /* 作業用変数               */

    printf("元の音声データを読み込みます．\n");
    load_wave_data( &RIFF1, &fmt1, &data1, "" );


    return 0;
}