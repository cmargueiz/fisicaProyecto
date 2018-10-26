#!/usr/bin/python
#!/usr/bin/env python
import serial
import time
import serial
import os

arduino=serial.Serial('/dev/ttyACM0',baudrate=9600, timeout = 1)

time.sleep(4)
arduino.write(b'1')

temp1=arduino.readline()

temp2=arduino.readline()
temp3=arduino.readline()
humedad=arduino.readline()

arduino.close()

fecha=time.strftime("%d-%m-%y")
hora=time.strftime("%H:%M:%S")


f = open ('datos.txt','a')
f.write("\n<tr><td>"+fecha+"</td><td>"+hora+"</td><td>" + temp1 + "</td><td>" + temp2 + "</td><td>" + temp3 + "</td><td>" +  humedad + "</td></tr>")
f.close()



