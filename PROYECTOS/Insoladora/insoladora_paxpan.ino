// Insoladora doble cara V.1.3
// escrito y dirigido por paxpancillo@hotmail.com

#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// iniciamos el LCD
  
LiquidCrystal_I2C lcd(0x27,16,2);

// iniciamos las constantes

const int botonInicio = 7;  // definimos la entrada digital 7 para el pulsador de inicio
const int botonCaras = 8;   // definimos la entrada digital 8 para el pulsador de numero de caras
const int botonMinUp = 12;  // definimos la entrada digital 12 para el pulsador de mas minutos
const int botonMinDown = 11;// definimos la entrada digital 11 para el pulsador de menos minutos
const int botonSegUp = 10;  // definimos la entrada digital 10 para el pulsador de mas segundos
const int botonSegDown = 9; // definimos la entrada digital 9 para el pulsador de menos segundos
const int cara1led = 4;     // definimos la placa de luz superior
const int cara2led = 2;     // definimos la placa de luz inferior
const int ledrojo = 6;      // definimos el led de control "no abrir"
const int ledverde = 5;     // definimos el led de control "podemos abrir"
const int LDR = A6;         // definimos la entrada de la fotorresistencia
 
// iniciamos las variables
 
int estadobotonCaras = 0;   // variable para el estatus del pulsador caras
int estadobotonMinUp = 0;   // variable para el estatus del pulsador mas minutos  
int estadobotonMinDown = 0; // variable para el estatus del pulsador menos minutos
int estadobotonSegUp = 0;   // variable para el estatus del pulsador mas segundos  
int estadobotonSegDown = 0; // variable para el estatus del pulsador menos segundos
int estadobotonInicio = 0;  // variable para el estatus del pulsador inicio
int cuentaatras = 30;       // variable para la cuenta atras de inicio de insolación
int inicio = 0;             // variable para el inicio
int caras = 1;              // variable para el numero de caras         
int minuto = 0;             // variable para el contador de minutos
int segundo = 0;            // variable para el contador de segundos
long tiempototal = 0;       // variable para la suma del tiempo
int valorLDR = 0;           // variable para el estatus de la fotorresistencia
int LDRComp = 512;          // variable para el convertidor de la fotorresistencia

void setup()
{
  
// establecemos las salidas digitales

pinMode(cara1led, OUTPUT);   // placa LED arriba 
pinMode(cara2led, OUTPUT);   // placa LED abajo 
pinMode(ledrojo, OUTPUT);    // chivato led rojo 
pinMode(ledverde, OUTPUT);   // chivato led verde
  
// establecemos los botones como entradas

pinMode(botonCaras, INPUT);  
pinMode(botonMinUp, INPUT);  
pinMode(botonMinDown, INPUT);  
pinMode(botonSegUp, INPUT);  
pinMode(botonSegDown, INPUT);  
pinMode(botonInicio, INPUT);  

// establecemos la fotoresistencia como chivato de apertura

pinMode(LDR, INPUT);
  
// iniciamos el LCD 

lcd.init();                      
lcd.backlight(); 

// escribimos el mensaje de bienvenida

lcd.print("   Bienvenido");
delay(1000);
lcd.setCursor(1, 0);
lcd.print("  Insoladora");
lcd.setCursor(0, 1);
lcd.print("    LunchBox");
delay(2000);
lcd.clear();
 
}

void loop()
{
  
  
// Aquí ponemos el tiempo y el numero de caras que queremos insolar  
  
estadobotonInicio = digitalRead(botonInicio);
if (estadobotonInicio == HIGH)
    { inicio = 1;
      } 
lcd.setCursor(0, 0);
lcd.print("Numero caras = ");
estadobotonCaras = digitalRead(botonCaras);
if (estadobotonCaras == HIGH)   
  if (caras == 1)
  {caras = 2;
  digitalWrite (cara1led, HIGH);
  digitalWrite (cara2led, HIGH);
  delay(500); 
  digitalWrite (cara1led, LOW);
  digitalWrite (cara2led, LOW);
  }
  else 
  {caras = 1;
  digitalWrite (cara1led, HIGH);
  delay(500); 
  digitalWrite (cara1led, LOW);
  }
lcd.print(caras);  
lcd.setCursor(0, 1);
lcd.print("Tiempo = ");
estadobotonMinUp = digitalRead(botonMinUp);
if (estadobotonMinUp == HIGH)
  {
    minuto++ ;
  }
estadobotonMinDown = digitalRead(botonMinDown);
if (estadobotonMinDown == HIGH)
  {
    minuto-- ;
    if (minuto < 0)  		// evitamos que de números negativos
    {
      minuto = 0;
    }
  }
estadobotonSegUp = digitalRead(botonSegUp);
if (estadobotonSegUp == HIGH)
  {
    segundo = segundo + 10;
    if (segundo == 60)
      segundo=0;
  }  
    estadobotonSegDown = digitalRead(botonSegDown);
    if (estadobotonSegDown == HIGH)
      {
        segundo = segundo - 10;
        if (segundo < 0)
          segundo = 0;
      }    
  
    lcd.print(minuto);
    lcd.print(":");
    lcd.print(segundo);
    delay(300); 


// Ya hemos acabado de poner el tiempo y el numero de caras y pulsamos inicio
// A continuación tenemos 30 segundos para posicionar la placa y cerrar la tapa

if (inicio == 1)  
  { 
    inicio = 0; 
    lcd.clear();
    lcd.print("Prepara la placa");
    for (cuentaatras=30; cuentaatras != 0; cuentaatras --)
    {
    lcd.setCursor(0, 1);
    lcd.print("Inicio en ");   
    lcd.print(cuentaatras);
    lcd.print(" seg ");
    delay(1000);
    }
    
    lcd.clear();                
    minuto = minuto * 10000;
    segundo = segundo * 1000;
    tiempototal = minuto + segundo;
    
if (caras == 1)  
    {
    lcd.noBacklight();
    digitalWrite (cara1led, HIGH);
    digitalWrite (ledverde, LOW);
    digitalWrite (ledrojo, HIGH);
    delay(tiempototal);
    digitalWrite (cara1led, LOW);
    digitalWrite (ledrojo, LOW);
    digitalWrite (ledverde, HIGH);
    while (valorLDR < LDRComp)
      {
       valorLDR = analogRead(LDR);
      }
    
    }
if (caras == 2)
    {
    lcd.noBacklight();
    digitalWrite (cara1led, HIGH);
    digitalWrite (cara2led, HIGH);
    digitalWrite (ledverde, LOW);
    digitalWrite (ledrojo, HIGH);

    digitalWrite (cara1led, LOW);
    digitalWrite (cara2led, LOW);
    digitalWrite (ledrojo, LOW);
    digitalWrite (ledverde, HIGH);  
    while (valorLDR < LDRComp)
      {
       valorLDR = analogRead(LDR);
      }  
    }
  
    lcd.backlight();
    lcd.clear();
    lcd.print("Retira la placa");
    lcd.setCursor(0, 1);
    lcd.print("y revelala "); 
    delay(10000);
    
// Reiniciamos las variables
    
    caras = 1;
    tiempototal = 0;
    minuto = minuto / 10000;
    segundo = segundo / 1000;
    valorLDR = 0; 
    digitalWrite (ledrojo, LOW);
    digitalWrite (ledverde, LOW); 
    
 }

}