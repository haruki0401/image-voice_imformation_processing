/* double.c */
#include<stdio.h>

int main(void)
{
    double param;  /* �����l�p�ϐ� */

    printf("input parameter(0-1):");   /* ���͂𑣂��\�� */
    scanf("%lf",&param);               /* �p�[�Z���g�E�G���E�G�t�̏��� */
                                       /* & ��Y��Ȃ��悤�� */ 
    printf("parameter = %f",param);    /* ���������͂��ꂽ���m�F */

    return 0;
}
