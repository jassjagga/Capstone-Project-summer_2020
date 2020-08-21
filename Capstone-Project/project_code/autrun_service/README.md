To Make your Program autorun when boot the beaglebone
=============================================================
1. First create the bash script simply provide the path to our .out file if you are runing c or c++ file.

eg: - 
________________________________________________________
#!/bin/bash 
sleep 5
/home/debian/projects/Cloud_main/bin/Cloud_main.out
________________________________________________________
2. Provide all executative access to your .sh file 

>> sudo chmod 755 /myfile.sh

place your .sh file at known location 
like : - /usr/local/sbin/

3. Create a service call for your script

>> sudo nano /lib/systemd/system/myfile.service
Example like: - 

_____________________________________________________
[Unit]

Description =myfile

After= getty.target

[Service]

Type=simple

ExecStart= /usr/local/sbin/myfile.sh

[Install]

WantedBy=multi-user.target
_____________________________________________________

If you don't want to type the login id and password again edit the autolog_in file 

change the 
[Service]
ExecStart=-/sbin/agetty -a root -s %I 115200      //change ExecStart line with this line in serial-getty@service file in same service folder
_____________________________________________________________________________________________________________

To check the status of your service type this command 

>> sudo systemctl status myfile.service

if it say disable to enable this service type this command

>> sudo systemctl enable myfile.service 

Now you are done 
So Now when you restart your Beaglebone black your program start within few seconds after the boot process. 

