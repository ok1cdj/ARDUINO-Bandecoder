/* Kenwood Bandecoder
!!! Warning this version was tested only with TS-590 in standalone mode !!!
Please let me know, if works also with other radios....

Tested with:  TS-590
Should work with: TS-480, TS-990 and TS-2000 
by Ondrej Kolonicny OK1CDJ, ondra@ok1cdj.com,   Enric EA3NR
http://www.remoteqth.com
you can get KIT here: 
http://hamshop.cz/remoteqth-com-c29/stavebnice-band-dekoderu-s-arduino-i230/
Change log:
v 1.1.4 9.1.2014
               - chages by EA3NR TNX
               If the radio is powered off and the band decoder remains powered on, the band 
               decoder output remains indefinitely showing the last selected band and never goes out of this status... It happens also if you 
               power the radio off and then you power the radio on immediately.
v 1.1.3 17.2.2014 
              - added 29 MHz and 51 and 52 MHz as 10m and 6m output TNX to Adam OK2IPW              
v 1.1.2 19.1.2014
              - solved bug in BCD output TNX to Frank - IZ4YDF	
v 1.1.1 10.12.2O13
              - minor change in serial comunication, now is source tested also with TS-590 
v 1.1 13.9.2013 
              - added BCD output like in YAESU RADIO to connect another accessories
                WARNING - only standard bands like 80,40,20,15,10 are suported on other bands are all BCD pins in low state
          
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
// uncomment next line if band decoder is connected alone to the radio and not sniffing comunication
#define ALONE_MODE  
// YAESU BCD
/* A B C D dec
 160 1 0 0 0 1
 80 0 1 0 0 2
 40 1 1 0 0 3
 20 1 0 1 0 5
 15 1 1 1 0 7
 10 1 0 0 1 9
 */
// IO port definition for BCD output
int D=12;
int C=13;
int B=A0;
int A=A1;
// IO port definition for bands
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
// variables
char inByte;  // incoming byte from serial RX
String buffer = "";  // empty string to store incoming serial data -- a buffer
boolean stringComplete = false;  // whether the string is complete or not

// Setup procedure
void setup()
{
  Serial.begin(57600);   // setup serial speed
  buffer.reserve(64);    // reserve 64 bytes for the incoming data buffer; UARTS's buffer is only 64 bytes long... :-P
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
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
}

void loop() {
  // send request for frequency only when bandecoder is connected alone to the radio
#ifdef ALONE_MODE
  Serial.print("IF;");
  // wait for the transmission of outgoing serial data from the Arduino to the radio to be completed
  Serial.flush();
  // we don't have to be always polling the radio frequency... we can wait for a while...XD
  delay(100);  
#endif
  if (Serial.available() > 0 ) {
    // get the first byte
    inByte = (char) Serial.read();
    // when the first byte is 'I' then we have to continue reading the input data 
    if (inByte == 'I') {
      buffer += inByte; 
      while (Serial.available() > 0) {
        inByte = (char) Serial.read(); 
        buffer += inByte; 
        // the reading procedure finishes when we read the ';' character
        if (inByte == ';') {
          stringComplete = true; 
        }
      }
    }
    // update band output only if the complete data has been received 
    if (stringComplete) {
      writeBand();
      // clear the RX buffer
      buffer = "";
      stringComplete = false; 
    }
  }
}
void writeBand() {
  String str_if = buffer;
  String qrg ;
  // tady je kmitocet od 5 do 10 znaku
  qrg = str_if.substring(5,10);
  //na tretim miste ma byt 1 pak do jde na HIGH
  // 160m band
  if ((qrg[0] == '0')&&(qrg[1] == '1'))
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
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
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
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  // 40m band
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
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
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
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  }
  // 20m band
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
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
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
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
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
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
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
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
  // 10m band
  if (((qrg[0] == '2')&&(qrg[1] == '8'))||((qrg[0] == '2')&&(qrg[1] == '9')))
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
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
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
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
  if ((qrg[0] == '5')&&(qrg[1] == '1'))
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
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
  if ((qrg[0] == '5')&&(qrg[1] == '2'))
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
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
  }
}
