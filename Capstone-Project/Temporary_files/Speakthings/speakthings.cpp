#include <iostream>
#include <sstream>
#include <fstream>
#include "SocketClient.h"
#define CPU_TEMP "/home/debian/t.txt"
using namespace std;
using namespace exploringRPi;

int getCPUTemperature() {          // get the CPU temperature
   int cpuTemp;                    // store as an int
   ifstream fs;
   fs.open(CPU_TEMP, fstream::in); // read from the file
   fs >> cpuTemp;
   fs.close();
   return cpuTemp;
}

int main() {
   ostringstream head, data;
   cout << "Starting ThingSpeak Example" << endl;
   SocketClient sc("thingspeak.com",80);
   data << "field1=" << getCPUTemperature() << endl;
   sc.connectToServer();
   cout<<"sending data"<<endl;
   head << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n"
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY: B5LXA3619JOUIZ1F\n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data.str()).length() << "\n\n";
   sc.send(string(head.str()));
   sc.send(string(data.str()));
   string rec = sc.receive(1024);
   cout << "[" << rec << "]" << endl;
   cout << "End of ThingSpeak Example" << endl;
}


