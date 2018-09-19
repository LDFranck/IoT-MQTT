void setUp_Inicial(void){
#ifdef Terminal_Serial
  uint8_t mac[6];
  String eMac;
  Serial.begin(115200); //inicial serial em 115200
  delay(10);
  //Obtem endereco MAC do dispositivo
  Serial.print("Endereço MAC: ");
  WiFi.macAddress(mac);
    for (int i = 0; i < 6; ++i) {
    eMac += String(mac[i], 16);
    if(i<5)eMac +=':';
  }
  Serial.print(eMac);
  //Conecta a rede WiFi
  Serial.print("\nConectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConexão WiFi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.readString(); //limpa buffer da serial

  //Conecta ao broker
  client.setServer(broker_address, broker_port);

  //Define funcao de callback ao receber mensagem do broker
  client.setCallback(brokerNewMessageCallback);

#elif defined Outra_Placa
  Serial.begin(115200); //inicial serial em 115200
  delay(10);
  while(Serial.read()!='S')delay(100);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
  }
  Serial.readString(); //limpa buffer da serial
  Serial.print('C');
  client.setServer(broker_address, broker_port);
  client.setCallback(brokerNewMessageCallback);
#endif
}
