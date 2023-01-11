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
  printf("\r\n     此程序仅使用微软提供的图形接口直接在显示器上绘制准星. ");
  printf("\r\n     未使用任何读写进程内存硬盘以及挂钩等非法操作. ");
  printf("\r\n     基于以上原因仅对非全屏独占游戏有效但程序绝对安全可靠. ");
  printf("\r\n============================================================\r\n");
  printf(">>>>>  自定义准星配置请键入0, 否则键入任意数字回车. ");
  scanf("%d",&df);
  system("cls");
  if (df==0)
  {
    printf("\r\n>>>>>  输入准星粗细(默认2,单位像素): ");
    scanf("%d",&sz);
    printf("\r\n>>>>>  输入准星宽度(默认10,单位像素): ");
    scanf("%d",&dx);
    printf("\r\n>>>>>  输入准星高度(默认24,单位像素): ");
    scanf("%d",&dy);
    printf("\r\n>>>>>  输入准星RGB颜色(默认红色:255 0 0,用空格分开,取值0~255,不支持黑色): ");
    scanf("%d %d %d",&r,&g,&b);
    printf("\r\n>>>>>  输入准星刷新频率(默认8000,单位微秒,过快会到导致残影): ");
    scanf("%d",&cd);
    printf("\r\n>>>>>  屏幕中心相对偏移(默认:0 0,单位像素,负数左上偏移,正数右下偏移): ");
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
  printf("\r\n.....  正在等待线程关闭, 为避免不必要的内存占用, 切勿强制关闭. \r\n.....  完成后程序会自行退出.");
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
