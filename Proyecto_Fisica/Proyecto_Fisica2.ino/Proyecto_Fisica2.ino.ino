
#include <Ethernet.h>   // Incluye la librería Ethernet
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
void setup()
{

  // Cambiamos referencia de las entradas analógicas
  analogReference(INTERNAL);

  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);

  //Incializa libreria y configuraciones de red
  Ethernet.begin(mac, ip);

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
