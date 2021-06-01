#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>


int code=1;
union REGS i,o;
int bgcolor=5;
struct SREGS s;
char FILL[]={"Fills the selected region in active color and pattern."};
char BRUSH[]={"Draw colors with brush"};
char BAR[]={"Draws A Bar "};
char TEXT[]={"Draw a box and Type Text in it."};
char  NEW[]={"Creates A New File"};
char  OPEN[]={"Opens An Existing File"};
char  SAVE[]={"Saves The Active File"};
char  ABOUT[]={"Displays Information About Program"};
char  PENCIL[]={"Draws A Free Form Line One Pixel Width"};
char  PAINT[]={"Fills An Area With Current Drawing Colour select draw color by right click"};
char  RECTANGLE[]={"Draws A Rectangle"};
char  ELLIPSE[]={"Draws An Ellipse"};
char  LINE[]={"Draws A Straight Line"};
char  POLYLINE[]={"Draws A Polygon"};
char  COLOUR[]={"Left  Click -> Foreground Color  Right Click -> Background Color"};
char  ERASER[]={"Erases A Portion Of Figure"};
char  EXIT[]={"Quits Program"};

int hourglass[32]={
		/*hourglass screen mask*/
		0x0000,0x0000,0x0000,0x0000,
		0x8001,0xc003,0xf00f,0xfc3f,
		0xfc3f,0xf00f,0xc003,0x8001,
		0x0000,0x0000,0x0000,0x0000,
		/*the mouse ptr bitmap*/
		0xffff,0x8001,0xffff,0x8001,
		0x4002,0x2004,0x1008,0x0240,
		0x0240,0x0810,0x2004,0x4002,
		0x8001,0xffff,0x8001,0xffff};


int cursor[32]={
	//screen mask
	0xe1ff,0xe1ff,0xe1ff,0xe1ff,
	0xe1ff,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	//bit map
	0x1e00,0x1200,0x1200,0x1200,
	0x13ff,0x1249,0x1249,0xf249,
	0x9001,0x9001,0x9001,0x8001,
	0x8001,0x8001,0xffff,0x0000,
       };

 cursor2[32]={
       0x0000,0x0000,0x0000,0x0000,
       0x8008,0xc003,0xf00f,0xfc3f,
       0xfc3f,0xf00f,0xc003,0x8001,
       0x0000,0x0000,0x0000,0x0000,
       };
int plus[32]={
		/*+ screen mask*/
		0xfe7f,0xfe7f,0xfe7f,0xfe7f,
		0xfe7f,0xfe7f,0xfe7f,0x0000,
		0x0000,0xfe7f,0xfe7f,0xfe7f,
		0xfe7f,0xfe7f,0xfe7f,0xfe7f,
		/*+mouseptr bitmap*/
		0x0180,0x0180,0x0180,0x0180,
		0x0180,0x0180,0x0180,0xfe7f,
		0xfe7f,0x0180,0x0180,0x0180,
		0x0180,0x0180,0x0180,0x0180};

int rubber[32]={

		/*Eraser screen mask*/
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		/*eraser bitmap*/
		0xffff,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0x8001,
		0x8001,0x8001,0x8001,0xffff};

int pencil[32] = {
		0x3ff ,0x5ff ,0x6ff ,0x1b7f,
		0x1dbf,0x6edf,0xb76f,0xdbb7,
		0xeddb,0xf6ed,0xfb76,0xfdb8,
		0xfed9,0xff63,0xffa7,0xffcf,

		0xfc00,0xfa00,0xf900,0xe480,
		0xe240,0x9120,0x4890,0x2448,
		0x1224,0x912 ,0x489 ,0x247 ,
		0x126 ,0x9c  ,0x58  ,0x30   };

int bottle[32]={
		0x0000,0xbffe,0xdffe,0xeffe,
		0xf7fe,0xf7fe,0xf7fe,0xf7fe,
		0xf000,0xf000,0xf000,0xf7fe,
		0xf7fe,0xf7fe,0xf7fe,0xf000,
		0xffff,0x4001,0x2001,0x1001,
		0x801 ,0x801 ,0x801 ,0x801 ,
		0xfff ,0xfff ,0xfff ,0x801 ,
		0x801 ,0x801 ,0x801 ,0xfff };

int hand[32]={/*hand-screenmask+pointer bitmap*/
		0xe1ff,0xe1ff,0xe1ff,0xe1ff,
		0xe1ff,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x1e00,0x1200,0x1200,0x2100,
		0x13ff,0x1249,0x1249,0xf249,
		0x9001,0x9001,0x9001,0x8001,
		0x8001,0x8001,0xffff,0x0000};

//******************* ALL Mouse functions ******************************
 //detecting mouse
void changecursor(int *shape){
 i.x.ax=9;
 i.x.bx=0;
 i.x.cx=0;
 i.x.dx=(unsigned)shape;
 segread(&s);
 s.es=s.ds;
 int86x(0x33,&i,&i,&s);
 return;
}
restrictmouseptr(int x1,int y1,int x2,int y2){
 i.x.ax=7;
 i.x.cx=x1;
 i.x.dx=x2;
 int86(0x33,&i,&o);
 i.x.ax=8;
 i.x.cx=y1;
 i.x.dx=y2;
 int86(0x33,&i,&o);
}

initmouse()
{
i.x.ax=0;
int86(0x33,&i,&o);
return o.x.ax;
}
//show mouse on screen
void showptr()
{
i.x.ax=1;
int86(0x33,&i,&o);

}
  //hide mouse
void hideptr()
{
i.x.ax=2;
int86(0x33,&i,&o);
}
void getmpos(int *button,int*x,int* y)
{
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;     //x cor
*y=o.x.dx;            //y cor
}

void placeptr(int x, int y)
{
i.x.ax=4;
i.x.cx=x; //x coordinate
i.x.dx=y; //y coordinate
int86(0x33,&i,&o);
return;
}
//**************** Main function ***********************************
int main()
{
       //	void * brush;
	//void * pencil, * eraser;

	int active_color=0,i,left,right,pattern=0;
	int x,y,button;
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"..\\bgi");
	initmouse();
	//brush=draw_brush();
	//pencil=draw_pencil();
	//eraser=draw_eraser();
	draw_panel();
	show_selected_color(active_color);
	setcolor(0);
	outtextxy(192,9,"Untitled");

       while(1)
	{

	 // show_mouse_ptr(); // show mouse pointer on the screen
	  getmpos(&button,&x,&y);
	   if(button==1) //color selection in color box
	   {
	      getmpos(&button,&x,&y);
	       left=15,right=35;
	     for(i=0;i<7;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>30)&&(y<45))
	       {
		 active_color=i;

	       }
	       left+=20;
	       right+=20;
	     }

	      left=15,right=35;
	     for(i=0;i<7;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>50)&&(y<63))
	       {
		 active_color=i+8;
	       }
	       left+=20;
	       right+=20;
	     }
	     show_selected_color(active_color);
	   }//if ends


	   if(button==1) //fill pattern selection in pattern box
	   {
	      getmpos(&button,&x,&y);
	       left=15,right=25;
	     for(i=0;i<5;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>205)&&(y<225))
	       {
		 pattern=i+1;

	       }
	       left+=15;
	       right+=15;
	     }

	      left=15,right=25;
	     for(i=0;i<5;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>230)&&(y<250))
	       {
		 pattern=i+6;
	       }
	       left+=20;
	       right+=20;
	     }
	    // show_selected_color(active_color);
	    setcolor(15);
	    rectangle(10,166,89,190);
	    setfillstyle(pattern,active_color);
	    floodfill(20,180,15);
	   }//if ends

	   gotoxy(3,18);
	  // printf("%d",pattern);
	   //show pattern selected in flood fill box
	  // setcolor(15);
	  // rectangle(10,170,90,190);
	  // setfillstyle(pattern,15);
	   //floodfill(20,180,15);

	   select_tool(active_color,pattern);
       //	 paint_with_brush(brush,active_color);// paint color with brush
	  getmpos(&button,&x,&y);
	  if((x>568)&&(x<615)&&(y>326)&&(343)&&(button==1)){
	    return;
	  }
       if((x>568)&&(x<615)&&(y>164)&&(y<183)&&(button==1)){
	  //  setfillstyle(1,bgcolor);
	   // floodfill(200,200,15);
	   int i,j;
	    for(i=101;i<540;i++){
	      for(j=81;j<460;j++){
		putpixel(i,j,bgcolor);
	      }
	    }
       }
       // about
	  if((x>568)&&(x<615)&&(y>286)&&(y<303)&&(button==1)){
	    FILE *fp;
	    int i,j;
	    char ch;
	   hideptr();
		  fp=fopen("temp.bmp","w+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=100;i<540;i++)
	      {
		for(j=80;j<470;j++)
	       {
		  ch=getpixel(i,j);
		  fputc(ch,fp);
	       }
	      }
	       fclose(fp);


	   setcolor(3);
	   setfillstyle(1,2);
	   bar3d(144,126,507,403,0,1);
	   outtextxy(195,185,"Developed By :");
	   setcolor(4);
	   outtextxy(251,223,"Narinder Sharma");
	   setcolor(5);
	   outtextxy(194,266,"G.G.M SCIENCE COLLEGE JAMMU ");
	   outtextxy(174,363,"Press ESC To Exit ");
	   while(1){
	    char ch;
	    ch=getch();
	    if(ch==27){
	    break;}
	   }
	     fp=fopen("temp.bmp","r+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=100;i<540;i++)
	      {
		for(j=80;j<470;j++)
	       {
		  ch=fgetc(fp);
		  putpixel(i,j,ch);
		  if(ch==EOF)
		  break;
	       }
	      }
	       fclose(fp);

	   showptr();

	  }
       // ************** SAVE A FILE ********************

	      if((x>568)&&(x<615)&&(y>246)&&(y<263)&&(button==1)){

		 FILE *fp;
	    int i,j;
	    char ch;
	    char buffer[16],c[16];
	    hideptr();
		  fp=fopen("temp.bmp","w+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=200;i<=450;i++)
	      {
		for(j=170;j<=315;j++)
	       {
		  ch=getpixel(i,j);
		  fputc(ch,fp);
	       }
	      }
	       fclose(fp);
	       setcolor(2);
		rectangle(200,170,450,315);
		rectangle(200,170,450,190);
		setfillstyle(1,8);
		floodfill(220,220,2);
		setfillstyle(1,4);
		floodfill(326,180,2);
		setcolor(2);
		outtextxy(236,178,"SAVE");
		outtextxy(227,205,"Enter File Name :");
		// c[i]=32;
		 for(i=0;c[i-1]!='\n'&& i<10;i++){
		   int x1=266,y1=240;
		   label:
		   c[i]=getch();
		   if(c[i]==13){
		     c[i]='\0';
		     break;
		   }
		   if(c[i]==8){
		     setcolor(8);
		     outtextxy(x1,y1,c);
		     i=i-1;
		    // c[i-1]=32;
		     c[i]='\0';
		    // y1+=10;
		    setcolor(2);
		     outtextxy(x1,y1,c);showptr();
		     goto label;

		   }
		  // c[i+1]=32;
		   c[i+1]='\0';
		   sprintf(buffer,"%s",c);
		   outtextxy(x1,y1,buffer);

		 }//for ends
	    //show file is saved
	    setfillstyle(1,3);
	    floodfill(220,220,2);
	    outtextxy(220,220,"File is saved successfully");
	    while(1){
	      ch=getch();
	      if(ch==13){
		break;
	      }
	     }

	     fp=fopen("temp.bmp","r+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=200;i<=450;i++)
	      {
		for(j=170;j<=315;j++)
	       {
		  ch=fgetc(fp);
		  putpixel(i,j,ch);
		  if(ch==EOF)
		  break;
	       }
	      }
	       fclose(fp);
		 //saved file
		 strcat(c,".bmp");
		  fp=fopen(c,"w+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=100;i<=540;i++)
	      {
		for(j=80;j<=460;j++)
	       {
		  ch=getpixel(i,j);
		  fputc(ch,fp);
	       }
	      }
	      fputc(bgcolor,fp);
	       fclose(fp);


	   showptr();


	    } // save button ends

       //************************************************
       //****************** OPEN AN IMAGE *****************

	   getmpos(&button,&x,&y);
	   if((x>568)&&(x<615)&&(y>204)&&(y<223)&&(button==1)){
		FILE *fp,*fp1;
	    int i,j;
	    char ch;
	    char buffer[16],c[20];
	    hideptr();
		  fp=fopen("temp.bmp","w+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  return ;
		}
	       for(i=200;i<=450;i++)
	      {

		for(j=170;j<=315;j++)
	       {
		  ch=getpixel(i,j);
		  fputc(ch,fp);
	       }
	      }
	       fclose(fp);
	       setcolor(2);
		rectangle(200,170,450,315);
		rectangle(200,170,450,190);
		setfillstyle(1,8);
		floodfill(220,220,2);
		setfillstyle(1,4);
		floodfill(326,180,2);
		setcolor(2);
		outtextxy(236,178,"OPEN");
		outtextxy(227,205,"Enter File Name :");

		    for(i=0;c[i-1]!='\n'&& i<10;i++){
		   int x1=266,y1=240;
		   label1:
		   c[i]=getch();
		   if(c[i]==13){
		     c[i]='\0';
		     break;
		   }
		   if(c[i]==8){
		     setcolor(8);
		     outtextxy(x1,y1,c);
		     i=i-1;
		    // c[i-1]=32;
		     c[i]='\0';
		    // y1+=10;
		    setcolor(2);
		     outtextxy(x1,y1,c);showptr();
		     goto label1;

		   }
		  // c[i+1]=32;
		   c[i+1]='\0';
		   sprintf(buffer,"%s",c);
		   outtextxy(x1,y1,buffer);

		 }//for ends

	    //show file is opened
	    strcat(c,".bmp");

	    fp1=fopen(c,"r+");
	    if(fp1==NULL){ // check if file exists.
		 //read background
		 outtextxy(300,300,"Cannot open file");
		 delay(1000);
		fp=fopen("temp.bmp","r+");
		if(fp==NULL)
		{
		  outtextxy(200,200,"cannot open file ");
		  //delay(1000);
		  return ;
		}

	       for(i=200;i<=450;i++)
	      {
		for(j=170;j<=315;j++)
	       {
		  ch=fgetc(fp);
		  putpixel(i,j,ch);
		  if(ch==EOF)
		  break;
	       }
	      }
	       fclose(fp);

	    } //if ends
	    else{
	      setfillstyle(1,8);
	      floodfill(220,220,2);
	      outtextxy(220,220,"File is Opened Successfully");
	      while(1){
	       ch=getch();
	       if(ch==13){
		break;
	       }
	      }

	       for(i=100;i<=540;i++)
	      {
		for(j=80;j<=460;j++)
	       {
		  ch=fgetc(fp1);
		  putpixel(i,j,ch);
		  if(ch==EOF)
		  break;
	       }
	      }
	      bgcolor=getc(fp1);
	       fclose(fp1);

	    }//else ends

	       //open file
	       //strcat(c,".bmp");


	   }//open ends
       //*************************************************

   //    ****************************************************


	   //close button  **********************************
	   if((x>620)&&(x<638)&&(y>3)&&(y<18) &&(button==1)){
	    return ;
	   }
	   else if(!(x>620)&&(x<638)&&(y>3)&&(y<18))
	   {

	    hideptr();
	    setfillstyle(1,7);
	    floodfill(625,10,12);
	    line(622,12,633,6);
	    line(622,6,633,12);
	    showptr();
	   }
	   else if((x>620)&&(x<638)&&(y>3)&&(y<18)){
	     hideptr();
	     setfillstyle(1,4);
	     floodfill(625,10,12);
	     line(622,12,633,6);
	    line(622,6,633,12);
	     showptr();
	   }
	    line(622,12,633,6);
	    line(622,6,633,12);

       //**********************************************************

	   if(1)// code to display mouse position
	   {

	    char buffer[20];
	    setcolor(4);
	    //rectangle(550,440,630,460);
	    getmpos(&button,&x,&y);
	    sprintf(buffer,"x:%d y:%d ",x,y);
	   // delay(10);
	    outtextxy(530,467,buffer);
	    delay(50);
	    setcolor(7);
	    outtextxy(530,467,buffer);
	   }
	   hover();
	   changebgcolor();
	   info();
	}//while ends
	closegraph();

}//main ends
//**********************************************************************
   info(){
     int x,y,button;
     setcolor(8);
     rectangle(0,462,640,480);
     setfillstyle(1,8);
     floodfill(50,470,8);
     getmpos(&button,&x,&y);
     if((x>6)&&(x<155)&&(y>26)&&(y<69)){  //color box
       setcolor(4);
       outtextxy(10,465,"Left Click ->Foreground color  Right Click->Background Color");
       delay(20);
     }
     else{
	 setcolor(8);
       outtextxy(10,465,"Left Click ->Foreground color  Right Click->Background Color");

     }

     if((x>568)&&(x<615)&&(y>164)&&(y<183)){
     setcolor(4);
     outtextxy(10,465,NEW);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,NEW);
     }

     if((x>568)&&(x<615)&&(y>204)&&(y<223)){  //open
     setcolor(4);
     outtextxy(10,465,OPEN);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,OPEN);
     }

     if((x>568)&&(x<615)&&(y>246)&&(y<263)){     //save
     setcolor(4);
     outtextxy(10,465,SAVE);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,SAVE);
     }

     if((x>568)&&(x<615)&&(y>286)&&(y<303)){   //about
     setcolor(4);
     outtextxy(10,465,ABOUT);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,ABOUT);
     }

     if((x>568)&&(x<615)&&(y>326)&&(y<343)){//exit
     setcolor(4);
     outtextxy(10,465,EXIT);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,EXIT);
     }

     if((x>451)&&(x<478)&&(y>39)&&(y<57)){   //rectangle
     setcolor(4);
     outtextxy(10,465,RECTANGLE);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,RECTANGLE);
     }

     if((x>492)&&(x<512)&&(y>39)&&(y<59)){ //ellipse
     setcolor(4);
     outtextxy(10,465,ELLIPSE);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,ELLIPSE);
     }

     if((x>525)&&(x<546)&&(y>41)&&(y<56)){    //line
     setcolor(4);
     outtextxy(10,465,LINE);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,LINE);
     }

     if((x>10)&&(x<50)&&(y>100)&&(y<150)){    //text
     setcolor(4);
     outtextxy(10,465,TEXT);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,TEXT);
     }

     if((x>568)&&(x<594)&&(y>42)&&(y<55)){  //bar3d
     setcolor(4);
     outtextxy(10,465,BAR);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,BAR);
     }

     if((x>227)&&(x<256)&&(y>27)&&(y<50)){ //pencil
     setcolor(4);
     outtextxy(10,465,PENCIL);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,PENCIL);
     }

     if((x>272)&&(x<306)&&(y>29)&&(y<49)){  //eraser
     setcolor(4);
     outtextxy(10,465,ERASER);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,ERASER);
       delay(50);
     }

     if((x>372)&&(x<412)&&(y>29)&&(y<49)){//brush
     setcolor(4);
     outtextxy(10,465,BRUSH);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,BRUSH);
     }

     if((x>323)&&(x<360)&&(y>29)&&(y<49)){   //fill
     setcolor(4);
     outtextxy(10,465,FILL);
     delay(50);
     }
     else{
       setcolor(8);
       outtextxy(10,465,FILL);
     }
   }  //info()ends

   changebgcolor(){
    int x,y,button,i,left,right;
    getmpos(&button,&x,&y);
    if(button==2){ //right click
	getmpos(&button,&x,&y);
	       left=15,right=35;
	     for(i=0;i<7;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>30)&&(y<45))
	       {
		 bgcolor=i;
		 hideptr();
		 setcolor(bgcolor);
		 rectangle(100,80,540,460);
		 setfillstyle(1,bgcolor);
		 floodfill(200,200,bgcolor);
		 showptr();

	       }
	       left+=20;
	       right+=20;
	     }

	      left=15,right=35;
	     for(i=0;i<7;i++)     //rectangle(left,50,right,63);
	     {
	       if((x>left)&&(x<right)&&(y>50)&&(y<63))
	       {
		 bgcolor=i+8;
		  hideptr();
		 setcolor(bgcolor);
		 rectangle(100,80,540,460);
		 setfillstyle(1,bgcolor);
		 floodfill(200,200,bgcolor);
		 showptr();

	       }
	       left+=20;
	       right+=20;
	     }

    }
   }//changebgcolor()ends

   hover(){
    int x,y,button;
    getmpos(&button,&x,&y);
    if((x>225)&&(x<260)&&(y>28)&&(y<50)){//pencil
     if(button==1){
      setcolor(2);
      rectangle(225,28,260,50);
     }
      else{
	setcolor(4);
	rectangle(225,28,260,50);
      }
    }
    else{
     setcolor(15);
     rectangle(225,28,260,50);
    }

    if((x>275)&&(x<310)&&(y>28)&&(y<50)){//eraser
     if(button==1){
      setcolor(2);
      rectangle(275,28,310,50);
     }
      else{
	setcolor(4);
	rectangle(275,28,310,50);
      }
    }
    else{
     setcolor(15);
     rectangle(275,28,310,50);
    }

    if((x>325)&&(x<365)&&(y>28)&&(y<50)){//fill
     if(button==1){
      setcolor(2);
      rectangle(325,28,365,50);
     }
      else{
	setcolor(4);
	rectangle(325,28,365,50);
      }
    }
    else{
     setcolor(15);
     rectangle(325,28,365,50);
    }

    if((x>375)&&(x<415)&&(y>28)&&(y<50)){//brush
     if(button==1){
      setcolor(2);
      rectangle(375,28,415,50);
     }
      else{
	setcolor(4);
	rectangle(375,28,415,50);
      }
    }
    else{
     setcolor(15);
     rectangle(375,28,415,50);
    }

    if((x>451)&&(x<478)&&(y>39)&&(y<57)){//rectangle
     if(button==1){
      setcolor(2);
      rectangle(450,38,479,58);
     }
      else{
	setcolor(4);
	rectangle(450,38,479,58);
      }
    }
    else{
     setcolor(15);
     rectangle(450,38,479,58);
    }

    if((x>492)&&(x<512)&&(y>39)&&(y<59)){//circle
     if(button==1){
      setcolor(2);
      rectangle(491,38,513,60);
     }
      else{
	setcolor(4);
	rectangle(491,38,513,60);
      }
    }
    else{
     setcolor(7);
     rectangle(491,38,513,60);
    }

    if((x>525)&&(x<546)&&(y>41)&&(y<56)){//line
     if(button==1){
      setcolor(2);
      rectangle(524,40,547,57);
     }
      else{
	setcolor(4);
	rectangle(524,40,547,57);
      }
    }
    else{
     setcolor(7);
     rectangle(524,40,547,57);
    }

    if((x>567)&&(x<594)&&(y>42)&&(y<55)){//bar3d
     if(button==1){
      setcolor(2);
      rectangle(566,38,598,56);
     }
      else{
	setcolor(4);
	rectangle(566,38,598,56);
      }
    }
    else{
     setcolor(7);
     rectangle(566,38,598,56);
    }

    if((x>10)&&(x<50)&&(y>100)&&(y<150)){//text box
     if(button==1){
      setcolor(2);
      rectangle(10,100,50,150);
     }
      else{
	setcolor(4);
	rectangle(10,100,50,150);
      }
    }
    else{
     setcolor(15);
     rectangle(10,100,50,150);
    }

      if((x>568)&&(x<615)&&(y>164)&&(y<183)){//new
     if(button==1){
      setcolor(2);
      rectangle(568,164,615,183);
     }
      else{
	setcolor(4);
	rectangle(568,164,615,183);
      }
    }
    else{
     setcolor(15);
     rectangle(568,164,615,183);
    }

     if((x>568)&&(x<615)&&(y>204)&&(y<223)){//open
     if(button==1){
      setcolor(2);
      rectangle(568,204,615,223);
     }
      else{
	setcolor(4);
	rectangle(568,204,615,223);
      }
    }
    else{
     setcolor(15);
     rectangle(568,204,615,223);
    }

     if((x>568)&&(x<615)&&(y>246)&&(y<263)){//save
     if(button==1){
      setcolor(2);
      rectangle(568,246,615,263);
     }
      else{
	setcolor(4);
	rectangle(568,246,615,263);
      }
    }
    else{
     setcolor(15);
     rectangle(568,246,615,263);
    }

     if((x>568)&&(x<615)&&(y>286)&&(y<303)){//about
     if(button==1){
      setcolor(2);
      rectangle(568,286,615,303);
     }
      else{
	setcolor(4);
	rectangle(568,286,615,303);
      }
    }
    else{
     setcolor(15);
     rectangle(568,286,615,303);
    }

     if((x>568)&&(x<615)&&(y>326)&&(y<343)){//exit
     if(button==1){
      setcolor(2);
      rectangle(568,326,615,343);
     }
      else{
	setcolor(4);
	rectangle(568,326,615,343);
      }
    }
    else{
     setcolor(15);
     rectangle(568,326,615,343);
    }
   }//hover() ends

//***************************** SCREEN **************************
draw_panel()
{
 setcolor(15);
 rectangle(0,0,639,20);

 //setcolor(2);
 setcolor(15);
 rectangle(0,20,639,479);
 rectangle(0,20,639,75);//create tool bar
 rectangle(10,25,160,70); //create color panel
 create_color_box();
 setfillstyle(1,7);
 floodfill(30,47,15);  //fill color box layers
setfillstyle(1,7);
 floodfill(400,50,15);//fill tool bar
 floodfill(10,10,15);  //fill top
 outtextxy(320,10,"Paint ");
 floodfill(100,400,15);
 setcolor(15);
 rectangle(100,80,540,460);//working panel
 setfillstyle(1,bgcolor);
 floodfill(150,200,15);
 setcolor(15);
	rectangle(215,25,420,70);  //tool bar
	rectangle(225,28,260,50); //pencil
	line(270,25,270,70);
	rectangle(275,28,310,50);//eraser
	line(320,25,320,70);
	rectangle(325,28,365,50); //fill color box
	rectangle(333,32,360,46);
	rectangle(333,36,360,46);
	setfillstyle(1,4);
	floodfill(340,40,15);
	setcolor(12);

	outtextxy(335,60,"Fill");
	setcolor(15);
	line(370,25,370,70);
	rectangle(375,28,415,50); // brush
	outtextxy(376,38,"BRUSH");
	//line(380,30,410,45);
	setcolor(3);
	//line(405,31,390,39);
	//line(412,31,394,39);
	//line(405,31,412,31);
       //	ellipse(390,40,0,100,3,2);
	//circle(390,40,2);
	//setfillstyle(1,4);
	//floodfill(390,40,3);
	setcolor(12);
	outtextxy(375,60,"Brush");

	setcolor(12);
	line(240,30,237,45);//vertical line 1
	line(244,30,242,45);//vertical line  2
	line(240,30,244,30);// horizontal top
	line(240,32,244,32);
	line(237,45,238,46);
	line(242,45,238,46);
	setfillstyle(1,12);
	floodfill(242,35,12);
	outtextxy(222,60,"Pencil");

	rectangle(280,32,305,45);//eraser icon
	rectangle(290,32,305,45);
	floodfill(295,38,12);
	outtextxy(272,60,"Eraser");

	setcolor(15);
	rectangle(440,25,620,70);//shape tool
	rectangle(444,28,616,67);//shape tool
	rectangle(451,39,478,57);//rectangle tool
	line(483,25,483,71);
	circle(502,49,10);//circle
	line(520,25,520,71);
	line(546,41,525,56);//line tool
	line(560,25,560,71);
	bar3d(567,42,594,55,3,1);//bar3d

	rectangle(10,100,50,150);// text box outer layer
	rectangle(15,105,45,135);//text box
	outtextxy(20,120,"A");
	setcolor(0);
	outtextxy(20,140,"TEXT ");
	setcolor(15);
	create_fillstyle_box();

	setcolor(12);
	rectangle(620,3,638,16);
	setcolor(15);
	line(622,12,633,6);
	line(622,6,633,12);
	//option dialog box
	rectangle(561,108,625,408);
	rectangle(564,110,622,406);
	line(564,150,622,150);
	line(564,152,622,152);
	rectangle(568,164,615,183);//new
	rectangle(570,166,613,181);
	rectangle(568,204,615,223);//open
	rectangle(570,206,613,221);
	rectangle(568,246,615,263);//save
	rectangle(570,248,613,261);
	rectangle(568,286,615,303);//about
	rectangle(570,288,613,301);
	rectangle(568,326,615,343);//exit
	rectangle(570,328,613,341);
	setfillstyle(1,8);
	floodfill(568,126,15);
	floodfill(573,173,15);
	floodfill(573,211,15);
	floodfill(573,253,15);
	floodfill(573,295,15);
	floodfill(573,332,15);

	setcolor(2);
	outtextxy(568,126,"Options");
	outtextxy(573,173,"New");
	outtextxy(573,211,"Open");
	outtextxy(573,253,"Save");
	outtextxy(573,294,"About");
	outtextxy(573,332,"Exit");

}

create_fillstyle_box()
{
  int i;
  int left,right;
  setcolor(15);
  rectangle(10,200,90,260);
  left=15;right=25;
  for(i=1;i<6;i++)
  {
   rectangle(left,205,right,225);
   setfillstyle(i,15);
   floodfill(left+5,210,15);
   left+=15;
   right+=15;
  }

  left=15,right=25;
  for(i=6;i<11;i++)
  {
   rectangle(left,230,right,250);
   setfillstyle(i,15);
   floodfill(left+5,240,15);
   left+=15;
   right+=15;
  }

}//end of function

create_color_box()
{
 int i,left,right;
 setcolor(15);
 left=15;right=35;
 for(i=0;i<7;i++)
 {
  rectangle(left,30,right,45);
  setfillstyle(1,i);
  floodfill(left+5,40,15);
  left+=20;
  right+=20;
 }
 left=15,right=35;
 for(i=8;i<15;i++)
 { rectangle(left,50,right,63);
   setfillstyle(1,i);
   floodfill(left+5,55,15);
   left+=20;
   right+=20;
 }
}

show_selected_color(int color)
{
  setcolor(15);
  rectangle(165,25,185,50);
  setfillstyle(1,color);
  floodfill(180,35,15);
  setcolor(0);
  outtextxy(170,53,"color");
}

detect_tool()
{
  int bt,x,y;
  getmpos(&bt,&x,&y);
  if(bt==1)
  {
   //225,28,260,50); //pencil
   if((x>225)&&(x<260)&&(y>28)&&(y<50))
   {
    code=1;
   }
   //275,28,310,50);//eraser
   if((x>275)&&(x<310)&&(y>28)&&(y<50))
   {
    code=2;
   }
   //325,28,365,50 // fill
   if((x>325)&&(x<365)&&(y>28)&&(y<50))
   {
    code =3;
   }

    //375,28,415,50); // brush
   if((x>375)&&(x<415)&&(y>28)&&(y<50))
   {
     code=4;
   }
   //rectangle tool
   if((x>451)&&(x<478)&&(y>39)&&(y<57))
   {
    code=5;
   }
   //circle
   if((x>492)&&(x<512)&&(y>39)&&(y<59))
   {
    code=6;
   }
   //(15,105,45,135) text box
   if((x>15)&&(x<45)&&(y>105)&&(y<135))
   {
     code=7;//text box;
   }
   if((x>525)&&(x<546)&&(y>41)&&(y<56)){
    code=8;//line
   }
   if((x>567)&&(x<594)&&(y>42)&&(y<55)){
    code=9;//bar3d
   }
   if((x>568)&&(x<615)&&(y>164)&&(183)){
    code=10;//new
   }
   if((x>568)&&(x<615)&&(y>204)&&(223)){
    code=11;//open
   }
   if((x>568)&&(x<615)&&(y>246)&&(263)){
    code=12;//save
   }
   if((x>568)&&(x<615)&&(y>286)&&(303)){
    code=13;//about
   }
   if((x>568)&&(x<615)&&(y>326)&&(343)){
    code=14;//exit
    return;
   }
 }
  return code;
}

fill_pattern(int pattern, int active_color){
  int a,b,c,d,color1,color2,color3,color4,button,x,y;
  changecursor(bottle);
   getmpos(&button,&x,&y);

	    if(button==1)
	    {
	      a=b=x;
	      c=d=y;
	     for(a;a<535;a++)
	     {
	      hideptr();
	      color1=getpixel(a,y);
	      showptr();
	      if((color1!=bgcolor))
	      {
	       break;
	      }
	     }// for ends
	      for(;b>105;b--)
	     {
	      hideptr();
	      color2=getpixel(b,y);
	      showptr();
	      if((color2!=bgcolor))
	      {
	       //printf("\n%d",color2);
	       break;
	      }
	     }// for ends

	     for(c;c<455;c++)
	     {
	      hideptr();
	      color3=getpixel(x,c);
	      showptr();
	     // printf("%d ",color1);
	      if((color3!=bgcolor))
	      {
	       //printf("%d",color3);
	       break;
	      }
	     }// for ends

	     for(d;d>90;d--)
	     {
	      hideptr();
	      color4=getpixel(x,d);
	      showptr();
	      if((color4!=bgcolor))
	      {
	      // printf("\n%d",color4);
	       break;
	      }
	     }// for ends

	     if(color1==color2)
	       if(color3==color4)
	       if(color1==color4)
		{
		  setcolor(color1);
		  rectangle(100,80,540,460);
		  delay(10);
		  hideptr();
		  setfillstyle(pattern,active_color);
		  floodfill(x,y,color1);
		  showptr();
		}
	  }//button==1 close

}

select_tool(int active_color,int pattern)
{
   int x,y,button,x1,y1;
    code=detect_tool();
   //225,28,260,50); //pencil
    getmpos(&button,&x,&y);
    if((x>115)&&(x<525)&&(y>95)&&(y<455)) //working space
    { showptr();
     switch(code){
     case 1 :      //pencil draw code
		  changecursor(pencil);
		  getmpos(&button,&x,&y);
		  getmpos(&button,&x1,&y1);
		  while(button==1 && ((x>100)&&(x<540)&&(y>80)&&(y<460))){

		     if((x>100)&&(x<529)&&(y>80)&&(y<449)){
		      hideptr();
		      setcolor(active_color);
		      line(x,y,x1,y1);
		      showptr();
		    }
		    x1=x,y1=y;
		    getmpos(&button,&x,&y);
		  }
		    //end
		  break;
     case 2 :     // eraser box
		       changecursor(rubber);
		       getmpos(&button,&x,&y);
		       while(button==1 &&((x>100)&&(x<529)&&(y>80)&&(y<449)))
		       {        hideptr();
				setcolor(bgcolor);
				rectangle(x,y,x+10,y+10);
				setfillstyle(1,bgcolor);
				floodfill(x+4,y+4,bgcolor);
				showptr();
				getmpos(&button,&x,&y);
		       } changecursor(rubber);
		 //end
		 break;
     case 3 :   fill_pattern(pattern,active_color);  //fill pattern
		break;
     case 4 :      // brush draw

		 getmpos(&button,&x,&y);
		 changecursor(pencil);
		 while(button==1 &&((x>100)&&(x<529)&&(y>80)&&(y<449)))
		{
		if(((x>100)&&(x<540)&&(y>80)&&(y<460))){
		 hideptr();
		 setcolor(active_color);
		 circle(x,y,0);
		 circle(x+1,y,0);
		 circle(x,y+1,0);
		 circle(x+1,y+1,0);
		 showptr();
		 }
		 getmpos(&button,&x,&y);
		 //circle(x1,y1,0);
		// circle(x1+1,y1,0);
		 //circle(x1,y1+1,0);
		 //circle(x1+1,y1+1,0);

		}
		break;
     case 5 :  draw_rect(active_color);
	       break;
     case 6 :  draw_circle(active_color);
	       break;
     case 7 :  type_text(active_color);
	       break;
     case 8 :  draw_line(active_color);
	       break;
     case 9 :  draw_bar(active_color,pattern);
	       break;
     default: showptr();

     }//end of switch
    }//end of working space
    else
    {
     showptr();
     changecursor(hand);
    }

 } //function ends


 draw_line(int active_color){
  int x,y,bt,x1,y1,k=0;
  //showptr();
  changecursor(plus);
 // outtextxy(200,34,"line");
  getmpos(&bt,&x1,&y1);
  getmpos(&bt,&x,&y);
	 while(bt==1 && ((x>100)&&(x<540)&&(y>80)&&(y<460)))
	 {
	     k=bt;
	      if (bt==1 &&((x>100)&&(x<540)&&(y>80)&&(y<460))){
	     hideptr();
	     setcolor(active_color);
	     line(x1,y1,x,y);
	     delay(100);
	     setcolor(bgcolor);
	     line(x1,y1,x,y);
	     showptr();
	     }
	       getmpos(&bt,&x,&y);
	 }
	 if(k==1 &&((x>100)&&(x<540)&&(y>80)&&(y<460))){
	 hideptr();
	  setcolor(active_color);
	  line(x1,y1,x,y);
	  k=0;
	  showptr();
	 }
	 showptr();
 }

 draw_bar(int active_color,int pattern){
    int k,x1,y1,x,y,button,depth=20;
  // showptr();
  changecursor(plus);
    getmpos(&button,&x1,&y1);
    getmpos(&button,&x,&y);
	 while(button==1 && ((x>120)&&(x<520)&&(y>100)&&(y<440)))
	 {

	    k=button;
	    getmpos(&button,&x,&y);
	  if(button==1 &&((x>120)&&(x<520)&&(y>100)&&(y<440))){
	    hideptr();
	    setcolor(active_color);
	    bar3d(x1,y1,x,y,depth,1);
	    delay(100);
	    setfillstyle(pattern,active_color);
	    setcolor(bgcolor);
	    bar3d(x1,y1,x,y,depth,1);
	    showptr();
	    }
	 }
	  if(k==1 &&((x>120)&&(x<520)&&(y>100)&&(y<440)))
	 {
	  hideptr();
	  setcolor(active_color);
	  bar3d(x1,y1,x,y,depth,1);
	  k=0;
	  showptr();
	 }
	 showptr();

 }

 draw_rect(int active_color){
  int k,x1,y1,x,y,button;
  // showptr();
    changecursor(plus);
    getmpos(&button,&x1,&y1);
    getmpos(&button,&x,&y);
	 while((button==1)&&((x>100)&&(x<540)&&(y>80)&&(y<460)))
	 {
	    k=button;

	    if((x>100)&&(x<540)&&(y>80)&&(y<460)){
	    hideptr();
	    setcolor(active_color);
	    rectangle(x1,y1,x,y);
	    delay(100);
	    setcolor(bgcolor);
	    rectangle(x1,y1,x,y);
	    showptr();
	     }
		 getmpos(&button,&x,&y);
	 }
	  if(k==1 &&(x>100)&&(x<540)&&(y>80)&&(y<460))
	 {
	  hideptr();
	  setcolor(active_color);
	  rectangle(x1,y1,x,y);
	  k=0;
	  showptr();
	 }

	 showptr();
 }
 type_text(int active_color){
    int k,x1,y1,x,y,button;
     int i=0,a=0,b=0,space=0;
      char buffer[8],buffer2[8];
      char ch,chprev;

   //showptr();
    changecursor(plus);
    getmpos(&button,&x1,&y1);
    getmpos(&button,&x,&y);
	 while(button==1 && ((x>100)&&(x<540)&&(y>80)&&(y<460)))
	 {

	    k=button;
	    if((x>100)&&(x<540)&&(y>80)&&(y<460)){
	    hideptr();
	    setcolor(active_color);
	    rectangle(x1,y1,x,y);
	    delay(100);
	    setcolor(bgcolor);
	    rectangle(x1,y1,x,y);
	    i=1;
	     showptr();
	    }
	     getmpos(&button,&x,&y);

	 }

	//code to type text
	     a=x1+10,b=y1+10;
	   if(i==1)
	   {
	     //char c;
	   //  ch=getch();
	    while(!(ch==13))
	    {
	       int flag=0;
	      space:
	      line(a+10,b,a+10,b+10);
	     ch=getch();

	    if((a>x1)&&(a<x-2)&&(b>y1)&&(b<y))//control the cursor to next line
	    {
	      setcolor(active_color);
	      //printf("t");

	     //ch=getch();
	     if(ch==13)
	     {

	      break;
	     }

	       if(ch==8)
	       {
		 //ch=32;
		// a=a-20;
		setcolor(bgcolor);
		 sprintf(buffer,"%c",ch);
		 outtextxy(a,b,buffer);
		 a-=10;
		 ch=0;
		 sprintf(buffer2,"%c",ch);
		 outtextxy(a,b,buffer2);
		 outtextxy(a+10,b,buffer2);
		 outtextxy(a-10,b,buffer2);
	     //	 flag=0;
		// setcolor(active_color);
		// outtextxy(a,b,buffer);
		 goto space;
	       //  outtextxy(a,b,buffer);
		 //a=a-20;

	       }


	     line(a+10,b,a+10,b+10);
	     sprintf(buffer,"%c",ch);
	     setcolor(active_color);
	     outtextxy(a,b,buffer);
	     setcolor(bgcolor);
	     line(a,b,a,b+10);
	     a+=10;

	    }
	    else //next line
	    {
	      i++;
	      a=x1+10;
	      b=y1+i*10;

	    }
	    }
	   }



 }//end

 draw_circle(int active_color){
  int x1,y1,i=0,xr=0,yr=0,k,button,x,y;
     //showptr();
     changecursor(plus);
	getmpos(&button,&x1,&y1);
    getmpos(&button,&x,&y);
	 while(button==1 && ((x-abs(x1-x)>100)&&(x+abs(x1-x)<540)&&(y-abs(y1-y)>80)&&(y+abs(y1-y)<460)) )
	 {
	    if((x-abs(x1-x)>100)&&(x+abs(x1-x)<540)&&(y-abs(y1-y)>80)&&(y+abs(y1-y)<460)){
	    k=button;
	    hideptr();
	    setcolor(active_color);
	    ellipse(x,y,0,360,abs(x1-x),abs(y1-y));
	    delay(100);
	    setcolor(bgcolor);
	    ellipse(x,y,0,360,abs(x1-x),abs(y1-y));
	    showptr();
	    }
	    getmpos(&button,&x,&y);
	 }
	  if(k==1&&((x-abs(x1-x)>100)&&(x+abs(x1-x)<540)&&(y-abs(y1-y)>80)&&(y+abs(y1-y)<460)) )
	 {
	  setcolor(active_color);
	  ellipse(x,y,0,360,abs(x1-x),abs(y1-y));
	  k=0;
	 }
       showptr();
 }//end

