/* Kenwood Bandecoder
by Ondrej Kolonicny OK1CDJ, ondra@ok1cdj.com

v 1.0 - 20.3.2013 

  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define ALONE_MODE
// uncomment this line if bandecoder is connected alone to the radio and not sniffing comunication

int  inByte= -1;             // incoming byte from serial RX

char buffer[100];             // string for incoming serial data -- a buffer

int  bufferPos = 0;          // string index counter

//  IO port definition for bands


int b160 = 9;

int b80 = 8;

int b40 = 7;

int b30 = 6;

int b20 = 5;

int b17 = 4;

int b15 = 3;

int b12 = 2;

int b10 = 11;

int b6 = 10;

// Setup proc

void setup()

{

  Serial.begin(9600); //  nastav si rychlost

  pinMode(b160, OUTPUT);

  pinMode(b80, OUTPUT);

  pinMode(b40, OUTPUT);
  
  pinMode(b30, OUTPUT);

  pinMode(b20, OUTPUT);
  
  pinMode(b17, OUTPUT);

  pinMode(b15, OUTPUT);

  pinMode(b12, OUTPUT);
  
  pinMode(b10, OUTPUT);

  pinMode(b6, OUTPUT);
  
  //Serial1.begin(9600);

}


void loop() {



  Serial.flush();  // send request for frequency, use only when bandecoder is connected alone to the radio
#ifdef ALONE_MODE
    Serial.println("IF;");
    
#endif
  if (Serial.available() > 0 ) {
    
    inByte = Serial.read();

// read frequency
    read_if ();

  }

}

void read_if () {

  if (inByte == 'I') {

    while (bufferPos != 38) {

      if (Serial.available() > 0) {

        buffer[bufferPos] = inByte;

        bufferPos++;

        inByte = Serial.read();

        if (inByte == ';') break;

      }

    }

String str_if = buffer;

String qrg ;


// tady je kmitocet od 5 do 10 znaku

qrg = str_if.substring(5,10);

//na tretim miste ma byt 1 pak do jde na HIGH

// 160m band
if (qrg[1] == '1')

{
 

  digitalWrite(b160, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}


// 80m band

if (qrg[1] == '3')

{

  digitalWrite(b80, HIGH);
  digitalWrite(b160, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}


//  40m band

if (qrg[1] == '7')

{

  digitalWrite(b40, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}


// 30m band

if ((qrg[0] == '1')&&(qrg[1] == '0'))

{

  digitalWrite(b30, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}

// 20m  band
if ((qrg[0] == '1')&&(qrg[1] == '4'))

{

  digitalWrite(b20, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}

// 17m band

if ((qrg[0] == '1')&&(qrg[1] == '8'))

{

  digitalWrite(b17, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}

// 15m band

if ((qrg[0] == '2')&&(qrg[1] == '1'))

{

  digitalWrite(b15, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);
}

// 12m band

if ((qrg[0] == '2')&&(qrg[1] == '4'))

{

  digitalWrite(b12, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b6, LOW);

}

// 10m band

if ((qrg[0] == '2')&&(qrg[1] == '8'))

{

  digitalWrite(b10, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b160, LOW);
  digitalWrite(b6, LOW);
}

//6m band

if ((qrg[0] == '5')&&(qrg[1] == '0'))

{

  digitalWrite(b6, HIGH);
  digitalWrite(b80, LOW);
  digitalWrite(b40, LOW);
  digitalWrite(b30, LOW);
  digitalWrite(b20, LOW);
  digitalWrite(b17, LOW);
  digitalWrite(b15, LOW);
  digitalWrite(b12, LOW);
  digitalWrite(b10, LOW);
  digitalWrite(b160, LOW);
}
//CD.print(".");

//GLCD.print(str_if.substring(10,12));





 for (int c = 0; c < bufferPos; c++) {

      buffer[c] = 0;

    }

    bufferPos = 0;

  }

}
