/* ���̃v���O�����̖��O�Fhighspeed.c    */
/* �����̍Đ����x���グ��v���O���� */
#include<stdio.h>
#include"wavelib.h"

int main(void)
{
    struct RIFF RIFF1, RIFF2;  /* RIFF�`�����N�p�\���̕ϐ� */
    struct fmt  fmt1, fmt2;    /* fmt �`�����N�p�\���̕ϐ� */
    struct data data1, data2;  /* data�`�����N�p�\���̕ϐ� */
    double alpha;              /* ���Ԏ������̒Z�k�W��     */
    int newsize, i, n;         /* ��Ɨp�ϐ�               */
    
    printf("===== �����̍Đ����x���グ�� ====\n");
    
    /* wave �t�@�C���̓ǂݍ��� */
    printf("���̉����f�[�^��ǂݍ��݂܂��D\n");
    load_wave_data( &RIFF1, &fmt1, &data1, "" );

    /* �����Q�ւ̃R�s�[ */
    RIFF2 = RIFF1;
    fmt2  = fmt1;
    data2 = data1;
    
    /* �����Q�̃f�[�^���l�߂� */
    do{
        printf("\n���������Ԏ������ɏk�߂�Ƃ��̌W���i [0, 1] �̎����j�F");
        scanf("%lf",&alpha);
    }while( alpha <= 0.0 || alpha >= 1.0 );
    
    /* �����Q����� */
    /* �T�C�Y�̕ύX */
    newsize = (int)( data2.size_of_sounds * alpha );
    /* RIFF�`�����N�S�̂̑傫�����ς��̂ŏC������ */
    RIFF2.SIZE = RIFF2.SIZE - data2.size_of_sounds + newsize;
    data2.size_of_sounds = newsize;
    /* �������̃f�[�^���Ԉ����ăR�s�[���� */
    for(i=0;i<data2.size_of_sounds;i++){
        /* ���̉��Ԗڂ̃f�[�^�ɂ��邩�����߂� */
        n = (int)( data1.size_of_sounds * ( i / (double)newsize ) );
        /* �f�[�^�̃R�s�[ */
        *( data2.sounds + i ) = *( data1.sounds + n );
    }

    /* �����Q�� wave �t�@�C���Ƃ��ĕۑ� */
    printf("\n��������������ۑ����܂��D\n");
    save_wave_data( &RIFF2, &fmt2, &data2, "" );
    
    return 0;
}
