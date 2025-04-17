#include <LiquidCrystal.h>

#define MQ135_PIN A1  // MQ135 sensor connected to A1
#define BUZZER_PIN 6  // Buzzer connected to pin 6

int co2Level;  // Variable to store CO2 level

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(MQ135_PIN, INPUT);  // Set the MQ135 pin as input
  pinMode(BUZZER_PIN, OUTPUT);  // Set the buzzer pin as output
  Serial.begin(9600);  // Begin serial communication at 9600 baud

  lcd.begin(16, 2);  // Initialize the 16x2 LCD display
  lcd.print("CO2 Monitor");  // Display welcome message
  delay(2000);  // Wait for 2 seconds
  lcd.clear();  // Clear the display
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);  // Read the analog value from MQ135 sensor
  co2Level = map(sensorValue, 0, 1023, 400, 5000);  // Map the sensor value to CO2 ppm range

  lcd.setCursor(0, 0);  // Set the cursor to the first row
  lcd.print("CO2 Level:");  // Display the CO2 level label
  lcd.setCursor(0, 1);  // Set the cursor to the second row
  lcd.print(co2Level);  // Display the CO2 level in ppm
  lcd.print(" ppm");  // Display the unit ppm

  // Check CO2 level and take appropriate actions
  if (co2Level < 1000) {
    lcd.print(" Good  ");
    digitalWrite(BUZZER_PIN, LOW);  // Turn off the buzzer
  } else if (co2Level < 2000) {
    lcd.print(" Warning ");
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
  } else {
    lcd.print(" Danger!");
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
  }

  delay(2000);  // Wait for 2 seconds before the next update
  lcd.clear();  // Clear the display for the next update
}