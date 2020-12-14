/*Feito por Carlos Daniel Batista e Ariel Vieira de Oliveira para materia de 
Projeto de Sistemas embarcados do segundo semestre de 2020, aulas ministradas 
pelos professores Cesar Albenes Zeferino, Paulo Roberto Valim e Felipe Viel.*/

#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <WiFi.h>
#include<WiFiClient.h>
#include "Arduino.h"
#include<BlynkSimpleEsp32.h>

char auth[] = "1nhfIAGxBrBy6iuvWSb4mEZm_rHRoEKe";
char ssid[] = "BR7 BATISTA 2.4G";
char pass[] = "deskjetf2050";


#define LDR 4 // Porta do LDR
#define RED 18 // Porta do LED RGB - VERMELHO
#define GREEN 19 // Porta do LED RGB - VERDE
#define BLUE 21 // Porta do LED RGB - AZUL
#define LED 23 // Saida do Relé NA
#define COMUM 13 // Porta comum do Relé
#define BOTAO 12 // Saida Botão

#define R 0
#define G 1
#define B 2
#define C 3

#define Frequencia 5000 // pwm

#define Resolucao 8 //8 bit

BLYNK_WRITE(V0){//LED RGB 
  void RGB_Cor(int i, int j, int k);
  int pinValue = param.asInt();
  if(pinValue == 1){
    RGB_Cor(255,0,0);// Vermelho
    delay(500);//Tempo de 1/2 segundo
    RGB_Cor(0,255,0); //Verde
    delay(500);//Tempo de 1/2 segundo
    RGB_Cor(0,0,255);// Azul
    delay(500);//Tempo de 1/2 segundo
    RGB_Cor(255,255,255); //Todas as cores
    delay(500); //Tempo de 1/2 segundo
    RGB_Cor(0,0,0); //Apagado
    delay(500); //Tempo de 1/2 segundo
  }else{
    RGB_Cor(0,0,0); //Apagado
    delay(500); //Tempo de 1/2 segundo
  }
}

BLYNK_WRITE(V1){//Botão
  void COMUM_valor(int z);
  int pinValue = param.asInt();
  int BOTAO_val = analogRead(BOTAO);
  if(pinValue == 1){
    if(BOTAO_val == 1){
      COMUM_valor(200);
    }else{
      COMUM_valor(10);
    }
  }else{
    COMUM_valor(0);
  }
}
  

BLYNK_WRITE(V2){ //RGB Caso Desligado
  void RGB_Cor(int i, int j, int k);
  int pinValue = param.asInt();
  int LED_val = analogRead(LED);
   if(pinValue == 1){ //RGB acendera uma das cores caso se consiga pegar o valor do LED
      if(LED_val == 10){ //Acaso LED receber NA
        RGB_Cor(255,0,0);
        delay(500); //Tempo de 1/2 segundo
      }else if(LED_val == 200) {//Acaso LED receber NF
        RGB_Cor(0,0,255); //Azul
        delay(500); //Tempo de 1/2 segundo
      }else{ //Acaso LED receber valor diferente de NA e NF
        RGB_Cor(0,255,0); //Verde
        delay(500); //Tempo de 1/2 segundo
      }
   }else{ //RGB acendera todas as cores caso não conseguir pegar o valor do LED
     RGB_Cor(255,255,255);
     delay(500); //Tempo de 1/2 segundo
   }
}
BLYNK_WRITE(V3){// RGB com LDR
  void RGB_Cor(int i, int j, int k);
  int pinValue = param.asInt();
  if(pinValue == 1){
  int LDR_val = analogRead(LDR); // Função para leitura do LDR
  Serial.println(LDR_val); //Função para printar o LDR
    if(LDR_val == 0){ // Ambinete escuro
      RGB_Cor(255,0,0); //Piscar luz Vermelha
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(0,0,0); //Apagado
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(255,0,0); //Vermelho
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(0,0,0); //Apagado
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(255,0,0); //Vermelho
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(0,0,0); //Apagado
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(255,0,0); //Vermelho
      delay(500); //Tempo de 1/2 segundo
      RGB_Cor(0,0,0); //Apagado
      delay(500); //Tempo de 1/2 segundo
    }else{
      RGB_Cor(0,0,0); //Apagado
      delay(5000); //Tempo de 5 segundo
    }
  }else{
    RGB_Cor(0,0,0); //Apagado
    delay(5000); //Tempo de 5 segundo
  }
}


BLYNK_WRITE(V4){ //Piscar LED
  void RGB_Cor(int i, int j, int k);
  int pinValue = param.asInt();
  if(pinValue == 1){
   digitalWrite(COMUM, HIGH);
   delay(500); //Tempo de 1/2 segundo
   digitalWrite(COMUM, LOW);
   delay(500); //Tempo de 1/2 segundo
   digitalWrite(COMUM, HIGH);
   delay(500); //Tempo de 1/2 segundo
   digitalWrite(COMUM, LOW);
   delay(500); //Tempo de 1/2 segundo
   digitalWrite(COMUM, HIGH);
   delay(500); //Tempo de 1/2 segundo
   digitalWrite(COMUM, LOW);
   delay(500); //Tempo de 1/2 segundo
  }
}
BLYNK_WRITE(V5){
  void RGB_Cor(int i, int j, int k);
  int pinValue = param.asInt();
  if(pinValue == 1){
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
  }
}
void setup(){
  pinMode(LED, OUTPUT); //LED padrão
  ledcAttachPin(RED, R); //LED RGB
  ledcAttachPin(GREEN, G); //LED RGB
  ledcAttachPin(BLUE, B); //LED RGB
  ledcAttachPin(COMUM, C); //COMUM

  ledcSetup(R, Frequencia, Resolucao); //Configuração led RGB - VERMELHO
  ledcSetup(G, Frequencia, Resolucao); //Configuração led RGB - VERDE
  ledcSetup(B, Frequencia, Resolucao); //Configuração led RGB - AZUL
  ledcSetup(C, Frequencia, Resolucao); //Configuração led RGB - AZUL
  Serial.begin(9600); // Taxa de comunicação serial em bits por segundoo
  Blynk.begin(auth, ssid, pass);
}
void COMUM_valor(int z){ //Função para controlar o COMUM
  ledcWrite(C, z);
}
void RGB_Cor(int i, int j, int k){ //Função para controlar a temperantura\cor do RGB
  ledcWrite(R, k);
  ledcWrite(G, j);
  ledcWrite(B, i);
}
void loop(){
  Blynk.run();
  int x = 255; // Valor minimo = 0 e valor maximo = 255
  int y = 255; // Valor minimo = 0 e valor maximo = 255
  int z = 255; // Valor minimo = 0 e valor maximo = 255
  int LDR_val = analogRead(LDR); // Função para leitura do LDR
  Serial.println(LDR_val); //Função para printar o LDR
}
