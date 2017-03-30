#ifndef Motor595_h
#define Motor595_h
#include "Arduino.h"


class Motor595
{
public:
	Motor595(int pinDados, int pinClock, int pinLatch); //verificar se declaração de nome no código é entre aspas duplas
	void setSpeed(int velocidade);
	void step(int distancia, int direcao, int motor); // Se direcao for 1, FORWARD, se for 0, BACKWARD :: Se motor for 0, X; se for 1, Y 
private:
	int _tempo;
	int _pinDados, _pinClock, _pinLatch;
};

#endif
