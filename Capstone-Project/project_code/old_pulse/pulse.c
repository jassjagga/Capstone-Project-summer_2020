#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
int main() {
#define pin115 "/sys/class/gpio/gpio115/value"
#define pin117 "/sys/class/gpio/gpio117/value"
    FILE* fptr, * fp1, * fp2;
    float diff;
    int value;
    int num = 100;
    int temp = 0;
    float bpm = 0.0;
    fp1 = fopen("/sys/class/gpio/gpio117/direction", "r");
    fputs("in", fp1);                                                //Initalising gpio_117 as input pin
    fclose(fp1);
    fp2 = fopen("/sys/class/gpio/gpio115/direction", "r");
    fputs("in", fp2);                                                //Initalising gpio_115 as input pin
    fclose(fp2);
    //Creating a Loop for continues data
    while (num > 0) {
        fp1 = fopen(pin115, "r");
        fp2 = fopen(pin117, "r");
        int dig1, dig2;
        fscanf(fp1, "%d", &dig1);                                       //Checking for value 1 or 0 from gpio_117
        fscanf(fp2, "%d", &dig2);                                      //Checking for value 1 or 0 from gpio_115
        //Loop for checking if all the Leads are connected (Digital Out)
        if ((dig1 == 1) || (dig2 == 1))
        {
            printf("Make sure that all the leads are connect");
            break;
        }
        else
        {
            fptr = fopen("/sys/bus/iio/devices/iio:device0/in_voltage4_raw", "r");
            fscanf(fptr, "%d", &value);                                               //Reading the angalog output (which is a bits data)
           // diff = fabs(value - temp);
          //  bpm = ((1 / diff) * 60 * 1000);                                             //Equation to caluculate the BPM
            //Loop for filtering the noise and showing BPM within range
           // if ((bpm > 110) || (diff == 0) || (bpm < 30))
           // {
             //   temp = value;
           // }
           // else
            {
                printf(value, "\n");
               // printf("Bpm:%f \t", bpm);
              //  printf("Diff:%f \t", diff);
              //  printf("Bits:%d \n", value);
                temp = value;
            }
        }
        fclose(fptr);
        fclose(fp1);
        fclose(fp2);
        usleep(60000);
    }
    num--;
    return 0;
}
