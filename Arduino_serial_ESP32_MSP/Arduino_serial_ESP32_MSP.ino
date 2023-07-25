//void setup() {
//  Serial.begin(115200);
//  Serial2.begin(115200, SERIAL_8N1, 15, 4);  // Inicializa a comunicação serial na Serial2
//}
//
//void loop() {
//  if (Serial2.available()) {  // Verifica se há dados disponíveis na Serial2
//    String response = Serial2.readString();  // Lê a resposta da Serial2 e armazena em uma string
//    Serial.println("Resposta: " + response);  // Imprime a resposta no monitor serial
//  }
//}

volatile int buttonPressCount = 0;
volatile unsigned long lastButtonPressTime = 0;
const int buttonPin = 0; // Pino GPIO0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR buttonInterrupt() {
  unsigned long currentTime = millis();
  if (currentTime - lastButtonPressTime > 100) { // Debouncing time of 100ms
    buttonPressCount++;
    lastButtonPressTime = currentTime;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING); // Configura a interrupção para o botão (borda de descida)
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 15, 4);  // Inicializa a comunicação serial na Serial2
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  
  String mensagem = receber_mensagem();
  if(mensagem.length() > 0){
    String mensagemSemExtremos = removePrimeiroUltimoCaractere(mensagem);
    Serial.println("Resposta: " + mensagemSemExtremos);  // Imprime a resposta no monitor serial
  }
  
  if (buttonPressCount > 0) {
    delay(5000); // Espera 5 segundos após o primeiro clique
    noInterrupts(); // Desabilita interrupções para evitar conflitos
    int count = buttonPressCount; // Salva a contagem atual
    buttonPressCount = 0; // Reinicia a contagem
    interrupts(); // Habilita interrupções novamente

    if (count == 1) {                     // foi pressionado 1 vez
      resete(); 
    } 
    else if (count == 2) {
      dormente(); 
    }
    else if (count == 3) {
      vigilia();
    }
    else if (count == 4) {
      alerta_1(); 
    }
    else if (count == 5) {
      alerta_2(); 
    }
    else if (count == 6) {
      suspeito();
    }
    else if (count == 7) {
      apagar();
    }
    else if (count == 8) {
      ler_n();
    }
    else if (count == 9) {
      ler_n_m();
    }
    else{
      code_erro();
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
