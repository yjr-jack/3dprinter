#include <stdio.h>
#include <stdlib.h>
#include "separate.h"

//命令数量
int gNumber=0, mNumber=0;
//具体命令，如G28命令用数字28保存
int gCommands[100],mCommands[100];

void get(){
    FILE *fp;
    char str[100];
    int a;
    
    //获取代码
    if( (fp=fopen("/var/mobile/Containers/Data/Application/4FF6791B-136C-4F0E-AD2F-0AF648E44C8A/Documents/KeepData/script/3d/g_find/3d.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(1);
    }
   
   //解析代码
    while(fgets(str, 99, fp) != NULL){
        //去除纯注释或空行
        if(str[0]!='\n'&&str[0]!=';'&&str[0]!='\0'){
            separate(str);
        }
    }
    fclose(fp);
    
    //输出结果
    printf("\nNumber of G commands:%d",gNumber);
    printf("\nNumber of M commands:%d \n",mNumber);
    printf("\nG commands:\n");
    for(a=0;a<gNumber;a++){
        printf("%d ",gCommands[a]);
    }
    printf("\n\nM commands:\n");
    for(a=0;a<mNumber;a++){
        printf("%d ",mCommands[a]);
        
    }
     printf("\n\nend\n");
}

int FindG(int g){
    int a;
    for(a=0;a<gNumber;a++){
        if(gCommands[a]==g) return 1;
    }
    return -1;
}

int FindM(int m){
    int a;
    for(a=0;a<mNumber;a++){
        if(mCommands[a]==m) return 1;
    }
    return -1;
}

void separate(char str[]){
    //str:命令后可能有注释
    //整句命令，不带注释
    char CommandSentence[100];
    //如"G28"中的'2'和'8'，将转换成int
    char CharCommand[20]="\0";
    //如"G28"中的"28"
    int a,IntCommand;
    
    //去除命令后注释
    //gcode中';'后的是注释
    for(a=0;(str[a]!='\n'&&str[a]!=';'&&str[a]!='\0');a++){
        CommandSentence[a]=str[a];
    }
    //结束字符串
    CommandSentence[a]='\0';
    
    //去除命令内容
    for(a=1;(CommandSentence[a]!='\0'&&CommandSentence[a]!=' ');a++){
        CharCommand[a-1]=CommandSentence[a];
    }
    //转换成int便于操作
    IntCommand=atoi(CharCommand);
    
    if(str[0]=='G'){
        //统计G命令个数
        if(FindG(IntCommand)==-1){
            gCommands[gNumber]=IntCommand;
            gNumber++;
        }
        
        //显示特定命令的整句命令
        //如：要找G1的命令，就在IntCommand后面写1
        //if(IntCommand==1) printf("%s",str);
        
    }else if(str[0]=='M'){
        //统计M命令个数
        if(FindM(IntCommand)==-1){
            mCommands[mNumber]=IntCommand;
            mNumber++;
        }
        
        //显示特定命令的整句命令
        //如：要找M105，就在IntCommand==后写105
        //if(IntCommand==105) printf("%s",str);
        
    }else{
        //未知命令
        printf("unknown:\n");
        printf("%s",str);
    }
}

