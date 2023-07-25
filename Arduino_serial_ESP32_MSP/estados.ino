void resete() {               //1
  String comando = "#RST#";
  enviar_comando(comando);
}

void dormente() {               //2
  String comando = "#DMT#";
  enviar_comando(comando);
}

void vigilia() {               //3
  String comando = "#VIG#";
  enviar_comando(comando);
}

void alerta_1() {               //4
  String comando = "#ALT1#";
  enviar_comando(comando);
}

void alerta_2() {               //5
  String comando = "#ALT2#";
  enviar_comando(comando);
}

void suspeito() {               //6
  String comando = "#SPT#";
  enviar_comando(comando);
}

void apagar() {               //7
  String comando = "#APG#";
  enviar_comando(comando);
}

void ler_n() {               //8
  String comando = "#RD n#";
  enviar_comando(comando);
}

//recebe dois argumentos, entre quais posição da memoria deve ler (n-m)
//Preciso pensar, se realmente vai receber dois argumentos
void ler_n_m() {               //9
  String comando = "#RD n m#";
  enviar_comando(comando);
}

void code_erro() {               //10
  String comando = "ERROR";
  enviar_comando(comando);
}
