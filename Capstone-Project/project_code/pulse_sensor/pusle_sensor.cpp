#include<iostream>
#include<chrono>
#include<fstream>
#include<sstream>

using namespace std;
using namespace std::chrono;

int counter = 0;
bool lock;

#define pin115 "/sys/class/gpio/gpio115/value"
#define pin117 "/sys/class/gpio/gpio117/value"
int
pulse_counter (int a)
{
  if (a <= 900)
    {
      if (lock == true)
	{
	  counter++;
	  lock = false;
	}
    }
  if (a >= 3000)
    {
      lock = true;
    }
  return counter;
}

int
main ()
{
  fstream fs1, fs2;
  int holder = 0;
  //string value;
  fs1.open("/sys/class/gpio/gpio115/direction",ios::in|ios::out);
  if (!fs1.is_open ())
    {
      cout << "Can't open fs1" << endl;
    }
  fs1 << "in";

  fs2.open("/sys/class/gpio/gpio117/direction", ios::in | ios::out);
  if (!fs1.is_open ())
    {
      cout << "Can't open fs2" << endl;
    }
  fs2 << "in";
  fs1.close ();
  fs2.close ();

  auto finish = system_clock
  ::now() + seconds
    { 15};
  do
    {
      string dig1, dig2;
      fs1.open(pin115, ios::in | ios::out);
      if (fs1.is_open ())
	{
	  while (getline (fs1, dig1))
	    {
	      //dig1;
	    }
	}
      fs2.open(pin117, ios::in | ios::out);
      if (fs2.is_open ())
	{
	  while (getline (fs2, dig2))
	    {
	      //dig2;
	    }
	}
      if ((dig1 == "1") || (dig2 == "1"))
	{
	  cout << "Please check the connections" << endl;
	}
      else
	{
	  ifstream
	  in ("/sys/bus/iio/devices/iio:device0/in_voltage4_raw");
	  char str[255];
	  while (in)
	    {
	      in.getline (str, 255);
	      if (in)
		cout << str << endl;
	      stringstream
	      g1 ( str);
	      g1 >> holder;
	      pulse_counter (holder);
	    }

	  in.close ();

	}
    }
  while (system_clock::now() < finish);
  cout << (pulse_counter (holder) * 4) << endl;
  ;
  fs1.close ();
  fs2.close ();

  return 0;
}
