// sample.c�i���̃v���O�����̖��O�j
#include<stdio.h>      // �W�����o�̓w�b�_�̃C���N���[�h
#include"ppmlib2.h"    // ��ʕ\�������J�b�g���� ppmlib.h
#include"makefname.c"  // �A�ԃt�@�C�����̍쐬

//�֐��̃v���g�^�C�v�錾�imakefname.c���̊֐��j
void make_filename( char head[], int keta, int num, char fname[] );

// main�֐��̎n�܂�
int main(void)
{
    int i;              // i:���̓t�@�C���ԍ�
    char fname[256];    // �t�@�C�����p�z��i���o�͌��p�j
    int x,y,col;        // ����ϐ�

    printf("���摜�̃t���[�� org00001.ppm�`org00010.ppm �𔽓]�����܂�\n");
    for(i=1;i<=10;i++){
        // �A�Ԃ̃t�@�C�����𐶐��iorg00001.ppm�`org00010.ppm�j
        make_filename( "org", 5, i, fname );   // 5:�����̌���
        // �摜��No.0�ɓǂݍ���
        load_color_image( 0, fname );
        // �摜�𔽓]������
        for(y=0;y<height[0];y++){
            for(x=0;x<width[0];x++){
                for(col=0;col<3;col++){
                    image[0][x][y][col] = 255 - image[0][x][y][col];
                }
            }
        }
        // �o�̓t�@�C�����iout00001.ppm�`out00010.ppm�j�����
        make_filename( "out", 5, i, fname );
        // �摜�̕ۑ�
        save_color_image( 0, fname );
    }
    printf("���ʉ摜�� out00001.ppm�`out00010.ppm �ŏo�͂��܂���\n");
    return 0;  // �v���O�����̐���I��
}
