/*
    BrailleSpeak
  
   Plays a series of pitches converted from a serial input string.
   
   Each character of the input is mapped through an array that converts
   it to braille pairs (left-hand / right-hand of a braille character), 
   then to binary pairs, then to decimal pairs. 
   Each of the decimal pairs is then mapped to the equivelant note.
   That note is then output by the speaker.
   
   WIP. E&OE
  
   circuit:
   * 8-ohm speaker on digital pin 8
  
   Based on 'Keyboard' by Tom Igoe ( http://www.arduino.cc/en/Tutorial/Tone3)

 */

#include "pitches.h"
const int speaker = 8; //Pin 8
const int toneDuration = 200;

const int LEDR = 13;
const int LEDG = 12;
const int LEDB = 11;


// Each character in alphabetical order converted to decimal equivelant of
// binary braille pairs.
const int brailleMap[][2] = {
  {4, 0},
  {6, 0},
  {4, 4},
  {4, 6},
  {4, 2},
  {6, 4},
  {6, 6},
  {6, 2},
  {2, 4},
  {2, 6},
  {5, 0},
  {7, 0},
  {5, 4},
  {5, 6},
  {5, 2},
  {7, 4},
  {7, 6},
  {7, 2},
  {3, 4},
  {3, 6},
  {5, 1},
  {7, 1},
  {2, 7},
  {5, 5},
  {5, 7},
  {5, 3}
};

// Each decimal from binary mapped to note.
const int toneMap[] {
  NOTE_G3,
  NOTE_GS3,
  NOTE_AS3,
  NOTE_B3,
  NOTE_CS4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4
};

void setup() {
  pinMode(speaker, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  
  char content[100] = {};
  int contentSize = 0;

  while(Serial.available()) 
  {
    content[contentSize++] = Serial.read();
  }

  for (int i = 0; i < contentSize; i ++)
  {
    handleChar(content[i]);
  }

  
}
void handleChar(char character)
{
  // Handle spaces.
  if (character == ' ')
  {
    Serial.println("[space]");
    delay(toneDuration);
    return;
  }
  
  Serial.print(character);
  Serial.print(" - ");
  
  // Get tones from braille character map
  int brailleChars[2] = {0,0};
  int pos = ((int)character - (int)'A');
  
  // Handle lowercase values
  if (pos > 25)
  {
    pos -= 32;
  }

  // If it isn't a valid uppercase value, don't do anything
  if (pos < 0 || pos > 25)
  {
    return;
  }
  
  Serial.print(pos);
  Serial.print(" / ");
  brailleChars[0] = brailleMap[pos][0];//getBraille(content[i]);
  brailleChars[1] = brailleMap[pos][1];
  Serial.print(brailleChars[0]);
  Serial.print(", ");
  Serial.print(brailleChars[1]);
  Serial.print(" - ");
  
  int tone  = toneMap[brailleChars[0]];
  Serial.print(tone);
  outputTone(tone);
  Serial.print(" x ");
  
  tone  = toneMap[brailleChars[1]];
  Serial.print(tone);
  outputTone(tone);
  
  Serial.println('.');
   
}

void outputColour(int t)
{
  setColour(0,0,0);
  switch(t)
  {
    case NOTE_G3:
      setColour(255, 0, 0);
      break;
    case NOTE_GS3:
      setColour(255, 255, 0);
      break;
    case NOTE_AS3:
      setColour(255, 0, 127);
      break;
    case NOTE_B3:
      setColour(0, 255, 0);
      break;
    case NOTE_CS4:
      setColour(255, 128, 0);
      break;
    case NOTE_D4:
      setColour(102, 0, 102);
      break;
    case NOTE_E4:
      setColour(0, 0, 255);
      break;
    case NOTE_F4:
      setColour(255, 255, 255);
      break;
  }
  
}
void setColour(int red, int green, int blue)
{
  analogWrite(LEDR, red);
  analogWrite(LEDG, green);
  analogWrite(LEDB, blue);
}
void outputTone(int t)
{
  outputColour(t);
  // Play tone for duration
  tone(speaker, t, toneDuration);

  delay(toneDuration);
  // Stop tone
  noTone(speaker);
  outputColour(-1);
}
