// Codigo de Cuchao

//Importacion de libreria para servomotor
#include <Servo.h>

//Instanciacion del servomotor para controlar direccion
Servo myservo;

//Variable de comunicacion
char dato;

//Variables para control de luces de parqueo
int temp = 0;
int extra = 0;
int extra_on = 0;

//Variables para activar motoreductores traseros
int In13 = 2;
int In24 = 4;
int enb = 3; // enable para los motoreductores

//Variables de Leds
int delanteras = 6;
int traseras = 5;


void setup() {
  pinMode(In13, OUTPUT);
  pinMode(In24, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(delanteras, OUTPUT);
  pinMode(traseras, OUTPUT);
  myservo.attach(9);  // asignamos el pin al servo. (PWM)

  //Apagar motores por default
  digitalWrite (In13, LOW);
  digitalWrite (In24, LOW);


  //Motoreductores a potencia maxima por defecto
  analogWrite(enb, 225);

  Serial.begin(9600); //Inicio de comunicacion Serial (HC-05 38400) (HC-06 9600)
}

void loop() {
  // Lee el dato resivido
  if (Serial.available())
  {
    dato=Serial.read();
    Serial.print("Dato recibido: ");  //Envia el dato resibido
    Serial.println(dato);
  }

  if(dato == 'S'){  // STOP apaga los motores y endereza el servo
    digitalWrite (In13, LOW);
    digitalWrite (In24, LOW);

    myservo.write(90);
  }

  if(dato == 'F'){  // ADELANTE
    digitalWrite (In13, HIGH);
    digitalWrite (In24, LOW);

    myservo.write(90);

  }

  if(dato == 'B'){  // ATRAS
    digitalWrite (In13, LOW);
    digitalWrite (In24, HIGH);

    myservo.write(90);

  }

  if(dato == 'R'){  // DERECHA
    myservo.write(35);
  }

  if(dato == 'L'){  // ISQUIERDA
    myservo.write(145);
  }

  if(dato == 'I'){  // ADELANTE Y DERECHA
    digitalWrite (In13, HIGH);
    digitalWrite (In24, LOW);

    myservo.write(35);
  }

  if(dato == 'G'){  // ADELANTE E ISQUIERDA
    digitalWrite (In13, HIGH);
    digitalWrite (In24, LOW);

    myservo.write(145);
  }

  if(dato == 'J'){  // ATRAS Y DERECHA
    digitalWrite (In13, LOW);
    digitalWrite (In24, HIGH);
 
    myservo.write(35);
  }

  if(dato == 'H'){  // ATRAS E ISQUIERDA
    digitalWrite (In13, LOW);
    digitalWrite (In24, HIGH);

    myservo.write(145);
  }

  if(dato =='W'){ //prender luces frontales
    digitalWrite(delanteras, HIGH);

  }

  if(dato =='w'){ //apagar luces frontales
    digitalWrite(delanteras, LOW);

  }

  if(dato =='U'){ //prender luces traseras
    digitalWrite(traseras, HIGH);

  }
  if(dato =='u'){ //apagar luces traseras
    digitalWrite(traseras,  LOW);

  }

  if(dato =='X'){ //Inicia el temporizador para las luces de parqueo
    extra = 1;
  }

  if(dato == 'x'){ //apaga en temporizador, lo encera y apaga las luces de parqueo
    extra = 0;
    temp = 0;
    digitalWrite(delanteras, LOW);
    digitalWrite(traseras, LOW);
    
  }

  if (extra == 1){ //Aumenta el temporizador
    temp++;
    Serial.print("temporizador es: ");
    Serial.println(temp);
  }

  if(temp == 40){ //Control que apaga y prendes las luces de parqueo de acuerdo al temporizador
    if(extra_on==0){
      digitalWrite(delanteras, HIGH);
      digitalWrite(traseras, HIGH);
      extra_on=1;
    }
    else{
      digitalWrite(delanteras, LOW);
      digitalWrite(traseras, LOW);
      extra_on=0;
    }
    temp=0;
  }

  //Control de potencia de los motores traceros
  if(dato == '0')
    analogWrite(enb, 0); //Potencia cero
  if(dato == '1')
    analogWrite(enb, 100); //Potencia minima para que el carro avance
  if(dato == '2')
    analogWrite(enb, 112);
  if(dato == '3')
    analogWrite(enb, 125);
  if(dato == '4')
    analogWrite(enb, 137);
  if(dato == '5')
    analogWrite(enb, 150);
  if(dato == '6')
    analogWrite(enb, 162);
  if(dato == '7')
    analogWrite(enb, 175);
  if(dato == '8')
    analogWrite(enb, 187);
  if(dato == '9')
    analogWrite(enb, 200);
  if(dato == 'q')
    analogWrite(enb, 225); //Potencia maxima
}
