/*
 * Display computer resources (CPU, GPU, RAM) on Arduino with tiny 16x2 lcd panel
 *
 * @package arduino-cpu-monitor
 * @author Sergei Miami <miami@blackcrystal.net>
 * @author Max Radchenko <max@blackcrystal.net>
 */

#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

char buf[16];
int cpu = 0;
int gpu = 0;
int ram = 0;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, try 0x27 or 0x3F.

void setup() {

  lcd.begin(16,2);  
  lcd.setCursor(0,0); // top row, write headers
  sprintf( buf, "%4s %4s %4s", "CPU%", "GPU", "RAM" ); 
  lcd.print( buf );
  Serial.begin(9600); // read for input from serial port
  Serial.setTimeout(1000); // wait 1 second for signal to come

}

void loop() {

  while (Serial.available() > 0) {
    cpu = Serial.parseInt();
    gpu = Serial.parseInt();
    ram = Serial.parseInt();  
    lcd.setCursor(0,1);
    sprintf( buf, "%4d %4d %4d", cpu, gpu, ram);
    lcd.print( buf );
    Serial.println( buf );     
  }

  delay(1000);
  
}
