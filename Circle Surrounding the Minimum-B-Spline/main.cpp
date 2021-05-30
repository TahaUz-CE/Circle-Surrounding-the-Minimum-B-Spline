
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<graphics.h>
#include<windows.h>

int fact(int n){

    if(n==0)
        return 1;
    else
        return n*fact(n-1);
}

int comb(int n,int r){

    return (fact(n)/(fact(n-r)*fact(r)));
}

float dist(float x_1,float y_1,int x_2,int y_2){

    return sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
}
void merkez_yaricap(float temp_merkezandyaricap[],int x1,int y1,int x2,int y2){
    *temp_merkezandyaricap = (float)(x1+x2)/2.0;
    *(temp_merkezandyaricap+1) = (float)(y1+y2)/2.0;
    *(temp_merkezandyaricap+2) =  dist(x1,y1,x2,y2)/2.0;
}
void merkez_yaricap_2(float temp_merkezandyaricap[],int x1,int y1,int x2,int y2,int x3,int y3){

    int D,E,F,det,det1,det2;
    float merkez_x,merkez_y;

    D = (x1*x1)+(y1*y1);
    E = (x2*x2)+(y2*y2);
    F = (x3*x3)+(y3*y3);

    det = (x1*(y2-y3))-(x2*(y1-y3))+(x3*(y1-y2));
    det1 = (D*(y2-y3))-(E*(y1-y3))+(F*(y1-y2));
    det2 = (x1*(E-F))-(x2*(D-F))+(x3*(D-E));
    if(det != 0){

    merkez_x = det1 / (2*det);
    merkez_y = det2 / (2*det);

    *temp_merkezandyaricap = merkez_x;
    *(temp_merkezandyaricap+1) = merkez_y;
    *(temp_merkezandyaricap+2) = dist(merkez_x,merkez_y,x1,y1);

    }
}

int icerde_mi(float tmp2[],int x,int y){
    if((dist(tmp2[0],tmp2[1],x,y))<= tmp2[2]){
        return 1;
    }
    return 0;
}

int nokta_icerde_mi(float tmp[],int matris[][2],int sizee){

    for(int i=0;i<sizee;i++){
        if(icerde_mi(tmp,matris[i][0],matris[i][1]) == 0){
            return 0;
        }
    }
    return 1;
}

void min_cember_hesap(float *merkezandyaricap,int matris[][2],int sizee ){

    int i,j,k;
    float temp_merkezandyaricap[3];
    if(sizee == 0){
            merkezandyaricap[0]=0;
            merkezandyaricap[1]=0;
            merkezandyaricap[2]=0;

    }if(sizee == 1){
            merkezandyaricap[0]=matris[0][0];
            merkezandyaricap[1]=matris[0][1];
            merkezandyaricap[2]=0;
    }
    merkezandyaricap[0]=0;
    merkezandyaricap[1]=0;
    merkezandyaricap[2]=100;
    for(i=0;i<sizee;i++){
        for(j=i+1;j<sizee;j++){
            merkez_yaricap(temp_merkezandyaricap,matris[i][0],matris[i][1],matris[j][0],matris[j][1]);
             if(temp_merkezandyaricap[2]<merkezandyaricap[2] && nokta_icerde_mi(temp_merkezandyaricap,matris,sizee) == 1){
                    merkezandyaricap[0]=temp_merkezandyaricap[0];
                    merkezandyaricap[1]=temp_merkezandyaricap[1];
                    merkezandyaricap[2]=temp_merkezandyaricap[2];
            }
        }
    }
    for(i=0;i<sizee;i++){
        for(j=i+1;j<sizee;j++){
            for(k=j+1;k<sizee;k++){
                merkez_yaricap_2(temp_merkezandyaricap,matris[i][0],matris[i][1],matris[j][0],matris[j][1],matris[k][0],matris[k][1]);
                if(temp_merkezandyaricap[2]<merkezandyaricap[2] && nokta_icerde_mi(temp_merkezandyaricap,matris,sizee) == 1){
                    merkezandyaricap[0]=temp_merkezandyaricap[0];
                    merkezandyaricap[1]=temp_merkezandyaricap[1];
                    merkezandyaricap[2]=temp_merkezandyaricap[2];
            }
        }
    }
}
     if(merkezandyaricap[2]==100){
                    merkezandyaricap[0]=temp_merkezandyaricap[0];
                    merkezandyaricap[1]=temp_merkezandyaricap[1];
                    merkezandyaricap[2]=temp_merkezandyaricap[2];
    }
}


int main()
{
    FILE * dosya;
    char buf[100];
    int i=0,j=0,boyut=0,dizi[boyut],k=0;

    if ((dosya = fopen("koordinat.txt", "r")) == NULL)
    {
        printf("dosya acilamadi!\n");
        exit(1);
    }

    while ( fgets(buf, 100, dosya) != NULL ){
    }

    fclose(dosya);

    for(i=0; i<100; i++){
        if ((isdigit(buf[i]) && buf[i] != '\0' && buf[i] != '\n')){
            if((isdigit(buf[i])) && (buf[i-1] == '-') && (isdigit(buf[i+1]) )){
                boyut++;
                i+=2;
            }else if((isdigit(buf[i])) && (isdigit(buf[i+1]) )){
                boyut++;
                i+=2;
            }else if((isdigit(buf[i]) && buf[i-1] == '-')){
                boyut++;
            }else{
                boyut++;
            }
        }
         if(buf[i] == '{' && buf[i+1] == ',' && buf[i+2] == '}' ){
            boyut++;
        }else{
            if(buf[i] == ',' && buf[i+1] == '}'){
            boyut++;
        }
        if(buf[i] == '{' && buf[i+1] == ','){
            boyut++;
        }
      }
      if(buf[i] == '}' && buf[i+1] != ','){
         break;
         }
    }

    int boyut2=boyut/2,matris[boyut2][2];

    for(i=0; i<100; i++){
        if ((isdigit(buf[i]) && buf[i] != '\0' && buf[i] != '\n'))
        {
            if((isdigit(buf[i])) && (buf[i-1] == '-') && (isdigit(buf[i+1]) )){
                dizi[j] = (((10)*(buf[i]-48))+(buf[i+1]-48))*(-1);
                i+=2;
                j++;
            }else if((isdigit(buf[i])) && (isdigit(buf[i+1]) )){
                dizi[j] = (((10)*(buf[i]-48))+(buf[i+1]-48));
                i+=2;
                j++;
            }else if((isdigit(buf[i]) && buf[i-1] == '-')){
                dizi[j] = (buf[i]-48)*(-1);
                j++;
            }else{
                dizi[j] = buf[i]-48;
                j++;
            }

        }
         if(buf[i] == '{' && buf[i+1] == ',' && buf[i+2] == '}' ){
            dizi[j] = 0;
            dizi[j+1] = 0;
            j+=2;
            i+=2;
        }else{
            if(buf[i] == ',' && buf[i+1] == '}'){
            dizi[j] = 0;
            j++;
            i++;
        }
        if(buf[i] == '{' && buf[i+1] == ','){
            dizi[j] = 0;
            j++;
            i++;
        }
      }
      if(buf[i] == '}' && buf[i+1] != ','){
         break;
         }
    }
          for(i=0; i<boyut2; i++){
        matris[i][0] = dizi[k];
        matris[i][1] = dizi[k+1];
        k+=2;
    }

    float merkezandyaricap[3];
    min_cember_hesap(merkezandyaricap,matris,boyut2);
    printf("Merkez kordinati = {%.1f,%.1f} ve yaricapi = %.2f(main)\n",merkezandyaricap[0],merkezandyaricap[1],merkezandyaricap[2]);

    int midx,midy,scale,limit,sayac=0,sayac2=0,decNumb,decNumb2,decNumb3;

    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);

    initwindow(screenWidth,screenHeight,"");

    char a[3] = "0 ";
    char b[4] = "-1 ";

    midx = screenWidth/2;
    midy = screenHeight/2;

    char stringkordinat[15] = {"M(   .0,   .0)"};
    char stringNoktalar[11] = {" (   ,   )"};
    char radius[13] = {"Radius =  .0"};

    for(i=0;i<boyut2;i++){
        if(((matris[i][0] > 10 || matris[i][0]<-10) || (matris[i][1] > 10 || matris[i][1]<-10))){
            sayac++;
        }
        if((matris[i][0]<5 && matris[i][0]>-5) && (matris[i][1]<5 && matris[i][1]>-5) && merkezandyaricap[2]<3){
            sayac2++;
        }
    }

    if(sayac != 0){
        limit = 26;
        scale = 20;
    }else if(sayac2 != 0){
        scale = 100;
        limit = 6;
    }else{
        scale = 50;
        limit = 11;
    }

    j=scale;

    decNumb3 = (int)((merkezandyaricap[2]-(int)merkezandyaricap[2])*10);
    radius[11] = decNumb3+48;

    if(merkezandyaricap[0]>=0 && merkezandyaricap[1]>=0){
        if((int)merkezandyaricap[0]%10 == (int)merkezandyaricap[0] && (int)merkezandyaricap[1]%10 == (int)merkezandyaricap[1] && (int)merkezandyaricap[2]%10 == (int)merkezandyaricap[2]){
            stringkordinat[3] = merkezandyaricap[0]+48;
            stringkordinat[9] = merkezandyaricap[1]+48;
            radius[9] = merkezandyaricap[2]+48;
        }else{
            stringkordinat[3] = (((int)merkezandyaricap[0]/10)+48);
            stringkordinat[4] = (((int)merkezandyaricap[0]%10)+48);
            stringkordinat[9] = (((int)merkezandyaricap[1]/10)+48);
            stringkordinat[10] = (((int)merkezandyaricap[1]%10)+48);
            radius[8] = (((int)merkezandyaricap[2]/10)+48);
            radius[9] = (((int)merkezandyaricap[2]%10)+48);
        }
        decNumb = (int)((merkezandyaricap[0]-(int)merkezandyaricap[0])*10);
        stringkordinat[6] = decNumb+48;
        decNumb2 = (int)((merkezandyaricap[1]-(int)merkezandyaricap[1])*10);
        stringkordinat[12] = decNumb2+48;
    }
    else if(merkezandyaricap[0]<0 && merkezandyaricap[1]>=0){
        if((int)merkezandyaricap[0]%10 == (int)merkezandyaricap[0] && (int)merkezandyaricap[1]%10 == (int)merkezandyaricap[1] && (int)merkezandyaricap[2]%10 == (int)merkezandyaricap[2]){
            stringkordinat[2] = '-';
            stringkordinat[3] = ((int)merkezandyaricap[0]*(-1))+48;
            stringkordinat[9] = (int)merkezandyaricap[1]+48;
            radius[9] = (int)merkezandyaricap[2]+48;
        }else{
            stringkordinat[2] = '-';
            stringkordinat[3] = ((((int)merkezandyaricap[0]*(-1))/10)+48);
            stringkordinat[4] = ((((int)merkezandyaricap[0]*(-1))%10)+48);
            stringkordinat[9] = (((int)merkezandyaricap[1]/10)+48);
            stringkordinat[10] = (((int)merkezandyaricap[1]%10)+48);
            radius[8] = (((int)merkezandyaricap[2]/10)+48);
            radius[9] = (((int)merkezandyaricap[2]%10)+48);
        }
        decNumb = (int)(((merkezandyaricap[0]*(-1))-(int)(merkezandyaricap[0]*(-1)))*10);
        stringkordinat[6] = decNumb+48;
        decNumb2 = (int)((merkezandyaricap[1]-(int)merkezandyaricap[1])*10);
        stringkordinat[12] = decNumb2+48;
    }
    else if(merkezandyaricap[0]>=0 && merkezandyaricap[1]<0){
        if((int)merkezandyaricap[0]%10 == (int)merkezandyaricap[0] && (int)merkezandyaricap[1]%10 == (int)merkezandyaricap[1] && (int)merkezandyaricap[2]%10 == (int)merkezandyaricap[2]){
            stringkordinat[8] = '-';
            stringkordinat[3] = (int)merkezandyaricap[0]+48;
            stringkordinat[9] = ((int)merkezandyaricap[1]*(-1))+48;
            radius[9] = (int)merkezandyaricap[2]+48;
        }else{
            stringkordinat[8] = '-';
            stringkordinat[3] = (((int)merkezandyaricap[0]/10)+48);
            stringkordinat[4] = (((int)merkezandyaricap[0]%10)+48);
            stringkordinat[9] = ((((int)merkezandyaricap[1]*(-1))/10)+48);
            stringkordinat[10] = ((((int)merkezandyaricap[1]*(-1))%10)+48);
            radius[8] = (((int)merkezandyaricap[2]/10)+48);
            radius[9] = (((int)merkezandyaricap[2]%10)+48);
        }
        decNumb = (int)((merkezandyaricap[0]-(int)merkezandyaricap[0])*10);
        stringkordinat[6] = decNumb+48;
        decNumb2 = (int)(((merkezandyaricap[1]*(-1))-(int)(merkezandyaricap[1]*(-1)))*10);
        stringkordinat[12] = decNumb2+48;
    }
    else if(merkezandyaricap[0]<0 && merkezandyaricap[1]<0){
        if((int)merkezandyaricap[0]%10 == (int)merkezandyaricap[0] && (int)merkezandyaricap[1]%10 == (int)merkezandyaricap[1] && (int)merkezandyaricap[2]%10 == (int)merkezandyaricap[2]){
            stringkordinat[2] = '-';
            stringkordinat[8] = '-';
            stringkordinat[3] = ((int)merkezandyaricap[0]*(-1))+48;
            stringkordinat[9] = ((int)merkezandyaricap[1]*(-1))+48;
            radius[9] = (int)merkezandyaricap[2]+48;
        }else{
            stringkordinat[2] = '-';
            stringkordinat[8] = '-';
            stringkordinat[3] = ((((int)merkezandyaricap[0]*(-1))/10)+48);
            stringkordinat[4] = ((((int)merkezandyaricap[0]*(-1))%10)+48);
            stringkordinat[9] = ((((int)merkezandyaricap[1]*(-1))/10)+48);
            stringkordinat[10] = ((((int)merkezandyaricap[1]*(-1))%10)+48);
            radius[8] = (((int)merkezandyaricap[2]/10)+48);
            radius[9] = (((int)merkezandyaricap[2]%10)+48);
        }
        decNumb = (int)(((merkezandyaricap[0]*(-1))-(int)(merkezandyaricap[0]*(-1)))*10);
        stringkordinat[6] = decNumb+48;
        decNumb2 = (int)(((merkezandyaricap[1]*(-1))-(int)(merkezandyaricap[1]*(-1)))*10);
        stringkordinat[12] = decNumb2+48;
    }

    int width = textwidth(stringkordinat);
    int height = textheight(stringkordinat);

    line(440,midy,1480,midy);
    line(midx,20,midx,1060);

    for(i=0; i<530; i+=scale){
        line(midx+i,midy-2,midx+i,midy+2);
        line(midx-i,midy-2,midx-i,midy+2);
        line(midx+2,midy+i,midx-2,midy+i);
        line(midx+2,midy-i,midx-2,midy-i);
    }

    outtextxy(midx,midy+2,a);

     for(i=1; i<limit; i++){
        if(i<10 && i>-1){
            a[0] = i+48;
            b[1] = i+48;
            outtextxy(midx+j,midy+2,a);
            outtextxy(midx+2,midy-j,a);
            outtextxy(midx-j,midy+2,b);
            outtextxy(midx+2,midy+j,b);
            j+=scale;
        }else if(i>9){
            a[0] = (i/10)+48;
            a[1] = (i%10)+48;
            b[1] = (i/10)+48;
            b[2] = (i%10)+48;
            outtextxy(midx+j,midy+2,a);
            outtextxy(midx+2,midy-j,a);
            outtextxy(midx-j,midy+2,b);
            outtextxy(midx+2,midy+j,b);
            j+=scale;
        }
    }
    for(i=0;i<boyut2;i++){
        if(matris[i][0]>=0 && matris[i][1]>=0){
            if(matris[i][0]<10 && matris[i][1]<10){
                stringNoktalar[2] = ' ';
                stringNoktalar[6] = ' ';
                stringNoktalar[4] = ' ';
                stringNoktalar[8] = ' ';
                stringNoktalar[3] = matris[i][0]+48;
                stringNoktalar[7] = matris[i][1]+48;
            }else{
                stringNoktalar[2] = ' ';
                stringNoktalar[6] = ' ';
                stringNoktalar[3] = (matris[i][0]/10)+48;
                stringNoktalar[4] = (matris[i][0]%10)+48;
                stringNoktalar[7] = (matris[i][1]/10)+48;
                stringNoktalar[8] = (matris[i][1]%10)+48;
            }
            outtextxy(midx+((matris[i][0])*scale),midy-((matris[i][1])*scale),stringNoktalar);
    }
        else if(matris[i][0]<0 && matris[i][1]>=0){
            if(matris[i][0]>-10 && matris[i][1]<10){
                stringNoktalar[2] = '-';
                stringNoktalar[6] = ' ';
                stringNoktalar[4] = ' ';
                stringNoktalar[8] = ' ';
                stringNoktalar[3] = (matris[i][0]*(-1))+48;
                stringNoktalar[7] = matris[i][1]+48;
            }else{
                stringNoktalar[2] = '-';
                stringNoktalar[6] = ' ';
                stringNoktalar[3] = ((matris[i][0]*(-1))/10)+48;
                stringNoktalar[4] = ((matris[i][0]*(-1))%10)+48;
                stringNoktalar[7] = (matris[i][1]/10)+48;
                stringNoktalar[8] = (matris[i][1]%10)+48;
            }
            outtextxy(midx+((matris[i][0])*scale),midy-((matris[i][1])*scale),stringNoktalar);
    }
        else if(matris[i][0]>=0 && matris[i][1]<0){
                if(matris[i][0]<10 && matris[i][1]>-10){
                    stringNoktalar[2] = ' ';
                    stringNoktalar[6] = '-';
                    stringNoktalar[4] = ' ';
                    stringNoktalar[8] = ' ';
                    stringNoktalar[3] = matris[i][0]+48;
                    stringNoktalar[7] = (matris[i][1]*(-1))+48;
                }else{
                    stringNoktalar[2] = ' ';
                    stringNoktalar[6] = '-';
                    stringNoktalar[3] = (matris[i][0]/10)+48;
                    stringNoktalar[4] = (matris[i][0]%10)+48;
                    stringNoktalar[7] = ((matris[i][1]*(-1))/10)+48;
                    stringNoktalar[8] = ((matris[i][1]*(-1))%10)+48;
                }
            outtextxy(midx+((matris[i][0])*scale),midy-((matris[i][1])*scale),stringNoktalar);
        }
        else if(matris[i][0]<0 && matris[i][1]<0){
                if(matris[i][0]>-10 && matris[i][1]>-10){
                    stringNoktalar[2] = '-';
                    stringNoktalar[6] = '-';
                    stringNoktalar[4] = ' ';
                    stringNoktalar[8] = ' ';
                    stringNoktalar[3] = (matris[i][0]*(-1))+48;
                    stringNoktalar[7] = (matris[i][1]*(-1))+48;
                }else{
                    stringNoktalar[2] = '-';
                    stringNoktalar[6] = '-';
                    stringNoktalar[3] = ((matris[i][0]*(-1))/10)+48;
                    stringNoktalar[4] = ((matris[i][0]*(-1))%10)+48;
                    stringNoktalar[7] = ((matris[i][1]*(-1))/10)+48;
                    stringNoktalar[8] = ((matris[i][1]*(-1))%10)+48;
                }
            outtextxy(midx+((matris[i][0])*scale),midy-((matris[i][1])*scale),stringNoktalar);
        }
    }

    circle(midx+((merkezandyaricap[0])*scale),midy-((merkezandyaricap[1])*scale),(merkezandyaricap[2])*scale);
    line(midx+((merkezandyaricap[0])*scale),midy-((merkezandyaricap[1])*scale),midx+((merkezandyaricap[0])*scale),midy-((merkezandyaricap[1])*scale)+(merkezandyaricap[2]*scale));
    outtextxy(midx+((merkezandyaricap[0])*scale)+5,midy-((merkezandyaricap[1])*scale)+20,radius);
    outtextxy(midx+((merkezandyaricap[0])*scale)-(width/2),midy-((merkezandyaricap[1])*scale)-(height/2),stringkordinat);

    float t,x,y;

    for(i=0;i<=boyut2-1;i++){
        circle((matris[i][0]*scale)+midx,(matris[i][1]*(-scale))+midy,5);
        if(i != boyut2-1){
            //line((matris[i][0]*scale)+midx,(matris[i][1]*(-scale)+midy),(matris[i+1][0]*scale)+midx,(matris[i+1][1]*(-scale)+midy));
        }
    }

    for(t=0;t<=1;t+=0.00001){
        x=0;
        y=0;
        for(i=0;i<=boyut2-1;i++){
            x=x+(comb(boyut2-1,i)*pow(1-t,boyut2-1-i)*pow(t,i)*matris[i][0]);
            y=y+(comb(boyut2-1,i)*pow(1-t,boyut2-1-i)*pow(t,i)*matris[i][1]);
        }
        putpixel((x*scale)+midx,(y*(-scale))+midy,YELLOW);
    }

    getch();
    closegraph();
    return 0;
}
