#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial mySerial(10, 11);

AF_Stepper MotorX (200,1);
AF_Stepper MotorY (200,2);


int umaCasa = 266;
int meiaCasa = 133;
int posX[7] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa, meiaCasa + 6 * umaCasa};
int posY[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa, meiaCasa + 3 * umaCasa, meiaCasa + 4 * umaCasa, meiaCasa + 5 * umaCasa};
int posYpecas [] = {umaCasa,  2 * umaCasa, 3 * umaCasa, 7 * umaCasa,  8 * umaCasa,  9 * umaCasa};
int jogadas = 1;
int colunasArr[] ={0,0,0,0,0,0,0};
String command;
int eletroIma = 9;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(eletroIma, OUTPUT);
  MotorX.setSpeed(10);
  MotorY.setSpeed(10);
}

void loop() {
  
  if(mySerial.available()){

        while(mySerial.available()){
            delay(1);
            command += (char) mySerial.read();
        }

        Serial.println(command);

        /*
        Frase: "*[coluna]#"
        Possibilidades: "um", "dois", "C", "D", "E", "F", "G"
        */

        if(command.substring(1, 3) == "um" || command.substring(1, 2) == "1"){ 
            jogada(1);
            
        }

        else if(command.substring(1, 5) == "dois" || command.substring(1, 2) == "2"){
            jogada(2);
        }

        else if(command.substring(1, 5) == "tres" || command.substring(1, 5) == "três" || command.substring(1, 2) == "3"){
            jogada(3);
        }

        else if(command.substring(1, 7) == "quatro" || command.substring(1, 2) == "4"){
            jogada(4);
        }

        else if(command.substring(1, 6) == "cinco" || command.substring(1, 2) == "5"){
            jogada(5);
        }

        else if(command.substring(1, 5) == "seis" || command.substring(1, 2) == "6"){
            jogada(6);
        }

        else if(command.substring(1, 5) == "sete" || command.substring(1, 2) == "7"){
            jogada(7);
        }

        else {
            // Acende LED vermelho
        }

        command = "";
  }
}

void jogada(int coluna){
  if(jogadas % 2 == 1) //Jogador 1
  {
    if (jogadas < 14) //pegar na primeira coluna
    {
      MotorY.step(posYpecas[3],FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[(jogadas/2) +1],FORWARD, DOUBLE);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa,BACKWARD,DOUBLE);
      delay(50);
     if(coluna < posX[(jogadas/2) +1]) //vai para tras
     {
       MotorX.step(posX[(jogadas/2) +1] - posX[coluna],BACKWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);    
     } 
     else if(coluna == posX[(jogadas/2) +1]) // so desce
     {
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);        
     }
     else // vai para frente 
     {
       MotorX.step(posX[coluna] - posX[(jogadas/2) +1],FORWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
       
     }

    }
    
    else if(jogadas < 28 && jogadas > 14) //pegar na segunda coluna
    {
      MotorY.step(posYpecas[4],FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[((jogadas - 15)/2) +1],FORWARD, DOUBLE
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa * 2,BACKWARD,DOUBLE);
      delay(50);
     if(coluna < posX[((jogadas-15)/2) +1]) //vai para tras
     {
       MotorX.step(posX[((jogadas-15)/2) +1] - posX[coluna],BACKWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    
     } 
     else if(coluna == posX[((jogadas-15)/2) +1]) // so desce
     {
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);
      }
     else // vai para frente 
     {
       MotorX.step(posX[coluna] - posX[((jogadas-15)/2) +1],FORWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);            
    }
    else //terceira coluna
    {
      MotorY.step(posYpecas[5],FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[((jogadas - 29)/2) +1],FORWARD, DOUBLE
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa * 3,BACKWARD,DOUBLE);
      delay(50);
     if(coluna < posX[((jogadas-29)/2) +1]) //vai para tras
     {
       MotorX.step(posX[((jogadas-29)/2) +1] - posX[coluna],BACKWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    
     } 
     else if(coluna == posX[((jogadas-29)/2) +1]) // so desce
     {
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
     }
     else // vai para frente 
     {
       MotorX.step(posX[coluna] - posX[((jogadas-29)/2) +1],FORWARD, DOUBLE);
       delay(50);
       MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiCasa,BACKWARD, DOUBLE);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    }
   
     MotorY.step(posY[colunasArr[coluna - 1]],BACKWARD, DOUBLE);
     delay(50);
     MotorX.step(posX[coluna - 1], BACKWARD, DOUBLE);
     delay(50);     
     colunasArr[coluna-1]++;  
}
  else //Jogador 2
  {
    if (jogadas < 15) //pegar na primeira coluna
    {        
      MotorY.step(posYpecas[0],BACKWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[jogadas/2],FORWARD, DOUBLE);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa,FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[jogadas/2],BACKWARD,DOUBLE);
      delay(50);
      MotorY.step(umaCasa * 6,FORWARD, DOUBLE);
      delay(50);
      MotorX.step(posX[coluna - 1],FORWARD, DOUBLE);
      delay(50);
      MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
      delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);      
    }
    
    else if(jogadas < 29 && jogadas > 15) //pegar na segunda coluna
    {
       MotorY.step(posYpecas[1],BACKWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[(jogadas - 16)/2],FORWARD, DOUBLE);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa * 2,FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[(jogadas - 16)/2],BACKWARD,DOUBLE);
      delay(50);
      MotorY.step(umaCasa * 6,FORWARD, DOUBLE);
      delay(50);
      MotorX.step(posX[coluna - 1],FORWARD, DOUBLE);
      delay(50);
      MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
      delay(50); 
      digitalWrite(eletroIma,1);
      delay(1000);      
    }
    else //terceira coluna
    {
      MotorY.step(posYpecas[2],BACKWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[(jogadas - 30)/2],FORWARD, DOUBLE);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      MotorY.step(umaCasa * 3,FORWARD,DOUBLE);
      delay(50);
      MotorX.step(posX[(jogadas - 30)/2],BACKWARD,DOUBLE);
      delay(50);
      MotorY.step(umaCasa * 6,FORWARD, DOUBLE);
      delay(50);
      MotorX.step(posX[coluna - 1],FORWARD, DOUBLE);
      delay(50);
      MotorY.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,BACKWARD, DOUBLE);
      delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);
    }
     MotorY.step(posY[colunasArr[coluna - 1]],BACKWARD, DOUBLE);
     delay(50);
     MotorX.step(posX[coluna - 1], BACKWARD, DOUBLE);
     delay(50);     
     colunasArr[coluna-1]++;  
  }
}



