#include <WiFi.h>       
#include <HTTPClient.h> 

// Configurações da rede WiFi à se conectar
const char* ssid = "SSI";
const char* password = "PASSWORD";

// URL do site para fazer a requisição GET
const char* url = "http://sitepythonyoutube.herokuapp.com/";

//Função que filtra apenas o conteúdo da mensagem
String getResponseBody(const String& response);

//Função que remove todas as tags <p>, </p> e tabulação
String removeTagsAndTabs(const String& inputString);

void setup() {
  Serial.begin(115200);

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede WiFi...");
  }
  Serial.println("Conectado à rede WiFi!");
}

void loop() {
  // Criar um objeto HTTPClient
  HTTPClient http;

  // Enviar a requisição GET
  http.begin(url);
  int httpCode = http.GET();

  // Verificar o código de resposta
  if (httpCode > 0) {
    // Ler o conteúdo da resposta
    String response = http.getString();
    Serial.println("Conteúdo da resposta:");

    //Funçoes que filtram o corpo e removem as tags
    String responseBody = getResponseBody(response); 
    String output = removeTagsAndTabs(responseBody);
    
    Serial.println(output);
    
  } else {
    Serial.println("Falha na requisição GET!");
  }

  // Liberar os recursos da requisição
  http.end();

  // Aguardar por um intervalo antes de fazer a próxima requisição
  delay(5000);
}

String getResponseBody(const String& response) {
  int bodyIndex = response.indexOf("<body>");
  if (bodyIndex != -1) {
    return response.substring(bodyIndex + 6, response.length() - 15); //Pega o conteudo depois do "<body>" e remove os 15 ultimos caracteres que são "</body> </html>" 
  }
  return "";
}

String removeTagsAndTabs(const String& inputString) {
  String resultString = inputString;
  
  // Remove as tags <p> e </p>
  resultString.replace("<p>", "");
  resultString.replace("</p>", "");
  
  // Remove tabulações
  resultString.replace("    ", ""); //São 4 espaços
  
  return resultString;
}
