/*
  PINES PARA DTH11 S-2,5V-+,GND
  PINES PARA SENSOR TEMPERTURA 1 A0,5V,GND
  PINES PARA SENSOR TEMPERTURA 2 A1,5V,GND
  PINES PARA SENSOR TEMPERTURA 3 A2,5V,GND
  PINES PARA MODULO RELOJ A5-SCL,A4-SDA,5V,GND
*/


#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

#include "DHT.h" //cargamos la librería DHT
#define DHTPIN 2 //Seleccionamos el pin en el que se //conectará el sensor
#define DHTTYPE DHT11 //Se selecciona el DHT11 (hay //otros DHT)
DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que será usada por Arduino para comunicarse con el sensor


RTC_DS3231 rtc;

//PINES PARA SENSORES DE TEMPERATURA LM35
const int sensorPin0= A0;
const int sensorPin1= A1;
const int sensorPin2= A2;


const int chipSelect = 4;
void setup()
{

 // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
  
  dht.begin(); //Se inicia el sensor

  //CONFIGURACION DE RELOJ
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while (1);
  }

  // Si se ha perdido la corriente, fijar fecha y hora
  if (rtc.lostPower()) {
    // Fijar a fecha y hora de compilacion
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
    // rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));
  }


  pinMode(10, OUTPUT);         // Esto es necesario aunque creas que no lo usas.
  if (!SD.begin(chipSelect))
  { Serial.println("No hay tarjeta");
    return;    // NO sigas
  }
}

void loop() {
  delay(60000);
  //LEYENDO TEMPERATURAS---------------------------

  int value0 = analogRead(sensorPin0);
  int value1 = analogRead(sensorPin1);
  int value2 = analogRead(sensorPin2);
  float millivolts0 = (value0 / 1023.0) * 5000;
  float millivolts1 = (value1 / 1023.0) * 5000;
  float millivolts2 = (value2 / 1023.0) * 5000;
  float tempC = millivolts0 / 10; 
  float tempC_2 = millivolts1 / 10; 
  //float tempC_3 = millivolts2 / 10; 

float humedad = dht.readHumidity(); //Se lee la humedad
float tempC_3=dht.readTemperature();


  // Obtener fecha actual y mostrar por Serial
  DateTime date = rtc.now();

  int anio = date.year();
  int mes = date.month();
  int dia = date.day();
  int hora = date.hour();
  int minu = date.minute();




Serial.println(String(dia)+"/"+String(mes)+"/"+String(anio));
Serial.println(String(hora)+":"+String(minu));
  Serial.println(tempC);
  Serial.println(tempC_2);
  Serial.println(tempC_3);
  Serial.println(humedad);
  


  //Escritura del archivo

  if (tempC != 0 && tempC_2 != 0 ) {
    File datosTemp1 = SD.open("sensor1.txt", FILE_WRITE);
    if (datosTemp1)   // Si ha podido abrir el fichero
    {
      datosTemp1.println("<tr><td>"+String(dia)+"/"+String(mes)+"/"+String(anio)+"</td><td>"+String(hora)+":"+String(minu)+"</td><td>" + String(tempC) + "</td><td>" + String(tempC_2) + "</dt><td>" + String(tempC_3) + "</td><td>" +  String(humedad) + "</td></tr>");
      datosTemp1.close();
    }

  }

}
