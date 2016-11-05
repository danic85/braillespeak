# BrailleSpeak

Plays a series of pitches converted from a serial input string.
   
Each character of the input is mapped through an array that converts
it to braille pairs (left-hand / right-hand of a braille character), 
then to binary pairs, then to decimal pairs. 
       
Each of the decimal pairs is then mapped to the equivelant note.
That note is then output by the speaker.

WIP. E&OE

## Circuit

* 8-ohm speaker on digital pin 8
* RGB LED on pins 11 - 13

Based on 'Keyboard' by Tom Igoe ( http://www.arduino.cc/en/Tutorial/Tone3)

## Example ouput of alphabet

 a - 0 / 4, 0 - 277 x 196.
 b - 1 / 6, 0 - 330 x 196.
 c - 2 / 4, 4 - 277 x 277.
 d - 3 / 4, 6 - 277 x 330.
 e - 4 / 4, 2 - 277 x 233.
 f - 5 / 6, 4 - 330 x 277.
 g - 6 / 6, 6 - 330 x 330.
 h - 7 / 6, 2 - 330 x 233.
 i - 8 / 2, 4 - 233 x 277.
 j - 9 / 2, 6 - 233 x 330.
 k - 10 / 5, 0 - 294 x 196.
 l - 11 / 7, 0 - 349 x 196.
 m - 12 / 5, 4 - 294 x 277.
 n - 13 / 5, 6 - 294 x 330.
 o - 14 / 5, 2 - 294 x 233.
 p - 15 / 7, 4 - 349 x 277.
 q - 16 / 7, 6 - 349 x 330.
 r - 17 / 7, 2 - 349 x 233.
 s - 18 / 3, 4 - 247 x 277.
 t - 19 / 3, 6 - 247 x 330.
 u - 20 / 5, 1 - 294 x 208.
 v - 21 / 7, 1 - 349 x 208.
 q - 16 / 7, 6 - 349 x 330.
 x - 23 / 5, 5 - 294 x 294.
 y - 24 / 5, 7 - 294 x 349.
 z - 25 / 5, 3 - 294 x 247.

