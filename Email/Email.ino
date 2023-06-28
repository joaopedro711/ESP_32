#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Base64.h>

// Configurações de rede
const char* ssid = "SSID";
const char* password = "Senha";

// Configurações do servidor SMTP2GO
const char* server = "mail.smtp2go.com";
const int port = 465;

// Configurações da conta de e-mail do servidor smtp2go
const char* email = "e-mail da conta";
const char* email_password = "senha da conta";

// E-mail de envio(conforme configurado no smtp2go) e recepção(qualquer e-mail)
const char* email_from = "e-mail_from";
const char* email_to = "e-mail_to";

// Função para esperar a resposta do servidor SMTP com delays adequados
void waitForResponse(WiFiClientSecure& client) {
  while (!client.available()) {
    delay(100);
  }
  while (client.available()) {
    String response = client.readStringUntil('\n');
    Serial.println(response);
  }
}

void setup() {
  Serial.begin(115200);

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede WiFi...");
  }
  Serial.println("Conectado à rede WiFi!");

  // Inicializar a conexão segura com o servidor SMTP
  WiFiClientSecure client;
  client.setInsecure(); // Usar essa opção somente se o servidor SMTP não tiver certificado SSL válido

  if (!client.connect(server, port)) {
    Serial.println("Falha na conexão com o servidor SMTP!");
    return;
  }
  Serial.println("Conectado ao servidor SMTP!");

  // Esperar a resposta do servidor SMTP
  waitForResponse(client);

  // Enviar comandos SMTP para enviar o e-mail
  client.println("EHLO 192.168.1.123");
  waitForResponse(client);

  client.println("AUTH LOGIN");
  waitForResponse(client);

  client.println(base64::encode(email));
  waitForResponse(client);

  client.println(base64::encode(email_password));
  waitForResponse(client);

  client.println("MAIL FROM:<" + String(email_from) + ">");
  waitForResponse(client);

  client.println("RCPT TO:<" + String(email_to) + ">");
  waitForResponse(client);

  client.println("DATA");
  waitForResponse(client);

  client.println("Subject: Teste de e-mail ESP32");
  client.println("From: <" + String(email_from) + ">");
  client.println("To: <" + String(email_to) + ">");
  client.println("Content-Type: text/plain");
  client.println("Ai zé da manga\n\rQue isso meu filho calme.");
  client.println(".");
  waitForResponse(client);

  client.println("QUIT");
  waitForResponse(client);

  // Fechar a conexão com o servidor SMTP
  client.stop();
  Serial.println("\nE-MAIL ENVIADO\n");
  Serial.println("Desconectado do servidor SMTP");
}

void loop() {
  // Nada a fazer no loop principal
}
