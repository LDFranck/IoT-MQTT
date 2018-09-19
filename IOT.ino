/*
 * Autor: Lucas Daudt Franck
 * Email: lfranck@outlook.com.br
 * 
 * Placa: NodeMCU8266 ou NodeMCUESP32
 * 
 * Objetivo:
 * Realizar conexão ao broker MQTT da Tago.io
 * 
 * Versão: 0.2
 */

//Placa de desenvolvimento
#define Placa_ESP8266
//#define Placa_ESP32


//Modo de comunicaçao - apenas um modo pode estar definido
/*
 * Em modo Terminal_Serial:
 * 1# Esperar confirmação da conexão
 * 2# Enviar string de caracteres no formato JSON via serial para publicar no broker: {"variable":"temperature","value":5}
 * 3# Esperar confirmação da publicação antes de enviar nova string
 * 
 * Em modo Outra_Placa:
 * 1# Enviar 'S' (letra S maiuscula) via serial para informar inicializar a conexão com a internet
 * 2# Esperar confirmação da conexão 'C' (letra C maiuscula)
 * 3# Enviar string de caracteres no formato JSON via serial para publicar no broker: {"variable":"temperature","value":5}
 * 4# Esperar confirmação da publicação 'P' (letra P maiuscula) antes de enviar nova string
 */
 //#define Terminal_Serial
#define Outra_Placa


//Bibliotecas necessárias
#ifdef Placa_ESP8266
#include <ESP8266WiFi.h>
#elif defined Placa_ESP32
#include <WiFi.h>
#endif 
#include <PubSubClient.h>
#include <WiFiClientSecure.h>


//Configurações da Internet
const char* ssid = "..."; //Nome da rede
const char* pass = "..."; //Senha da rede


//Configurações do Broker
const char* broker_address = "mqtt.tago.io";
const int broker_port = 8883;
const char* clientID = "clientID";
const char* username = "username";
const char* password = "..."; //Token
const char* publish_topic = "tago/data/post";


//Cria as instancias dos objetos
WiFiClientSecure espClient;
PubSubClient client(espClient);


//Variaveis globais
String msg;


void setup() {
  setUp_Inicial();
}


void loop() {

if(Serial.available()){
  msg=Serial.readString();
  publicaMQTT(msg.c_str());
}
  delay(1);
}


void brokerNewMessageCallback(char* topic, byte* payload, unsigned int length){
  //Interrupcao chamada quando uma nova mensagem é recebida do broker

}
