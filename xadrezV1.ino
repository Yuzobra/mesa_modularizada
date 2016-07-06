#include <SoftwareSerial.h>
#include <ShiftRegister74HC595.h>
#include <Motor595.h>
#include <HashMap.h>

SoftwareSerial mySerial(10, 11);

Motor595 sr (10,12,11);

const byte HASH_SIZE = 8;

HashType<char,int> hashRawArray[HASH_SIZE];
HashMap<char,int> hashMap = HashMap<char,int>(hashRawArray, HASH_SIZE);

String command;
int umaCasa = 320; // Passos para andar uma casa
int meiaCasa = 160; // Passos para andar meia casa
int numeroDeJogadas = 0;
int posCemiterioY[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa, meiaCasa + 6 * umaCasa, meiaCasa + 7 * umaCasa};
int posCemiterioX[] = {-meiaCasa, meiaCasa + 8 * umaCasa, -meiaCasa -umaCasa, meiaCasa + 9 * umaCasa};  
int posTabuleiro[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa, meiaCasa + 6 * umaCasa, meiaCasa + 7 * umaCasa};
int cemiterioJ1 = 0;
int cemiterioJ2 = 0;
int eletroIma = 9;

void setup(){
    Serial.begin(9600);
    mySerial.begin(9600);

    sr.setSpeed(35);
    
    hashMap[0]("A",0);
    hashMap[1]("B",1);
    hashMap[2]("C",2);
    hashMap[3]("D",3);
    hashMap[4]("E",4);
    hashMap[5]("F",5);
    hashMap[6]("G",6);
    hashMap[7]("H",7);
    
    // Serial.println(hashMap.getValueOf("A")) retornaria 0
}

void loop(){

    if(mySerial.available()){

        while(mySerial.available()){
            delay(1);
            command += (char) mySerial.read();
        }

        Serial.println(command);

        /*
        Frase: "*posiçãoinicial tipodejogada posiçãofinal#"
        Posição inicial: tamanho 2
        Posição final: tamanho 2
        Tipo de jogada pode ser "atacar" ou "para"
        */

        if(command.substring(4, 5) == "a" || command.substring(4, 5) == "A"){ // Jogada de ataque
            // Chamar função de ataque
            atacarPeca(command.substring(1, 3), command.substring(11, 13));

        }

        else if(command.substring(4, 5) == "p" || command.substring(4, 5) == "P"){ // Jogada de movimento (para)
            // Chamar função de movimento
            moverPeca(command.substring(1, 3), command.substring(9, 11));
        }

        else {
            // Movimento hockey
        }

        command = "";
    }
}

void moverPeca(string posicaoInicial, string posicaoFinal){
    /*
    Eletroimã esta na origem (0, 0)
    Levar eletroimã até a posiçãoInicial
    sr.step(posTabuleiro[hashMap.getValueOf(posicaoInicial[0])], 1, 0);
    delay(50);
    sr.step(posTabuleiro[posicaoInicial[1] - 1], 1, 1);
    delay(50);
    Ligar eletroimã
    digitalWrite(eletroIma, HIGH);
    delay para ligar
    delay(500);
    Levar peça até posiçãoFinal
    if(posicaoFinal[0] > posicaoInicial[0]){
    
      if(posicaoFinal[1] > posicaoInicial[1]){
        sr.step(meiaCasa, 1, 0);
        delay(50);
         sr.step((posTabuleiro[posicaoFinal[1] - 1] - posTabuleiro[posicaoInicial[1] - 1] - meiaCasa), 1, 1);
         delay(50);
         sr.step((posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posTabuleiro[hashMap.getValueOf(posicaoInicial[0]) - meiaCasa), 1, 0);
         delay(50);
         sr.step(meiaCasa, 1, 1);
         delay(50);
      }
      else if(posicaoFinal[1] < posicaoInicial[1]){
        sr.step(meiaCasa, 1, 0);
        delay(50);
        sr.step((posTabuleiro[posicaoInicial[1] - 1] - posTabuleiro[posicaoFinal[1] - 1] - meiaCasa), 0, 1);
        delay(50);
        sr.step((posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posTabuleiro[posicaoInicial[hashMap.getValueOf(posicaoInicial[0]) - meiaCasa), 1, 0);
        delay(50);
        sr.step(meiaCasa, 0, 1);
        delay(50);
      }
      else{
        sr.step(meiaCasa, 1, 1);
        delay(50);
        sr.step((posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posTabuleiro[hashMap.getValueOf(posicaoInicial[0])), 1, 0);
        delay(50);
        sr.step(meiaCasa, 0, 1);
        delay(50);
      }
      
    }
    
    else if(posicaoFinal[0] < posicaoInicial[0]){
           
      if(posicaoFinal[1] > posicaoInicial[1]){
        sr.step(meiaCasa, 0, 0);
        delay(50);
        sr.step(posTabuleiro[posicaoFinal[1] - 1] - posTabuleiro[posicaoInicial[1] - 1] - meiaCasa), 1, 1);
        delay(50);
        sr.step((posTabuleiro[hashMap.getValueOf(posicaoInicial[0]) - posTabuleiro[posicaoInicial[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa), 0, 0);
        delay(50);
        sr.step(meiaCasa, 1, 1);
        delay(50);
      }
      else if(posicaoFinal[1] < posicaoInicial[1]){
       sr.step(meiaCasa, 0, 0);
       delay(50);
       sr.step((posTabuleiro[posicaoInicial[1] - 1] - posTabuleiro[posicaoFinal[1] - 1] - meiaCasa), 0, 1);
       delay(50);
       sr.step(posTabuleiro[hashMap.getValueOf(posicaoInicial[0]) - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa), 0, 0);
       delay(50);
       sr.step(meiaCasa, 0, 1);
       delay(50);
      }
      else{
        sr.step(meiaCasa,1, 1);
        delay(50);
        sr.step((posTabuleiro[hashMap.getValueOf(posicaoInicial[0]) - posTabuleiro[hashMap.getValueOf(posicaoFinal[0])), 0, 0);
        delay(50);
        sr.step(meiaCasa, 0, 1);
        delay(50);
       }
    }
    
    else{
      if(posicaoFinal[1] > posicaoInicial[1]){
        sr.step(meiaCasa, 1, 0);
        delay(50);
        sr.step(posTabuleiro[posicaoFinal[1] - 1] - posTabuleiro[posicaoInicial[1] - 1]), 1, 1);
        delay(50);
        sr.step(meiaCasa, 0, 0);
        delay(50);
      }
      else if(posicaoFinal[1] < posicaoInicial[1]){
       sr.step(meiaCasa, 1, 0);
       delay(50);
       sr.step((posTabuleiro[posicaoInicial[1] - 1] - posTabuleiro[posicaoFinal[1] - 1]), 0, 1);
       delay(50);
       sr.step(meiaCasa, 0, 0);
       delay(50);
     }
   }
    Desligar eletroimã
    digitalWrite(eletroIma, LOW);
    delay(500);
    Delay devido ao efeito do campo
    Retornar eletroimã para a origem (0, 0)
    sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]), 0, 0);
    delay(50);
    sr.step(posTabuleiro[posicaoFinal[1] - 1], 0, 1);
    delay(50);
    incrementar a variável de número de jogadas
    numeroDeJogadas++;
    */
}

void atacarPeca(string posicaoInicial, string posicaoFinal){
    /*
    Eletroimã esta na origem (0, 0)
    Levar eletroimã até a posicaoFinal
     sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]), 1, 0);
     delay(50);
     sr.step(posTabuleiro[posicaoFinal[1] - 1], 1, 1);
     delay(50);
    Ligar Eletroimã
    digitalWite(eletroIma, HIGH);
    delay para ligar
    delay(500);
    Conferir de qual jogador é a vez 
    Conferir o numero de peças que ja matou
    Levar a peça morta do adversário até o cemitério do jogador atual, na posição certa
    if(numeroDeJogadas % 2 == 1)
    {
      if(posCemiterioY[cemiterioJ2] > posTabuleiro[posicaoFinal[1] - 1])
      {
        sr.step(meiaCasa, 1, 1);
        delay(50);
        if(cemiterioJ2 > 8){
          sr.step(posCemiterioX[3] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa, 1, 0);
        } else {
          sr.step(posCemiterioX[1] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa, 1, 0);
        }
        delay(50);
        sr.step(posCemiterioY[cemiterioJ2] - posicaoFinal[1], 1, 1);
        delay(50);
        sr.step(meiaCasa, 1, 0);
        delay(50);
      }
      if (posCemiterioY[cemiterioJ2] < posTabuleiro[posicaoFinal[1] - 1]
      {
        sr.step(meiaCasa, 0, 1);
        delay(50);
        if(cemiterioJ2 > 8){
          sr.step(posCemiterioX[3] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa, 1, 0);
        } else {
          sr.step(posCemiterioX[1] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - meiaCasa, 1, 0);
        }    
        delay(50);
        sr.step(posicaoFinal[1] - posCemiterioY[cemiterioJ2] - meiaCasa, 0, 1);
        delay(50);
        sr.step(meiaCasa, 1, 0);
        delay(50);
      }
       if (posCemiterioY[cemiterioJ2]  ==  posTabuleiro[posicaoFinal[1] - 1]
      {
        sr.step(meiaCasa, 1, 1);
        delay(50);
        if(cemiterioJ2 > 8){
          sr.step(posCemiterioX[3] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]), 1, 0);
        } else {
          sr.step(posCemiterioX[1] - posTabuleiro[hashMap.getValueOf(posicaoFinal[0]), 1, 0);
        }
        delay(50);
        sr.step(meiaCasa, 0, 1);
        delay(50);
      }
      cemiterioJ2++;
      Desligar Eletroimã
      digitalWrite(eletroIma, LOW);    
      delay(500);
      Voltar para a origem (0, 0)  
      sr.step(cemiterioJ2, 0, 1);
      delay(50);
      if(cemiterioJ2 > 8){
        sr.step(posCemiterioX[3], 0, 0);
      } else {
        sr.step(posCemiterioX[1], 0, 0);
      }
      delay(50);
    }
    else if (numeroDeJogadas % 2 == 0)
    {
      if(posCemiterioY[cemiterioJ1] > posTabuleiro[posicaoFinal[1] - 1])
      {
        sr.step(meiaCasa, 1, 1);
        delay(50);
        if(cemiterioJ1 > 8){
          sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[2] - meiaCasa, 0, 0);
        } else {
           sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[0] - meiaCasa, 0, 0);
        }
        delay(50);
        sr.step(posCemiterioY[cemiterioJ1] - posTabuleiro[posicaoFinal[1] - 1] - meiaCasa, 1, 1);
        delay(50);
        sr.step(meiaCasa, 0, 0);
        delay(50);
      }
      if (posCemiterioY[cemiterioJ2] < posTabuleiro[posicaoFinal[1] - 1]
      {
        sr.step(meiaCasa, 0, 1);
        delay(50);
        if (cemiterioJ1 > 8){
           sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[2] - meiaCasa, 0, 0);
        } else {
           sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[0] - meiaCasa, 0, 0);
        }
        delay(50);
        sr.step(posTabuleiro[posicaoFinal[1] - 1] - posCemiterioY[cemiterioJ2] - meiaCasa, 0, 1);
        delay(50);
        sr.step(meiaCasa, 0,, 0);
        delay(50);
      }
       if (posCemiterioY[cemiterioJ2]  ==  posTabuleiro[posicaoFinal[1] - 1]
      {
        sr.step(meiaCasa, 1, 1);
        delay(50);
        if (cemiterioJ1 > 8){
           sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[2] - meiaCasa, 0, 0);
        } else {
           sr.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0]) - posCemiterioX[0] - meiaCasa, 0, 0);
        }
        delay(50);
        sr.step(meiaCasa, 0, 1);
        delay(50);
      }
      cemiterioJ1++;
      Desligar Eletroimã
      digitalWrite(eletroIma, LOW);
      delay(500);
      Voltar para a origem (0, 0)
      sr.step(cemiterioJ1, 0, 1);
      delay(50);
      if(cemiterioJ1 > 8){
        sr.step(posCemiterioX[2], 1, 0);
      } else {
        sr.step(posCemiterioX[0], 1, 0);
      }
      delay(50);
    }
    
    moverPeca(posicaoInicial, posicaoFinal);
    */
}
