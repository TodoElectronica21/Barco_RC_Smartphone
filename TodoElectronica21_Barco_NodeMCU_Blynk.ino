#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Puedes obtener este código en el apartado de opciones de tu APP en Blynk
char auth[] = "Código que nos proporciona la API de Blynk";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "El SSID de tu red WiFi";
char pass[] = "La contraseña WiFi";

int marcha=0;
int atras=0;
int parar=0;
int luces=1;
int vel1=400;
int vel2=400;

Servo servo;

WidgetTerminal terminal(V10);

void setup()
{
  
  // Debug console
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  servo.attach(14,400,2400);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  //El pin 12 realmente es el D6 en ESP8266

  terminal.clear();
  
  Blynk.virtualWrite(V10,"Soy un Barco y he sido creado ");
  Blynk.virtualWrite(V10,"por TodoElectronica 21        ");
  Blynk.virtualWrite(V10,"Gracias por traerme a la vida ");
  Blynk.virtualWrite(V10,"Rafa !! ......................");
  Blynk.virtualWrite(V10,"...........................   ");

  Blynk.virtualWrite(V8,400);
  Blynk.virtualWrite(V9,400);
  Blynk.virtualWrite(V3,90);
  Blynk.virtualWrite(V7,1);

}

/*Comunicación con los pines virtuales de Blynk - Leemos y obtenemos datos*/

BLYNK_WRITE(V3){
  servo.write(param.asInt());
}

BLYNK_WRITE(V4){
  marcha=param.asInt();
  Serial.print("Marcha= ");
  Serial.println(marcha);
  if(marcha==1){
  Blynk.virtualWrite(V10,"Arrancando motores ...      ");
  }
}
BLYNK_WRITE(V5){
  parar=param.asInt();
  Serial.print("STOP= ");
  Serial.println(parar);
  if(parar==1){
  Blynk.virtualWrite(V10,"Parando motores ...         ");
  }
}
BLYNK_WRITE(V6){
  atras=param.asInt();
  Serial.print("Marcha atras= ");
  Serial.println(atras);
  if(atras==1){
  Blynk.virtualWrite(V10,"Inversión de la marcha ...  ");
  }
}
BLYNK_WRITE(V7){
  luces=param.asInt();
  Serial.print("Luces= ");
  Serial.println(luces);
  if(luces==1){
  Blynk.virtualWrite(V10,"Apagando Iluminicación....  ");
  }
  else{
  Blynk.virtualWrite(V10,"Encendiendo Iluminicación.. ");
  }
}
BLYNK_WRITE(V8){
  if(marcha==1){
  vel1=param.asInt();
  analogWrite(4,vel1);
  }
}
BLYNK_WRITE(V9){
  if(atras==1){
  vel2=param.asInt();
  analogWrite(5,vel2);
  }
}
BLYNK_WRITE(V10){
  terminal.println("Aún no soy tan inteligente como para contestarte");
  terminal.flush();
}

/* Configuramos qué acciones queremos que se realicen de forma cíclica */

void loop()
{
  Blynk.run();

  if(marcha==1){
    atras=0;
    Blynk.virtualWrite(V6,0);
    Blynk.virtualWrite(V4,1);
    analogWrite(4, vel1);
    digitalWrite(5, LOW);
    if(marcha==0){
      Blynk.virtualWrite(V4,0);
      analogWrite(4, LOW);
      digitalWrite(5, LOW);
    }
  }
  
  if(atras==1){
    marcha=0;
    Blynk.virtualWrite(V4,0);
    Blynk.virtualWrite(V6,1);
    digitalWrite(4, LOW);
    analogWrite(5, vel2);
    if(atras==0){
      Blynk.virtualWrite(V6,0);
      analogWrite(4, LOW);
      digitalWrite(5, LOW);
    }
  }
  
  if(parar==1){
    marcha=0;
    atras=0;
    Blynk.virtualWrite(V4,0);
    Blynk.virtualWrite(V6,0);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(1000);
    parar=0;
    Blynk.virtualWrite(V5,0);
  }
  
  if(luces==1){
    digitalWrite(12, LOW);
  }
  
  if(luces==0){
    digitalWrite(12, HIGH);
  }
}
