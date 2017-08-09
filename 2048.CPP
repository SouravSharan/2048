//2048
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>

//function prototypes
void grid();
void newgame();
void instr();
void display();
void ifover();
void ifwin();
void menu();
void logo();

//global variables
int arr[4][4];
int check_change[4][4];
int way[4][4];
int way_clr[4][4];
char clr[4][4][5];
char ch[4][4][5];
int flag[16];
int score;
char score_clr[6];
char score_ch[6];

void main(){
	clrscr();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	logo();
	getch();
}

void newgame(){
	grid();
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			arr[i][j]=0;
		}
	}
	arr[0][3]=2;
	score=0;
	score_ch[0]=0;
	score_ch[1]='\0';
	display();
	char press;
	while(1){
		if(kbhit()){
			for(i=0;i<4;i++){
				for(int j=0;j<4;j++){
					check_change[i][j]=arr[i][j];
				}
			}
			char press = getch();
			switch(press){
				case 27:
					cleardevice();
					menu();
				case 'w':
					//up
					for(i=0;i<4;i++){
						for(int j=0;j<4;j++){
							if(arr[i][j]==0){
								for(int k=j+1;k<4;k++){
									if(arr[i][k]!=0){
										arr[i][j]=arr[i][k];
										arr[i][k]=0;
										break;
									}
								}
							}
						}
					}
					for(i=0;i<4;i++){
						for(int j=0;j<4;j++){
							if(arr[i][j]==arr[i][j+1]){
								arr[i][j]+=arr[i][j+1];
								score+=arr[i][j];
								for(int k=j+1;k<3;k++){
									arr[i][k]=arr[i][k+1];
								}
								arr[i][3]=0;
							}
						}
					}
					break;
				case 'd':
					//right
					for(int j=3;j>=0;j--){
						for(int i=3;i>=0;i--){
							if(arr[i][j]==0){
								for(int k=i-1;k>=0;k--){
									if(arr[k][j]!=0){
										arr[i][j]=arr[k][j];
										arr[k][j]=0;
										break;
									}
								}
							}
						}
					}
					for(j=3;j>=0;j--){
						for(int i=3;i>=0;i--){
							if(arr[i][j]==arr[i-1][j]){
								arr[i][j]+=arr[i-1][j];
								score+=arr[i][j];
								for(int k=i-1;k>0;k--){
									arr[k][j]=arr[k-1][j];
								}
								arr[0][j]=0;
							}
						}
					}
					break;
				case 'a':
					//left
					for(j=0;j<4;j++){
							for(int i=0;i<4;i++){
							if(arr[i][j]==0){
								for(int k=i+1;k<4;k++){
									if(arr[k][j]!=0){
										arr[i][j]=arr[k][j];
										arr[k][j]=0;
										break;
									}
								}
							}
						}
					}
					for(j=0;j<4;j++){
						for(int i=0;i<4;i++){
							if(arr[i][j]==arr[i+1][j]){
								arr[i][j]+=arr[i+1][j];
								score+=arr[i][j];
								for(int k=i+1;k<3;k++){
									arr[k][j]=arr[k+1][j];
								}
								arr[3][j]=0;
							}
						}
					}
					break;
				case 's':
					//down
					for(i=3;i>=0;i--){
						for(int j=3;j>=0;j--){
							if(arr[i][j]==0){
								for(int k=j-1;k>=0;k--){
									if(arr[i][k]!=0){
										arr[i][j]=arr[i][k];
										arr[i][k]=0;
										break;
									}
								}
							}
						}
					}
					for(i=3;i>=0;i--){
						for(int j=3;j>=0;j--){
							if(arr[i][j]==arr[i][j-1]){
								arr[i][j]+=arr[i][j-1];
								score+=arr[i][j];
								for(int k=j-1;k>0;k--){
									arr[i][k]=arr[i][k-1];
								}
								arr[i][0]=0;
							}
						}
					}
					break;
			}
			int check_flag=0;
			for(i=0;i<4;i++){
				for(int j=0;j<4;j++){
					if(check_change[i][j]!=arr[i][j]){
						check_flag=1;
						break;
					}
				}
				if(check_flag==1)
					break;
			}
			if(check_flag==1){
				int count=0;
				for(int k=0;k<16;k++){
					int i=k/4, j=k%4;
					if(arr[i][j]==0){
						flag[count++]=k;
					}
				}
				int m=flag[random(count)];
				arr[m/4][m%4]=2;
				display();
			}
			ifover();
			ifwin();
		}
	}
}

void ifwin(){
	int midx = getmaxx() / 2;
	int midy = getmaxy() / 2;
	int flag=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(arr[i][j]==2048){
				flag=1;
				break;
			}
		}
		if(flag==1)
			break;
	}
	if(flag==1){
		settextstyle(0,0,4);
		setcolor(3);
		outtextxy(midx-140,midy-15,"YOU WIN!!");
		delay(2000);
		settextstyle(0,0,2);
		outtextxy(midx-210,midy+200,"PRESS ANY KEY TO CONTINUE...");
		getch();
		cleardevice();
		menu();
	}
}

void ifover(){
	int midx = getmaxx() / 2;
	int midy = getmaxy() / 2;
	int flag=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(arr[i][j]==0){
				flag=1;
				break;
			}
		}
	}
	if(flag==1){
		return;
	}
	for(i=0;i<4;i++){
		 for(int j=0;j<3;j++){
			if(arr[i][j]==arr[i][j+1]){
				flag=1;
				break;
			}
			if(arr[j][i]==arr[j+1][i]){
				flag=1;
				break;
			}
		 }
		 if(flag==1)
			break;
	}
	if(flag==0){
		settextstyle(0,0,4);
		setcolor(3);
		outtextxy(midx-140,midy-15,"GAME OVER");
		delay(2000);
		settextstyle(0,0,2);
		outtextxy(midx-210,midy+200,"PRESS ANY KEY TO CONTINUE...");
		getch();
		cleardevice();
		menu();
	}
}

void grid(){
	int midx = getmaxx() / 2;
	int midy = getmaxy() / 2;
	setbkcolor(15);
	setfillstyle(0,6);
	setcolor(8);

	setlinestyle(0,0,3);
	bar3d(midx-160, midy-160, midx+160,midy+160, 10, 1);
	//vertical
	line(midx-80,midy-160,midx-80,midy+160);
	line(midx,midy-160,midx,midy+160);
	line(midx+80,midy-160,midx+80,midy+160);
	//horizontal
	line(midx-160,midy+80,midx+160,midy+80);
	line(midx-160,midy,midx+160,midy);
	line(midx-160,midy-80,midx+160,midy-80);

	settextstyle(0,0,2);
	outtextxy(0,70,"  SCORE:");
}

void display(){
	int temp, temp1, k;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			k=0;
			temp=0;
			temp1 = arr[i][j];
			way[i][j]=0;
			while(temp1){
				temp=(temp*10)+(temp1%10);
				temp1/=10;
			}
			while(temp){
				ch[i][j][k]=(temp%10)+48;
				temp/=10;
				k++;
				way[i][j]++;
			}
			ch[i][j][k]='\0';
		}
	}
	int len=0;
	for(i=score;i>0;i/=10){
		len++;
	}
	temp=score;
	for(i=len-1;i>=0;i--){
		score_ch[i]=(temp%10)+48;
		temp/=10;
	}
	score_ch[len+1]='\0';
	int midx = getmaxx() / 2,subx=-130;
	int midy = getmaxy() / 2,suby=-130;
	setcolor(9);
	for(i=0;i<4;i++){
		subx=-130;
		for(int j=0;j<4;j++){
			switch(way_clr[j][i]){
				case 0:
					setcolor(0);
					outtextxy(midx+subx,midy+suby,clr[j][i]);
					break;
				case 1:
					settextstyle(0,0,4);
					setcolor(0);
					outtextxy(midx+subx,midy+suby,clr[j][i]);
					break;
				case 2:
					settextstyle(0,0,3);
					setcolor(0);
					outtextxy(midx-12+subx,midy+suby,clr[j][i]);
					break;
				case 3:
					settextstyle(0,0,3);
					setcolor(0);
					outtextxy(midx-24+subx,midy+suby,clr[j][i]);
					break;
				case 4:
					settextstyle(0,0,2);
					setcolor(0);
					outtextxy(midx-19+subx,midy+suby,clr[j][i]);
					break;
				}
				subx+=80;
		}
		suby+=80;
	}
	subx=-130;
	suby=-130;
	for(i=0;i<4;i++){
		subx=-130;
		for(int j=0;j<4;j++){
			switch(way[j][i]){
				case 1:
					settextstyle(0,0,4);
					setcolor(9);
					outtextxy(midx+subx,midy+suby,ch[j][i]);
					break;
				case 2:
					settextstyle(0,0,3);
					setcolor(9);
					outtextxy(midx-12+subx,midy+suby,ch[j][i]);
					break;
				case 3:
					settextstyle(0,0,3);
					setcolor(9);
					outtextxy(midx-24+subx,midy+suby,ch[j][i]);
					break;
				case 4:
					settextstyle(0,0,2);
					setcolor(9);
					outtextxy(midx-19+subx,midy+suby,ch[j][i]);
					break;
				}
				subx+=80;
		}
		suby+=80;
	}
	settextstyle(0,0,2);
	setcolor(0);
	outtextxy(30,100,score_clr);
	setcolor(1);
	outtextxy(30,100,score_ch);
	for(i=0;i<4;i++){
		for(int j=0;j<4;j++){
			strcpy(clr[i][j],ch[i][j]);
			way_clr[i][j]=strlen(clr[i][j]);
		}
	}
	strcpy(score_clr,score_ch);
}

void instr(){
	int midx=getmaxx()/2, midy=getmaxy()/2;
	setbkcolor(GREEN);
	settextstyle(0,0,3);
	outtextxy(midx-140,40,"INSTRUCTIONS");
	setcolor(RED);
	settextstyle(0,0,1);
	outtextxy(25,100,"Use arrow keys to play 2048 on your computer. The objective of the game is");
	outtextxy(25,125,"to get the number 2048 using additions of the number two and its multiples.");
	outtextxy(25,150,"You will have a grid of 16 tiles. One numbers will be given that is two.");
	outtextxy(25,175,"Move up or down, left or right trying to join two equal numbers. When two");
	outtextxy(25,200,"equal numbers are in touch, they will add up. After every move the game will");
	outtextxy(25,225,"provide us another two. If there are no free tiles on our grid and there is");
	outtextxy(25,250,"no move possible, the game ends. By adding numbers, we get higher numbers ");
	outtextxy(25,275, "and we can approach to 2048, which is the goal of the game.");
	//W-A-S-D
	setcolor(YELLOW);
	setlinestyle(0,0,3);
	rectangle(midx-25,midy+65,midx+25,midy+115);
	rectangle(midx-75,midy+115,midx-25,midy+165);
	rectangle(midx-25,midy+115,midx+25,midy+165);
	rectangle(midx+25,midy+115,midx+75,midy+165);
	settextstyle(0,0,3);
	outtextxy(midx-10,midy+80,"W");
	outtextxy(midx-10,midy+130,"S");
	outtextxy(midx-60,midy+130,"A");
	outtextxy(midx+40,midy+130,"D");
	getch();
	cleardevice();
	menu();
}

void menu(){
	int midx=getmaxx()/2, midy=getmaxy()/2;
	setbkcolor(CYAN);
	setcolor(RED);
	int pos=0;
	for(int i=0;i<=10;i++){
		setcolor(CYAN);
		outtextxy(midx-10-pos,midy-pos,"2048");
		settextstyle(0,0,i);
		pos=i*15;
		setcolor(RED);
		if(i>0)
			outtextxy(midx-10-pos,midy-pos,"2048");
		delay(180);
	}
	pos=0;
	for(i=0;i<=2;i++){
		setcolor(CYAN);
		outtextxy(midx-40-pos,midy,"NEW GAME");
		settextstyle(0,0,i);
		pos=i*15;
		setcolor(YELLOW);
		if(i>0)
			outtextxy(midx-40-pos,midy,"NEW GAME");
		delay(100);
	}
	for(i=0;i<=2;i++){
		setcolor(CYAN);
		outtextxy(midx-10-pos,midy+50,"EXIT");
		settextstyle(0,0,i);
		pos=i*15;
		setcolor(YELLOW);
		if(i>0)
			outtextxy(midx -10-pos,midy+50,"EXIT");
		delay(100);
	}
	for(i=0;i<=2;i++){
		setcolor(CYAN);
		outtextxy(midx-70-pos,midy+100,"INSTRUCTIONS");
		settextstyle(0,0,i);
		pos=i*15;
		setcolor(YELLOW);
		if(i>0)
			outtextxy(midx-70-pos,midy+100,"INSTRUCTIONS");
		delay(100);
	}
	setcolor(BLUE);
	outtextxy(midx-70,midy,"NEW GAME");
	int cur = 1; // 1-new game, 2-exit, 3-instructions
	//int state = 0; //tells the position of the curser, 0 - new game, 1 - exit , 2- instructions
	while(1){
		if(kbhit()){
			char press = getch();
			switch(press){
				case 27:
					exit(0);
				case 13:
					switch(cur){
						case 1:
							cleardevice();
							newgame();
						case 2:
							exit(0);
						case 3:
							cleardevice();
							instr();
							break;
					}
				case 'w':
					//up
					if(cur==2){
						setcolor(BLUE);
						outtextxy(midx-70,midy,"NEW GAME");
						setcolor(YELLOW);
						outtextxy(midx-40,midy+50,"EXIT");
						//state=0;
						cur=1;
					}else if(cur==3){
						setcolor(YELLOW);
						outtextxy(midx-70-pos,midy+100,"INSTRUCTIONS");
						setcolor(BLUE);
						outtextxy(midx-40,midy+50,"EXIT");
						//state=1;
						cur=2;
					}
					break;
				case 's':
					//down
					if(cur==1){
						setcolor(YELLOW);
						outtextxy(midx-70,midy,"NEW GAME");
						setcolor(BLUE);
						outtextxy(midx-40,midy+50,"EXIT");
						//state=1;
						cur=2;
					}else if(cur==2){
						setcolor(BLUE);
						outtextxy(midx-70-pos,midy+100,"INSTRUCTIONS");
						setcolor(YELLOW);
						outtextxy(midx-40,midy+50,"EXIT");
						cur=3;
						//state=2;
					}
					break;
			}
		}
	}
}

void logo(){
	int midx = getmaxx() / 2;
	int midy = getmaxy() / 2;
	setbkcolor(8);
	setcolor(9);
	for(int x=midx;x>=-50;x--){
		circle(midx-x,midy-150,50);
	}
	settextstyle(0,0,3);
	setcolor(2);
	outtextxy(midx/2-120,midy-160,"MegaMind Games");
	setcolor(10);
	outtextxy(midx-80,midy,"SOURAV");
	outtextxy(midx-20,midy+30,"&");
	outtextxy(midx-90,midy+60,"SANCHIT");
	getch();
	cleardevice();
	menu();
}