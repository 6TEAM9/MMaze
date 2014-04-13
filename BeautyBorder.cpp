#include <stdio.h>
#include <string.h>
#include "BeautyBorder.h"

#define DEF_FILE "ASCII Border.txt"

using namespace std;//std ifstream

BeautyBorder::BeautyBorder(const char filename[]){
	n=1;
	for(int i=0;i<CONFIG_LENGTH;i++,n*=BMN);
	n++;
	a=new char[n];
	if(strlen(filename)==0){
		open(DEF_FILE);
	}else{
		open(filename);
	}
}

int BeautyBorder::configToInt(const int config[]){//not safe
	int result=0;
	int mul=1;
	for(int i=0;i<CONFIG_LENGTH;i++){
		if(!(0<=config[i] && config[i]<BMN)) return 81;
		result+=config[i]*mul;
		mul*=BMN;
	}
	return result;
}

int BeautyBorder::configToInt(int d0, int d1, int d2, int d3){
	int temp[CONFIG_LENGTH]={d0, d1, d2, d3};
	return configToInt(temp);
}

int BeautyBorder::configToInt(const char config[]){
	if(strlen(config)!=(unsigned)CONFIG_LENGTH) return 81;
	int temp[CONFIG_LENGTH];
	for(int i=0;i<CONFIG_LENGTH;i++){
		temp[i]=config[i]-'0';
	}
	return configToInt(temp);
}

void BeautyBorder::set(const char config[], const int val){
	a[configToInt(config)]=val;
}

void BeautyBorder::testConvert(){
	char s[80];
	int index;
	char result;
	while(true){
		scanf("%s", s);
		index=configToInt(s);
		result=a[index];
		printf("%s||%d||\'%c\'\n", s, index, result);
	}
}

void BeautyBorder::open(const char filename[]){
	for(int i=0;i<n;i++){
		a[i]=ERR;
	}
	FILE *fin=fopen(filename, "r");
	if(!fin) return;
	int tnum;
	char tconf[CONFIG_LENGTH+1];
	while(!feof(fin)){
		fscanf(fin, "%d", &tnum);
		fscanf(fin, " %s", tconf);
		set(tconf, tnum);
	}
	fclose(fin);
}

char BeautyBorder::operator()(const char config[]){
	return a[configToInt(config)];
}

char BeautyBorder::operator()(int rht,int top,int lft,int btm){
	return a[configToInt(rht, top, lft, btm)];
}

char BeautyBorder::operator()(int rht,int top,int lft,int btm,int ERR){
	if(rht<0) rht=ERR;
	if(top<0) top=ERR;
	if(lft<0) lft=ERR;
	if(btm<0) btm=ERR;
	return operator()(rht,top,lft,btm);
}
