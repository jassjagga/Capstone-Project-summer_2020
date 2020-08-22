#include <iostream>     //Standard Input Output stream
#include <sstream>     //Header used for string stream
#include<unistd.h>    //Header used for delay
#include <fstream>   //File Stream
#include "network/SocketClient.h"     //SocketClient.h used for setting up cloud
using namespace std;
using namespace exploringBB;
//Starting Main
int main() {
   ostringstream head, data;         //Output string stream
int val1,val2,val3,num=100;
   cout << "Starting ThingSpeak Example" << endl;
cout << "Enter the temperature: "<< endl;
 cin >> val1;

   SocketClient sc("api.thingspeak.com",80);   //SocketClient is used to connect to the network host
   data << "field1=" << val1 << endl;          //Sending val1 to Feild1 of channel
   cout << "Sending the temperature: " << val1 << endl;
//Used to establish a connection between the cloud
   sc.connectToServer();
//Head is used to create an HTTP request and  API key to communicate with cloud
   head << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n"
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY:5TASEOVO82PL7FA8 \n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data.str()).length() << "\n\n";
   sc.send(string(head.str()));      //Request to send data to cloud
   sc.send(string(data.str()));     //Sending data to cloud
   string rec = sc.receive(1024);   //Used to check the status of data send
   cout << "[" << rec << "]" << endl;   // Gives some ASCII at the end to the monitor
   cout << "End of ThingSpeak Example" << endl;
sleep(15);                          //Delay used to send data 15s
ostringstream head1, data1;        //Output String Stream for sending second data
   cout << "Starting ThingSpeak Example" << endl;
cout << "Enter the heart rate : "<< endl;
   cin >> val2;
   SocketClient sc1("api.thingspeak.com",80);
 data1 << "field2=" << val2 << endl;
   cout << "Sending the Heart rate: " << val2 << endl;
   sc1.connectToServer();
   head1 << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n"
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY:5TASEOVO82PL7FA8 \n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data1.str()).length() << "\n\n";
   sc1.send(string(head1.str()));
   sc1.send(string(data1.str()));
   string rec1 = sc1.receive(1024);
   cout << "[" << rec1 << "]" << endl;
   cout << "End of ThingSpeak Example" << endl;
sleep(15);
//Sending Third Data to cloud
ostringstream head2, data2;
   cout << "Starting ThingSpeak Example" << endl;
cout << "Enter the Blood Pressure: "<< endl;
   cin >> val3;
   SocketClient sc2("api.thingspeak.com",80);
   data2 << "field3=" << val3 << endl;
   cout << "Sending the Blood Pressure: " << val3 << endl;
   sc2.connectToServer();
   head2 << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n"
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY:5TASEOVO82PL7FA8 \n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data2.str()).length() << "\n\n";
   sc2.send(string(head2.str()));
   sc2.send(string(data2.str()));
   string rec2 = sc2.receive(1024);
   cout << "[" << rec2 << "]" << endl;
   cout << "End of ThingSpeak Example" << endl;
        sleep(15);
}
