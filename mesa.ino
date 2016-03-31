#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <HashMap.h>

SoftwareSerial mySerial(10, 11);

AF_Stepper MotorX (200,1);
AF_Stepper MotorY (200,2);

const byte HASH_SIZE = 8;

HashType<char,int> hashRawArray[HASH_SIZE];
HashMap<char,int> hashMap = HashMap<char,int>(hashRawArray, HASH_SIZE);

String command;
int umaCasa = 266; // Passos para andar uma casa
int meiaCasa = 133; // Passos para andar meia casa
int numeroDeJogadas = 0;
int posCemiterioY[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa, meiaCasa + 6 * umaCasa, meiaCasa + 7 * umaCasa};
int posCemiterioX[] = {-meiaCasa, meiaCasa + 8 * umaCasa};
int posTabuleiro[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa, meiaCasa + 6 * umaCasa, meiaCasa + 7 * umaCasa};

void setup(){
    Serial.begin(9600);
    mySerial.begin(9600);

    MotorX.setSpeed(10);
    MotorY.setSpeed(10);

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
    Levar eletroimã até a posiçãoInicial:
      MotorX.step(posTabuleiro[hashMap.getValueOf(posicaoInicial[0])], FORWARD, DOUBLE); MotorY.step(posTabuleiro[posicaoInicial[1] - 1], FORWARD, DOUBLE);
    Ligar eletroimã
    delay para ligar
    Levar peça até posiçãoFinal:
      if(posicaoFinal[0] > posicaoInicial[0]){
        MotorX.step(meiaCasa, FORWARD, DOUBLE);

        if(posicaoFinal[1] > posicaoInicial[1]){
           MotorY.step((posTabuleiro[posicaoFinal[1] - 1] - posTabuleiro[posicaoInicial[1] - 1] - meiaCasa), FORWARD, DOUBLE);
        }
        else if(posicaoFinal[1] < posicaoInicial[1]){
          MotorY.step(-(posTabuleiro[posicaoFinal[1] - 1] - posTabuleiro[posicaoInicial[1] - 1] - meiaCasa), BACKWARD, DOUBLE);
        }

        else{
          MotorY.step(meiaCasa, BACKWARD, DOUBLE);
        }

        MotorX.step(posTabuleiro[hashMap.getValueOf(posicaoFinal[0])] - posTabuleiro[hashMap.getValueOf(posicaoInicial[0])] - meiaCasa, FORWARD, DOUBLE);
        MotorY.step(meiaCasa, FORWARD, DOUBLE);
      }

      else if(posicaoFinal[0] < posicaoInicial[0]){

      }

      else{

      }
    Desligar eletroimã
    Delay devido ao efeito do campo
    Retornar eletroimã para a origem (0, 0)
    incrementar a variável de número de jogadas
    */
}

void atacarPeca(string posicaoInicial, string posicaoFinal){
    /*
    Eletroimã esta na origem (0, 0)
    Levar eletroimã até a posicaoFinal
    Ligar Eletroimã
    delay para ligar
    Conferir de qual jogador é a vez
    Conferir o numero de peças que ja matou
    Levar a peça morta do adversário até o cemitério do jogador atual, na posição certa
    Desligar Eletroimã
    Voltar para a origem (0, 0)
    incrementar variável do numero de peças ja mortas do adversário pelo jogador atual
    Levar o eletroimã até a posicaoInicial
    Ligar o eletroimã
    delayt para ligar
    Levar a peça até a posicaoFinal
    Desligar o Eletroimã
    delay para desligar
    Voltar até a origem (0, 0)
    incrementar a variável de número de jogadas
    */
}
