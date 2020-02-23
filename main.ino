#include "morse_def_text.hpp"

std::string MESSAGE = "HELLO KEVIN BIT.LY ABCDE AES SAREGAMA";
const int TIME_PERIOD = 100;
const int SLEEP_BEFORE_START = 5000;
int pins[] = {LED_BUILTIN, 12};
int numPins = 0; 
int done = 0;

void multiDigitalWrite(int mode){
  for (int i = 0; i < numPins; i++)
    digitalWrite(pins[i], mode);
}

void morse_write(std::string sym){
  for (char const &c: sym){

    switch(c){
      case '.': 
        Serial.write(c);
        multiDigitalWrite(HIGH);
        delay(TIME_PERIOD);
        multiDigitalWrite(LOW);
        break;
      case '-': 
        Serial.write(c);
        multiDigitalWrite(HIGH);
        delay(3*TIME_PERIOD);
        multiDigitalWrite(LOW);
        break;
      case ' ': 
        Serial.write("_");
        multiDigitalWrite(LOW);
        delay(TIME_PERIOD);
        break;
      default:
        Serial.write(c);
    }
  }
}

void morse_start(){
  delay(SLEEP_BEFORE_START);
  Serial.write("start : ");
  morse_write(morseProsignStartingSignal);
  morse_write(morseLetterSpace);
  Serial.write("\n");
}

void morse_end(){
  Serial.write("end : ");
  morse_write(morseProsignEndOfWork);
  Serial.write("\n");

}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  numPins = (int) (sizeof(pins) / sizeof(int));  
  for (int i = 0; i < numPins; i++)
    pinMode(pins[i], OUTPUT);
  Serial.begin(9600); 
  Serial.write("done setup\n");

}

void loop()
{
  if(done) return;
  Serial.write("starting delay\n");
  delay(SLEEP_BEFORE_START);
  Serial.write("starting morse\n");
  morse_start();  
  for (char const &c: MESSAGE){
    Serial.write(c);
    Serial.write(" : ");
    morse_write(getMorseCode(c));
    morse_write(morseLetterSpace);
    Serial.write("\n");
  }
  morse_end();
  done++;
}
