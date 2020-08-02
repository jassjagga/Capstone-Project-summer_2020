#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int
main ()
{
//strings to store the value 
  string sys, dys, pulse;
//calling the python code by python2.7 compiler
  system ("/usr/bin/python2.7 BP.py");

  ifstream Myfile;  //opening the file 
  Myfile.open("data.txt",ios::in);
  if (!Myfile.is_open ())
    {
      cout << "can't open file" << endl;
    }
  string Line[3];
  for (int i = 0; i < 3; i++)
    {
      getline (Myfile, Line[i]);
      sys = Line[0];
      dys = Line[1];
      pulse = Line[2];
    }
  cout << sys << "-" << dys << "-" << pulse << endl;
  //printf("Message sent");

}

