#include <Ethernet.h>   // Incluye la librería Ethernet
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

// Identificador Ethernet unico
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Dirección IP asignanda al Arduino Ethernet Shield
byte ip[] = { 192, 168, 1, 10 };

// Es el puerto HTML para conexión a Internet
EthernetServer server(80);

float tempC; // Variable para almacenar el valor obtenido del sensor 1(0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)

float tempC_2; // Variable para almacenar el valor obtenido del sensor 2(0 a 1023)
int pinLM35_2 = 1; // Variable del pin de entrada del sensor (A1)

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = 4;
void setup()
{

  // Cambiamos referencia de las entradas analógicas
  analogReference(INTERNAL);

  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);

  //Incializa libreria y configuraciones de red
  Ethernet.begin(mac, ip);

  //Incia comunicación a trevés del puerto
  server.begin();

  // Comenzamos el sensor DHT
  dht.begin();

  pinMode(10, OUTPUT);         // Esto es necesario aunque creas que no lo usas.
  if (!SD.begin(chipSelect))
  { Serial.println("No hay tarjeta");
    return;    // NO sigas
  }
}

void loop()
{
  //LEYENDO TEMPERATURAS---------------------------

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35);

  // Calculamos la temperatura con la fórmula
  tempC = (tempC * 100.0) / 1024.0;

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023 sensor 2
  tempC_2 = analogRead(pinLM35_2);

  // Calculamos la temperatura con la fórmula
  tempC_2 = (tempC_2 * 100.0) / 1024.0;

  // Esperamos un tiempo para repetir el loop
  delay(1000);

  //----Sensor de temperatura y humedad------------

  // Esperamos 5 segundos entre medidas
  delay(5000);

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
  //-----------------------------------------------
  //PAGINA
  EthernetClient client = server.available();

  if (client) {


    boolean current_line_is_blank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && current_line_is_blank)
        {


          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Datos Recolectados</title>");
          
          client.println("</head>");
          client.println("<body>");
          client.println("<center><table border=1>");

          client.println("</table><center>");
          client.println("</body>");
          client.println("</html>");
          break;
        }

        if (c == '\n')
        {

          current_line_is_blank = true;
        }
        else if (c != '\r')
        {

          current_line_is_blank = false;
        }
      }
    }

    delay(1);

    client.stop();
  }
}
