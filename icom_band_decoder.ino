/* ICOM Bandecoder
by Ondrej Kolonicny OK1CDJ, ondra@ok1cdj.com
based on Marios Nicolaou 5B4WN Icom decoder to BCD
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

int icomBandPin = 5;    // select the input where is icom voltage output connected
int sensedVoltage=0;
float calculatedVoltage=0;
int band=0;
int counter =0;
int previousValue=0;

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


 void setup() {
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
 }
 void loop() {
   // read the value from the sensor:
   sensedVoltage = analogRead(icomBandPin);    
   

   // measure voltage 5 times
   if (counter==5) {
   
   calculatedVoltage = float(sensedVoltage)*5/1024;
   
   setBand(calculatedVoltage);
  
   delay (20);
                  
 } else {
   if (abs(previousValue-sensedVoltage)>10) {
    //means change or spurious number 
     previousValue=sensedVoltage;
   } else {
     counter++; 
     previousValue=sensedVoltage;
   }
   
   
 }
 
}
 
int  setBand(float voltage) {
   int band=0;

  
if (voltage>4.20 && voltage<4.68) {
 band=160; 
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
 
} else if (voltage>3.50 && voltage<4.20) {
 band=80;
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

 
} else if (voltage>=2.95 && voltage<3.50) {
  band=40;
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
} else if(voltage>=2.30 && voltage<2.95) {
  band=20;
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
  
} else if (voltage>=1.70 && voltage<2.30) {
  band=15;
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
  
} else if (voltage>=1.2 && voltage<1.7) {
  band=10;
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
  
} else if (voltage>=0.75 && voltage<1.2) {
  band=6;
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
} else if (voltage  <0.75) {
  band=30;
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
 return band; 
  
}
