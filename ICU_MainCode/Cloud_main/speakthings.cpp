#include <iostream>   //Input Output Header file
#include <fstream>    //Header Used to open file (file stream)
#include<cstdio>
#include<string.h>
#include<iterator>
#include<vector>
#include<sstream>      // String Stream file
#include<chrono>      
#include<thread>       //Used along with chrono for delay
#include "SocketClient.h" // Header file used for Cloud connection

using namespace std;
using namespace exploringRPi;
using namespace std::chrono;

//Path for gpio pin for pulse sensor 
#define pin115 "/sys/class/gpio/gpio115/value"
#define pin117 "/sys/class/gpio/gpio117/value"

//vector string iterator to store and update that to the cloud.
vector<string>::iterator iter;

//variables
int counter;
int timer_counter = 3;      //this counter used as a time delay for blood pressure sensor
bool lock;

//For Temperature Sensor DS18B20
//----------------------------------------------
int getCPUTemperature() {
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
			fscanf(fs, "%*x %*x %*x %*x %*x %*x %*x %*x %*x : crc=%*x %s",
				crcConf);
			if (strncmp(crcConf, "YES", 3) == 0) {
				fscanf(fs, "%*x %*x %*x %*x %*x %*x %*x %*x %*x t=%5d",
					&tempInt);
				temp = (float)tempInt / 1000.0;
			}
		}
	}
	fclose(fs);
	return (temp);

}

//For Blood Pressure Sensor 
//-------------------------------------------------------------
void Blood(string* data1, string* data2, string* data3) {
	string sys, dys, pulse;
	//calling the blood pressure function to get the data
	system("/usr/bin/python2.7 /home/debian/Blood_pressure/BP.py");

	ifstream Myfile;
	Myfile.open("/home/debian/Blood_pressure/data.txt", ios::in);
	if (!Myfile.is_open()) {
		cout << "can't open file" << endl;
	}
	string Line[3];
	for (int i = 0; i < 3; i++) {
		getline(Myfile, Line[i]);
		*data1 = Line[0];
		*data2 = Line[1];
		*data3 = Line[2];

	}

}
//---------------------------------------------------------------------------
//For Pulse Sensor-----------------------------
//pulse Sensor function to coutn pulse in 15 seconds interval
int pulse_counter(int a) {
	if (a <= 900) {
		if (lock == true) {
			counter++;
			lock = false;
		}
	}
	if (a >= 3000) {
		lock = true;
	}
	return counter;
}
//Pulse sensor detection and reading -------------------------
int pulse_sensor() {
	counter = 0;
	fstream fs1, fs2;
	int holder = 0;
	
	fs1.open("/sys/class/gpio/gpio115/direction", ios::in | ios::out);
	if (!fs1.is_open()) {
		cout << "Can't open fs1" << endl;
	}
	fs1 << "in";

	fs2.open("/sys/class/gpio/gpio117/direction", ios::in | ios::out);
	if (!fs1.is_open()) {
		cout << "Can't open fs2" << endl;
	}
	fs2 << "in";
	fs1.close();
	fs2.close();

	auto finish = system_clock::now() + seconds{ 15 };
	do {
		string dig1, dig2;
		fs1.open(pin115, ios::in | ios::out);
		if (fs1.is_open()) {
			while (getline(fs1, dig1)) {}
		}
		fs2.open(pin117, ios::in | ios::out);
		if (fs2.is_open()) {
			while (getline(fs2, dig2)) {}
		}
		if ((dig1 == "1") || (dig2 == "1")) {
			cout << "Please check the connections" << endl;
		}
		else {
			ifstream
				in("/sys/bus/iio/devices/iio:device0/in_voltage4_raw");
			char str[255];
			while (in) {
				in.getline(str, 255);
				stringstream g1(str);
				g1 >> holder;
				pulse_counter(holder);
			}
			in.close();

		}
	} while (system_clock::now() < finish);
	fs1.close();
	fs2.close();

	return (pulse_counter(holder) * 4);
	//counter = 0;

}

int main()
{
	while (1)
	{
		//----------------temp. data ---------------------------------
		ostringstream head, data;
		cout << "Starting ThingSpeak Example" << endl;
		SocketClient sc("api.thingspeak.com", 80);
		data << "field1=" << getCPUTemperature() << endl;
		// cout << "Sending the temperature: " << getCPUTemperature() << endl;
		sc.connectToServer();
		cout << "sending data" << endl;
		head << "POST /update HTTP/1.1\n" << "Host: api.thingspeak.com\n"
			<< "Connection: close\n" << "X-THINGSPEAKAPIKEY: XXXXXXXXXXXXXXX\n" //change  XXXXXX with your channel Key
			<< "Content-Type: application/x-www-form-urlencoded\n"
			<< "Content-Length:" << string(data.str()).length() << "\n\n";
		sc.send(string(head.str()));
		sc.send(string(data.str()));
		string rec = sc.receive(1024);
		cout << "[" << rec << "]" << endl;
		cout << "End of ThingSpeak Example" << endl;

		//------------------------------------------------------------------------
		string sys = "0";
	    string dia, pulse; //to store Blood pressure data
		if (timer_counter == 3)
		{
			
			//vector to store data in vector[] so we can unload it to cloud one by one.
			vector < string > data_vec;
			Blood(&sys, &dia, &pulse);

			data_vec.push_back(sys);
			data_vec.push_back(dia);
			data_vec.push_back(pulse);

			for (iter = data_vec.begin(); iter != data_vec.end(); iter++) {
				ostringstream head, data;

				cout << *iter << endl;
				SocketClient sc("api.thingspeak.com", 80);
				data << "field2=" << *iter << endl;
				sc.connectToServer();
				cout << "sending data" << endl;
				head << "POST /update HTTP/1.1\n" << "Host: api.thingspeak.com\n"
					<< "Connection: close\n"
					<< "X-THINGSPEAKAPIKEY: XXXXXXXXXXXXX\n"
					<< "Content-Type: application/x-www-form-urlencoded\n"
					<< "Content-Length:" << string(data.str()).length() << "\n\n";
				sc.send(string(head.str()));
				sc.send(string(data.str()));
				string rec = sc.receive(1024);
				cout << "[" << rec << "]" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(15));
			}
		}
		if (timer_counter == 3)
		{
			timer_counter = 0;
		}
		//------------------------------------------------------------------------------
		int heart_beat = 0;
		ostringstream head1, data1;
	    heart_beat = pulse_sensor();
		cout << heart_beat << endl;
		SocketClient sc1("api.thingspeak.com", 80);
		data1 << "field3=" << heart_beat << endl;
		sc1.connectToServer();
		cout << "sending data" << endl;
		head1 << "POST /update HTTP/1.1\n" << "Host: api.thingspeak.com\n"
			<< "Connection: close\n" << "X-THINGSPEAKAPIKEY: XXXXXXXXXXXXXXXXX\n"
			<< "Content-Type: application/x-www-form-urlencoded\n"
			<< "Content-Length:" << string(data1.str()).length() << "\n\n";
		sc1.send(string(head1.str()));
		sc1.send(string(data1.str()));
		string rec1 = sc1.receive(1024);
		cout << "[" << rec1 << "]" << endl;
		cout << "End of ThingSpeak Example" << endl;

		//---------------------------------------------------------------------------------
		//For GSM :- Sends the data if something is wrong
		int temp_gsm = getCPUTemperature();
		string blood_gsm = sys;
		if ((temp_gsm >= 37) || (blood_gsm >= "120") || (heart_beat >= 82))
		{
			system("/usr/bin/python2.7 /home/debian/gsm/pysms.py");
		}
		else
		{
			cout << "everthing is good" << endl;

		}
		timer_counter++;

	}
}
