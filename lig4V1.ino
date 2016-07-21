#include <SoftwareSerial.h>
#include <ShiftRegister74HC595.h>
#include <Motor595.h>

SoftwareSerial mySerial(7, 8);

Motor595 sr (10, 12, 11);

int umaCasa = 320;
int meiaCasa = 160;
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
  sr.setSpeed(35);
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
      sr.step(posYpecas[3],1,1);
      delay(50);
      sr.step(posX[(jogadas/2) +1],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa,0,1);
      delay(50);
     if(coluna < posX[(jogadas/2) +1]) //vai para tras
     {
       sr.step(posX[(jogadas/2) +1] - posX[coluna],0, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);    
     } 
     else if(coluna == posX[(jogadas/2) +1]) // so desce
     {
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);        
     }
     else // vai para frente 
     {
       sr.step(posX[coluna] - posX[(jogadas/2) +1],1, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
       
     }

    }
    
    else if(jogadas < 28 && jogadas > 14) //pegar na segunda coluna
    {
      sr.step(posYpecas[4],1,1);
      delay(50);
      sr.step(posX[((jogadas - 15)/2) +1],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa * 2,0,1);
      delay(50);
     if(coluna < posX[((jogadas-15)/2) +1]) //vai para tras
     {
       sr.step(posX[((jogadas-15)/2) +1] - posX[coluna],0, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    
     } 
     else if(coluna == posX[((jogadas-15)/2) +1]) // so desce
     {
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);
      }
     else // vai para frente 
     {
       sr.step(posX[coluna] - posX[((jogadas-15)/2) +1],1, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);            
    }
    else //terceira coluna
    {
      sr.step(posYpecas[5],1,1);
      delay(50);
      sr.step(posX[((jogadas - 29)/2) +1],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa * 3,0,1);
      delay(50);
     if(coluna < posX[((jogadas-29)/2) +1]) //vai para tras
     {
       sr.step(posX[((jogadas-29)/2) +1] - posX[coluna],0, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    
     } 
     else if(coluna == posX[((jogadas-29)/2) +1]) // so desce
     {
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
     }
     else // vai para frente 
     {
       sr.step(posX[coluna] - posX[((jogadas-29)/2) +1],1, 0);
       delay(50);
       sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
       delay(50); 
       digitalWrite(eletroIma,0);
       delay(1000);
    }
   
     sr.step(posY[colunasArr[coluna - 1]],0, 1);
     delay(50);
     sr.step(posX[coluna - 1], 0, 0);
     delay(50);     
     colunasArr[coluna-1]++;  
}
  else //Jogador 2
  {
    if (jogadas < 15) //pegar na primeira coluna
    {        
      sr.step(posYpecas[0],0,1);
      delay(50);
      sr.step(posX[jogadas/2],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa,1,1);
      delay(50);
      sr.step(posX[jogadas/2],0,0);
      delay(50);
      sr.step(umaCasa * 6,1, 1);
      delay(50);
      sr.step(posX[coluna - 1],1, 0);
      delay(50);
      sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
      delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);      
    }
    
    else if(jogadas < 29 && jogadas > 15) //pegar na segunda coluna
    {
       sr.step(posYpecas[1],0,1);
      delay(50);
      sr.step(posX[(jogadas - 16)/2],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa * 2,1,1);
      delay(50);
      sr.step(posX[(jogadas - 16)/2],0,0);
      delay(50);
      sr.step(umaCasa * 6,1, 1);
      delay(50);
      sr.step(posX[coluna - 1],1, 0);
      delay(50);
      sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
      delay(50); 
      digitalWrite(eletroIma,1);
      delay(1000);      
    }
    else //terceira coluna
    {
      sr.step(posYpecas[2],0,1);
      delay(50);
      sr.step(posX[(jogadas - 30)/2],1, 0);
      delay(50);
      digitalWrite(eletroIma,1);
      delay(1000);
      sr.step(umaCasa * 3,1,1);
      delay(50);
      sr.step(posX[(jogadas - 30)/2],0,0);
      delay(50);
      sr.step(umaCasa * 6,1, 1);
      delay(50);
      sr.step(posX[coluna - 1],1, 0);
      delay(50);
      sr.step(posY[5] - posY[colunasArr[coluna-1]] + meiaCasa,0, 1);
      delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);
    }
     sr.step(posY[colunasArr[coluna - 1]],0, 1);
     delay(50);
     sr.step(posX[coluna - 1], 0, 0);
     delay(50);     
     colunasArr[coluna-1]++;  
  }
  jogadas++;
}
