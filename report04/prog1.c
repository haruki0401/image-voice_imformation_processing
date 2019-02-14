#include<stdio.h>
#include<math.h>
#include "wavelib.h"


int main(void){
    struct RIFF RIFF1, RIFF2;  /* RIFFチャンク用構造体変数 */
    struct fmt  fmt1, fmt2;    /* fmt チャンク用構造体変数 */
    struct data data1, data2;  /* dataチャンク用構造体変数 */

    int addNum;
    int delayInterval;
    double delayRatio;
    double functionSelect;
    double common;//common diff or ratio
    int newsize;
    unsigned char *sounds;
    int i, j;
    int upperLim;
    int lowerLim;
    int flag16 = 0;


    printf("元の音声データを読み込みます．\n");
    load_wave_data( &RIFF1, &fmt1, &data1, "" );

    RIFF2 = RIFF1;
    fmt2 = fmt1;
    data2 = data1;

    //bit type check
    if(fmt1.BitsPerSample == 8){
        printf("入力データ: 8bit\n");
        upperLim = 255;
        lowerLim = 0;
    }else if(fmt1.BitsPerSample == 16){
        flag16 = 1;
        printf("入力データ: 16bit\n");
        upperLim = 32767;
        lowerLim = -32768;
    }


    printf("入力データの音声サイズ: %d\n", data1.size_of_sounds);

    do{
        printf("add number (integer(0~)): ");
        scanf("%d",&addNum);
    }while(addNum < 0);

    do{
        printf("delay interval (integer(0~); 16bitのときは1intervalあたり音声サイズ2): ");
        scanf("%d",&delayInterval);
    }while(delayInterval < 0);

    do{
        printf("delay ratio (double(0~1)): ");
        scanf("%lf",&delayRatio);
    }while(delayRatio < 0 || delayRatio > 1);

    do{
        printf("function select (fifference:0, ratio:1): ");
        scanf("%lf",&functionSelect);
    }while(functionSelect != 0 && functionSelect != 1);

    do{
        printf("common difference or ratio (double(0~1)): ");
        scanf("%lf",&common);
    }while(common < 0 || common > 1);


    int tempsize;

    if(flag16 == 0){
        newsize = data2.size_of_sounds;

        for(i = 0; i < addNum; i++){
            newsize += (int)(delayInterval * pow(delayRatio, i));
        }
    }else if(flag16 == 1){
        newsize = data2.size_of_sounds;

        for(i = 0; i < addNum; i++){
            if(((int)(delayInterval * 2 * pow(delayRatio, i))) % 2 == 0){//16bitなので1間隔2byteで*2しておき、結果が偶数になるように調整する
                newsize += (int)(delayInterval * 2 * pow(delayRatio, i));
            }else{
                newsize += (int)(delayInterval * 2 * pow(delayRatio, i)) + 1;
            }
        }

    }


    RIFF2.SIZE = RIFF2.SIZE - data2.size_of_sounds + newsize;
    data2.size_of_sounds = newsize;

    sounds = (unsigned char *)malloc(data2.size_of_sounds);
    
    if ( sounds == NULL ){
        printf("メモリが確保できません． プログラムを終了しす¥n");
        exit(1);
    } else {

        int tempInterval = 0;


        if(flag16 == 0){
            for(j = 0; j < data1.size_of_sounds; j++){
                *(sounds + j) = *(data1.sounds + j);
            }

            for(i = 0; i < addNum; i++){
                tempInterval += (int)((double)delayInterval * pow(delayRatio, i));

                for(j = 0; j < data1.size_of_sounds; j++){
                    int tempSounds;

                    if(functionSelect == 0){
                        tempSounds = (int)((*(data1.sounds + j) - 127) * (1.0 - common * (i + 1)));//128が0であるため -127
                    }else{
                        tempSounds = (int)((*(data1.sounds + j) - 128) * pow(common, (i + 1)));
                    }

                    if((*(sounds + tempInterval + j) + tempSounds) > upperLim){
                        *(sounds + tempInterval + j) = upperLim;
                    }else if((*(sounds + tempInterval + j) + tempSounds) < lowerLim){
                        *(sounds + tempInterval + j) = lowerLim;                    
                    }else{
                        *(sounds + tempInterval + j) += tempSounds;
                    }
                }
            }
        }
        else if(flag16 == 1){

            for(j = 0; j < data1.size_of_sounds; j++){
                *(sounds + j) = *(data1.sounds + j);
            }
            
            for(i = 0; i < addNum; i++){
                if(((int)(delayInterval * 2 * pow(delayRatio, i))) % 2 == 0){
                    tempInterval += (int)(delayInterval * 2 * pow(delayRatio, i));
                }else{
                    tempInterval += (int)(delayInterval * 2 * pow(delayRatio, i)) + 1;
                }

                for(j = 0; j < data1.size_of_sounds; j = j + 2){//16bitなので2byteずつ読み込む
                    int tempSounds;

                    union originSounds{//byte→shortのための共用体
                        char byte[2];
                        short buff;
                    }origin;  

                    union addSounds{//byte→shortのための共用体
                        char byte[2];
                        short buff;
                    }modified;

                    //char*2→short1
                    origin.byte[0] = *(data1.sounds + j);
                    origin.byte[1] = *(data1.sounds + j + 1);

                    modified.byte[0] = *(sounds + tempInterval + j);
                    modified.byte[1] = *(sounds + tempInterval + j + 1);                   


                    if(functionSelect == 0){
                        tempSounds = (int)(origin.buff * (1.0 - common * (i + 1)));
                    }else{
                        tempSounds = (int)(origin.buff * pow(common, (i +1)));
                    }



                    if((modified.buff + tempSounds) > upperLim){
                        modified.buff = upperLim;
                    }else if((modified.buff + tempSounds) < lowerLim){
                        modified.buff = lowerLim;                    
                    }else{
                        modified.buff += tempSounds;
                    }

                    *(sounds + tempInterval + j) = modified.byte[0];
                    *(sounds + tempInterval + j + 1) = modified.byte[1];
                }
            }

        }

    }
    
    data2.sounds = sounds;

    /*for(i=0;i<data1.size_of_sounds;i=i+1000){
        printf("%d\n",*(data1.sounds+i));
    }

    printf("=======\n");
    for(i=0;i<data2.size_of_sounds;i=i+1000){
        printf("%d\n",*(data2.sounds+i));
    }*/
    save_wave_data(&RIFF2, &fmt2, &data2,"out1.wav");

    //save_wave_data(&RIFF1, &fmt1, &data1,"out2.wav");



    printf("\n生成した音声を保存します．\n");    
    //save_wave_data( &RIFF2, &fmt2, &data2, "" );


    return 0;
}