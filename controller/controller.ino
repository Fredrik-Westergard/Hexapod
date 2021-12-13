#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(3, 10); // CE, CSN

const byte address[6] = "00001";
//button rows
int row[2][4];
//joystick switches
int sw1;        
int sw2;
//joystick x,y and z axes
int jy1;   
int jx1;   
int jz1;     
int jy2;     
int jx2;     
int jz2;  


//function for compiling and transmitting data
void trn(){
  String str1 = "A";                //As the nrf24l01 can only transmit 32 bytes at a time
  String str2 = "B";                //the message needs to be split in two, string A and B.
  char str3[32];                    //message to be sent.
  char str4[32];
  
  for(int i = 0; i < 2; i++){       //Converting and adding the rows to the message 1
    for(int j = 0; j < 4; j++){
      str1 += (String(row[i][j]));
    }
  }

  
  str1 += (String(sw1));            //Converting and adding the joystick switches to the message 1
  str1 += (String(sw2));

  //Serial.println(str1);           //uncomment prints for debug if needed
  
  str2 += (String(jy1));            //converting and adding joystick x,y and z axes to message 2
  str2 += (',');
  str2 += (String(jx1));
  str2 += (',');
  str2 += (String(jy2));
  str2 += (',');
  str2 += (String(jx2));
  str2 += (',');
  str2 += (String(jz1));
  str2 += (',');
  str2 += (String(jz2));
  str2 += (',');
  
  //Serial.println(str2);

  str1.toCharArray(str3, (str1.length()+1));    //converting string to char array
  //Serial.println(str3);
  radio.write(&str3, sizeof(str3));             //transmit first message
  
  str2.toCharArray(str4, (str2.length()+1));
  //Serial.println(str4);
  radio.write(&str4, sizeof(str4));             //transmit second message
}

void setup() {
  //rows 0-3
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  //columns 0,1
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);                         
  digitalWrite(7, HIGH);
  
  //Analog sticks
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  //switches
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(115200);

}

void loop() {
  //reading joystick x,y,z axes
  jy1 = analogRead(A1);
  jx1 = analogRead(A0);
  jz1 = analogRead(A6);
  jy2 = analogRead(A3);
  jx2 = analogRead(A2);
  jz2 = analogRead(A7);
  //reading joystick switches
  sw1 = digitalRead(9);
  sw2 = digitalRead(8);
  
  //set one column high and one low to only read one side
  digitalWrite(6, LOW);           
  digitalWrite(7, HIGH);
  //read that side
  row[0][0] = digitalRead(A5);
  row[0][1] = digitalRead(A4);
  row[0][2] = digitalRead(4);
  row[0][2] = digitalRead(5);
  
  //switch values
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  //read other side
  row[1][0] = digitalRead(A5);
  row[1][1] = digitalRead(A4);
  row[1][2] = digitalRead(4);
  row[1][2] = digitalRead(5);
  
  //transmit
  trn();
}
