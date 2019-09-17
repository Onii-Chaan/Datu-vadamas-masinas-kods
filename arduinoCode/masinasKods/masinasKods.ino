#define mainMotorPlus 11
#define mainMotorMinus 10
#define turnMotorPlus 9
#define turnMotorMinus 6
#define redDiodeOne 5
#define redDiodeTwo 4
#define whiteDiodeOne 3
#define whiteDiodeTwo 7
#define LMVcc 8
#define MPUInt 2
#define MPUScl A5
#define MPUSda A4
#define voltagePin A3

class audioVcc{//klase , kas atbild par audio Vcc iedarbināšanu
  public:

  bool vccState;//nosaka vai audio pins ir vaļā vai ciet

  void setup(){
    pinMode(LMVcc, OUTPUT);
  }
  void loop(){
    if(vccState == true){
      digitalWrite(LMVcc, HIGH);
    } else {
      digitalWrite(LMVcc, LOW);
    }
  }

};

class BTdata {//bluetooth datu saņemšanas klase
  private://mainīgie, kas nepieciešami, lai sadalītu datus
      int countDataSwCase;//recvWithStartEndMarkers switch operatora skaitītājs
      bool recvInProgress = false;
      byte ndx = 0;
      char startMarker = '<';
      char endMarker = '>';
      char rc;//šajā mainīgajā tiek saglabāts katrs ienākošais baits
      const byte numChars = 32;
      char receivedChars[32];
      int onValue;//pirmais saņemtais cipars
      int mode;//otrais saņemtais cipars

  public:
    byte activeValues[5];//šajā sarakstā glabājas apstrādātie dati, kuri tiek izpildīti un izmantoti turpmāk visur
    byte prevActiveValues[5];//iepriekšējās activeValues masīva dati
    //active values paskaidrojums: {0,0,0,0}
    /*
    0. - mašīna brauc uz priekšu/atpakaļ (vērtības 0,1,2, kur 0 stāv, 1 uz priekšu, 2 atpakaļ)
    1. - mašīna pagriežas pa labi/pa kreisi (vērtības 0, 1, 2, kur 0 sākuma stāvoklis, 1 pa kreisi, 2 pa labi)
    2. - deg diodes (vērtības 0, 1, 2 kur 0 ir izslēgtas abas gaismas, 1, priekšējās, 2, aizmugurējās)
    3. - tiek atskaņota signalizācija vai ieraksts (vērtības 0,1,2, kur 0 nekas netiek atskaņots, 1, tiek atskaņots ieraksts, 2 tiek atskaņota signalizācija)
    */ 

    void setup() {
      Serial.begin(9600);
    }

    void loop() {
        while (Serial.available() > 0) {
        rc = Serial.read();
        if (recvInProgress == true) {
          if (rc != endMarker) {
            receivedChars[ndx] = rc;//no šiem datiem tiek piešķirtas mainīgo vērtības, kas tiek iesūtītas un no saraksta pārveidotas skaitlī
            ndx++;
            switch (countDataSwCase) {
              case 1: { //tiek noteikts ienākošo datu tips
                  onValue = atoi(receivedChars);
                  ndx = 0;
                }
                break;
              case 2: { //tiek noteikts kurām led daļām ir jāstrādā
                  mode = atoi(receivedChars);
                  ndx = 0;
                }
                break;
            }
            if (ndx >= numChars) {
              ndx = numChars - 1;
            }   
          } else {
            receivedChars[sizeof(receivedChars)+1] = '\0'; // terminate the string, svarīga koda rindiņa, kur iepriekš [] iekšā bija ndx. Ndx patstāvīgi mainās, tāpēc bija nepieciešams ievietot citu garuma vērtību
            recvInProgress = false;
            setNewData();
          }
          countDataSwCase ++;//datu sadalīšanas daļas skaitītājs
        } else if (rc == startMarker) {
          recvInProgress = true;
          countDataSwCase = 1;//reseto mainīgo no iepriekšējās vērtības
        }
      }
    }

    void setNewData(){
    for ( int i = 0; i < 3;  ++i ) { //notīra receivedChars masīvu
      receivedChars[i] = (char)0; 
    }
      for(int i = 0; i<5; i++){//saliek iepriekšējos datus iepriekšējo datu masīvā
        prevActiveValues[i] = activeValues[i];
      }
      activeValues[onValue] = mode;//jaunie dati tiek ievietoti masīvā 
    }
};

class carLights {//klase, kas atbild par mašīnītes gaismas iedarbināšanu
  public:
    void setup() {
      pinMode(redDiodeOne, OUTPUT);
      pinMode(redDiodeTwo, OUTPUT);
      pinMode(whiteDiodeOne, OUTPUT);
      pinMode(whiteDiodeTwo, OUTPUT);
    }

    void loop() {
      
    }

    void turnLights(byte lightState){
      switch (lightState)
      {
      case 0:
        digitalWrite(redDiodeOne, LOW);
        digitalWrite(redDiodeTwo, LOW);
        digitalWrite(whiteDiodeOne, LOW);
        digitalWrite(whiteDiodeTwo, LOW);
      break;
      case 1:
        digitalWrite(redDiodeOne, HIGH);
        digitalWrite(redDiodeTwo, HIGH);
      break;
      case 2:
        digitalWrite(whiteDiodeOne, HIGH);
        digitalWrite(whiteDiodeTwo, HIGH);
      break;
      case 3://Mašīnītei ieslēdzoties pašā sākumā tā nomirgo
      bool onOffStart = false;
      for(int i = 0; i<=2; i++){
        if(i%2 == 0){//katra otrā vērtība ir negatīva un tas ļauj mašīnītei nomirgot
          onOffStart = true;
        } else {
          onOffStart = false;
        }
          digitalWrite(redDiodeOne, onOffStart);
          digitalWrite(redDiodeTwo, onOffStart);
          digitalWrite(whiteDiodeOne, onOffStart);
          digitalWrite(whiteDiodeTwo, onOffStart);
          delay(200);
        }
      break;
      }
    }
};

class carControl {//klase , kas atbild par mašīnītes motoru darbināšanu
  public:
    void setup() {
      pinMode(mainMotorPlus, OUTPUT);
      pinMode(mainMotorMinus, OUTPUT);
      pinMode(turnMotorPlus, OUTPUT);
      pinMode(turnMotorMinus, OUTPUT);
    }

    void loop() {

    }

    void driveCar(byte mainMotor, byte turnMotor, byte prevTurnMotorVal){//motoru darbināšanas funkcija
      switch (mainMotor)
      {
      case 0:
        digitalWrite(mainMotorMinus, LOW);
        digitalWrite(mainMotorPlus, LOW);
      break;
      case 1:
        digitalWrite(mainMotorPlus, HIGH);
        digitalWrite(mainMotorMinus, LOW);
      break;
      case 2:
        digitalWrite(mainMotorMinus, HIGH);
        digitalWrite(mainMotorPlus, LOW);
      break;
      }
      switch (turnMotor)
      {
      case 0://jāstāv vidū
        if(prevTurnMotorVal == 1){
          turnFromLeftToMid();
        } else if (prevTurnMotorVal == 2){
          turnFromRightToMid();
        }
        digitalWrite(turnMotorPlus, LOW);
        digitalWrite(turnMotorMinus, LOW);
      break;
      case 1://kreisi
        digitalWrite(turnMotorPlus, LOW);
        digitalWrite(turnMotorMinus, HIGH);
      break;
      case 2://labi
        digitalWrite(turnMotorPlus, HIGH);
        digitalWrite(turnMotorMinus, LOW);
      break;
      }
    }
      void turnFromLeftToMid(){//atgriež pagrieziena motoru uz vidu
        digitalWrite(turnMotorPlus, HIGH);
        digitalWrite(turnMotorMinus, LOW);
        delay(100);
        digitalWrite(turnMotorPlus, LOW);
        digitalWrite(turnMotorMinus, LOW);
      }
      void turnFromRightToMid(){//atgriež pagrieziena motoru uz vidu 
        digitalWrite(turnMotorPlus, LOW);
        digitalWrite(turnMotorMinus, HIGH);
        delay(100);
        digitalWrite(turnMotorPlus, LOW);
        digitalWrite(turnMotorMinus, LOW);
      }
};

class gyroData {//sprieguma nolasīšanas un žiroskopa klase
  public:
    int deltaAnl[3];
    unsigned long oldTimeInt = millis();

    void setup() {
      pinMode(voltagePin, INPUT);
    }

    void loop() {
      
    }

    byte readAcc(){//šo funkciju ir jāpārveido atbilstoši žiroskopam, bet princips paliek tas pats
      if(millis()-oldTimeInt >= 1000){
        oldTimeInt = millis();
        deltaAnl[2] = deltaAnl[1];
        deltaAnl[1] = deltaAnl[0];
        deltaAnl[0] = analogRead(voltagePin);
        for(int i = 2; i>0; i--){
          if(deltaAnl[i-1]-deltaAnl[i]>500){//ja accelerometram pirmās vērtības ir lielas, tad salīdzināšana ar citām šūnām neizdosies, jo tās sākumā ir 0
            Serial.println("<!>");
            return 2;
          }
        }
      }
      return 0;
    }

    byte readVoltage(){//nolasa baterijas spriegumu
      return map(analogRead(voltagePin), 777/*analogā vērtība no sprieguma dalītāja, lai 4,5V būtu nulle*/, 1023, 0, 100);
    }

};

BTdata BTdata;//tiek inicializētas klases
carLights carLights;
carControl carControl;
gyroData gyroData;
audioVcc audioVcc;

void setup() {
  BTdata.setup();
  carLights.setup();
  carControl.setup();
  gyroData.setup();
}

void loop() {
  BTdata.loop();
  carControl.driveCar(BTdata.activeValues[0], BTdata.activeValues[1], BTdata.prevActiveValues[1]);//iedarbina mašīnītes motorus
  BTdata.prevActiveValues[1] = 0;//seto iepriekšējo pagrieziena motora vērtību uz nulli, lai pagrieziens atpakaļ izpildītos tikai vienreiz
  carLights.turnLights(BTdata.activeValues[2]);//mašīnītes gaismas
  if(BTdata.activeValues[2] == 3){//sākumā gaismiņas iemirgojas un lai tas tā nebūtu līdz nākamajai datu iesūtīšanai, par to atbildīgā vērtība tiek mainīta šeit
    BTdata.activeValues[2] = 1;
  }
  if(gyroData.readAcc()>0 || BTdata.activeValues[3]>0){//iedarbina signalizāciju, ja ir atbilstoši accelerometra lasījumi vai arī tiek manuāli iesūtīta
    audioVcc.vccState = true;
    BTdata.activeValues[3] = 1;
  } else if(BTdata.activeValues[3] == 0){
    audioVcc.vccState = false;
  }
  if(BTdata.activeValues[4] == 1){//izsūta datus , ja tie tiek pieprasīti
    BTdata.activeValues[4] = 0;
    if(gyroData.readVoltage()>=100){
      Serial.println("<100>");
    } else if (gyroData.readVoltage()>=10){
      Serial.print("<0");
      Serial.print(gyroData.readVoltage());
      Serial.println(">");
    } else if (gyroData.readVoltage()<10){
      Serial.print("<00");
      Serial.println(gyroData.readVoltage());
      Serial.println(">");
    }
  }
  audioVcc.loop();
}

/*

<[0 vai 1, on vai off, viencipara][kurai daļai jāstrādā, viencipara]>
////////////////<00> //mašīnīte divreiz pamirgo ar lukturiem norādot, ka ir savienojums ar serveri//////////////////
<01> //mašīnīte brauc uz priekšu
<02> //mašīnīte brauc atpakaļ
<00> //mašīnīte stāv

<10> //mašīnīte atgriežas sākuma stāvoklī>
<11>//mašīnīte pagriežās pa kreisi
<12>//mašīnīte pagriežās pa labi

<20>// tiek izslēgtas abas gaismas
<21>//tiek ieslēgtas priekšējās gaismas
<22>//tiek ieslēgtas aizmugurējās gaismas


<30>//nekas netiek atskaņots
<31>//tiek atskaņota signalizācija


<41>//tiek pieprasīti dati no mašīnītes (optional)


Ja no mašīnas MPU paatrinājums Z asij paliek lielāks par 26k, tad jāceļ trauksme Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));

*/
