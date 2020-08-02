
#include "DS18B20.h"

DS18B20::DS18B20(const char* address) {
    address_ = strdup(address);
    unit_ = CELCIUS;
    snprintf(path, 46, "%s%s%s", BUS, address_, TEMPFILE);
}

DS18B20::~DS18B20() {
}

float DS18B20::getTemp() {
    FILE* devFile = fopen(path, "r");
    if (devFile == NULL) {
        printf("Count not open %s\n", path);
        perror("\n");
    }
    float temp = -1;
    if (devFile != NULL) {
        if (!ferror(devFile)) {
            unsigned int tempInt;
            char crcConf[5];
            fscanf(devFile, "%*x %*x %*x %*x %*x %*x %*x %*x %*x : crc=%*x %s", crcConf);
            if (strncmp(crcConf, "YES", 3) == 0) {
                fscanf(devFile, "%*x %*x %*x %*x %*x %*x %*x %*x %*x t=%5d", &tempInt);
                temp = (float)tempInt / 1000.0;
            }
        }
    }
    fclose(devFile);

    if (unit_ == CELCIUS) {
        return temp;
    }
    else
        return CtoF(temp);
}

uint8_t DS18B20::getUnits() {
    return unit_;
}

void DS18B20::setUnits(uint8_t u) {
    unit_ = u;
}
float DS18B20::CtoF(float temp) {
    return temp * 1.8 + 32;
}
