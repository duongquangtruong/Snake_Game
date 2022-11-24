#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//thay doi mau van ban 
void TextColor(int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

//Lay toa do di chuyen con tro den to do 'xy'
void gotoxy(short x,short y)
{
HANDLE hConsoleOutput;
COORD Cursor_an_Pos = { x,y};
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
//Ham thay doi kich thuoc mang hinhf cua xo
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
};

//Kieu trang thai di chuyen cua ran
enum Trangthai {up, down,left,right};//4 kieu 

//khai bao bien
struct Toado{
	int x,y;
};
struct Snake{
	Toado dot[60];
	int n;
	Trangthai tt;
};
struct Hoaqua{
	Toado td;
};

void playgame(int &thoat, char name[], int &lever, Snake &luusnake, char dname[]);
void khungplay();
void help(int &thoat, char name[], int &lever, Snake &luusnake, char dname[]);
void Score(int &thoat, char name[], int &lever, Snake &luusnake, char dname[]);
void khungngoai();
void khoitao(Snake &snake, Hoaqua &hq);
void hienthi(Snake &snake, Hoaqua &hq);
void dieukhien(Snake &snake,int &cam);
void Random(Snake &snake, Hoaqua &hq);
void thuagame(Snake snake, int &thua);
void vaogame(char name[], int &lever,  Snake &luusnake, char dname[]);
void docfile(Snake &luusnake, char dname[]);
void ghifile(Snake snake, char name[]);
void Score(Snake &luusnake, char dname[]);
void gameover(char name[], Snake snake, Snake luusnake);
//void tamdung();

//Ham khoi tao ko doi so ,dat gia tri ban dau cho snake
void khoitao(Snake &snake, Hoaqua &hq)
{
    snake.dot[0].x = 7;  snake.dot[0].y = 8;
    snake.dot[1].x = 6;  snake.dot[1].y = 8;
    snake.dot[2].x = 5;  snake.dot[2].y = 8;
    hq.td.x = 20;        hq.td.y = 20;
    snake.tt = right;
    snake.n = 3;
}

void hienthi(Snake &snake, Hoaqua &hq)
{
	//Tao ky hieu dau snake
    TextColor(113);
    gotoxy(snake.dot[0].x, snake.dot[0].y); putchar(2);
    //Tao ky hieu dot duoi
    TextColor(113);
    for(int i = 1; i < snake.n; i++)
    {
        gotoxy(snake.dot[i].x, snake.dot[i].y); putchar(1);
    }
    int n = 0, l = 0;
   if(snake.tt == right) n++; l++;
   gotoxy(snake.dot[snake.n].x, snake.dot[snake.n].y); printf(" ");
   //Tao ky hieu con moi
   gotoxy(hq.td.x, hq.td.y); TextColor(124); putchar('*');
   //In ra do dai snake
   gotoxy(9, 3);TextColor(15); printf("%d", snake.n);
}

void dieukhien(Snake &snake, int &cam)
{
    fflush(stdin);
    	//Trang thai tung dot
    for(int i = snake.n; i>0; i--)   snake.dot[i] = snake.dot[i-1];
    int tamdung = 0;
    if(kbhit())//kbhit nhan ki tu tu ban phim
    {
        int key = getch();
        if((key=='a'||key=='A'||key=='4') && cam != 2) { snake.tt = left;cam=1;}
        else if((key=='d'||key=='D'||key=='6') && cam!=1) { snake.tt = right;cam=2; }
        else if((key=='s'||key=='S'||key=='2') && cam!=12) { snake.tt = down;cam=11;}
        else if((key=='w'||key=='W'||key=='8') && cam!=11)  {snake.tt = up;cam=12;}
        else if(key=='P'||key=='P')  tamdung = 1;
    } 
    if(snake.tt == left) snake.dot[0].x--;
    else if(snake.tt == right) snake.dot[0].x++;
    else if(snake.tt == down) snake.dot[0].y++;
    else if(snake.tt == up) snake.dot[0].y--;
     if(tamdung == 1)
    {
        gotoxy(34, 18);TextColor(144); printf("PAUSE!!!!");
        gotoxy(29, 18);
        int thoat = 0;
        do{
            char key = getch(); if(key == 'p' ||key =='P') thoat = 1;
        }while(thoat!=1);
    }
}
void khungngoai()
{
           for(int i = 5; i<75; i++)
    {
        for(int j = 2; j<28; j++)
        {
            gotoxy(i, j+6); TextColor(112); printf(" ");
        }
      //  printf("\n");
    }
    TextColor(14);
    gotoxy(33,0); putchar(201);  
    gotoxy(45,0); putchar(187);
    TextColor(11);
    for(int i = 2; i<=77; i++)
    {
        gotoxy(i, 1); putchar(205);
    }
        for(int i = 1; i<=77; i++)
    {
        gotoxy(i, 41); putchar(205);
    }
    for(int i = 1; i<=41; i++)
    {
        gotoxy(1, i); putchar(186);
    }
    for(int i = 1; i<=41; i++)
    {
        gotoxy(78, i); putchar(186);
    }
    TextColor(14);
    gotoxy(1,1); putchar(201);
    gotoxy(1,41); putchar(200);
    gotoxy(78,1); putchar(187);
    gotoxy(78,41); putchar(188);
    TextColor(6);
    for(int i = 4; i<=75; i++)
    {
        gotoxy(i, 7); putchar(220);
    }
        for(int i = 4; i<=75; i++)
    {
        gotoxy(i, 34); putchar(223);
    }
    for(int i = 1; i<=26; i++)
    {
        gotoxy(4, i+7); putchar(186);
    }
    for(int i = 1; i<=26; i++)
    {
        gotoxy(75, i+7); putchar(186);
    }
    TextColor(15);
    gotoxy(4,7); putchar(201);
    gotoxy(4,34); putchar(200);
    gotoxy(75,7); putchar(187);
    gotoxy(75,34); putchar(188);
    TextColor(14);
    gotoxy(5, 2);TextColor(10); printf("Chieu Dai");
    TextColor(11);
    for(int i = 0; i<15; i++)
    {
        gotoxy(2+i, 4); putchar(205);
    }
    for(int i = 0; i<2; i++)
    {
        gotoxy(17, i+2); putchar(186);
    }
    TextColor(14);
    gotoxy(17, 4); putchar(188);
    gotoxy(34, 0); TextColor(160); printf(" GAMESNAKE ");
    gotoxy(35,3); TextColor(12); printf("NHOM 9");
}
void khungplay()
{
    for(int i = 0; i<78; i++)
    {
        gotoxy(1+i, 0);TextColor(12); putchar(220);
    }
        for(int i = 0; i<78; i++)
   {
        gotoxy(1+i, 41); TextColor(12); putchar(205);
    }
    gotoxy(34, 0); TextColor(160); printf(" GAME SNAKE ");
   
        TextColor(1);
        for(int i = 0; i<25; i++){
        gotoxy(30+i, 38); putchar(205);
    }
        for(int i = 0; i<25; i++){
        gotoxy(30+i, 40); putchar(205);
    }
    gotoxy(38, 39); TextColor(2); printf("NHOM 9");
}

void Random(Snake &snake, Hoaqua &hq)
{
    if(snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y)
    {
    hq.td.x = rand()%69+5;
    hq.td.y = rand()%18+8;
    snake.n++;
    Beep(1000, 100);
    }
    gotoxy(78,40);
}

void vaogame(char name[], int &lever,  Snake &luusnake, char dname[])
{
    lever = 100;
    khungplay();
    TextColor(12);
    gotoxy(35,7); printf("BAT DAU");
    TextColor(11);
    gotoxy(26,13); printf("Lever: ");
    gotoxy(26,9); printf("User Name: "); gotoxy(37,9);TextColor(7); gets(name); fflush(stdin);
    gotoxy(39,13);TextColor(15); printf("4");
    int chon = 0;
    int capdo=4;
    gotoxy(27,16);TextColor(2); printf("Phim A: -1 | Phim D: +1");
     gotoxy(39, 13);
    do{
        fflush(stdin);
        char a = getch();
        if(a == 'a'||a=='A'||a=='4') chon = 1;
        else if(a == 'd'||a=='D'||a=='6') chon = 2;
        else if(a == 13 ) chon = 3;// enter chay
        if(chon == 1 && capdo > 1) capdo=capdo-1;
        else if(chon == 2 && capdo < 7) capdo=capdo+1;
        gotoxy(39,13);TextColor(15); printf("%d", capdo);
    }while(chon != 3);
    //gan cap do
    switch(capdo){
        case 1: lever = 1000; break;
        case 2: lever = 500;  break;
        case 3: lever = 250;  break;
        case 4: lever = 150;  break;
        case 5: lever = 100;  break;
        case 6: lever = 80;   break;
        case 7: lever = 50;   break;
    }
    system("cls");
}
/////////////////////////
void docfile(Snake &luusnake, char dname[])
{
    FILE *p = fopen("Diemcao.txt","rt");
    if(p!=NULL)
    do{
        fgets(dname, 30, p);
        fscanf(p, "%d", &luusnake.n);
    }while(feof(p) == 0);
    fclose(p);
}
     
void ghifile(Snake snake, char name[])
{
    FILE *p = fopen("Diemcao.txt","wt");
    {
        fprintf(p, "%s\n%d", name, snake.n);
    }
    fclose(p);
}
///////////////////////////
void thuagame(Snake snake, int &thua)
{      //cham tuong phai 
    if (snake.dot[0].x == 75) {
    	thua = 0;
    }  //cham tran
    else if (snake.dot[0].y == 34){  
		thua = 0;
    }  //cham tuong trai
    else if (snake.dot[0].x == 4){
        thua = 0;
    }  //cham day
    else if (snake.dot[0].y == 7) {
	    thua = 0;
    }
    else thua = 1;
    for(int i = snake.n-1; i>0; i--){
    	   //cham duoi
        if(snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y ){
            thua = 0;
        }
    }
}
///////////////////////
void playgame(int &thoat, char name[], int &lever, Snake &luusnake, char dname[])
{
    khungplay();
        for(int i = 0; i<40; i++){
        TextColor(12); gotoxy(20+i, 6); Sleep(5); putchar(220);
    }
        for(int i = 0; i<40; i++){
		TextColor(12); gotoxy(20+i, 17);Sleep(5); putchar(220);
    }
    TextColor(202);
            gotoxy(33, 10); printf("  PLAY GAME  ");
            TextColor(14);
            gotoxy(33, 11); printf("  HELP         ");
            gotoxy(33, 12); printf("  HIGHT SCORE   ");
            gotoxy(33, 13); printf("  EXIT         ");
            gotoxy(78,40);
    int chon = 0;
    int toado = 0;
    do{
        char a = getch();
        if(a == 's'||a=='S'||a=='2') chon = 1;
        else if(a == 'w'||a=='W'||a=='8') chon = 2;
        else if(a == 13 ) chon = 3;
        else chon = 0;
        if(chon == 1 && toado <=4) toado++;
        else if(chon == 2 && toado >=0) toado--;
        if(toado == 1){
            TextColor(202);
            gotoxy(33, 10); printf("PLAY GAME  ");
            TextColor(14);
            gotoxy(33, 11); printf("  HELP         ");
            gotoxy(33, 12); printf("  HIGHT SCORE   ");
            gotoxy(33, 13); printf("  EXIT         ");
            TextColor(0);
        }
        if(toado == 2)
        {
            TextColor(14);
            gotoxy(33, 10); printf("  PLAY GAME    ");
            TextColor(202);
            gotoxy(33, 11); printf("HELP       ");
            TextColor(14);
            gotoxy(33, 12); printf("  HIGHT SCORE   ");
            gotoxy(33, 13); printf("  EXIT         ");
            TextColor(0);
        }
            if(toado == 3)
        {
            TextColor(14);
            gotoxy(33, 10); printf("  PLAY GAME    ");
            gotoxy(33, 11); printf("  HELP         ");
            TextColor(202);
            gotoxy(33, 12); printf("HIGHT SCORE  ");
            TextColor(14);
            gotoxy(33, 13); printf("  EXIT        ");
        }
        if(toado == 4)
        {
            TextColor(14);
            gotoxy(33, 10); printf("  PLAY GAME    ");
            gotoxy(33, 11); printf("  HELP         ");
            gotoxy(33, 12); printf("  HIGHT SCORE   ");
            TextColor(202);
            gotoxy(33, 13); printf("EXIT      ");
            TextColor(0);
        }
    }while(chon != 3);
    system("cls");
    if(toado == 1) vaogame(name, lever, luusnake, dname);
    else if(toado == 2) help(thoat, name, lever, luusnake, dname);
    else if(toado == 3) Score(thoat, name,lever, luusnake, dname);
    else if(toado == 4)
     {
         thoat = 1;
         TextColor(14);
         gotoxy(22,15); printf("CAM ON BAN DA CHOI GAME CUA CHUNG TOI!!");
         Sleep(2000);
     }
}
////////////////////////////////////
void help(int &thoat, char name[], int &lever,  Snake &luusnake, char dname[])
{
    khungplay();
    gotoxy(34, 0); TextColor(160); printf("    HELP   ");
    gotoxy(31, 4);TextColor(12); printf("2 TO HOP PHIM");
    TextColor(14);
    gotoxy(12,7);  printf("To hop 1");
    TextColor(15);
    gotoxy(16, 8); printf("A: Sang Trai");
    gotoxy(16, 9); printf("D: Sang Phai");
    gotoxy(16, 10); printf("S: Len Tren");
    gotoxy(16, 11); printf("W: Xuong Duoi");
    TextColor(14);
    gotoxy(46,7); printf("To hop 2");
    TextColor(15);
    gotoxy(50, 8); printf("4: Sang Trai");
    gotoxy(50, 9); printf("6: Sang Phai");
    gotoxy(50, 10); printf("8: Len Tren");
    gotoxy(50, 11); printf("2: Xuong Duoi");
    TextColor(14);
    gotoxy(28,14);  printf("P :");
    TextColor(15);
    gotoxy(32, 14); printf("Tam dung - Tiep Tuc");
    gotoxy(36,36); TextColor(47); printf("  EXIT  ");
    gotoxy(39,36);
    TextColor(0);
    char a;
    do{
        a = getch();
    }while(a!=13 );
    system("cls");
    fflush(stdin);
    playgame(thoat, name, lever, luusnake, dname);
}

/////////////////
void Score(int &thoat, char name[], int &lever, Snake &luusnake, char dname[])
{
  khungplay();
  gotoxy(34, 0); TextColor(160); printf(" HIGHT SCORE ");
  TextColor(0);
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 11); printf(" ");
    }
        for(int i = 0; i<45; i++)
    {
        gotoxy(18+i, 21); printf(" ");
    }
 gotoxy(33, 6); TextColor(12); printf("DIEM CAO NHAT");  
 gotoxy(25, 8); TextColor(11); printf("Ten Nguoi Choi:");       gotoxy(41, 8); TextColor(15); printf("%s", dname);
 gotoxy(25, 9); TextColor(11); printf("Diem Cao:");             gotoxy(41, 9); TextColor(10); printf("%d", luusnake.n);
    gotoxy(36,36); TextColor(47); printf("  EXIT  ");
    gotoxy(39,36);
    TextColor(0);
 char a;
    do{
        a = getch();
    }while(a!=13 );
    system("cls");
    fflush(stdin);
    playgame(thoat, name, lever, luusnake, dname);  
}
//////////////////////////////////////////


///////////////////////////////
void gameover(char name[], Snake snake, Snake luusnake)
{
   for(int i = 5; i<75; i++){
	    for(int j = 2; j<28; j++){
		    gotoxy(i, j+6); TextColor(112); printf(" ");
        }
        printf("\n");
    }
    int thoat = 0;
    if(snake.n <= luusnake.n){
        gotoxy(33,15); TextColor(124); printf("GAME OVER");
        gotoxy(20,18); TextColor(121); printf("Diem: ");
        gotoxy(33,18); TextColor(121); printf("%d", snake.n);
        gotoxy(20,17); TextColor(121); printf("Name player: ");
        gotoxy(33,17); TextColor(121); printf("%s", name);
        do{
		thoat = thoat+1;
        if(kbhit()){
            char a = getch();   if(a==13) thoat = 13;
        }
        gotoxy(77,40);  Sleep(300);
        }while(thoat != 13);
    } 
    if(snake.n > luusnake.n){
        gotoxy(25,15); TextColor(124); printf("CHUC MUNG BAN DAT DIEM CAO MOI");
        gotoxy(45,17); TextColor(121); printf("Diem cu: ");
        gotoxy(54,17); TextColor(121); printf("%d", luusnake.n);
        gotoxy(20,17); TextColor(121); printf("Diem moi: ");
        gotoxy(30,17); TextColor(121); printf("%d", snake.n);
        do{
        thoat = thoat+1;
        if(kbhit()){
            char a = getch();   if(a==13) thoat = 13;
        }
        gotoxy(77,40);  Sleep(300);
        }while(thoat != 13);
    }
    TextColor(0);
}
////////////////////////
int main(){
	resizeConsole(700,550);
    int thua=1, cam=0, thoat = 0, lever;
    char name[30], dname[30] = "No name";
    Snake snake, luusnake;
    luusnake.n = 0;
    Hoaqua hq;
    docfile(luusnake, dname);
    playgame(thoat, name, lever, luusnake, dname);
    system("cls");
    fflush(stdin);
    if(thoat==0){
        do{
            thua=1; cam=0;
            khungngoai();
            khoitao(snake, hq);
            do{
                hienthi(snake, hq);
                dieukhien(snake, cam);
                Random(snake, hq);
                thuagame(snake, thua);
                Sleep(lever);
            }while(thua != 0);
            gameover(name, snake,luusnake);
            system("cls");
            if(snake.n > luusnake.n){
                ghifile(snake, name);
                docfile(luusnake, dname);
            }
            playgame(thoat, name, lever, luusnake, dname);
        }while(thoat == 0);
    }
}
    































