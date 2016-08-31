#include <SoftwareSerial.h>
#include <ShiftRegister74HC595.h>
#include <Motor595.h>
#include <HashMap.h>

SoftwareSerial mySerial(8, 9);

Motor595 sr (10,12,11);

const byte HASH_SIZE = 3;

HashType<char,int> hashRawArray[HASH_SIZE];
HashMap<char,int> hashMap = HashMap<char,int>(hashRawArray, HASH_SIZE);

String command;
int umaCasa = 640; // Passos para andar uma casa
int meiaCasa = 320; // Passos para andar meia casa
int numeroDeJogadas = 1;

int eletroIma = 9;
int pecas[3] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa};
int pecasX[4] = {umaCasa * 2,umaCasa, umaCasa * 4,umaCasa * 5};
int matriz [3][3]= {{0,0,0},{0,0,0},{0,0,0}};
int posTabuleiro[] = {meiaCasa, meiaCasa + umaCasa, meiaCasa + 2 * umaCasa};
int proximaX;
int proximaY;
char placeholder[2];


void setup() {
     Serial.begin(9600);
    mySerial.begin(9600);
    sr.setSpeed(35);
    hashMap[0]('A',0);
    hashMap[1]('B',1);
    hashMap[2]('C',2);
}

void loop() {
    if(mySerial.available())
    {

        while(mySerial.available()){
            delay(1);
            command += (char) mySerial.read();
        }

        Serial.println(command);
        
        if(command != "")
        {
           if(numeroDeJogadas % 2 == 1) // Jogada do jogador
           {
            command.toCharArray(placeholder, 1);
            jogadaJogador(hashMap.getValueOf(placeholder[0]), command.substring(2,3).toInt());
           } 
           numeroDeJogadas++;   
        }
        if(numeroDeJogadas % 2 == 0)
        {
          jogadaComputador();
          numeroDeJogadas++;   
        }
        command = "";
    }
}



void jogadaJogador(int posX, int posY)
{
  if(numeroDeJogadas < 6)
  {
   sr.step(pecasX[1],0,0);
   delay(50);
   sr.step(pecas[numeroDeJogadas / 2] , 1, 1);
   delay(50);
   digitalWrite(eletroIma,1);
   delay(1000);
   sr.step(pecasX[1],1,0);
   delay(50);
   if(pecas[posY - 1] < pecas[numeroDeJogadas / 2]) // objetivo menor do que atual
   {
      sr.step(pecas[numeroDeJogadas / 2] - posTabuleiro[posY - 1] - meiaCasa,0,1);
      delay(50);
      sr.step(posTabuleiro[posX],1,0);
      delay(50);
      sr.step(meiaCasa,0,1);
      delay(50); 
      digitalWrite(eletroIma,0);
      delay(1000);  
   }
   else if(pecas[posY - 1] == pecas[numeroDeJogadas / 2]) // objetivo igual ao atual
   {
    sr.step(meiaCasa,1,1);
    delay(50);
    sr.step(posTabuleiro[posX],1,0);
    delay(50); 
    sr.step(meiaCasa,0,1);
    delay(50); 
    digitalWrite(eletroIma,0);
      delay(1000);  
   }
   else  // objetivo maior do que atual
   {        
      sr.step(posTabuleiro[posY - 1]-pecas[numeroDeJogadas / 2] - meiaCasa,1,1);
      delay(50);
      sr.step(posTabuleiro[posX],1,0);
      delay(50);
      sr.step(meiaCasa,0,1);
      delay(50);   
      digitalWrite(eletroIma,0);
      delay(1000);  
   }
  }
  else if(numeroDeJogadas > 6)
  {
   sr.step(pecasX[0],0,0);
   delay(50);
   sr.step(pecas[numeroDeJogadas / 8] , 1, 1);
   delay(50);
   digitalWrite(eletroIma,1);
   delay(1000);
   sr.step(pecasX[0],1,0);
   delay(50);
   if(pecas[posY - 1] < pecas[numeroDeJogadas / 8]) // objetivo menor do que atual
   {
    sr.step(pecas[numeroDeJogadas / 2] - posTabuleiro[posY - 1] - meiaCasa,0,1);
    delay(50);
    sr.step(posTabuleiro[posX],1,0);
    delay(50);
    sr.step(meiaCasa,0,1);
    delay(50);   
    digitalWrite(eletroIma,0);
      delay(1000);  
   }
   else if(pecas[posY - 1] == pecas[numeroDeJogadas / 8]) // objetivo igual ao atual
   {
    sr.step(meiaCasa,1,1);
    delay(50);
    sr.step(posTabuleiro[posX],1,0);
    delay(50); 
    sr.step(meiaCasa,0,1);
    delay(50);     
    digitalWrite(eletroIma,0);
      delay(1000);  
   }
   else  // objetivo maior do que atual
   {
     sr.step(posTabuleiro[posY - 1]-pecas[numeroDeJogadas / 2] - meiaCasa,1,1);
     delay(50);
     sr.step(posTabuleiro[posX],1,0);
     delay(50);
     sr.step(meiaCasa,0,1);
     delay(50);    
     digitalWrite(eletroIma,0);
      delay(1000);   
   }
  }
 sr.step(posTabuleiro[posY - 1],0,1);
 delay(50);
 sr.step(posTabuleiro[posX],0,0);
 delay(50);
 numeroDeJogadas++;
 matriz[posY-1][posX] = 1;
}



void jogadaComputador()
{
  //feita a função de checar derrota, falta passos 3-8
}

void checarVitoria()
{
 for(int i = 0; i < 3; i++){
  int check = 0;
  for(int j = 0; j < 3; j++){
    if(matriz[i][j] == 2){
      check++;
    }
  }
  if(check == 2){
    for(int j = 0; j < 3; j++)
    {
      if(matriz[i][j] == 0)
      {
        proximaX = j;
        proximaY = i;
      }
    }
    return;
  }
 }

 for(int j = 0; j < 3; j++)
  {
    int check = 0;
    for(int i = 0; i < 3;i++)
    {
     if (matriz[i][j] == 2)
     {
     check++;  
     }
    }
   if(check == 2)
   {
    for(int i = 0; i < 3; i++)
    {
      if(matriz[i][j] == 0)
      {
        proximaX = j;
        proximaY = i;
      }
    }
    return;
   }
  }

  if(matriz[0][0] + matriz[1][1] + matriz[2][2] == 4)
   { 
    if(matriz[0][0] == 0)
    {
      proximaX = 0;
      proximaY = 0;
    }
    else if(matriz[1][1] == 0)
    {
      proximaX = 1;
      proximaY = 1;
    }
    else
    {
      proximaX = 2;
      proximaY = 2;
    }
    return;
   }
   if(matriz[0][2] + matriz[1][1] + matriz[2][0] == 4)
   { 
    if(matriz[0][2] == 0)
    {
      proximaX = 2;
      proximaY = 0;
    }
    else if(matriz[1][1] == 0)
    {
      proximaX = 1;
      proximaY = 1;
    }
    else
    {
      proximaX = 0;
      proximaY = 2;
    }
    return;
   }
}

void checarDerrota()
{

  for(int i = 0; i < 3; i++)
  {    
    int check = 0;
    for(int j = 0; j < 3;j++)
    {
     if (matriz[i][j] == 1)
     {
     check++;  
     }
    }
   if(check == 2)
   {
    for(int j = 0; j < 3; j++)
    {
      if(matriz[i][j] == 0)
      {
        proximaX = j;
        proximaY = i;
      }
    }
    return;
   }
  }
  for(int j = 0; j < 3; j++)
  {
    int check = 0;
    for(int i = 0; i < 3;i++)
    {
     if (matriz[i][j] == 1)
     {
     check++;  
     }
    }
   if(check == 2)
   {
    for(int i = 0; i < 3; i++)
    {
      if(matriz[i][j] == 0)
      {
        proximaX = j;
        proximaY = i;
      }
    }
    return;
   }
  }
  if(matriz[0][0] + matriz[1][1] + matriz[2][2] == 2)
   { 
    if(matriz[0][0] == 0)
    {
      proximaX = 0;
      proximaY = 0;
    }
    else if(matriz[1][1] == 0)
    {
      proximaX = 1;
      proximaY = 1;
    }
    else
    {
      proximaX = 2;
      proximaY = 2;
    }
    return;
   }
   if(matriz[0][2] + matriz[1][1] + matriz[2][0] == 2)
   { 
    if(matriz[0][2] == 0)
    {
      proximaX = 2;
      proximaY = 0;
    }
    else if(matriz[1][1] == 0)
    {
      proximaX = 1;
      proximaY = 1;
    }
    else
    {
      proximaX = 0;
      proximaY = 2;
    }
    return;
   }
}

void blockFork(){
  if(matriz[0][0] == 1 && (matriz[0][0] + matriz[1][1] + matriz[2][2] == 4)){
    proximaX = 0;
    proximaY = 1;

    return;
  }

  if(matriz[0][2] == 1 && (matriz[0][2] + matriz[1][1] + matriz[2][0] == 4)){
    proximaX = 2;
    proximaY = 1;

    return;
  }

  if((matriz[1][0] == 1 || matriz[2][1] == 1) && (matriz[1][0] + matriz[2][1] + matriz[1][1] == 4)){
    proximaX = 0;
    proximaY = 2;

    return;
  }

  if((matriz[1][2] == 1 || matriz[2][1] == 1) && (matriz[1][2] + matriz[2][1] + matriz[1][1] == 4)){
    proximaX = 2;
    proximaY = 2;

    return;
  }

  if((matriz[0][1] == 1 || matriz[1][2] == 1) && (matriz[0][1] + matriz[1][2] + matriz[1][1] == 4)){
    proximaX = 2;
    proximaY = 0;
    
    return;
  }

  if((matriz[0][1] == 1 || matriz[1][0] == 1) && (matriz[0][1] + matriz[1][0] + matriz[1][1] == 4)){
    proximaX = 0;
    proximaY = 0;
    
    return;
  }
}

// Falta passos 5-8

