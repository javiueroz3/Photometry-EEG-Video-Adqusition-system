/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ssd1306 - Version: 1.8.3


/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
#define outputA 2
#define outputB 3
#define outputC 4
#define outputD 5
#define outputE 6
#define outputF 7
#define piezoPin 8
#define BUTTON_PIN 12

//#define ButtonA 13
//#define ButtonA 9
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//const int BUTTON_PIN = 12; 

//int piezoPin = 8;
 int counter = 0;
 //float z =0;
 int countery = 0;
 //float y =0;
 int counterx = 0;
 //float x =0;
 int aState;
 int aLastState;
 int cState;
 int cLastState;
 int eState;
 int eLastState;
 int ResetState;
// int BUTTON_PIN;
 int ledState = LOW;        // tracks the current state of LED
int lastButtonState;        // the previous state of button
int currentButtonState; // the current state of button
 
int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;// variable to store the value coming from the sensor
int sensorValueAvg = 0;
int sensorValueAvg2 = 0;
int cicleCounter =0;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(9600);
    // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode (outputA,INPUT_PULLUP);
   pinMode (outputB,INPUT_PULLUP);
   pinMode (outputC,INPUT_PULLUP);
   pinMode (outputD,INPUT_PULLUP);
   pinMode (outputE,INPUT_PULLUP);
   pinMode (outputF,INPUT_PULLUP);

   //pinMode(LED_PIN, OUTPUT);
   pinMode(BUTTON_PIN, INPUT_PULLUP);
   //pinMode (ButtonA,INPUT);
   
  // Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);
   cLastState = digitalRead(outputC);
   eLastState = digitalRead(outputE); 
   //buttonLastState =  digitalRead(BUTTON_PIN);
   currentButtonState = digitalRead(BUTTON_PIN);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println(" System On");
  display.display(); 
  delay(2000);
}

void loop() { 
 display.clearDisplay();   


///////////// Conduct measure //////////
  //if(cicleCounter = 4){
  sensorValue = analogRead(A0);
  //sensorValueAvg = ((sensorValue+ sensorValueAvg)/2) ;
  //sensorValueAvg2 = ((sensorValueAvg2+ sensorValueAvg)/2);
  //cicleCounter = 0;
  //}
  //cicleCounter ++;
  
  lastButtonState    = currentButtonState;                // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state
  //Serial.print("The button state: ");
  //Serial.print(currentButtonState);
  
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");
  
    // toggle state of LED
    if(ledState == LOW) {
       ledState = HIGH;  
       digitalWrite(LED_BUILTIN, HIGH);
       //Serial.println("Turning LED on");
       
    }
    else {
      ledState = LOW;
      digitalWrite(LED_BUILTIN, LOW);
      //Serial.println("Turning LED off");
    }
 
    // control LED arccoding to the toggled state
    //digitalWrite(piezoPin, ledState);  //turns the LED on or off based on the variable
  }
  if(ledState== HIGH && sensorValue > 10){ 
        //Serial.println("Turning PIEZO on");
        //digitalWrite(piezoPin, HIGH);
        
        tone(piezoPin, 5000, 10);
        }

  
////////Stereo sensors///////////////////
  
  ////Position Sensor 1  
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   //ResetState = digitalRead(ButtonA);
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   //if (ResetState == true) { counter = 0;}
  if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
       counter ++;
    } else {
      counter --;
     }
      
  }
  aLastState = aState; // Updates the previous state of the outputA with the current state

  //Serial.print("Position Z: ");
  //Serial.print(counter*.1250);
  ////Position Sensor 2  
  cState = digitalRead(outputC); // Reads the "current" state of the outputA
   //ResetState = digitalRead(ButtonA);
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  //if (ResetState == true) { counter = 0;}
  if (cState != cLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputD) != cState) { 
      countery ++;
    } else {
      countery --;
    }
    
  }
  cLastState = cState;
  //Serial.print("Position y: ");
  //Serial.print(countery*.1250);
  ////Position Sensor 3  
  eState = digitalRead(outputE); // Reads the "current" state of the outputA
   //ResetState = digitalRead(ButtonA);
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   //if (ResetState == true) { counter = 0;}
  if (eState != eLastState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputF) != eState) { 
       counterx ++;
     } else {
       counterx --;
     }
     
  }
  eLastState = eState;
  Serial.print("X, ");
  Serial.print(counter*.1250, 3);
  Serial.print(", Z, ");
  Serial.print(countery*(.04545), 4);
  Serial.print(", Y, ");
  Serial.print(counterx*.1250, 3);
  Serial.print(", Con, ");
  Serial.print(sensorValue);
  Serial.print(",");
  
 ///////////// Display  //////////////////////////////////
// z= counter*.1250;
 //y= countery*.1250; 
 //x= counterx*.1250; 

 display.setTextSize(2);
 display.setCursor(0,0);
 display.print((String)" Z:"+countery*(.04545));//counter*.125);
 display.setTextSize(2);
 display.setCursor(0,16);
 display.print((String)" Y:"+counter*.125);//+countery*(.004545));
 display.setTextSize(1);
 display.print("  mm");
 display.setTextSize(2);
 display.setCursor(0,34);
 display.print((String)" X:"+counterx*.125);
 display.setCursor(0,50);
 display.print((String)" Con:"+sensorValue);
      
     //display.println();
 display.display();
     //Serial.print("Position: ");
     Serial.println(counter*.1250);
     //digitalWrite(piezoPin, LOW);
  // } 

  

}
