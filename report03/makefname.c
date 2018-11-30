void make_filename( char head[], int keta, int num, char fname[] )
// org00100.ppm などの連続的なファイル名を作成する関数
// head[]:"in","out"などの最初の文字列
// keta:桁数．上の例では5
// num:番号(0,1,2,...)．上の例では100
// fname[]:最終的なファイル名．上の例では"org00100.ppm"
{
    char buffer[20];  // 作業変数
    int i,length;     // 作業変数

    strcpy( fname, head);        // fname に最初の文字列を代入
    sprintf( buffer,"%d",num );  // num を10進数の文字にしてbufferへ
    length=strlen(buffer);       // buffer の文字数を調べる
    for(i=1;i<=keta-length;i++){
        strcat( fname, "0" );  // 必要なだけ0を追加
    }
    strcat( fname, buffer );   // 数字部分を追加
    strcat( fname, ".ppm");    // 最終的なファイル名
}
