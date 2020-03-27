  #include <Adafruit_GFX.h>
  #include <Adafruit_PCD8544.h>
  #include <OneWire.h>
  #include <DallasTemperature.h>
  #include <SPI.h>

  // Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);
  Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

  #define ONE_WIRE_BUS 7                 // Dallas temperature sensor on pin D7

  #define pwm 6
 
  OneWire oneWire(ONE_WIRE_BUS);
 
  DallasTemperature sensors(&oneWire);

  /////////////////////////////////////////////////////////////////////
  

  int NbTopsFan; int Calc;
 
//The pin location of the sensor
int hallsensor = 2; typedef struct{
 
//Defines the structure for multiple fans and 
//their dividers 
char fantype;
unsigned int fandiv; }fanspec;
 
//Definitions of the fans
//This is the varible used to select the fan and it's divider,
//set 1 for unipole hall effect sensor
//and 2 for bipole hall effect sensor
fanspec fanspace[3]={{0,1},{1,2},{2,8}}; char fan = 1;



 

  int ledpin1 = 5; //RED led
  int ledpin2 = 4; //GREEN led

  float tempC = 0;

  char TempCelciusFahrenheit[6];

  float tempF = 0;

  void rpm ()
  //This is the function that the interupt calls
  { NbTopsFan++; }


  void setup(){
    pinMode(hallsensor, INPUT);
  Serial.begin(9600);
  display.begin();
  delay(1000);
  display.clearDisplay(); // clears the screen and buffer
  display.display();
  display.setTextColor(BLACK);
  display.setContrast(50);
  analogWrite(pwm, 255);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  attachInterrupt(0, rpm, RISING);
  
  
  }

  void loop(){

  float tempC = 0;
  float tempF = 0;
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  tempF = sensors.toFahrenheit(tempC);

  int temp = tempC;
  
  display.clearDisplay();
  display.setContrast(50);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temp:");
  display.setTextSize(1);
  display.setCursor(30,0);
  display.print(tempC,2);
  display.print("*C");
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("RPM:");
  display.setTextSize(1);
  display.setCursor(25,10);
  display.print(Calc, DEC);
  

  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Cooling:");
  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("Speed:");

  NbTopsFan = 0;
 
//Enables interrupts
sei();
 
//Wait 1 second
delay (1000);
 
//Disable interrupts
cli();
 
//Times NbTopsFan (which is apprioxiamately the fequency the fan 
//is spinning at) by 60 seconds before dividing by the fan's divider
Calc = ((NbTopsFan * 60)/fanspace[fan].fandiv);


   //display.display();
    
    if(temp <24 )
    { 
      analogWrite(pwm,0);
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("OFF");
      display.setTextSize(1);
      display.setCursor(45,30);
      display.print("0%");
      digitalWrite(ledpin1, LOW);
      digitalWrite(ledpin2, HIGH);
      delay(100);
    }
    
   /* else if(temp==24)
    {
      analogWrite(pwm, 255);
      display.setTextSize(1);
      display.setCursor(40,30);
      display.print("20%");
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("ON");
      digitalWrite(ledpin1, HIGH);
      digitalWrite(ledpin2, LOW);
      delay(100);
    }*/
    
     else if(temp==24)
    {
      analogWrite(pwm, 255);
      display.setTextSize(1);
      display.setCursor(40,30);
      display.print("100%");
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("ON");
      digitalWrite(ledpin1, HIGH);
      digitalWrite(ledpin2, LOW);
      delay(100);
    }
    
     else if(temp==25)
    {
      analogWrite(pwm, 255);
      display.setTextSize(1);
      display.setCursor(40,30);
      display.print("100%");
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("ON");
      digitalWrite(ledpin1, HIGH);
      digitalWrite(ledpin2, LOW);
      delay(100);
    }
    
    else if(temp==26)
    {
      analogWrite(pwm, 255);
      display.setTextSize(1);
      display.setCursor(40,30);
      display.print("100%");
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("ON");
      digitalWrite(ledpin1, HIGH);
      digitalWrite(ledpin2, LOW);
      delay(100);
    }
     else if(temp>26)
    {
      analogWrite(pwm, 255);
      display.setTextSize(1);
      display.setCursor(40,30);
      display.print("100%");
      display.setTextSize(1);
      display.setCursor(50,20);
      display.print("ON");
      digitalWrite(ledpin1, HIGH);
      digitalWrite(ledpin2, LOW);
      delay(100);
    } 
    display.display();
    
  delay(1000);
  }

  
  
