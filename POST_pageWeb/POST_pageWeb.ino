#include <WiFi.h>
#include <HTTPClient.h>

// Configurações da rede WiFi à se conectar
const char* ssid = "sua_rede";
const char* password = "sua_senha";

const char* serverURL = "..................";  // URL do servidor para enviar a requisição POST

int buttonPin = 0;  // Pino GPIO0 interno do ESP32

void setup() {
  Serial.begin(115200);

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...");
  }

  Serial.println("Conexão Wi-Fi estabelecida!");

  pinMode(buttonPin, INPUT_PULLUP);  // Configura o pino do botão como entrada com pull-up interno
}

void loop() {
  // Verifica se o botão GPIO0 foi pressionado
  if (digitalRead(buttonPin) == LOW) {
    
    String body = "Oi zé da manga";
    
    Serial.println("Botão pressionado!");

    // Cria o objeto HTTPClient
    HTTPClient http;

    // Monta a mensagem a ser enviada no corpo da requisição POST
    String menssagem = "<p>";
    menssagem += body;
    menssagem += "</p>";

    // Envia a requisição POST
    http.begin(serverURL);
    http.addHeader("Content-Type", "text/html");
    int httpResponseCode = http.POST(menssagem);

    // Verifica a resposta do servidor
    if (httpResponseCode > 0) {
      Serial.print("Resposta do servidor: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.println("Falha na requisição POST");
    }

    // Libera os recursos do objeto HTTPClient
    http.end();

    // Aguarda um tempo antes de enviar uma nova requisição
    delay(1000);
  }
}
