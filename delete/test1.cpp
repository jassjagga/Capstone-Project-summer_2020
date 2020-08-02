#include<iostream>
#include<cstdio>
#include<string.h>

using namespace std;
int main()
{
    char path[] = "/sys/bus/w1/devices/28-01191a41efa3/";
    char file[] = "w1_slave";
    char full[256];

    snprintf(full, sizeof(full), "%s%s", path, file);
    FILE* fs = fopen(full, "r");
    if (fs == NULL) {
        printf("Count not open %s\n", full);
        perror("\n");
    }
    float temp = -1;
    if (fs != NULL) {
        if (!ferror(fs)) {
            unsigned int tempInt;
            char crcConf[5];
            fscanf(fs, "%*x %*x %*x %*x %*x %*x %*x %*x %*x : crc=%*x %s", crcConf);
            if (strncmp(crcConf, "YES", 3) == 0) {
                fscanf(fs, "%*x %*x %*x %*x %*x %*x %*x %*x %*x t=%5d", &tempInt);
                temp = (float)tempInt / 1000.0;
                cout<<temp<<endl;
            }
        }
    }
    fclose(fs);
    return 0;

}
