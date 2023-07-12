#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// void printer(char a[][][]){
//     for(int i=0;;i++){
//     for(int j=0;;j++){
//     printf("%d",a[i][i][i])
// }}}

int grayness(int R, int G, int B){
    return (255-(0.3*R+0.59*G+0.11*B))/255*0.234375;
    
}

int hex(int color[], int i){
	int a[6],mul,j;
	mul=16*16*16*16*16;
	for(j=0;j<6;j++){
		if(j==0){
			color[j]=i/mul;
			a[j]=i%mul;
		}else {
		color[j]=a[j-1]/mul;
		a[j]=a[j-1]%mul;
		}
		mul/=16;
	}
}


// double round(double a){
//     int x = a;
//     if(x - a >= 0.5)
//     return a++;
//     else return a;
// }

int main(){
    unsigned char junk;
    unsigned char filesize[4];
    unsigned char offSetChar[4];
    unsigned char imageWidthChar[4],imageHeightChar[4];
    scanf("%c", &junk);
    scanf("%c", &junk);
    for (int i=0;i<4;i++){
        scanf("%c",&filesize[i]);}
    printf("finish size scanning");
    //printf("&u\n",*(unsigned*)filesize);
    scanf("%c", &junk);
    scanf("%c", &junk);
    for (int i=0;i<4;i++){
        scanf("%c",&offSetChar[i]);}
    
    for(int i=0;i<4;i++)
        scanf("%c",&junk);
    for (int i=0;i<4;i++){
        scanf("%c",&imageWidthChar[i]);}
    for (int i=0;i<4;i++){
        scanf("%c",&imageHeightChar[i]);}
    
    unsigned int offSet = *(unsigned*)offSetChar;
    for (int i=0;i<offSet;i++){
        scanf("%c",&junk);}
    

    
    unsigned int imageWidth = *(unsigned*)imageWidthChar;
    unsigned int imageHeight = *(unsigned*)imageHeightChar;
    
    unsigned char*** pixelArray;
    pixelArray=malloc(imageHeight * sizeof(unsigned char **));
    for(int i=0; i<imageHeight; i++){
        pixelArray[i] = malloc(imageWidth * sizeof(unsigned char *));
        for(int j=0; j<imageWidth; j++){
            pixelArray[i][j] = malloc(3 * sizeof(unsigned char));
        }
    }
    unsigned int padding=(4-(imageWidth*3)%4)%4;
    
    for(int i=imageHeight-1;i>=0;i--){
        for(int j=0;j<imageWidth+padding;j++){
            for(int k=0;k<3;k++){
                if(j>=imageWidth)
                    scanf("%c",&junk);
                else scanf("%c",&pixelArray[i][j][k]);
            }}}
    
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
    int term_width = w.ws_col;
     double blockWidth = MAX(1,imageWidth/term_width);
     double tempBlockheight = blockWidth * 2;
     double rowNumber = round(imageHeight/tempBlockheight);
     double blockHeight = imageHeight/ rowNumber;
    
    // char*** rePixel = malloc()
//    unsigned char** blockRGB=malloc(blockWidth*sizeof(char*));
//    for(int i=0; i<blockWidth;i++)
//        blockRGB[i]=malloc(blockHeight*sizeof(unsigned char));

// int ASCII[26]={32,96,39,45,58,123,47,63,61,108,55,114,73,76,54,110,70,97,88,82,103,64,72,35,78,77};
    // for(int i=0;i<blockWidth;i++){
    //     for(int j=0;j<blockHeight;j++){
    //         if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<=0.007)
    //             printf("%c",ASCII[0]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.02)
    //             printf("%c",ASCII[1]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.037)
    //             printf("%c",ASCII[2]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.052)
    //             printf("%c",ASCII[3]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.066)
    //             printf("%c",ASCII[4]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.074)
    //             printf("%c",ASCII[5]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.082)
    //             printf("%c",ASCII[6]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.089)
    //             printf("%c",ASCII[7]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.097)
    //             printf("%c",ASCII[8]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.105)
    //             printf("%c",ASCII[9]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.113)
    //             printf("%c",ASCII[10]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.121)
    //             printf("%c",ASCII[11]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.128)
    //             printf("%c",ASCII[12]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.136)
    //             printf("%c",ASCII[13]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.144)
    //             printf("%c",ASCII[14]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.152)
    //             printf("%c",ASCII[15]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.16)
    //             printf("%c",ASCII[16]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.168)
    //             printf("%c",ASCII[17]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.175)
    //             printf("%c",ASCII[18]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.183)
    //             printf("%c",ASCII[19]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.191)
    //             printf("%c",ASCII[20]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.20)
    //             printf("%c",ASCII[21]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.214)
    //             printf("%c",ASCII[22]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.0222)
    //             printf("%c",ASCII[23]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.229)
    //             printf("%c",ASCII[24]);
    //         else if(grayness(pixelArray[i][j][0],pixelArray[i][j][1],pixelArray[i][j][2])<0.24)
    //             printf("%c",ASCII[25]);        
    //     }
    // }

//static int B[3000][3000],G[3000][3000],R[3000][3000],Re_B[3000][3000]={0},Re_G[3000][3000]={0},Re_R[3000][3000]={0},temp_R[3000][3000]={0},temp_G[3000][3000]={0},temp_B[3000][3000]={0};
	char ASCII[26]={32,96,39,45,58,123,47,63,61,108,55,114,73,76,54,110,70,97,88,82,103,64,72,35,78,77};
	static double Grayness[3000][3000],
    lookup_table[26]={0.000000,0.015625,0.031250,0.046875,0.062500,0.070313,0.078125,0.085938,0.093750,0.0101563,0.109375,0.117188,0.125000,0.132813,0.140625,0.148438,0.156250,0.164063,0.171875,0.179688,0.187500,0.195313,0.210938,0.218750,0.226563,0.234375},
    temp=100;

for(int i=0;imageHeight;i++){
    for(int j=0;imageWidth;j++){
    printf("%d",pixelArray[i][j][i]);}}



// 	for(i=blockHeight-1;i>=0;i--){
// 		for(j=0;j<blockWidth;j++){
// 			unsigned temp=reader(3),tempary[6];
// 			hex(tempary,temp);
// 			R[i][j]=tempary[0]*16+tempary[1];
// 			G[i][j]=tempary[2]*16+tempary[3];
// 			B[i][j]=tempary[4]*16+tempary[5];							
// 		}				
// 	}
// for(j=0;j<height;j++){            //rescale width
// 	for(k=0;k<term_width;k++){
// 		count+=block_width;
// 		temp_=round(count);
// 		for(i=last;i<=temp_;i++){
// 			temp_R[j][k]+=R[j][i];
// 			temp_G[j][k]+=G[j][i];
// 			temp_B[j][k]+=B[j][i];
// 		}
// 		temp_R[j][k]/=(temp_-last)+1;
// 		temp_G[j][k]/=(temp_-last)+1;
// 		temp_B[j][k]/=(temp_-last)+1;
// 			last=temp_;
// 	}
// 	count=0;
// 	last=0;
// }
// for(j=0;j<term_width;j++){				//rescale height
// 	for(k=0;k<(int)(height/block_height);k++){
// 		count+=block_height;
// 		temp_=round(count);
// 		for(i=last;i<=temp_;i++){
// 			Re_R[k][j]+=temp_R[i][j];
// 			Re_G[k][j]+=temp_G[i][j];
// 			Re_B[k][j]+=temp_B[i][j];
// 		}
// 		Re_R[k][j]/=(temp_-last)+1;
// 		Re_G[k][j]/=(temp_-last)+1;
// 		Re_B[k][j]/=(temp_-last)+1;
// 		last=temp_;
// 	}
// 	count=0;
// 	last=0;
// }										//rescale end
// 	for(i=0;i<(int)(height/block_height);i++){
// 		for(j=0;j<term_width;j++){
// 			Grayness[i][j]=(255-(0.3*Re_R[i][j]+0.59*Re_G[i][j]+0.11*Re_B[i][j]))/255*0.234375;
// 			for(k=26;k>=0;k--){
// 				if(fabs(Grayness[i][j]-lookup_table[k])<=temp){
// 					temp=fabs(Grayness[i][j]-lookup_table[k]);
// 					temp_k=k;
// 				}
// 			}
// 			for(x=255;x>=0;x--){
// 				unsigned int color[6];
// 				hex(color,palette[x]);
// 				man_dis=abs((int)Re_R[i][j]-(color[0]*16)-color[1])+abs((int)Re_G[i][j]-(color[2]*16)-color[3])+absolute_int((int)Re_B[i][j]-(color[4]*16)-color[5]);
// 				if(man_dis<=temp_dis){
// 					temp_x=x;
// 					temp_dis=man_dis;
// 				}
// 			}
// 			printf("\x1b[38;5;%dm",temp_x);
// 			printf("%c",ascii[temp_k]);	
// 			printf("\x1b[0m");	
// 			temp=100;
// 			temp_dis=1000;
// 		}
// 	}
// }
    
    
    return 0;
    
}


