// colorsim.c�i���̃v���O�����̖��O)
#include <stdio.h>   // �W�����o�̓w�b�_�̃C���N���[�h
#include "ppmlib.h"  // ppm�t�@�C���p�w�b�_�̃C���N���[�h
#include "label.h"   // ���x�����O�p�w�b�_�̃C���N���[�h

#define RMIN 0.0001   // �̈�ʐς̉���(=0.01%)
#define RMAX 0.3    // �̈�ʐς̏��(=30%)

int main(void)
{
        int x,y; // ���W�p�̐���ϐ�
        int number; // �Ǘ��̈�̑���
        int add_hsv[3];// ������l(�z��ɕύX)
        int i;   // ���x���p�̐���ϐ�
        int area; // �̈�̖ʐ�
        int count; // �ŏI�I�Ɏc�����̈�̑���
        int xmin,ymin,xmax,ymax;  // ���x���̗̈�
        double ratio; // �ʐϗ�
        int color; // ��ƕϐ�

        printf("==== �J���[�V�~�����[�^�[ =====\n");
        printf("���摜(ppm(�o�C�i��)�`��)��ǂݍ��݂܂�\n");
        load_color_image(0,""); // �t�@�C�� �� �摜No.0 �ւ̓ǂݍ���
        copy_color_image(0,1); // �摜No.0 �� �摜No.1 �փR�s�[


        int max;
        int min;
        int max_num;
        int c;
        int a,b;





        // �����P�F�摜No.1 �̖ڕW�̐F�̉�f��F�Œ��o���܂�
        printf("\n�����P�F�ڕW�̐F�̉�f��F�Œ��o���܂��D\n");
        // ********************************************************************
        // �����ɁC�摜No.1�̉�f�̐F���C���摜(No.0)�̐F�ύX�Ώۗ̈�Ȃ�iR=
        // G=0,B=255�j�C�����łȂ��Ȃ甒�iR=G=B=255�j�ɂ��鏈���������ĉ������D
        // �������͑ΏۂƂ��錴�摜�Ɉˑ����܂��D�܂�C�����ł̑I�ʂ́C������
        // �I�񂾌��摜�����ɗL���ŁC���̉摜�ɂ͎g���Ȃ����̂ŗǂ��ł��D
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



        printf("���摜�̖ڕW�F�̉�f��F�ɂ����摜�� mask1.ppm �ŕۑ����܂��D\n");
        save_color_image( 1, "mask1.ppm" );

        // �����Q�F���x�����O
        printf("\n�����Q�F�ڕW�F�̗̈�̃��x�����O���s�Ȃ��܂��D\n");
        printf("���x�����O���ł��D���������Ǝ��Ԃ�������܂�...\n");
        // ********************************************************************
        // �֐� labeling( ) ���g���āC�摜No.1 ��w�i��f�̐F�𔒁iR=G=B=255)��
        // ���ă��׃����O���s�Ȃ��C�Ǘ��̈�̑�����ϐ� number �ɑ������L�q��
        // ����ĉ������D�������P�s�����ł��D
        // ********************************************************************

        number=labeling(1,255,255,255);

        printf("�I�����܂����D�Ǘ��̈�̑�����%d��\n",number);
        if ( number == 0 ) {
                printf("�Y������̈悪�Ȃ��̂ŏI�����܂��D\n");
                exit(1);
        }



        // �����R�F�ʐςőI�ʂ���
        printf("\n�����R�F�ڕW�F�̗̈�̖ʐςőI�ʂ��܂��D\n");
        printf("�ʐς��͈͊O�̂��͔̂���f�ɂ��܂�.\n");
        count = number;
        // ���x��=1 ���� number �܂ł𒲂ׂ�
        for(i=1; i<=number; i++) {
                // ****************************************************************
                // �܂��C���x�� i �̗̈�̖ʐ� area �����߂܂��傤�D
                // ���̍ہC�����ɂ��̗̈�� x, y �͈̔́ixmin,ymin)<--->(xmax,ymax)
                // �����߂Ă����܂��傤�i��̑��������������邽�߂ł��j�D�����ŁC
                // (xmin,ymin)�F���x�� i �̗̈�̍���̍��W
                // (xmax,ymax)�F���x�� i �̗̈�̉E���̍��W
                // ���ɖʐϗ� ratio �����߂܂��傤�D�����ł̖ʐϗ��Ƃ́Carea ���摜
                // �S�̖̂ʐςŊ��������̂ł��D���Ȃ킿�C0.0�`1.0�̎����l�ɂȂ�܂��D
                // ���ɂ��� ratio �̒l�͈̔́i�v���O�����̖`���� define���Œ�`����
                // �Ă��܂��D���̗�ł� 1%�ȏ�30%�ȉ��ł��j�ł͂Ȃ���f�𔒂ɂ��܂��D
                // ���̏����͊��Ɏ��ɏ�����Ă��܂��̂ō��Ȃ��Č��\�ł��D
                // ****************************************************************

                //���ꂼ��̕ϐ���������
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

                if (( ratio < RMIN || ratio > RMAX ) || ymax<550) {//���̌��̏����͐Ԃ����g�ɂ��������Ă��܂��A�ʐςł̋�ʂ͂ł��Ȃ������̂ŁA�ʒu�ŋ�ʂ��邽�߂̂��̂ł���
                        // �ʐς��Y�����Ȃ��ꍇ�͐�f�𔒉�f�֕ύX����
                        count--;
                        for(y=ymin; y<=ymax; y++) {
                                for(x=xmin; x<=xmax; x++) {
                                        if ( label[x][y] == i ) {
                                                // ����f�֕ύX����
                                                image[1][x][y][0] = 255;
                                                image[1][x][y][1] = 255;
                                                image[1][x][y][2] = 255;
                                        }
                                }
                        }
                }
        }
        printf("�I�����܂����D�Y�������Ǘ��̈�̑�����%d��\n",count);
        if ( count > 0 ) {
                printf("�Y���̈��F�ɂ����摜�� mask2.ppm �ŕۑ����܂��D\n");
                save_color_image( 1, "mask2.ppm" );
        } else {
                printf("�Y������̈悪�c��Ȃ������̂ŏI�����܂��D\n");
                exit(1);
        }


        //rgb��hsv
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





        // �����S�F�F�̕ύX
        printf("\n�����S�F�Y���̈�̐F��ύX���܂��D\n");

           printf("Hue(�F��)   �̃V�t�g�� [-100,100] = ");  scanf("%d",&add_hsv[0]);
           printf("Saturation(�ʓx) �̃V�t�g�� [-100,100] = ");  scanf("%d",&add_hsv[1]);
           printf("Value(���x)  �̃V�t�g�� [-100,100] = ");  scanf("%d",&add_hsv[2]);



        // ********************************************************************
        // ���摜�iNo.0�j�����X�^�������C�Ή�����No.1�̉�f���̂Ƃ������CNo.0
        // �̉�f�̐F�ɏ�L�̃V�t�g�ʂ������܂��D0��菬�����Ȃ��Ă��܂����� 0,
        // 255 ���傫���Ȃ����� 255 �ɂ��邱�Ƃ����Y��Ȃ��D
        // ����ɂ���āC�ŏI�I�ȏo�͉摜�� No.0 �ɍ���܂��D
        // ********************************************************************


        for(y=0; y<height[0]; y++) {
                for(x=0; x<width[0]; x++) {
                        if(image[1][x][y][0]==0) {//���ꂾ���Ő������̔���͉\�ł���

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



        //hsv��rgb
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


        printf("�F��ύX�����摜��ۑ����܂��D\n");
        save_color_image( 0,"");


        return 0; // ����I���������l���V�X�e���ɕԂ��܂�
}
