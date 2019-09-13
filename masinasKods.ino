#define mainMotorPlus D11
#define mainMotorMinus D10
#define turnMotorPlus D9
#define turnMotorMinus D6
#define redDiodeOne D5
#define redDiodeTwo D4
#define whiteDiodeOne D3
#define whiteDiodeTwo D2
#define LMVcc D8
#define MPUInt D7
#define MPUScl A7
#define MPUSda A6

class BTdata {
  private:
      int countDataSwCase;//recvWithStartEndMarkers switch operatora skaitītājs
      static boolean recvInProgress = false;
      static byte ndx = 0;
      char startMarker = '<';
      char endMarker = '>';
      char rc;//šajā mainīgajā tiek saglabāts katrs ienākošais baits
      const byte numChars = 32;
      char receivedChars[numChars];
      int onValue;
      int mode;

  public:
    int activeValues[4];
    //active values paskaidrojums: {0,0,0,0}
    /*
    0. - mašīna brauc uz priekšu/atpakaļ (vērtības 0,1,2, kur 0 stāv, 1 uz priekšu, 2 atpakaļ)
    1. - mašīna pagriežas pa labi/pa kreisi (vērtības 0, 1, 2, kur 0 sākuma stāvoklis, 1 pa kreisi, 2 pa labi)
    2. - deg diodes (vērtības 0, 1, 2, kur 0 ir izslēgtas abas gaismas, 1, priekšējās, 2, aizmugurējās, 3, kopā abas puses)
    3. - tiek atskaņota signalizācija vai ieraksts (vērtības 0,1,2, kur 0 nekas netiek atskaņots, 1, tiek atskaņots ieraksts, 2 tiek atskaņota signalizācija)
    */ 

    void setup() {
      Serial.begin(9600);
      pinMode(LMVcc OUTPUT);
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
              
              default:
                break;
            }
            if (ndx >= numChars) {
              ndx = numChars - 1;
            }
          } else {
            receivedChars[sizeof(receivedChars)] = '\0'; // terminate the string, svarīga koda rindiņa, kur iepriekš [] iekšā bija ndx. Ndx patstāvīgi mainās, tāpēc bija nepieciešams ievietot citu garuma vērtību
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
    switch(mode){
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
        default:
        break;
    }
    }
};

class carLights {
  public:
    void setup() {
      pinMode(redDiodeOne, OUTPUT);
      pinMode(redDiodeTwo, OUTPUT);
      pinMode(whiteDiodeOne, OUTPUT);
      pinMode(whiteDiodeTwo, OUTPUT);
    }

    void loop() {

    }
};

class carControl {
  public:
    void setup() {
      pinMode(mainMotorPlus, OUTPUT);
      pinMode(mainMotorMinus, OUTPUT);
      pinMode(turnMotorPlus, OUTPUT);
      pinMode(turnMotorMinus, OUTPUT);
    }

    void loop() {

    }
};

class gyroData {
  public:
    void setup() {

    }

    void loop() {

    }
};



void setup() {

}

void loop() {

}

/*

Datu vadāmās mašīnītes darbības
1. Tiek saņemti dati no telefona caur rx un tie apstrādāti
2. Mašīnīte brauc visos četros virzienos
3. Mašīnīte apstājas braukt uz kādu konkrēto pusi kad tiek saņemts stop simbols
4. Mašīnīte nevar braukt uz abām pusēm vienlaicīgi
5. Mašīnīte beidz atskaņot ierakstu kad tiek iesūtītas ieraksta apstāšanās simbols
6. Mašīnītei ieslēdzoties divreiz iemirgojas un deg priekšējās un aizmugurējās diodes
7. Diožu stāvokli var mainīt
Realizācija
<[0 vai 1, on vai off, viencipara][kurai daļai jāstrādā, viencipara]>
<00> //mašīnīte divreiz pamirgo ar lukturiem norādot, ka ir savienojums ar serveri
<11> //mašīnīte brauc uz priekšu
<12> //mašīnīte brauc atpakaļ
<13>//mašīnīte pagriežās pa kreisi
<14>//mašīnīte pagriežās pa labi
<15>//tiek ieslēgtas priekšējās gaismas
<16>//tiek ieslēgtas aizmugurējās gaismas
<17>//tiek atskaņota signalizācija un mirgo gaismas
<08>//tiek pieprasīti dati no mašīnītes (optional)










*/