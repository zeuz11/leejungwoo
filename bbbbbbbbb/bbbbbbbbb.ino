/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}
int mul=10;
int cnt = 0;
int dataCnt =1;
char dataArr[200];
int dataArrCnt=0;
char receiveData[200];
int receiveDataCnt=0;
int dataStart=0;
int dataEnd=0;

 int doubleCnt=0;
void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
char inByte =Serial1.read();
   if(inByte == '\n'){
  
     receiveData[receiveDataCnt]='\n';
     for(int i=0;i<receiveDataCnt+1;i++){
  
        if(receiveData[i] == ':'){
          
          dataStart=i+1;
        }
        if(receiveData[i] == '\n'){
          dataEnd = i-1;
   
          break;
        }
     
      }
      if(receiveData[0] == 'A'){
        Serial.print(receiveData);
        Serial.println("Type - Analog");
        Serial.print("size - ");
        int tmp =(int)dataEnd - (int)dataStart;
 
        Serial.println(tmp);
        Serial.print("Data - ");
tmp--;

        for(int c=dataStart;c<dataEnd;c++){
         
         
       
          int temp=(int)(receiveData[c]-'0')*(int)pow(10,tmp);
          
          Serial.println(temp);
          doubleCnt= doubleCnt+temp;
     
         
         
         tmp--;
        
        }
          Serial.print(doubleCnt);
          Serial.print(" * 2 = ");
          Serial.print(doubleCnt*2);
        Serial.println("");
        Serial.println("");
        for(int j=0;j<receiveDataCnt+1;j++){
        
          receiveData[j]=0;          
        }
        receiveDataCnt=0;
        dataStart=0;
        dataEnd=0;
        doubleCnt=0;
      }
         if(receiveData[0] == 'C'){
          Serial.print(receiveData);
        Serial.println("Type - Chat");
        Serial.print("size - ");
        int tmp = dataEnd - dataStart;
        Serial.println(tmp);
        Serial.print("Data - ");
         for(int c=dataStart;c<dataEnd;c++){
          Serial.print(receiveData[c]);
        }
        Serial.println("");
        Serial.println("");
        for(int j=0;j<receiveDataCnt+1;j++){
          receiveData[j]=0;          
        }
        dataStart=0;
        dataEnd=0;
        receiveDataCnt=0;
      }
    }else{
      
     receiveData[receiveDataCnt] = inByte;
     receiveDataCnt++;
    }
   
    
   
   }
    

  
if(cnt>30000){

  int sensorValue = analogRead(A0);
   while(1){
    int tmp=sensorValue/mul;
    if(tmp == 0){
      Serial1.print('A');
      Serial1.print(dataCnt);
       Serial1.print(':');
      mul=10;
      dataCnt=1;
      
      break;
    }else{
      dataCnt++;
      mul=mul*10;
    }
  }

  Serial1.println(sensorValue);
   cnt=0;
}
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    //Serial1.write(inByte);
    if(inByte == '\n'){
      dataArrCnt--;
      Serial1.print('C');
      Serial1.print(dataArrCnt);
      Serial1.print(':');
      Serial1.println(dataArr);
      dataArrCnt=0;
      for(int i=0;i<sizeof(dataArr);i++){
        dataArr[i]=0;
      }
    }else{
      dataArr[dataArrCnt]=inByte;
      dataArrCnt++;
    }
    
    
  }
  cnt++;
}
