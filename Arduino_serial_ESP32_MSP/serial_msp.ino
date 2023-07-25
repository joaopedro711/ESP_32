//recebe o endereço da string que deverá ser enviada para o MSP430

void enviar_comando(const String &str) {
    int tamanho = str.length();
    for (int i = 0; i < tamanho; i++) {
        Serial2.print(str[i]);
        delay(2);
    }
    Serial2.print('\n');                      //só para o ultimo caractere da mensagem ser um '\n', tem que ser aspas simples para reconhecer como unico caractere
}

String receber_mensagem(){
  String response= "";
  if (Serial2.available()) {  // Verifica se há dados disponíveis na Serial2
    response = Serial2.readStringUntil('\0');  // Lê a resposta até encontrar o caractere nulo
    if (response.charAt(0) == '$') {                                        // Verifica se o primeiro caractere é igual a '$'
      if (response.charAt(response.length() - 1) == ';') {                  // Verifica se o último caractere é igual a ';'
        return response;
      }
    }
    else{                         //significa que a mensagem não foi satisfeita
      response = "";
      return response;
    }  
  }  
}

String removePrimeiroUltimoCaractere(const String& str) {
  return str.substring(1, str.length() - 1);
}
