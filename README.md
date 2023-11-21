# PARCIAL SPD ( PRIMERA PARTE)

## Integrantes 
- Ezequiel Cura
- DNI: 44160534


## Proyecto: 3 DISPLAY SEGMENTOS, MOTOR, SENSOR DE TEMPERATURA, SLIDESWITCH & PHOTODIODE
![Tinkercad](/Image/PRIMERA%20PARTE/Imagen%20sistema%20primeraParte.png)


## Descripcion
Este codigo es un programa escrito en el lenguaje de programacion C++. Su objetivo es simular un sistema de incendio con arduino. Tiene que poder leer temperatura, mover un servo, mostrar por display y controlarlo con un control remoto.

#### Componentes
- Sensor de temperatura
- 2 LEDS
- Display
- Control remoto IR (Infrarrojo)
- Display LCD (16x2 caracteres)
- Servo motor

### Inicializacion variables

~~~ C++ (lenguaje en el que esta escrito)
// Importo la librerias que necesito
#include <IRremote.hpp> // Para el control remoto
#include <LiquidCrystal.h> // Para el display
#include <Servo.h> // Para el Servo

// Le pongo nombres a las pines del arduino
#define PIN_SERVO_AZUL 11
#define SENSOR_TEMP A0

Servo miServo; // Le pongo nombre a mi servo
LiquidCrystal lcd(2,3,4,5,6,7); // Le pongo nombre a mi display lcd

//Inicializo unas variables
int lectura;
int temperatura;
int value;
bool sistema_estado = false;

// IR REMOTE SETUP
const int rcvPin=10; // setup del recibidor IR
IRrecv irrecv(rcvPin);
~~~


### Funcion SetUp
~~~ C++ (lenguaje en el que esta escrito)
void setup()
{
  irrecv.enableIRIn(); //Empezar el recibidor
  lcd.begin(16,2);// configurar el numero de filas y columnas
  Serial.begin(9600);
}
~~~


### Funcion loop
~~~ C++ (lenguaje en el que esta escrito)
void loop()
{
  lectura_CR(); // llamo una funcion donde se fija si recibe algo del control remoto

  if (sistema_estado == true){ // Si se prende el sistema con el control remoto entra aca
    prenderLeds(true); // Prende la led verde y apaga la roja, prende el display tambien
    ejecutar_sistema(); // Ejecuta el sistema de incendio
  }else{
    prenderLeds(false); // Apaga la led verde y prende la roja, apaga el display
  }
}
~~~


### Funcion lectura_CR
~~~ C++ (lenguaje en el que esta escrito)
void lectura_CR(){
  if(IrReceiver.decode()) {// retorna true si se recibe algo
    auto value= IrReceiver.decodedIRData.decodedRawData; // Obtenemos el valor 	

      switch(value) 
      {        
        case 4278238976: // Si el boton apretado es el correcto cambiamos el estado de la varaible
            Serial.println("POWER");  // Button 1
        	cambiar_estado_sistema();
          	break;
        default: Serial.println(value);     
      }  
    IrReceiver.resume(); //  Recibe el sisguiente valor
  }
}
~~~


### Funcion cambiar_estado_sistema
~~~ C++ (lenguaje en el que esta escrito)
void cambiar_estado_sistema(){
   sistema_estado = !sistema_estado; // Lo unico que hacemos en esta funcion es cambiar el estado de la variable para poder despues iniciar el sistema
}
~~~

### Funcion prenderLeds
~~~ C++ (lenguaje en el que esta escrito)
void prenderLeds(bool prender){ // recibe un parametro para saber que prender
  if (prender == true){
    lcd.display(); // prende la display
    analogWrite(9, 255); // prende la led verde 
    digitalWrite(8, LOW); // apaga la led roja
  }else{
    lcd.noDisplay(); // apaga la display
    digitalWrite(9, LOW); // apaga la led verde
    analogWrite(8, 255); // prende la led roja
  }
}
~~~


### Funcion ejecutar_sistema
~~~ C++ (lenguaje en el que esta escrito)
void ejecutar_sistema(){
  float temperatura = leerTemp();  // Llama a leer_temp() para obtener la temperatura actualizada.

  // Tenemos una cadena de if para poder sabes que estacion del año es con su temperatura
  if (temperatura <= 11)
  {
    writeLcd("Invierno", temperatura); // LLamamos a la funcion writeLcd para escribir en el display
    no_incendio(); // Si no hay incendio no se mueve el servo
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
  delay(500); // Un delay de medio segundo 
  lcd.clear(); // Limpiar la display
}
~~~

### Funcion writeLcd
~~~ C++ (lenguaje en el que esta escrito)
void writeLcd(String palabra,int temperatura){
  lcd.setCursor(0, 0);// Establece el cursor en la primera línea.
  lcd.print(palabra);
  lcd.setCursor(0,2); // establece el cursor en la segunda linea
  lcd.print(temperatura);
}
~~~

### Funcion leerTemp
~~~ C++ (lenguaje en el que esta escrito)
int leerTemp(){
  // Leo la temperatura y la retorno
  lectura = analogRead(SENSOR_TEMP);
  temperatura = map(lectura,20,358,-40,125);
  return temperatura;
}
~~~

### Funcion incendio
~~~ C++ (lenguaje en el que esta escrito)
void incendio(){
  miServo.attach(PIN_SERVO_AZUL, 500,2500);
  miServo.write(100); // Al haber un incendio lo unico que hace es prender el servo y empieza a girar
}
~~~

### Funcion no_incendio
~~~ C++ (lenguaje en el que esta escrito)
void no_incendio(){
  miServo.detach(); // Si no hay incendio lo unico que hace es parar el servo
}
~~~


## Diagrama del proyecto
![Diagrama](/Image/PRIMERA%20PARTE/Diagrama%20primeraParte.png)

## :robot: Link al proyecto
- [Proyecto](https://www.tinkercad.com/things/9kFKA8px4Yf-segundo-parcial-1/editel?returnTo=%2Fdashboard%3Ftype%3Dcircuits%26collection%3Ddesigns&sharecode=p4DzKCCaWABnkM_nGRRJnBEv8hvFJL1POEOXUeQscZk)






