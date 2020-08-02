#include<iostream>
#include<cstdio>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
//#include<chrono>
//#include<thread>
using namespace std;
#define pin115 "/sys/class/gpio/gpio115/value"
#define pin117 "/sys/class/gpio/gpio117/value"
int main()
{
    int value;

    FILE* fptr, * fp1, * fp2;

    fp1 = fopen("/sys/class/gpio/gpio115/direction", "r");
    fputs("in", fp1);

    fp2 = fopen("/sys/class/gpio/gpio117/direction", "r");
    fputs("in", fp2);

    fclose(fp1);
    fclose(fp2);

    //loop
    while (1)
    {
        int dig1, dig2;
        fp1 = fopen(pin115, "r");
        fp2 = fopen(pin117, "r");

        fscanf(fp1, "%d", &dig1);
        fscanf(fp2, "%d", &dig2);

        if ((dig1 == 1) || (dig2 == 1))
         {
         cout << "Make sure the that all the leads are connected" << endl;
         }
        
        else
        {
            fptr = fopen("/sys/bus/iio/devices/iio:device0/in_voltage4_raw", "r");
            fscanf(fptr, "%d", &value);
            cout << value << endl;

        }
    }
  return 0;

}  

