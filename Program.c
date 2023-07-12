
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "palette.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


int scanData(int size){
	int i;
	char a[size];
	for(i=0;i<size;i++){
		scanf("%c",&a[i]);
	}
	return *(unsigned*)a;
}

int hex(int color[], int i){
	int temp[6],a = pow(16,5);
	for(int j=0;j<6;j++){
		if(j==0){
			color[j]=i/a;
			temp[j]=i%a;
		}else {
		color[j]=temp[j-1]/a;
		temp[j]=temp[j-1]%a;
		}
		a/=16;
	}
}

int main(){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int t_width = w.ws_col,temp_k,k,m,n,temp_,last,man_dis,temp_dis=1000,x,temp_x;	
	int junk = scanData(10);
	int offset=scanData(4);
	junk = scanData(4);
	unsigned int width=scanData(4);
	unsigned int height=scanData(4);
	junk = scanData(offset-26);	


// CHECKPOINT 2
	double block_width=MAX(1,(double)width/t_width);
	double temp_block_height=block_width*2;
	double row_number=round(height/temp_block_height);
	double block_height=height/row_number;


	static int B[3000][3000],G[3000][3000],R[3000][3000],
    resB[3000][3000]={0},resG[3000][3000]={0},resR[3000][3000]={0},
    temR[3000][3000]={0},temG[3000][3000]={0},temB[3000][3000]={0};
	char ASCII[26]={32,96,39,45,58,123,47,63,61,108,55,114,73,76,54,110,70,97,88,82,103,64,72,35,78,77};
	static double Grayness[3000][3000],
    grayTable[26]={0.000000,0.015625,0.031250,0.046875,0.062500,0.070313,0.078125,0.085938,0.093750,0.0101563,0.109375,0.117188,0.125000,0.132813,0.140625,0.148438,0.156250,0.164063,0.171875,0.179688,0.187500,0.195313,0.210938,0.218750,0.226563,0.234375},
    temp=100;


    int i,j;
    for(i=height-1;i>=0;i--){
		for(j=0;j<width;j++){
			unsigned temp=scanData(3),tempary[6];
			hex(tempary,temp);
			R[i][j]=tempary[0]*16+tempary[1];
			G[i][j]=tempary[2]*16+tempary[3];
			B[i][j]=tempary[4]*16+tempary[5];							
		}				
	}

    // RESCALE
    int ct = 0;
    for(j=0;j<height;j++){            
	for(k=0;k<t_width;k++){
		ct+=block_width;
		temp_=round(ct);
		for(i=last;i<=temp_;i++){
			temR[j][k]+=R[j][i];
			temG[j][k]+=G[j][i];
			temB[j][k]+=B[j][i];
		}

		temR[j][k]/=(temp_-last)+1;
		temG[j][k]/=(temp_-last)+1;
		temB[j][k]/=(temp_-last)+1;
			last=temp_;
	}
	ct=0;
	last=0;
}
    for(j=0;j<t_width;j++){				
	for(k=0;k<(int)(height/block_height);k++){
		ct+=block_height;
		temp_=round(ct);
		for(i=last;i<=temp_;i++){
			resR[k][j]+=temR[i][j];
			resG[k][j]+=temG[i][j];
			resB[k][j]+=temB[i][j];
		}
		resR[k][j]/=(temp_-last)+1;
		resG[k][j]/=(temp_-last)+1;
		resB[k][j]/=(temp_-last)+1;
		last=temp_;
	}
	ct=0;
	last=0;
}										

// CHECKPOINT 3
	for(i=0;i<(int)(height/block_height);i++){
		for(j=0;j<t_width;j++){
			Grayness[i][j]=(255-(0.3*resR[i][j]+0.59*resG[i][j]+0.11*resB[i][j]))/255*0.234375;
			for(k=26;k>=0;k--){
				if(fabs(Grayness[i][j]-grayTable[k])<=temp){
					temp=fabs(Grayness[i][j]-grayTable[k]);
					temp_k=k;
				}
			}
			for(x=255;x>=0;x--){
				unsigned int color[6];
				hex(color,palette[x]);
				man_dis=abs((int)resR[i][j]-(color[0]*16)-color[1])+abs((int)resG[i][j]-(color[2]*16)-color[3])+abs((int)resB[i][j]-(color[4]*16)-color[5]);
				if(man_dis<=temp_dis){
					temp_x=x;
					temp_dis=man_dis;
				}
			}
			printf("\x1b[38;5;%dm",temp_x);
			printf("%c",ASCII[temp_k]);	
			printf("\x1b[0m");	
			temp=100;
			temp_dis=1000;
		}
	//	printf("\n");
	}
}
