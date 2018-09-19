void conectaMQTT(void) {
#ifdef Terminal_Serial
  //Verifica conexão
  if(!client.connected()){
    //Enquanto não estivermos conectados
    while (!client.connected()){
    Serial.print("Realizando uma conexão MQTT... ");
    //Tenta realizar uma conexão
    if(client.connect(clientID, username, password)) Serial.println("Conexão estabelecida");
    else{
      Serial.print("Falha ao conectar, rc=");
      Serial.print(client.state());
      Serial.println(" , tentando novamente em 5s");
      delay(5000);
      }
    }
  }
  client.loop();

#elif defined Outra_Placa
  if(!client.connected()){
      while (!client.connected()){
        if(client.connect(clientID, username, password))break;
        else delay(5000);
      }
  }
    client.loop();
#endif
}

void publicaMQTT(const char* payload){
#ifdef Terminal_Serial  
  conectaMQTT();
  Serial.print("Mensagem publicada: ");
  Serial.println(payload);
  client.publish(publish_topic, payload);

#elif defined Outra_Placa
  conectaMQTT();
  client.publish(publish_topic, payload);
  Serial.print('P');
#endif
}
