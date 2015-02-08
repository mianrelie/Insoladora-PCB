// ----------------------------------------
// -- Insoladora PCB
// -- Temporizador con menu para una insoladora casera de PCB. Nos permite determinar el tiempo de insolado
// -- Preparado para una cara con avisador luminoso de fin del insolado.
// -- Version 0.1 (Febrero 2015)
// -- Se utilizan la libreria CountDownTimer.h de AndrewMascolo https://github.com/AndrewMascolo/CountDownTimer
// -- Miguel Angel Redondo
// -- maredondo.liebana@gmail.com

#include <LiquidCrystal.h>
#include <CountDownTimer.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Up = 6;
int Down = 7;
int Ok = 8;
int Cancel = 9;
CountDownTimer T;


void setup(){

  T.SetTimer(0,0,0);
  T.StartTimer();
  
  
  lcd.begin(16, 2);
  lcd.print(" Insoladora PCB"); // Mensaje de bienvenida
  delay(5000);
  lcd.clear(); // Borra a los 5sg
  
  lcd.setCursor(0,0);
  lcd.print("Tiempo insolado");  
  lcd.setCursor(0,1);
  lcd.print(T.ShowMinutes());
  lcd.print(" min ");
  lcd.print(T.ShowSeconds());
  lcd.print(" sg"); 
}

void loop(){
 
 
  
}
