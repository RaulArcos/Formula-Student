#include <Ticker.h>
#include <Wire.h>  // Lo trae Arduino IDE
#include <LiquidCrystal_I2C.h> // Incluimos la libreria del LCD
#include <SPI.h>
#include <MaxMatrix.h> 
#include <stdlib.h>
#include "mcp_can.h"
#include <ArduinoSort.h>

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif

const int SPI_CS_PIN = 53;

MCP_CAN CAN(SPI_CS_PIN);                      
LiquidCrystal_I2C lcd(0x3F, 20, 4);

//DEFINIMOS LA TIRA LED Y FUNCION DE INICIO
int led[] = {22,23,24,25,26,27,28,29,30,31,32,33};
int ledaviso[] = {36,37,39};

void InicioLed(){

  for (int i = 0;i < 12;i++){
    digitalWrite(led[i],HIGH);
    delay(100);
  }
    for (int i = 0;i < 12;i++){
    digitalWrite(led[i],LOW);
    delay(100);
  }
     for (int i = 0;i < 12;i++){
    digitalWrite(led[i],HIGH);
    digitalWrite(ledaviso[i],HIGH);
   
  }
   delay(100);
   for (int i = 0;i < 12;i++){
    digitalWrite(led[i],LOW);
    digitalWrite(ledaviso[i],LOW);
   
  }
  delay(100);
      for (int i = 0;i < 12;i++){
    digitalWrite(led[i],HIGH);
    digitalWrite(ledaviso[i],HIGH);
   
  }
  delay(100);
   for (int i = 0;i < 12;i++){
    digitalWrite(led[i],LOW);
    digitalWrite(ledaviso[i],LOW);
   
  }
   delay(100);
      for (int i = 0;i < 12;i++){
    digitalWrite(led[i],HIGH);
    digitalWrite(ledaviso[i],HIGH);
   
  }
  delay(100);
   for (int i = 0;i < 12;i++){
    digitalWrite(led[i],LOW);
    digitalWrite(ledaviso[i],LOW);
   
  }



};
//FIN

PROGMEM unsigned char const GRID[] = {
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
};

int data = 8;    // DIN pin del módulo MAX7219
int load = 9;    // CS pin del módulo MAX7219
int clock = 10;  // CLK pin del módulo MAX7219
int maxInUse = 1;    // Cuantos módulos MAX7219 se estan usando
MaxMatrix m(data, load, clock, maxInUse);
byte buffer[10];

void grid(int marcha){

     if(marcha == 0){
     memcpy_P(buffer, GRID + 7, 7);
     m.writeSprite(2, 0, buffer);    
    }

    if(marcha == 1){
        memcpy_P(buffer, GRID + 14, 7);
        m.writeSprite(2, 0, buffer);    
    }
     if(marcha == 2){
        memcpy_P(buffer, GRID + 21, 7);
        m.writeSprite(2, 0, buffer);    
    }
    if(marcha == 3){
        memcpy_P(buffer, GRID + 28, 7);
        m.writeSprite(2, 0, buffer);    
    }
 
  
}

//DATA Y FUNCION PARA LOGO INICIO
//INICIO
byte BUno[8] = {B00000,B00011,B00111,B01111,B01111,B11111,B11110,B11100};
byte BDos[8] = {B01101,B11101, B11011,B11000,B10000,B00000,B00011,B00011};
byte BTres[8] = {B11110,B11110,B11110,B01110,B00000,B00000,B11110,B11110};
byte BCuatro[8] = {B11011,B11011,B10111,B10111,B00111,B00111,B00111,B00000};
byte BCinco[8] = {B00011,B00011,B00001,B10001,B11001,B11101,B11110,B11110};
byte BSeis[8] = {B11110,B11110,B11110,B11100,B11100,B11100,B11000,B00000};

void Logo(){
  lcd.createChar(0, BUno);
  lcd.createChar(1, BDos);
  lcd.createChar(2, BTres);
  lcd.createChar(3, BCuatro);
  lcd.createChar(4, BCinco);
  lcd.createChar(5, BSeis);
  lcd.home();
  lcd.setCursor(8, 1);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(8, 2);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  delay(3000);
  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(10, 2);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(2, 2);
  lcd.print("FORMULA");
  lcd.setCursor(13, 2);
  lcd.print("ADES");
}
//FIN LOGO
//FUNCION DE PARPADEO DE PANTALLA PARA PELIGRO
//INICIO
int WarningCode = 0;
int OkButton = 0;
int PButton = 0;
int Pantalla = 0;
int Riesgo = 0;
int MemWarning[10];
int MemCont=0;
int AuxWarning=1;

void ImprimirWarning(int pos){

    
    if(MemWarning[pos] == 1){
     lcd.setCursor(14,0);
      lcd.print("AGUA");
     lcd.setCursor(14,1);
      lcd.print("TEMP");
     lcd.setCursor(14,2);
      lcd.print("ALTA"); 
      
    }
    if(MemWarning[pos] == 2){
     lcd.setCursor(14,0);
      lcd.print("    ");
     lcd.setCursor(14,1);
      lcd.print("NOSE");
     lcd.setCursor(14,2);
      lcd.print("ALTO"); 
     if(Riesgo == 0) Riesgo = 1;
    } 
    
    Serial.print("CODIGO ACTUAL: ");
    Serial.println(MemWarning[pos]);

    if(MemWarning[pos] == 2 && Riesgo == 1){
        for (int i = 0;i < 3;i++){  
         digitalWrite(ledaviso[i],HIGH);
        }
           delay(80);
        for (int i = 0;i < 3;i++){
          digitalWrite(ledaviso[i],LOW);
        }
    } else{ for (int i = 0;i < 3;i++){
          digitalWrite(ledaviso[i],LOW);
          }
    }

    if(MemWarning[pos] == 1){digitalWrite(43,HIGH);}else {digitalWrite(43,LOW);}
    if(MemWarning[pos] == 2){digitalWrite(42,HIGH);}else {digitalWrite(42,LOW);}
    
    lcd.setCursor(13,3);
    lcd.print(" ");
    lcd.setCursor(18,3);
    lcd.print("  ");
    lcd.setCursor(14,3);
    lcd.print(MemCont);
    lcd.setCursor(15,3);
    lcd.print("W");
    lcd.setCursor(17,3);
    lcd.print(pos+1);
  
}

int ComprobarWarning(int cod){

  if(MemCont > 0){

    for(int i = 0; i < MemCont; i++){ 
    
      if(MemWarning[i] == cod){ 
        return 1;
      }
      
    }
      return 0;
  }
  else return 0;

}
void EliminarWarning(int cod){
int aux = 0;
//Encontramos donde esta el codigo que queremos eliminar y lo quitamos.
  for(int i = 0; i < MemCont; i++){ 
    if(MemWarning[i] == cod){ 
      MemWarning[i] = NULL;
      aux = 1;
     }
     if(aux == 1){
      MemWarning[i] = MemWarning[i+1];
     }
    }
    MemCont--;
}

void RegistraWarning(int cod){

    MemWarning[MemCont] = cod;
    MemCont++;
    Riesgo=0;
    AuxWarning = 1;
   sortArray(MemWarning, MemCont);
}
void Warning(){
    
    
    if(MemCont>0){
       if(digitalRead(2) == HIGH) {
          if(Riesgo == 1){
            Riesgo=-1;
          }else{
          lcd.clear();
          AuxWarning++;
          if(MemCont-AuxWarning<0){AuxWarning = 1;}
          delay(150);
          }
        }
        ImprimirWarning(MemCont-AuxWarning);
      
    }else{

      lcd.setCursor(14,0);
      lcd.print("    ");
      lcd.setCursor(14,1);
      lcd.print("    ");
      lcd.setCursor(14,2);
      lcd.print("    ");
      lcd.setCursor(13,3);
      lcd.print("ALL OK!");
      digitalWrite(43,LOW);
      digitalWrite(42,LOW);
      }
}
void luzRPM(int rpm){ //Probar con Switch
  
  if(rpm > 100){digitalWrite(led[1],HIGH);digitalWrite(led[0],HIGH);}else{digitalWrite(led[1],LOW);digitalWrite(led[0],LOW);}
  if(rpm > 300){digitalWrite(led[3],HIGH);digitalWrite(led[2],HIGH);}else{digitalWrite(led[3],LOW);digitalWrite(led[2],LOW);}
  if(rpm > 500){digitalWrite(led[5],HIGH);digitalWrite(led[4],HIGH);}else{digitalWrite(led[5],LOW);digitalWrite(led[4],LOW);}
  if(rpm > 700){digitalWrite(led[7],HIGH);digitalWrite(led[6],HIGH);}else{digitalWrite(led[7],LOW);digitalWrite(led[6],LOW);}
  if(rpm > 900){digitalWrite(led[9],HIGH);digitalWrite(led[8],HIGH);}else{digitalWrite(led[9],LOW);digitalWrite(led[8],LOW);}
  if(rpm >1000){
    for (int i = 0;i < 12;i++){digitalWrite(led[i],HIGH);}
    delay(100);
    for (int i = 0;i < 12;i++){digitalWrite(led[i],LOW);}
  }
}
void CambioPantalla(){
   
  
        if(digitalRead(3) == HIGH && Pantalla == 0) {
          Serial.println("si");
          Pantalla = 1;
          lcd.clear();
          delay(150);
        }
         
        if(digitalRead(3) == HIGH && Pantalla == 1) {
          Pantalla = 0;
          lcd.clear();
          delay(150);
          
        }
  
}
void LecturaCAN(){
   
    unsigned char len = 0;
    unsigned char buf[8];
    
    
    do{
        CAN.readMsgBuf(&len, buf); 
        }while(buf[0]!=1);
          if( buf[0] == 1 ){
        unsigned int a = buf[1] * 256 + buf[2]; //DatoRPM
        luzRPM(a);        
        unsigned int b = buf[3] * 256 + buf[4]; //DatoTemp
        unsigned int c = buf[5] * 256 + buf[6]; //DatoNuevo

          if(b >= 90 && ComprobarWarning(1) == 0){RegistraWarning(1);} 
          if(ComprobarWarning(1) == 1 && b<90){EliminarWarning(1);Serial.println("Eliminado error 1");}
          

          if(Pantalla == 0){
          if(a<1000){lcd.setCursor(9,0);lcd.print(" ");}
          if(a<100){lcd.setCursor(8,0);lcd.print(" ");}
          if(a<10){lcd.setCursor(7,0);lcd.print(" ");}
            lcd.setCursor(0,0); 
            lcd.print("RPM = ");
            lcd.print(a);
          
            lcd.setCursor(0,1); 
            lcd.print("WTEMP = ");
            lcd.print(b);
          if(b<1000){lcd.setCursor(11,1);lcd.print(" ");}
          if(b<100){lcd.setCursor(10,1);lcd.print(" ");}
          if(b<10){lcd.setCursor(9,1);lcd.print(" ");}   
        }
        
        if(Pantalla == 1){
          if(a<1000){lcd.setCursor(9,0);lcd.print(" ");}
          if(a<100){lcd.setCursor(8,0);lcd.print(" ");}
          if(a<10){lcd.setCursor(7,0);lcd.print(" ");}
            lcd.setCursor(0,0); 
            lcd.print("RPM = ");
            lcd.print(a);

          lcd.setCursor(0,1); 
            lcd.print("COSAS = ");
            lcd.print(c);
          if(c<1000){lcd.setCursor(11,1);lcd.print(" ");}
          if(c<100){lcd.setCursor(10,1);lcd.print(" ");}
          if(c<10){lcd.setCursor(9,1);lcd.print(" ");}   
        
        
        }
       
       
            }
       

     do{
        CAN.readMsgBuf(&len, buf);
      }while(buf[0]!=2);
          if(buf[0] == 2){     
        unsigned int a = buf[1] * 256 + buf[2]; //DatoRPM
        unsigned int b = buf[3] * 256 + buf[4]; //DatoTemp
       // if(b >= 500 && ComprobarWarning(2) == 0){RegistraWarning(2);} 
       //  if(ComprobarWarning(2) == 1 && b<500){EliminarWarning(2);}
        grid(a);
          
       if(Pantalla == 0){
          if(a<1000){lcd.setCursor(9,2);lcd.print(" ");}
          if(a<100){lcd.setCursor(8,2);lcd.print(" ");}
          if(a<10){lcd.setCursor(7,2);lcd.print(" ");}
            lcd.setCursor(0,2); 
            lcd.print("MAR = ");
            lcd.print(a);
          
            lcd.setCursor(0,3); 
            lcd.print("NSE = ");
            lcd.print(b);
            
          if(b<1000){lcd.setCursor(9,3);lcd.print(" ");}
          if(b<100){lcd.setCursor(8,3);lcd.print(" ");}
          if(b<10){lcd.setCursor(7,3);lcd.print(" ");}   
        }
        
        
        }
        

       
}


void setup() {
   
    
    SERIAL.begin(115200);

    pinMode(2,INPUT);//OK BUTTON
    pinMode(3,INPUT);//PRINCIPAL BUTTON
    pinMode(42,OUTPUT);//LED AVISO
    pinMode(43,OUTPUT);//LED PELIGRO
    digitalWrite(36,HIGH);
    
    m.init(); 
    m.setIntensity(15); // Intensidad luminosa de la matriz
    
    for(int i= 0;i<12;i++){
       pinMode(led[i],OUTPUT);
    }
    for(int i= 0;i<4;i++){
       pinMode(ledaviso[i],OUTPUT);
    }
    lcd.begin(); 
     memcpy_P(buffer, GRID + 14, 7);
        m.writeSprite(2, 0, buffer); 
    Logo();
    
    InicioLed();
    delay(1000);
    lcd.clear();
    
    while (CAN_OK != CAN.begin(CAN_250KBPS)) {            // init can bus : baudrate = 500k
        SERIAL.println("CAN BUS Shield Fallo Inicio");
        lcd.setCursor(3, 0);
        lcd.print("CAN BUS FAIL");
        SERIAL.println(" Init CAN BUS Shield again");
        lcd.setCursor(2, 1);
        lcd.print("BIEN CONECTADO??");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("CAN BUS Iniciado");
    lcd.setCursor(3, 1);
    lcd.print("Correctamente");
    lcd.setCursor(1, 3);
    lcd.print("SalpicaderoFG Test");
    delay(2000);
    lcd.clear();
      
     
}



void loop() {
    unsigned char len = 0;
    unsigned char buf[8];
    LecturaCAN();
    Warning();
   // CambioPantalla();
    
        lcd.setCursor(12,0); 
        lcd.print("|");
        lcd.setCursor(12,1); 
        lcd.print("|");
        lcd.setCursor(12,2); 
        lcd.print("|");
        lcd.setCursor(12,3); 
        lcd.print("|");
        
       /* for(int i = 0;i<10;i++){
          Serial.print(MemWarning[i]);
          
        }
        Serial.println();
        Serial.println(MemCont);
        if (CAN_MSGAVAIL == CAN.checkReceive()) {      // check if data coming
        unsigned long canId = CAN.getCanId();
        CAN.readMsgBuf(&len, buf);
        SERIAL.println("-----------------------------");
        SERIAL.print("Get data from ID: 0x");
        SERIAL.println(canId, DEC);
        for (int i = 0; i < len; i++) { // print the data
            SERIAL.print(buf[i]);
            SERIAL.print("\t");
        }
      }
*/      
      
}
/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
