import serial, time
import os
import Adafruit_BBIO.GPIO as GPIO
ser = serial.Serial()
ser.port = "/dev/ttyO1"

def get_last_n_lines(file_name, N):
    # Create an empty list to keep the track of last N lines
    list_of_lines = []
    # Open file for reading in binary mode
    with open(file_name, 'rb') as read_obj:
        # Move the cursor to the end of the file
        read_obj.seek(0, os.SEEK_END)
        # Create a buffer to keep the last read line
        buffer = bytearray()
        # Get the current position of pointer i.e eof
        pointer_location = read_obj.tell()
        # Loop till pointer reaches the top of the file
        while pointer_location >= 0:
            # Move the file pointer to the location pointed by pointer_location
            read_obj.seek(pointer_location)
            # Shift pointer location by -1
            pointer_location = pointer_location -1
            # read that byte / character
            new_byte = read_obj.read(1)
            # If the read byte is new line character then it means one line is read
            if new_byte == b'\n':
                # Save the line in list of lines
                list_of_lines.append(buffer.decode()[::-1])
                # If the size of list reaches N, then return the reversed list
                if len(list_of_lines) == N:
                    return list(reversed(list_of_lines))
                # Reinitialize the byte array to save next line
                buffer = bytearray()
            else:
                # If last read character is not eol then add it in buffer
                buffer.extend(new_byte)
        # As file is read completely, if there is still data in buffer, then its first line.
        if len(buffer) > 0:
            list_of_lines.append(buffer.decode()[::-1])
    # return the reversed list
    return list(reversed(list_of_lines))
#baudate speed and other properties
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS #number of bits per bytes
ser.parity = serial.PARITY_NONE #set parity check: no parity
ser.stopbits = serial.STOPBITS_ONE #number of stop bits
#ser.timeout = None          #block read
ser.timeout = 1 

ser.open()

#To trigger the gpio pin to trigger the Realy which will turn on the sensor.
GPIO.setup("P8_12", GPIO.OUT)
GPIO.output("P8_12", GPIO.HIGH)

GPIO.setup("P8_12", GPIO.OUT)
GPIO.output("P8_12", GPIO.LOW)

file = open("/home/debian/Blood_pressure/data.txt","w+")
time.sleep(5)  #give the serial port sometime to receive the data
while True:
     try:
        data = ord(ser.read())
        file.write(str(data) + '\n')
     except:
        break

file.close()

# Get last three lines from file 'sample.txt'
last_lines = get_last_n_lines("/home/debian/Blood_pressure/data.txt", 10)
file = open("/home/debian/Blood_pressure/data.txt","w+")
# Iterate over the list of last 10 lines and print one by one
for line in last_lines:
      # print(line)
       file.write(line + '\n')
          
#close everthing.
file.close()
ser.close()
