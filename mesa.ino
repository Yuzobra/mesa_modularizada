#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial mySerial(10, 11);

AF_Stepper MotorX (200,1);
AF_Stepper MotorY (200,2);

String command;

void setup(){
    Serial.begin(9600);
    mySerial.begin(9600);

    MotorX.setSpeed(10);
    MotorY.setSpeed(10);
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

        if(command.substring(4) == "a"){ // Jogada de ataque
            // Chamar função de ataque
            atacarPeca(command.substring(1, 3), command.substring(11, 13));

        }

        else if(command.substring(4) == "p"){ // Jogada de movimento (para)
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
    Ligar eletroimã
    Levar peça até posiçãoFinal
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
    Conferir de qual jogador é a vez
    Conferir o numero de peças que ja matou
    Levar a peça morta do adversário até o cemitério do jogador atual, na posição certa
    incrementar variável do numero de peças ja mortas do adversário pelo jogador atual
    Desligar Eletroimã
    Voltar para a origem (0, 0)
    Levar o eletroimã até a posicaoInicial
    Ligar o eletroimã
    Levar a peça até a posicaoFinal
    Desligar o Eletroimã
    Voltar até a origem (0, 0)
    incrementar a variável de número de jogadas
    */
}
