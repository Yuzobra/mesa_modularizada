#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
String command;
int led1 = 13;
int led2 = 12;

void setup(){
    Serial.begin(9600);
    mySerial.begin(9600);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop(){

    if(mySerial.available()){

        while(mySerial.available()){
            delay(1);
            command += (char)mySerial.read();
        }

        Serial.println(command);

        if(command == "*Ligar LED#"){
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
        }

        if(command == "*apagar#"){
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
        }

        command = "";
    }
}
