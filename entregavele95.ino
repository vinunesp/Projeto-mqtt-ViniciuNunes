int pino2 = 2; //cria uma variavel para o pino 2

bool estado_sensor; //cria uma variavel para armazenar o estado do sensor 

#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>


//Define o endereço MAC que será utilizado
byte mac[] = {0x00,0xE0,0x4C,0x2A,0x2A,0xEC};
boolean mensagem;
//Inicia o cliente Ethernet
EthernetClient client;

PubSubClient mqttClient(client);
 
void setup() {

  pinMode(pino2,INPUT_PULLUP); // coloca o pino 2 como entrada 
Serial.begin(9600); //Inicia o monitor serial

    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    mqttClient.setServer("54.161.191.80",1883);

    //Inicia o monitor Serial
    Serial.begin(9600);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop() {

  estado_sensor = digitalRead(pino2); // Efetua a leitura do pino 2 e armazena o valor obitido na varialvel 

if  (estado_sensor==1){
Serial.println ("O sensor esta aberto!!");
Serial.println(estado_sensor);
mensagem = mqttClient.publish("0vinunesp","aberto");}

if (estado_sensor==0){
Serial.println ("O sensor esta fechado!!");
Serial.println(estado_sensor);
mensagem = mqttClient.publish("0vinunesp","fechado");}
 
 
mqttClient.connect("vinunesp");


 
  //Serial.println(" o sensor esta fechado");
  //mensagem = mqttClient.publish("0vinunesp","fechado");
  //Serial.println(mensagem);
  
  mqttClient.loop();

}
