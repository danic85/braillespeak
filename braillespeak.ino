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
const int speaker 8; //Pin 8
const int toneDuration 20;

// Each character in alphabetical order converted to decimal equivelant of
// binary braille pairs.
const int[][2] brailleMap = {
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
}

// Each decimal from binary mapped to note.
const int[] toneMap {
  NOTE_G3,
  NOTE_GS3,
  NOTE_AS3,
  NOTE_B3,
  NOTE_CS4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4
}

void setup() {
  pinMode(speaker, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  
  String content = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
  }

  if (content != "") {
    content = content.toUpperCase();
    Serial.println(content);
    for (i = 0; i < content.length(); i = i + 1) 
    {
      Serial.print(content[i]);
      Serial.print(' - ');
      // Handle spaces.
      if (content[i] == ' ')
      {
        delay(toneDuration);
        continue;
      }
      
      // Get tones from braille character map
      int[2] brailleChars = getBraille(content[i]);
      Serial.print(braileChars[0]);
      Serial.print(', ');
      Serial.print(braileChars[1]);
      Serial.print(' - ');
      for (j = 0; j < brailleChars.length(); j = j+1)
      {
        int tone  = toneMap[brailleMap[brailleChar[j]]];
        Serial.print(tone);
        Serial.print(' ');
        outputTone(tone);
      }
      Serial.println('.');
    }
  }
}

int[] getBraille(char character)
{
  // convert to ascii value then offset (so that A is 0)
  int asciiVal = (int)character - (int)'A';
  // return tone pair from braille map
  return brailleMap[asciiVal]
}

void outputTone(int tone)
{
  // Play tone for 20ms
  tone(speaker, tone, toneDuration);
  // Stop tone
  noTone(speaker);
}
