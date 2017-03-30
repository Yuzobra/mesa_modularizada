#include "Arduino.h"
#include "Motor595.h"
#include "ShiftRegister74HC595.h"


Motor595::Motor595(int pinDados, int pinClock, int pinLatch)
{
	_pinDados = pinDados;
	_pinClock = pinClock;
	_pinLatch = pinLatch;
	
}

void Motor595::setSpeed(int velocidade)
{
	_tempo = velocidade / 4;
}

void Motor595::step(int distancia, int direcao, int motor)
{
	ShiftRegister74HC595 sr(1, _pinDados, _pinClock, _pinLatch);

	if(motor == 0)
	{
	sr.setAllLow();
	if(direcao == 1)
	{
		for(int i = 0; i < distancia / 4; i++)
		{
			sr.set(0, HIGH);
			delay(_tempo);
			sr.set(3, LOW);
			sr.set(1, HIGH);
			delay(_tempo);
			sr.set(0, LOW);
			sr.set(2, HIGH);
			delay(_tempo);
			sr.set(1, LOW);
			sr.set(3, HIGH);
			delay(_tempo);
			sr.set(2, LOW);
		}
	}
	else if(direcao == 0)
	{
		for(int i = 0; i < distancia / 4; i++)
		{
			sr.set(3,HIGH);
			delay(_tempo);
			sr.set(0,LOW);
			sr.set(2,HIGH);
			delay(_tempo);
			sr.set(3,LOW);
			sr.set(1,HIGH);
			delay(_tempo);
			sr.set(2,LOW);
			sr.set(0,HIGH);
			delay(_tempo);
			sr.set(1,LOW);
		}
	} 
	sr.setAllLow();
	}
	else if(motor == 1)
	{
		sr.setAllLow();
		if(direcao == 1)
		{
		for(int i = 0; i < distancia / 4; i++)
		{
			sr.set(4, HIGH);
			delay(_tempo);
			sr.set(7, LOW);
			sr.set(5, HIGH);
			delay(_tempo);
			sr.set(4, LOW);
			sr.set(6, HIGH);
			delay(_tempo);
			sr.set(5, LOW);
			sr.set(7, HIGH);
			delay(_tempo);
			sr.set(6, LOW);
		}
	}
	else if(direcao == 0)
	{
		for(int i = 0; i < distancia / 4; i++)
		{

			sr.set(7,HIGH);
			delay(_tempo);
			sr.set(4,LOW);
			sr.set(6,HIGH);
			delay(_tempo);
			sr.set(7,LOW);
			sr.set(5,HIGH);
			delay(_tempo);
			sr.set(6,LOW);
			sr.set(4,HIGH);
			delay(_tempo);
			sr.set(5,LOW);
		}
	} 
	sr.setAllLow();
	}
}
