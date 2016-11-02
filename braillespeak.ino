/*
  BrailleSpeak

 Plays a series of pitches converted from a serial input string.
 
 Each character of the input is mapped through an array that converts
 it to braille, then each section of the braille character is mapped to the
 equivelant combination of 'keys' on a trumpet to select the appropriate note.
 That note is then output by the speaker.
 
 WIP. E&OE

 circuit:
 * 8-ohm speaker on digital pin 8

 Based on 'Keyboard' by Tom Igoe ( http://www.arduino.cc/en/Tutorial/Tone3)

 */

#include "pitches.h"
const int speaker 8;
const int toneDuration 20;

// @todo populate with notes for each letter.
const int[][2] brailleMap = {
  {NOTE_G5, NOTE_A5} // A
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
      // Handle spaces.
      if (content[i] == ' ')
      {
        delay(toneDuration);
        continue;
      }
      
      // Get tones from braille character map
      int[2] brailleChars = getBraille(content[i]);
      for (j = 0; j < brailleChars.length(); j = j+1)
      {
        outputTone(brailleMap[brailleChar[j]]);
      }
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
