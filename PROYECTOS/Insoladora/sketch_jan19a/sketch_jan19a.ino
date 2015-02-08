#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Inicializacion de constantes

// Definimos una cruceta para manejar las opciones
int botonUp = 13;
int botonDown = 7;
int botonRight = 8;
const int botonLeft = 9;
const int botonOk = 6; // Boton para confirmar opcion

int cara1Led = 4; // Cara tapa inferior
int cara2Led = 2; // Cara tapa superior
//int ledRojo = 6; // "Trabajando"
int ledVerde = 5; // "En resposo"
int LDR = A6; // "Sensor luz - apertura maleta"

// Inicializamos las variables

int Caras = 1;
int Minutos = 0;
int Segundos = 0;
int Aceptar = 0;
int Left = 0;
int Right = 0;
int cuentaAtras = 30;
long tiempoTotal = 0;
int valorLDR = 512;
int On = 0;

void setup(){
  
  // Salidas digitales
  
  pinMode(cara1Led, OUTPUT);
  pinMode(cara2Led, OUTPUT);
//  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Entradas para botones

  pinMode(botonUp, INPUT);
  pinMode(botonDown, INPUT);
  pinMode(botonRight, INPUT);
  pinMode(botonLeft, INPUT);
  
  pinMode(LDR, INPUT);
  
  lcd.begin(16, 2);
  lcd.print(" Insoladora PCB"); // Mensaje de bienvenida
  delay(5000);
  lcd.clear(); // Borra a los 5sg
  lcd.print("Aceptar para menu");
}

void loop(){
  
  Aceptar = digitalRead(botonOk); 
  
  if (Aceptar == HIGH){ //Si presionamos OK - Salta al menu (Se puede prescindir de esto y que salte a caras-tiempo
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<-Caras Tiempo->");
  }

  
  Left = digitalRead(botonLeft);
  
  if (Left == HIGH){
    lcd.clear();
    lcd.print("Caras: ");
  }

  Right = digitalRead(botonRight);

  if (Right == HIGH){
    lcd.clear();
    lcd.print("Tiempo: ");
  }
  
}


