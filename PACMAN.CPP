 #include<stdio.h>
 #include<stdlib.h>
 #include<conio.h>
 #include<graphics.h>
 #include<dos.h>
 #include<ctype.h>
 #include<time.h>
 #define RIGHT 0
 #define LEFT 1
 #define UP 2
 #define DOWN 3

 void initialise(void);
 char endscreen(void);
 void startscreen(void);
 void music(int);
 void vline(unsigned char,int ,int ,int ,int);
 void hline(unsigned char,int ,int ,int ,int);
 void drawbox(int,int,int,int,char);
 void gamescreen(void);
 void size(int,int);
 void writechar(char,int,int,int);
 void monitor(void);
 void getkeyhit(void);
 int testkeys(void);
 void readchar(int,int,unsigned char*);
 void bug(int*,int*,int*,unsigned char*);
 void movebugright(int*,int*,unsigned char*);
 void movebugleft(int*,int*,unsigned char*);
 void movebugup(int*,int*,unsigned char*);
 void movebugdown(int*,int*,unsigned char*);
 void killeater(void);

 int maze[25][80],score,row,col,ascii,scan,liveslost,delayfactor;
 int gd=DETECT,gm,midx,midy,maxx,maxy;
 int bugnumber,r[5],c[5],dir[5];
 unsigned char charbelow[5];
 char far *vid_mem= (char far *) 0xB8000000L ;
 void main(void)
 { char ans;
 clrscr();
 randomize();
 startscreen();
 while(1)
 {
 initialise();
 gamescreen();
 monitor();
 ans=endscreen();
 if(ans=='N')
 break;
 }
 }
//Initializing the main window.
 void startscreen(void)
 {
 char ch;
 int i;
 initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
 maxx=getmaxx();
 maxy=getmaxy();
 midx=maxx/2;
 midy=maxy/2;
 setcolor(GREEN);
 rectangle(0,0,maxx,maxy);
 setcolor(BLUE);
 rectangle(2,2,maxx-2,maxy-2);
 setcolor(YELLOW);
 line(55,1,55,maxy-2);
 line(maxx-55,1,maxx-55,maxy-2);
 setcolor(6);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 settextstyle(4,HORIZ_DIR,8);
 outtextxy(midx,midy,"The PacMan");
 int loop;
 randomize();
 for(loop=0;loop<40;loop++)
 {
 gotoxy(rand()%80,rand()%25);
 music(1);
 printf("%c",2);
 delay(100);
 }
 nosound();
 setviewport(0,0,maxx,maxy,1);
 clearviewport();
 setcolor(BLUE);
 rectangle(30,0,maxx-33,maxy);
 setcolor(YELLOW);
 for(i=15;i<=maxy-15;i+=15)
 {
 ellipse(15,i,0,360,6,3);
 ellipse(maxx-15,i,0,360,6,3);
 }
 setcolor(5);
 settextjustify(CENTER_TEXT,TOP_TEXT);
 settextstyle(4,HORIZ_DIR,5);
 outtextxy(midx,60,"INSTRUCTION");
 settextstyle(2,HORIZ_DIR,5);
 outtextxy(midx,110,"You goal:-To eatup all the dots  ");
 outtextxy(midx,330,"If you are ready to start, press any key");
 setcolor(GREEN);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
 outtextxy(midx,400,"We wish you best of luck");

 while(!kbhit());

 if(getch()==0)
 getch();

 setviewport(0,0,maxx,maxy,1);
 clearviewport();
 rectangle(midx-200,midy-60,midx+200,midy+60);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 outtextxy(midx,60,"Select Speed");

 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 outtextxy(midx,90,"Slow(S)");
 outtextxy(midx,105,"Medium(M)");
 outtextxy(midx,120,"Fast(F)");
 if((ch=getch())==0)
 getch();

 switch(toupper(ch))
 {
 case'S':
 delayfactor=100;
 break;
 case'M':
 delayfactor=50;
 break;
 case'F':
 delayfactor=20;
 break;
 default:
 delayfactor=100;
 }
 if(delayfactor==100)
 outtextxy(midx,midy,"Slow(S)");
 if(delayfactor==50)
 outtextxy(midx,midy,"Medium(M)");
 if(delayfactor==20)
 outtextxy(midx,midy,"Fast(F)");
 while(!kbhit());

 closegraph();
 restorecrtmode();
 }
//Function for game sounds.
 void music(int type)
 {
 float octave[7]={130.81,146.83,164.81,174.61,196,220,246.94};
 int n,i;
 switch(type)
 {
 case 1:
 n=random(6);
 sound(octave[n]*4);
 delay(50);
 break;
 case 2:
 for(i=6;i>=0;i--){
 sound(octave[i]);
 delay(54);}
 nosound();
 break;
 case 3:
 sound(octave[6]*2);
 delay(50);
 nosound();
 }}

//Game over screen.

 char endscreen()
 {
 char ans;
 initgraph(&gd,&gm,"C:\\TARBOC3\\BGI");
 rectangle(0,0,maxx,maxy);
 rectangle(2,2,maxx-2,maxy-2);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
 if(liveslost==3)
 {
 outtextxy(midx,midy-30,"Bad Luck!!");
 outtextxy(midx,midy,"Try Again");}
 else
 {
 outtextxy(midx,midy/2,"You really are a");
 settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
 outtextxy(midx,midy,"GENIUS!!");
 }
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
 outtextxy(midx,midy+midy/2,"Another Game(Y/N)...");
 while(!(ans=='Y'||ans=='N'))
 {
 fflush(stdin);
 ans=getch();
 ans=toupper(ans);
 }
 closegraph();
 restorecrtmode();
 return(ans);
 }
 void initialise(void)
 {
 int j;
 row=12;
 col=40;

 r[0]=3;c[0]=76;
 r[1]=3;c[1]=12;
 r[2]=12;c[2]=4;
 r[3]=14;c[3]=62;
 score=0;
 liveslost=0;
 bugnumber=0;
 for(j=0;j<4;j++)
 {
 dir[j]=0;
 charbelow[j]=250;
 }
 }
//The map.
 void gamescreen(void)
 {
 int i;
 size(32,0);
 drawbox(0,0,16,79,12);
 hline(205,1,0,0,79);
 hline(205,1,2,2,20);
 hline(205,1,2,22,38);
 hline(205,1,2,42,61);
 hline(205,1,2,63,77);
 hline(205,1,4,2,20);
 hline(205,1,4,22,61);
 hline(205,1,4,63,77);
 hline(205,1,17,0,79);
 hline(205,1,15,2,38);
 hline(205,1,15,42,77);
 hline(205,1,13,0,12);
 hline(205,1,13,65,78);
 hline(205,1,13,16,61);
 hline(205,1,11,2,14);
 hline(205,1,11,62,77);
 hline(205,1,8,16,61);
 hline(205,1,6,2,38);
 hline(205,1,6,42,77);
 hline(205,1,7,63,77);
 hline(205,1,9,63,78);
 hline(205,1,7,2,14);
 hline(205,1,9,1,14);

 vline(186,1,0,0,16);
 vline(186,1,79,0,16);
 vline(186,1,40,0,2);
 vline(186,1,40,4,6);
 vline(186,1,14,12,14);
 vline(186,1,40,13,15);
 vline(186,1,63,12,14);
 vline(186,1,40,9,11);
 vline(202,1,14,15,15);
 vline(202,1,63,15,15);
 vline(203,1,40,0,0);
 vline(203,1,40,4,4);
 vline(203,1,40,8,8);
 vline(203,1,40,13,13);
 vline(187,1,79,0,0);
 vline(201,1,0,0,0);
 vline(188,1,79,17,17);
 vline(200,1,0,17,17);
 vline(204,1,0,9,9);
 vline(185,1,79,9,9);
 vline(185,1,79,13,13);

 for(int vlin=16;vlin<=60;vlin+=2)
 vline(186,1,vlin,10,11);

 gotoxy(51,24);
 printf("Press Esc to stop the game");
 gotoxy(2,24);
 printf("point: %3d",score);

 writechar(2,3,76,15);
 writechar(2,3,12,15);
 writechar(2,12,4,15);
 writechar(2,14,62,15);

 music(2);
 }

 void drawbox(int sr,int sc,int er,int ec, char attr)
 {
 int r,c;
 char far *v;
 for(r=sr;r<=er;r++)
 {for(c=sc;c<=ec;c++){
 v=vid_mem+(r*160)+(c*2);
 *v=250;
 v++;
 *v=attr;}}}

 void writechar(char ch,int r,int c,int attr)
 {
 char far *v;
 v=vid_mem+(r*160)+c*2;
 *v=ch;
 v++;
 *v=attr;
 }
 void hline(unsigned char ch,int attr,int r,int c1,int c2)
 {
 int c;
 for(c=c1;c<=c2;c++)
 {
 writechar(ch,r,c,attr);
 maze[r][c]=1;
 }
 }

void vline(unsigned char ch,int attr,int c,int r1,int r2)
{
int r;
for(r=r1;r<=r2;r++)
{
writechar(ch,r,c,attr);
maze[r][c]=1;
}
}
 void size(int ssl,int esl)
 {union REGS i,o;
 i.h.ah=1;
 i.h.ch=ssl;
 i.h.cl=esl;
 i.h.bh=0;
 int86(16,&i,&o);
 }
 void monitor(void)
 {int key;
 unsigned char ch;
 while(1)
 {
 writechar(1,row,col,14);
 getkeyhit();
 if(liveslost==3)
 break;

 writechar(' ',row,col,1);
 key=testkeys();
 if(key==0)
 {
 writechar(1,row,col,14);
 }
 else
 {
 readchar(row,col,&ch);
 if(ch==250)
 {
 score++;
 music(3);
 }
 if(ch==2)
 killeater();
 if(liveslost==3)
 break;
 gotoxy(2,24);
 printf("points : %3d",score);

 if(score>=692)
 {
 writechar(' ',row,col,1);
 break;
 }
 }
 }
}
 void getkeyhit()
 {
 union REGS i,o;
 int count;
 while(!kbhit())
 {
 delay(delayfactor);
 bug(&r[bugnumber],&c[bugnumber],&dir[bugnumber],&charbelow[bugnumber]);
 if(liveslost==3)
 return;
 bugnumber++;
 if(bugnumber==4)
 bugnumber=0;
 }
 i.h.ah=0;
 int86(22,&i,&o);
 ascii=o.h.al;
 scan=o.h.ah;
 }
 int testkeys(void)
 {
 switch(scan)
 {
 case 72:
 if(maze[row-1][col]==1)
 return(0);

 row--;
 break;

 case 80:
 if(maze[row+1][col]==1)
 return(0);
 row++;
 break;

 case 77:
 if(maze[row][col+1]==1)
 return(0);
 col++;
 break;

 case 75:
 if(maze[row][col-1]==1)
 return(0);
 col--;
 break;

 case 1:
 exit(0);
 default:
 return(0);
 }
 }

 void readchar(int r,int c, unsigned char *ch)
 {
 char far *v;
 v=vid_mem+(r*160)+c*2;
 *ch=*v;
 }
 void bug(int *r,int *c,int *dir,unsigned char *ch)
 {
 int trials=1,flag=0;
 char temp;
 if(abs(*r-1-row)<abs(*r-row)&&maze[*r-1][*c]!=1)
 *dir=UP;
 else
 if(abs(*r+1-row)<abs(*r-row)&&maze[*r+1][*c]!=1)
 *dir=DOWN;
 else
if(abs(*c+1-col)<abs(*c-col)&&maze[*r][*c+1]!=1)
 *dir=RIGHT;
else
if(abs(*c-1-col)<abs(*c-col)&&maze[*r][*c-1]!=1)
 *dir=LEFT;

while(1)
{
switch(*dir)
{
case RIGHT:
if(maze[*r][*c+1]!=1)
{
readchar(*r,*c+1,&temp);
if(temp==2)
{
if(maze[*r][*c-1]!=1)
*dir=LEFT;
else
{
if(maze[*r-1][*c]!=1)
*dir=UP;
else
{
if(maze[*r+1][*c]!=1)
*dir=DOWN;
}
}
}
else
{
movebugright(r,c,ch);
flag=1;
}
}
else
{
*dir=random(4);
}
break;
case LEFT:
if(maze[*r][*c-1]!=1)
{
readchar(*r,*c-1,&temp);
if(temp==2)
{
if(maze[*r][*c+1]!=1)
*dir=RIGHT;
else
{
if(maze[*r-1][*c]!=1)
*dir=UP;
else
{
if(maze[*r+1][*c]!=1)
*dir=DOWN;
}
}
}
else
{
movebugleft(r,c,ch);
flag=1;
}
}
else
{
*dir=random(4);
}
break;
case UP:
if(maze[*r-1][*c]!=1)
{
readchar(*r-1,*c,&temp);
if(temp==2)
{
if(maze[*r][*c+1]!=1)
*dir=RIGHT;
else
{
if(maze[*r][*c-1]!=1)
*dir=LEFT;
else
{
if(maze[*r+1][*c]!=1)
*dir=DOWN;
}
}
}
else
{
movebugleft(r,c,ch);
flag=1;
}
}
else
{
*dir=random(4);
}
break;
case DOWN:
if(maze[*r+1][*c]!=1)
{
readchar(*r+1,*c,&temp);
if(temp==2)
{
if(maze[*r][*c+1]!=1)
*dir=RIGHT;
else
{
if(maze[*r][*c-1]!=1)
*dir=LEFT;
else
{
if(maze[*r-1][*c]!=1)
*dir=UP;
}
}
}
else
{
movebugleft(r,c,ch);
flag=1;
}
}
else
{
*dir=random(4);
}
break;
}
if(flag==1)
break;
trials++;
if(trials>15)
break;
}
if(*r==row&&*c==col)
killeater();
}
void movebugleft(int *row,int *colm,unsigned char *ch)
{
if(*ch==0)
*ch=0;
writechar(*ch,*row,*colm,12);
*colm=*colm-1;
readchar(*row,*colm,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*colm,15);
}
void movebugright(int *row,int *colm,unsigned char *ch)
{
if(*ch==0)
*ch=0;
writechar(*ch,*row,*colm,12);
*colm=*colm+1;
readchar(*row,*colm,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*colm,15);
}
void movebugup(int *row,int *col,unsigned char *ch)
{
if(*ch==0)
*ch=0;
writechar(*ch,*row,*col,12);
*row=*row-1;
readchar(*row,*col,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*col,15);
}
void movebugdown(int *row,int *col,unsigned char *ch)
{
if(*ch==0)
*ch=0;
writechar(*ch,*row,*col,12);
*row=*row+1;
readchar(*row,*col,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*col,15);
}
void killeater(void){
int r,c;
r=row;
c=col;
writechar(1,row,col,112);
writechar(1,23,15+liveslost*3,14);
music(2);
liveslost++;
if(liveslost==3)
return;
row=12;
col=40;
writechar(1,row,col,14);
}
