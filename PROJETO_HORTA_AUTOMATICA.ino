/*Projeto Horta automática com arduino LabInec 2022
 *Autor: Caio Livium Barros de Sousa
 *Orientadora: Anny Caroline
 */

#include <LiquidCrystal.h> // Inclui a biblioteca para o display LCD

#define sensor A0        // Define o pino A0 como sensor de umidade
#define rgbAzul 7        // Define o pino 7 como LED RGB azul
#define rgbVerde 6       // Define o pino 6 como LED RGB verde
#define rgbVermelho 8    // Define o pino 8 como LED RGB vermelho
#define Buzzer 9         // Define o pino 9 como buzzer
#define Rele 13          // Define o pino 13 como relé para controlar a bomba de água

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Configura os pinos para o display LCD

float nivelUmidade; // Variável para armazenar o nível de umidade

// Função para ligar o LED vermelho
void ligar_vermelho(){
  digitalWrite(rgbAzul, LOW);
  digitalWrite(rgbVerde, LOW);
  digitalWrite(rgbVermelho, HIGH);
}

// Função para ligar o LED verde
void ligar_verde(){
  digitalWrite(rgbAzul, LOW);
  digitalWrite(rgbVerde, HIGH);
  digitalWrite(rgbVermelho, LOW);
}

// Função para acionar o buzzer
void ApitoBuzzer(){
  tone(Buzzer, 1500); // Emite um som de 1500 Hz
  delay(500);         // Espera 500 milissegundos
  noTone(Buzzer);     // Desliga o buzzer
  delay(500);
  tone(Buzzer, 1500);
  delay(500);
  noTone(Buzzer);
  delay(500);
  tone(Buzzer, 1500);
  delay(500);
  noTone(Buzzer);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(Rele, OUTPUT);
  digitalWrite(Rele, HIGH); // Desliga o relé inicialmente
  pinMode(sensor, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(rgbVermelho, OUTPUT);
  pinMode(rgbVerde, OUTPUT);
  pinMode(rgbAzul, OUTPUT);
}

void loop() {
  nivelUmidade = analogRead(sensor); // Lê o valor do sensor de umidade
  Serial.print("\nUmidade: ");
  Serial.println(nivelUmidade);
  Serial.println(Rele);

  if (nivelUmidade >= 600) {
    lcd.clear(); // Limpa o display LCD
    lcd.print("ESTOU COM SEDE");
    lcd.setCursor(0, 2); // Move o cursor para a segunda linha
    lcd.print("Umidade: ");
    lcd.print(nivelUmidade / 1023 * 100); // Calcula a umidade em porcentagem
    ligar_vermelho(); // Liga o LED vermelho
    if (nivelUmidade >= 700) {
      ApitoBuzzer(); // Aciona o buzzer
      digitalWrite(Rele, LOW); // Liga a bomba de água
    }
  } else if (nivelUmidade < 600) {
    lcd.clear();
    lcd.print("HIDRATADA");
    lcd.setCursor(0, 2);
    lcd.print("Umidade: ");
    lcd.print(nivelUmidade / 1023 * 100);
    ligar_verde(); // Liga o LED verde
    noTone(Buzzer); // Desliga o buzzer
    digitalWrite(Rele, HIGH); // Desliga a bomba de água
  }
}