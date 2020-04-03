#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define NSIZE  8

void print_2(int val2);
/***********文本文件转二进制**********/
void Text2Bin(const char* sIn,const char* sOut){
    char a[255];
    int count = 0;
    int ch;
    for(int j=0; j<255;j++)a[j]='\0';
    FILE* fin=fopen(sIn,"r");
    FILE* fout=fopen(sOut,"w");
    for(int i=0 ; i<=255 ; i++)fscanf(fin,"%c",&a[i]);
    for(int k=0 ; k<=254&&a[k] !='\0'; k++)
    {   
        ch = a[k];
        for(int a=7;a>=0;a--) fprintf(fout,"%d",ch>>a&1);
        //fprintf(fout,"\n");
    }
    fclose(fin);
    fclose(fout);
}
/***********二进制文件转文本文件**********/
void Bin2Text(const char* sIn,const char* sOut){
    FILE* fin=fopen(sIn,"r");
    FILE* fout=fopen(sOut,"w");
    char str[255*8];
    for(int r=0; r<255 ;r++) str[r]='\0';
    int i = 0, j = 0, iTemp = 0, flag = 0;
    int  ibina[NSIZE];          
    char cRead[NSIZE];              
    char cChar;
    for(int a=0 ; a<=255 ; a++)fscanf(fin,"%c",&str[a]);
    //for(int f=0 ; f<=255 ; f++)printf("%c",str[f]);
    while(flag <= 255){
        //printf("%d",flag);
        for(int b=flag ; b>=flag && b<flag+NSIZE ; b++)
        {
            //printf("%d",b%8);
            cRead[b%8] = str[b];
            //printf("%c",cRead[b%8]);
        }
        for(i = 0; i < NSIZE; i++)
        {
            ibina[i] = (cRead[i]-'0'); 
        }
        iTemp = 1;
        cChar = 0;
        for(j = 7; j >=0 ; j--)
        {
            //printf("%c",ibina[j]);
            //printf("%d\n",cChar);
            cChar+=ibina[j]*iTemp;
            iTemp *= 2;
        }
        printf("%c",cChar);
        fprintf(fout,"%c",cChar);
        flag=flag+8;
    }
    fclose(fin);
    fclose(fout);
}

int main(){
    Text2Bin("vnet10_uart_switch.jed","bina.vme");
    //Bin2Text("d:\\a2.txt","d:\\b2.txt");
    printf("\nSuccessfully converted file!\n"); 
    return 0;
}


