#include <syGDI.c>
#include <stdio.h>
#include <processthreadsapi.h>
#include <time.h>
DWORD WINAPI draw(LPVOID lpParameter);
DWORD WINAPI while_clk(LPVOID lpParameter);
long long getclk();

struct syGDIst_gdi gdi0={0};
char OVER=0, df=1;
int dx=10,dy=24,sz=2,r=255,g=0,b=0,ex=0,ey=0;  //reticle size
int bmpCx=100,bmpCy=100;
LARGE_INTEGER StartingTime, EndingTime; 
LARGE_INTEGER Frequency;
long long cd=8000, delay=0;
int main()
{
  system("color 03");
  QueryPerformanceFrequency(&Frequency); 
  printf("============================================================");
  printf("\r\n     �˳����ʹ��΢���ṩ��ͼ�νӿ�ֱ������ʾ���ϻ���׼��. ");
  printf("\r\n     δʹ���κζ�д�����ڴ�Ӳ���Լ��ҹ��ȷǷ�����. ");
  printf("\r\n     ��������ԭ����Է�ȫ����ռ��Ϸ��Ч��������԰�ȫ�ɿ�. ");
  printf("\r\n============================================================\r\n");
  printf(">>>>>  �Զ���׼�����������0, ��������������ֻس�. ");
  scanf("%d",&df);
  system("cls");
  if (df==0)
  {
    printf("\r\n>>>>>  ����׼�Ǵ�ϸ(Ĭ��2,��λ����): ");
    scanf("%d",&sz);
    printf("\r\n>>>>>  ����׼�ǿ��(Ĭ��10,��λ����): ");
    scanf("%d",&dx);
    printf("\r\n>>>>>  ����׼�Ǹ߶�(Ĭ��24,��λ����): ");
    scanf("%d",&dy);
    printf("\r\n>>>>>  ����׼��RGB��ɫ(Ĭ�Ϻ�ɫ:255 0 0,�ÿո�ֿ�,ȡֵ0~255,��֧�ֺ�ɫ): ");
    scanf("%d %d %d",&r,&g,&b);
    printf("\r\n>>>>>  ����׼��ˢ��Ƶ��(Ĭ��8000,��λ΢��,����ᵽ���²�Ӱ): ");
    scanf("%d",&cd);
    printf("\r\n>>>>>  ��Ļ�������ƫ��(Ĭ��:0 0,��λ����,��������ƫ��,��������ƫ��): ");
    scanf("%d %d",&ex,&ey);
    system("cls");
  }
  syGDIfc_inis(0,bmpCx,bmpCy,&gdi0);
  syGDIfc_putPen(sz, r, g, b, &gdi0);
  syGDIfc_line(gdi0.width_bmp/2-dx, gdi0.height_bmp/2-dy/3, gdi0.width_bmp/2-dx, gdi0.height_bmp/2+2*dy/3,&gdi0);
  syGDIfc_line(gdi0.width_bmp/2+dx, gdi0.height_bmp/2-dy/3, gdi0.width_bmp/2+dx, gdi0.height_bmp/2+2*dy/3,&gdi0);
  syGDIfc_line(gdi0.width_bmp/2-dx/3, gdi0.height_bmp/2+3, gdi0.width_bmp/2+dx/3, gdi0.height_bmp/2+3,&gdi0);
  HANDLE hThr = CreateThread(NULL, 0, draw, NULL, 0, NULL);
  CloseHandle(hThr);
  //BitBlt(gdi0.scrDC, 0, 0, gdi0.width_scr, gdi0.height_scr, gdi0.memDC, 0, 0, SRCCOPY);
  system("pause");
  OVER=1;
  printf("\r\n.....  ���ڵȴ��̹߳ر�, Ϊ���ⲻ��Ҫ���ڴ�ռ��, ����ǿ�ƹر�. \r\n.....  ��ɺ����������˳�.");
  while(OVER!=-1);
  syGDIfc_clr(&gdi0);
  //system("pause");
}

DWORD WINAPI draw(LPVOID lpParameter)
{
  do for (long long i = 0; i < 500; i++)
  {
    TransparentBlt(gdi0.scrDC, gdi0.width_scr/2-bmpCx/2+ex, gdi0.height_scr/2-bmpCy/2+ey, bmpCx, bmpCy, gdi0.memDC, 0, 0, gdi0.width_bmp, gdi0.height_bmp, RGB(0,0,0));
    QueryPerformanceCounter(&StartingTime);
    do
    {
      QueryPerformanceCounter(&EndingTime);
      delay = 1000000 * (EndingTime.QuadPart - StartingTime.QuadPart) / Frequency.QuadPart;
    } while (delay<cd);
  }while (!OVER);
  OVER=-1;
}
