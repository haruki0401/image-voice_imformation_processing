void make_filename( char head[], int keta, int num, char fname[] )
// org00100.ppm �Ȃǂ̘A���I�ȃt�@�C�������쐬����֐�
// head[]:"in","out"�Ȃǂ̍ŏ��̕�����
// keta:�����D��̗�ł�5
// num:�ԍ�(0,1,2,...)�D��̗�ł�100
// fname[]:�ŏI�I�ȃt�@�C�����D��̗�ł�"org00100.ppm"
{
    char buffer[20];  // ��ƕϐ�
    int i,length;     // ��ƕϐ�

    strcpy( fname, head);        // fname �ɍŏ��̕��������
    sprintf( buffer,"%d",num );  // num ��10�i���̕����ɂ���buffer��
    length=strlen(buffer);       // buffer �̕������𒲂ׂ�
    for(i=1;i<=keta-length;i++){
        strcat( fname, "0" );  // �K�v�Ȃ���0��ǉ�
    }
    strcat( fname, buffer );   // ����������ǉ�
    strcat( fname, ".ppm");    // �ŏI�I�ȃt�@�C����
}
