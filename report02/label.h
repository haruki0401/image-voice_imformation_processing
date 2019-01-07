/* ���x�����O�p�w�b�_�t�@�C�� label.h */
/* ���x���p���ϐ� */
int label[MAX_IMAGESIZE][MAX_IMAGESIZE];

int labeling( int n, int red, int green, int blue );
    /* ���x�����O���s���֐� */
int search_4neighbors( int x, int y, int n );
    /* �S�ߖT�̃��x���̍ő�l��Ԃ��֐� */
void modify_label( int num1, int num2, int n );
    /* ���x����ύX����֐� */


void modify_label( int num1, int num2, int n )
/* label[][]���̑S�Ă� num1 �� num2 �ɕύX */
{
    int x,y;  /* ����ϐ� */

    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            if ( label[x][y]==num1){
                label[x][y]=num2;
            }
        }
    }
}


int search_4neighbors( int x, int y, int n )
/* label[x][y]�̂S�ߖT�̃��x���̍ő�l��Ԃ��֐� */
/* n �͑Ώۉ摜�̔ԍ��i���O������̂��߂Ɏg���j  */
{
    int max=0;  /* �ő�l */

    if (y-1>=0 && label[x][y-1]>max ){
        max=label[x][y-1];  /* �� */
    }
    if (x-1>=0 && label[x-1][y]>max ){
        max=label[x-1][y];  /* �� */
    }
    if (y+1<height[n] && label[x][y+1]>max ){
        max=label[x][y+1];  /* �� */
    }
    if (x+1<width[n]  && label[x+1][y]>max ){
        max=label[x+1][y];  /* �E */
    }
    return max;
}


int labeling( int n, int red, int green, int blue )
/* �摜No.n ���̔w�i�F(red,green,blue)�ȊO�̐F�̐}�`�Ƀ��x�����O���� */
/* ���ʂ���ϐ�label[][]�ɑ������D�߂�l�͍ŏI�I�ȃ��x���̍ő�l�D*/
{
    int x,y,num;    /* ����ϐ��C��ƕϐ� */
    int count=0;    /* ���x���ő�l       */
    int new_count;  /* ��ƕϐ�           */

    /* ���x���������� */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            label[x][y]=0; /* 0:��������\�� */
        }
    }
    /* �摜No.n���X�L���� */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            if ( (image[n][x][y][0]!=red   || image[n][x][y][1]!=green ||
                  image[n][x][y][2]!=blue)  && label[x][y] == 0 ){
                num = search_4neighbors(x,y,n);
                if (num==0){  /* �V�����Ǘ��̈� */
                    label[x][y]=++count; /* count��+1���Ă����� */
                } else {
                    label[x][y]=num;
                }
            }
        }
    }
    /* label[][]�𐮌`���� */
    if ( count > 0 ){
        /* �d���̍폜 */
        for(y=0;y<height[n];y++){
            for(x=0;x<width[n];x++){
                if (label[x][y]!=0){
                    num = search_4neighbors(x,y,n);
                    if ( num > label[x][y]){
                        /* ���x��num ��S�ĕύX */
                        modify_label(num,label[x][y],n);
                    }
                }
            }
        }
        /* �󂢂��ԍ����l�߂� */
        new_count=0;
        for(y=0;y<height[n];y++){
            for(x=0;x<width[n];x++){
                if ( label[x][y] > new_count ){
                    new_count++;
                    modify_label(label[x][y],new_count,n);
                }
            }
        }
        return new_count;  /* ���ŏI�I�ȃ��x���̍ő�l */
    } else return 0;  /* ���Ǘ��̈�Ȃ� */
}
