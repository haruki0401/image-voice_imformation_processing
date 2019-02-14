/* double.c */
#include<stdio.h>

int main(void)
{
    double param;  /* 実数値用変数 */

    printf("input parameter(0-1):");   /* 入力を促す表示 */
    scanf("%lf",&param);               /* パーセント・エル・エフの書式 */
                                       /* & を忘れないように */ 
    printf("parameter = %f",param);    /* 正しく入力されたか確認 */

    return 0;
}
