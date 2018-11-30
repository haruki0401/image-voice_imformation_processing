/* �J���[�摜�����p�w�b�_�t�@�C�� ppmlib2.h */
/* ��ʂ̓ǂݍ��݂⏑�����݂̍ۂ̉�ʕ\�����Ȃ����� ppmlib.h */
#include<stdlib.h>
#include<string.h>

/* �萔�錾 */
#define MAX_IMAGESIZE   2000 /* �z�肷��c�E���̍ő��f��    */
#define MAX_BRIGHTNESS   255 /* �z�肷��ő�K���l            */
#define GRAYLEVEL        256 /* �z�肷��K����(=�ő�K���l+1) */
#define MAX_FILENAME     256 /* �z�肷��t�@�C�����̍ő咷    */
#define MAX_BUFFERSIZE   256 /* ���p����o�b�t�@�ő咷        */
#define MAX_NUM_OF_IMAGES  3 /* ���p����摜�̖���            */

/* ���ϐ��̐錾 */
/* �摜�f�[�^ image[n][x][y][col] (col=0:R, =1:G, =2:B) */
unsigned char image[MAX_NUM_OF_IMAGES]
    [MAX_IMAGESIZE][MAX_IMAGESIZE][3];
/* �����Əc�� */
int width[MAX_NUM_OF_IMAGES],height[MAX_NUM_OF_IMAGES];

/* �֐��̃v���g�^�C�v�錾 */
void load_color_image( int n, char name[] ); /* �摜�̓���   */
void save_color_image( int n, char name[] ); /* �摜�̏o��   */
void copy_color_image( int n1, int n2 );     /* �摜�̃R�s�[ */
void init_color_image( int n, int red, int green, int blue );
                                             /* �摜�̏����� */

void load_color_image( int n, char name[] )
/* �J���[�摜No.n���o�́Dname[]��""�Ȃ�t�@�C��������́D   */
{
    char fname[MAX_FILENAME];     /* �t�@�C�����p�̕����z�� */
    char buffer[MAX_BUFFERSIZE];  /* �f�[�^�Ǎ��ݗp�ϐ�     */
    FILE *fp;                     /* �t�@�C���|�C���^       */
    int max_gray=0,x,y,col;       /* �ő�K���l�Ɛ���ϐ�   */

    /* ���̓t�@�C���̃I�[�v�� */
    if ( name[0]=='\0' ){
        printf("���̓t�@�C���� (�g���q��ppm) : ");
        scanf("%s",fname);
    } else {
        strcpy( fname, name );
    }
    if ( (fp = fopen( fname, "rb" ))==NULL ){
        printf("�t�@�C�����I�[�v���ł��܂���ł���\n");
        exit(1);  /* �����I�� */
    }
    fgets( buffer, MAX_BUFFERSIZE, fp );
    if ( buffer[0]!='P' || buffer[1]!='6' ){  /* P6�̊m�F */
        printf("�t�@�C���^�C�v��P6�ł͂���܂���\n");
        exit(1);  /* �����I�� */
    }
    /* width[n], height[n] �̑���i#����̃R�����g�͔�΂��j*/
    width[n] = 0;
    height[n] = 0;
    while ( width[n] == 0 || height[n] == 0 ){
        fgets( buffer, MAX_BUFFERSIZE, fp );
        if ( buffer[0] != '#' ) {
            sscanf( buffer, "%d %d", &width[n], &height[n] );
        }
    }
    /* max_gray �̑���i#����̃R�����g�͓ǂݔ�΂��j */
    while ( max_gray == 0 ){
        fgets( buffer, MAX_BUFFERSIZE, fp );
        if ( buffer[0] != '#' ){
            sscanf( buffer, "%d", &max_gray );
        }
    }
    /* �p�����[�^�̉�ʂւ̕\�� */
    // printf("���F%d, �c�F%d\n", width[n], height[n] );
    // printf("�ő�K���l = %d\n",max_gray);
    if ( width[n] > MAX_IMAGESIZE || height[n] >
        MAX_IMAGESIZE ||
        max_gray != MAX_BRIGHTNESS ){
        printf("�T�C�Y���ő�K���l���s�K�؂ł�\n");
        exit(1);  /* �����I�� */
    }
    /* �摜�f�[�^��ǂݍ���ŉ摜�p�z��ɑ������ */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            for(col=0;col<3;col++){
              image[n][x][y][col] = (unsigned char)fgetc( fp );
            }
        }
    }
    // printf("�J���[�摜���摜No.%d�ɓǂݍ��݂܂����D\n",n);
    fclose(fp);
}


void save_color_image( int n, char name[] )
/* n:�摜�ԍ��Cname[]:�t�@�C�����i""�̂Ƃ��̓L�[�{�[�h���́j*/
/* �摜�̉����C�c���͂��ꂼ�� width[n], height[n] �Ɏ��O��  */
/* �������Ă�����̂Ƃ��� */
{
    char fname[MAX_FILENAME];  /* �t�@�C�����p�̕����z�� */
    FILE *fp;                  /* �t�@�C���|�C���^       */
    int x,y,col;               /* ���[�v�ϐ�             */

    if ( name[0] == '\0' ){
        printf("�o�̓t�@�C���� (�g���q��ppm) : ");
        scanf("%s",fname);
    } else strcpy( fname, name );
    if ( (fp = fopen(fname, "wb"))==NULL ){
        printf("�t�@�C�����I�[�v���ł��܂���ł���\n");
        exit(1);  /* �����I�� */
    }
    fputs( "P6\n", fp );  /* ���ʎq */
    fputs( "# Created by Image Processing\n", fp );  /* �R�����g */
    fprintf( fp, "%d %d\n", width[n], height[n] );  /* �T�C�Y */
    fprintf( fp, "%d\n", MAX_BRIGHTNESS );  /* �ő�K���l */
    /* �摜�f�[�^�̏o�� */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            for(col=0;col<3;col++){
                fputc( image[n][x][y][col], fp );
            }
        }
    }
    fclose(fp);
    // printf("�摜�͐���ɏo�͂���܂����D\n");
}


void copy_color_image( int n1, int n2 )
/* �J���[�摜No.n1���J���[�摜No.n2�ɃR�s�[���� */
{
    int x,y,col;  /* ����ϐ� */

    /* �����C�c���̑�� */
    width[n2] = width[n1];  
    height[n2] = height[n1];
    /* �e�F�̊K���f�[�^�̃R�s�[ */
    for(y=0;y<height[n1];y++){
        for(x=0;x<width[n1];x++){
            for(col=0;col<3;col++){
                image[n2][x][y][col] = image[n1][x][y][col];
            }
        }
    }
}


void init_color_image( int n, int red, int green, int blue )
/* �J���[�摜No.n�̑S��f�̐F�������� */
/* -1�Ƃ����F�͏������ΏۊO�Ƃ���     */
{
    int x, y;  /* ����ϐ� */

    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            if (red   != -1) image[n][x][y][0] = red;
            if (green != -1) image[n][x][y][1] = green;
            if (blue  != -1) image[n][x][y][2] = blue;
        }
    }
}
