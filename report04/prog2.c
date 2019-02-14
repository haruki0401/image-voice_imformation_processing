#include<stdio.h>
#include<math.h>
#include "wavelib.h"

#define pi 3.1415926535     // 円周率

void freqchange(short *data, int N, int flag, int changeNum);


int main(void){
    struct RIFF RIFF1;  /* RIFFチャンク用構造体変数 */
    struct fmt  fmt1;    /* fmt チャンク用構造体変数 */
    struct data data1;  /* dataチャンク用構造体変数 */

    short *data;
    int dataLength;
    int i;
    int flag16 = 0;

    int changeNum;

    printf("元の音声データを読み込みます．\n");
    load_wave_data( &RIFF1, &fmt1, &data1, "" );


    //bit type check
    if(fmt1.BitsPerSample == 8){
        printf("入力データ: 8bit\n");
    }else if(fmt1.BitsPerSample == 16){
        flag16 = 1;
        printf("入力データ: 16bit\n");
    }

    printf("入力データの音声サイズ: %d\n", data1.size_of_sounds);


    if(flag16 == 0){
        dataLength = data1.size_of_sounds;
        data = (short *)malloc(sizeof(short) * dataLength);

        for(i = 0; i < data1.size_of_sounds; i++){
            *(data + i) = *(data1.sounds + i);
        }

    }else if(flag16 == 1){
        dataLength = data1.size_of_sounds/2;

        data = (short *)malloc(sizeof(short) * dataLength);

        for(i = 0; i < data1.size_of_sounds; i = i + 2){//16bitなので2byteずつ読み込む
            union u1{//byte→shortのための共用体
                char byte[2];
                short buff;
            }num;

            num.byte[0] = *(data1.sounds + i);
            num.byte[1] = *(data1.sounds + i + 1);

            *(data + (i / 2)) = num.buff;
        }

    }


    do{
        printf("change num: ");
        scanf("%d",&changeNum);
    }while(changeNum < -1000 || changeNum > 1000);

    
    
    freqchange(data, dataLength, flag16, changeNum);

    if(flag16 == 0){
        for(i = 0; i < data1.size_of_sounds; i++){
            *(data1.sounds + i) = *(data + i);
        }
    }
    else if(flag16 == 1){
        for(i = 0; i < data1.size_of_sounds; i = i+2){
            union u2{//byte→shortのための共用体
                char byte[2];
                short buff;
            }num;

            num.buff = *(data + (i / 2));

            *(data1.sounds + i) = num.byte[0];
            *(data1.sounds + i + 1) = num.byte[1];
        }

        

    }

    save_wave_data(&RIFF1, &fmt1, &data1,"out2.wav");

    printf("\n生成した音声を保存します．\n");    


    return 0;
}


void freqchange(short *data, int N, int flag, int changeNum){
    int n;
    int k;
    double Re[N];//実部
    double Im[N];//虚部


    if(flag == 0){
        for(n = 0; n < N; n++){//0を無音に持ってくる
            *(data + n) = *(data + n) - 128;
        }
    }


    //dft
    for(n = 0; n < 10000; n++){
        Re[n] = 0.0;
        Im[n] = 0.0;
        for(k = 0; k < N; k++) {
            Re[n] += (double)(*(data + k)) * cos(2 * pi * k * (n+changeNum) / N);//少し変更
            Im[n] += -(double)(*(data + k)) * sin(2 * pi * k * (n+changeNum) / N);
            
        }

        Re[n] = Re[n] / N;
        Im[n] = Im[n] / N;

    }

    printf("dft完了!\n");

    //idft
    for(n = 0; n < N; n++){
        double tempd = 0.0;
        int tempi;

        for(k = 0; k < 10000; k++){
            //printf("!\n");
            tempd += Re[k] * cos(2 * pi * k * n / N) - Im[k] * sin(2 * pi * k * n / N);
        }

        tempi = (int)tempd + 128;

        if(flag == 0){
            if(tempi > 255){
                *(data + n) = 255;
            }else if(tempi < 0){
                *(data + n) = 0;
            }else{
                *(data + n) = tempi;  
            }
        }
        else if(flag == 1){
            if(tempi > 32767){
                *(data + n) = 32767;
            }else if(tempi < -32768){
                *(data + n) = -32768;
            }else{
                *(data + n) = tempi;
            }
        }
    }

    printf("idft完了!\n");

}