/* ラベリング用ヘッダファイル label.h */
/* ラベル用大域変数 */
int label[MAX_IMAGESIZE][MAX_IMAGESIZE];

int labeling( int n, int red, int green, int blue );
    /* ラベリングを行う関数 */
int search_4neighbors( int x, int y, int n );
    /* ４近傍のラベルの最大値を返す関数 */
void modify_label( int num1, int num2, int n );
    /* ラベルを変更する関数 */


void modify_label( int num1, int num2, int n )
/* label[][]中の全ての num1 を num2 に変更 */
{
    int x,y;  /* 制御変数 */

    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            if ( label[x][y]==num1){
                label[x][y]=num2;
            }
        }
    }
}


int search_4neighbors( int x, int y, int n )
/* label[x][y]の４近傍のラベルの最大値を返す関数 */
/* n は対象画像の番号（内外部判定のために使う）  */
{
    int max=0;  /* 最大値 */

    if (y-1>=0 && label[x][y-1]>max ){
        max=label[x][y-1];  /* 上 */
    }
    if (x-1>=0 && label[x-1][y]>max ){
        max=label[x-1][y];  /* 左 */
    }
    if (y+1<height[n] && label[x][y+1]>max ){
        max=label[x][y+1];  /* 下 */
    }
    if (x+1<width[n]  && label[x+1][y]>max ){
        max=label[x+1][y];  /* 右 */
    }
    return max;
}


int labeling( int n, int red, int green, int blue )
/* 画像No.n 中の背景色(red,green,blue)以外の色の図形にラベリングして */
/* 結果を大域変数label[][]に代入する．戻り値は最終的なラベルの最大値．*/
{
    int x,y,num;    /* 制御変数，作業変数 */
    int count=0;    /* ラベル最大値       */
    int new_count;  /* 作業変数           */

    /* ラベルを初期化 */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            label[x][y]=0; /* 0:未処理を表す */
        }
    }
    /* 画像No.nをスキャン */
    for(y=0;y<height[n];y++){
        for(x=0;x<width[n];x++){
            if ( (image[n][x][y][0]!=red   || image[n][x][y][1]!=green ||
                  image[n][x][y][2]!=blue)  && label[x][y] == 0 ){
                num = search_4neighbors(x,y,n);
                if (num==0){  /* 新しい孤立領域 */
                    label[x][y]=++count; /* countに+1してから代入 */
                } else {
                    label[x][y]=num;
                }
            }
        }
    }
    /* label[][]を整形する */
    if ( count > 0 ){
        /* 重複の削除 */
        for(y=0;y<height[n];y++){
            for(x=0;x<width[n];x++){
                if (label[x][y]!=0){
                    num = search_4neighbors(x,y,n);
                    if ( num > label[x][y]){
                        /* ラベルnum を全て変更 */
                        modify_label(num,label[x][y],n);
                    }
                }
            }
        }
        /* 空いた番号を詰める */
        new_count=0;
        for(y=0;y<height[n];y++){
            for(x=0;x<width[n];x++){
                if ( label[x][y] > new_count ){
                    new_count++;
                    modify_label(label[x][y],new_count,n);
                }
            }
        }
        return new_count;  /* ＝最終的なラベルの最大値 */
    } else return 0;  /* ＝孤立領域なし */
}
