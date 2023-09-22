/*
Pines de Conexión
 Arduino pin 5 -> HX711 CLK
 Arduino pin 6 -> HX711 DOUT
 Arduino pin 5V -> HX711 VCC
 Arduino pin GND -> HX711 GND 
*/

#include <HX711.h>

HX711 scale(6, 5);

float calibration_factor = -14; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

void setup() {
  Serial.begin(9600);
  Serial.println("Sketch De Calibración");
  Serial.println("Retire cualquier peso de la bascula");
  Serial.println("Después de que la bascula comience con lecturas, coloque un peso conocido en la bascula");
  Serial.println("Presione + o 'a' para incrementar el factor de calibración");
  Serial.println("Presione - or 'z' para ecrementar el factor de calibración");
  delay(5000);

  scale.set_scale();
  scale.tare();  //Hacemos que la bascula se haga 0

  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Ajustamos la bascula con el factor de calibración actual

  Serial.print("Leyendo: ");
  units = scale.get_units(), 10;//realizamos 10 lecturas
  if (units < 0)//Si la lectura es negativa (peso menor a 0), lo asignamos directo a 0
  {
    units = 0.00;
  }
  ounces = units * 0.035274;//Lo multiplicamos por esta constante que nos da las unidades en gramos
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" Factor de Calibración: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
}
