#include <esp_camera.h>
#include <BluetoothSerial.h>
#include <Wire.h>
BluetoothSerial SerialBT;

#define D0 19
#define D1 21
#define D2 22
#define D3 23
#define D4 34
#define D5 25
#define D6 26
#define D7 27
#define SDA 17
#define SCL 16
#define HS 33
#define VS 13
#define Mclk 14
#define Pclk 15
#define PWDN    -1
#define RST   -1
#define bton 32
// Since my camera is OV7670 without FIFO, I have to make a manual clock rate
#define LINE_SIZE 120
uint8_t lineBuffer[LINE_SIZE][LINE_SIZE];// square pic

void setup() {
  Serial.begin(115200);
  delay(1000);
  // bluetooth
  SerialBT.begin("Klinh");
  //button
  pinMode(bton, INPUT_PULLUP);
  if(digitalRead(bton)==LOW)chupanh();
  //send clockrate to mclk 
  ledcAttach(Mclk,10000000, 1); //f=10MHz, resolution: 1bit
  ledcWrite(Mclk,1); //high low high low 
  //camera monitor
  Wire.begin(SDA,SCL);
  // checking if cam work
  delay(1000);

  // pin
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  pinMode(VS, INPUT);
  pinMode(HS, INPUT);
  pinMode(Pclk, INPUT);
}

void loop()
{
    if(digitalRead(bton) == LOW)
    {
        chupanh();

        while(digitalRead(bton) == LOW);
        delay(50);
    }
}
//functions to check if the clock rate is working
// read from reg
uint8_t readReg(uint8_t reg)
{
    Wire.beginTransmission(0x21);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(0x21,1);
    return Wire.read();
}
//write value to reg 
void writeReg(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(0x21);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}
// reading data
//reading 1 bytes 
uint8_t readDataBus()
{
    return
        (digitalRead(D0) << 0)|
        (digitalRead(D1) << 1)|
        (digitalRead(D2) << 2)|
        (digitalRead(D3) << 3)|
        (digitalRead(D4) << 4)|
        (digitalRead(D5) << 5)|
        (digitalRead(D6) << 6)|
        (digitalRead(D7) << 7);
}//slli so that it shows the trọng số 
// only start reading when the clock goes high so that it wont write over during reading
uint8_t readByte()
{
  while(digitalRead(Pclk)==LOW);
  uint8_t data = readDataBus();
  while(digitalRead(Pclk)==HIGH);
  return data;
}
// Capture the pic
void chupanh()
{  // Vertical frame 
  while(digitalRead(VS) == HIGH);
  while(digitalRead(VS) == LOW);
//Take picture
  SerialBT.print("START");
  for(int i = 0; i < 120; i++)
  {while(digitalRead(HS) == LOW); // Waiting for new row
    for(int j = 0; j < 120; j++){
      uint8_t pixel = readByte(); 
      SerialBT.write(pixel); 
    }    
    while(digitalRead(HS) == HIGH);
  }
  SerialBT.print("END");
  Serial.println("Pics Taken & Sent");
}
