#include<iostream>
#include<cstdio>
#include<string.h>
//#include<chrono>
//#include<thread>
using namespace std;

#define pin115 "/sys/class/gpio/gpio115/value"
#define pin117 "/sys/class/gpio/gpio117/value"

int main()
{
  int value;
  int  dig1,dig2;

  FILE *fptr,*fp1,*fp2;

  fp1=fopen("/sys/class/gpio/gpio115/direction","r");
  fput("in",fp1);

  fp2=fopen("/sys/class/gpio/gpio117/direction","r");
  fput("in",fp2);

  fclose(fp1);
  fclose(fp2);

//loop
while(1){
        fp1=fopen(pin115,"r");
        fp2=fopen(pin117,"r");
        fscanf(fp1,"%d",&dig1,);


        }
        return 0;

}
