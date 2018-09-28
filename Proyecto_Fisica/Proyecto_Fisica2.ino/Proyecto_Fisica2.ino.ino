
#include <Ethernet.h>   // Incluye la librería Ethernet
#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

// RTC_DS1307 rtc;
RTC_DS3231 rtc;



// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = 4;
void setup()
{

 // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
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




  // Comenzamos el sensor DHT
  dht.begin();

  pinMode(10, OUTPUT);         // Esto es necesario aunque creas que no lo usas.
  if (!SD.begin(chipSelect))
  { Serial.println("No hay tarjeta");
    return;    // NO sigas
  }
}

void loop() {
  //LEYENDO TEMPERATURAS---------------------------

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35);

  // Calculamos la temperatura con la fórmula
  tempC = (tempC * 100.0) / 1024.0;

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023 sensor 2
  tempC_2 = analogRead(pinLM35_2);

  // Calculamos la temperatura con la fórmula
  tempC_2 = (tempC_2 * 100.0) / 1024.0;



  // Leemos la humedad relativa
  float humedad = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float tempC_3 = dht.readTemperature();
  // Comprobamos si ha habido algún error en la lectura
  /*if (isnan(humedad) || isnan(tempC_3) ) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
    }*/


  // Obtener fecha actual y mostrar por Serial
  DateTime date = rtc.now();

  int anio = date.year();
  int mes = date.month();
  int dia = date.day();
  int hora = date.hour();
  int minu = date.minute();

  Serial.println(anio, DEC);


  Serial.println(tempC);
  Serial.println(tempC_2);
  Serial.println(tempC_3);
  Serial.println(humedad);


  //Escritura del archivo

  if (tempC != 0 && tempC_2 != 0 ) {
    File datosTemp1 = SD.open("sensor1.txt", FILE_WRITE);
    if (datosTemp1)   // Si ha podido abrir el fichero
    {
      datosTemp1.println("<tr><td>" + String(tempC) + "</td><td>" + String(tempC_2) + "</dt><td>" + String(tempC_3) + "</td><td>" +  String(humedad) + "</td></tr>");
      datosTemp1.close();
    }

  }

}
