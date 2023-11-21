#include <IRremote.hpp>
#include <LiquidCrystal.h>
#include <Servo.h>

#define PIN_SERVO_AZUL 11
#define SENSOR_TEMP A0

Servo miServo;
LiquidCrystal lcd(2,3,4,5,6,7);

int lectura;
int temperatura;
int value;
bool sistema_estado = false;

// IR REMOTE SETUP
const int rcvPin=10;
IRrecv irrecv(rcvPin);

void setup()
{
   // configurar el numero de filas y columnas
  irrecv.enableIRIn(); //Empezar el recibidor
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop()
{
  lectura_CR();

  if (sistema_estado == true){
    prenderLeds(true);
    ejecutar_sistema();
  }else{
    prenderLeds(false);
  }
}

void ejecutar_sistema(){
  float temperatura = leerTemp();  // Llama a leer_temp() para obtener la temperatura actualizada.
    
  if (temperatura <= 11)
  {
    writeLcd("Invierno", temperatura);
    no_incendio();
  }
  else if (temperatura <= 17)
  {
    writeLcd("Otonio", temperatura);
    no_incendio();
  }
  else if (temperatura <= 26)
  {
    writeLcd("Primavera", temperatura);
    no_incendio();
  }
  else if (temperatura <= 39)
  {
    writeLcd("Verano", temperatura);
    no_incendio();
  }
  else
  {
    writeLcd("Incendio", temperatura);
    incendio();
  }
  delay(500);
  lcd.clear();
}

void writeLcd(String palabra,int temperatura){
  lcd.setCursor(0, 0);// Establece el cursor en la primera línea.
  lcd.print(palabra);
  lcd.setCursor(0,2);
  lcd.print(temperatura);
}
// Leeo la temperatura y la retorno
int leerTemp(){
  lectura = analogRead(SENSOR_TEMP);
  temperatura = map(lectura,20,358,-40,125);
  return temperatura;
}

void incendio(){
  miServo.attach(PIN_SERVO_AZUL, 500,2500);
  miServo.write(100);
}

void no_incendio(){
  miServo.detach();
}

void prenderLeds(bool prender){
  if (prender == true){
    lcd.display();
    analogWrite(9, 255);
    digitalWrite(8, LOW);
  }else{
    lcd.noDisplay();
    digitalWrite(9, LOW);
    analogWrite(8, 255);
  }
}

void lectura_CR(){
  if(IrReceiver.decode()) {// retorna true si se recibe algo, y lo guarda en la variable results
    auto value= IrReceiver.decodedIRData.decodedRawData; 	

      switch(value)
      {        
        case 4278238976:
            Serial.println("POWER");  // Button 1
        	cambiar_estado_sistema();
          	break;
        default: Serial.println(value);     
      }  
    IrReceiver.resume(); // Receibe the next value
  }
}

void cambiar_estado_sistema(){
   sistema_estado = !sistema_estado;
}