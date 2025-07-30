String readvoice;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int a=0;
int b=0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 
void setup() {
  
 
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight

}
//-----------------------------------------------------------------------//  
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readvoice.length() > 0) {
    Serial.println(readvoice); 
  if (readvoice == "*start#"){
    
    lcd.setCursor(1, 0);
    lcd.print(" CHAIR IS STARTED ");
    delay (3000);
    lcd.clear();


    lcd.setCursor(1, 0);
    lcd.print("PLEASE ENSURE  ");
    lcd.setCursor(2, 1);
    lcd.print(" SAFETY FIRST");
    delay(5000);
    lcd.clear();

 
    lcd.setCursor(1,0);
    lcd.print(" COMMAND ME ");
    delay(3000);
    lcd.clear();



    a=1;
    
  }
  if((readvoice == "*start#") && (a==1))
  {
    lcd.setCursor(1, 0);
    lcd.print("ALREADY STARTED");
    delay (3000);
    lcd.clear();
  } 
  if (readvoice == "*switch off#"){
    a=0;

  }
  if((readvoice == "*go#") && (a==1))
  {
    digitalWrite(6, HIGH);
    digitalWrite (4, HIGH);
    digitalWrite(5,LOW);
    digitalWrite(3,LOW);
    lcd.setCursor(1, 0);
    lcd.print("  LET'S GO ");
 
    delay (2000);
    lcd.clear();
  } 
  else if((readvoice == "*forward#") && (a==1))
  {
    digitalWrite(6, HIGH);
    digitalWrite (4, HIGH);
    digitalWrite(5,LOW);
    digitalWrite(3,LOW);
    lcd.setCursor(1, 0);
    lcd.print(" FORWARD ");
    delay(1000);
    digitalWrite(6, LOW);
    digitalWrite (4, LOW);
    delay (1000);
    lcd.clear();
    
    
  } 
  
  

  else if((readvoice == "*back#") && (a==1))
  {
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
    lcd.setCursor(1, 0);
    lcd.print(" BACK ");
    delay(1000);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    lcd.clear();

  }
  else if((readvoice == "*turn back#") && (a==1))
  {
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    digitalWrite(3,HIGH);
    delay (2000);
    digitalWrite(5,LOW);
    digitalWrite(3,LOW);

    lcd.setCursor(1, 0);
    lcd.print("TURNING BACK ");
    delay (2000);
    lcd.clear();
  }
  
  else if ((readvoice == "*left#") && (a==1))
  {
    digitalWrite (6,HIGH);
    digitalWrite (5,LOW);
    digitalWrite (4,LOW);
    digitalWrite (3,LOW);
    lcd.setCursor(1, 0);
    lcd.print("TURNING LEFT ");
    delay (750);
    digitalWrite (6,LOW);
    delay (1000);
    lcd.clear();
     
    
  }
    
 else if (( readvoice == "*right#") && (a==1))
 {
   digitalWrite (6, LOW);
   digitalWrite (5, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (3, LOW);
   lcd.setCursor(1, 0);
   lcd.print("TURNING RIGHT");
   delay (750);
   digitalWrite (4, LOW);
   delay (1000);
   lcd.clear();
 }
 
 else if (((readvoice == "*left bend#")|| (readvoice == "*left band#") || (readvoice == "*left bent#")||(readvoice == "*lift bent#")||(readvoice == "*left belt#")||(readvoice == "*lift belt#")) && (a==1))
 {
   digitalWrite (6, HIGH);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (3, LOW);
   lcd.setCursor(1, 0);
   lcd.print("LEFT  BEND "); 
   delay (500);
   digitalWrite (6,LOW);
   delay (1000);
   lcd.clear();
    
 }
 else if (((readvoice == "*right bend#")|| (readvoice == "*right band#")||(readvoice == "*right bent#"))&&(a==1))
 {
   digitalWrite (6, LOW);
   digitalWrite (4, HIGH);
   digitalWrite (3, LOW);
   digitalWrite (5, LOW);
   lcd.setCursor(1, 0);
   lcd.print("RIGHT BEND");
   lcd.clear();
   delay (500);

   digitalWrite (4,LOW);
   delay (1000);
   lcd.clear();
    
 }

 else if ((readvoice == "*stop#")|| (readvoice == "*top#"))
 {
   digitalWrite (6, LOW);
   digitalWrite (5, LOW);
   digitalWrite (4, LOW);
   digitalWrite (3, LOW);
 
   if (a==1){
    lcd.setCursor(1, 0);
    lcd.print("STOPPED");
    delay(2000);
    lcd.clear();


   }
   if(a==0) {
    lcd.setCursor(1, 0);
    lcd.print("ALREADY STOPPED");
    delay(2000);
    lcd.clear();
     
   }
 }
 if((readvoice == "*hello#") && (a==1))
 {
   lcd.setCursor(1, 0);
   lcd.print(" HI WHAT's UP ");
   
   delay (3000);
   lcd.clear();
   lcd.setCursor(1, 0);
   lcd.print("TAKE YOUR SEAT");
   delay (3000);
   lcd.clear();
   b=1;
 }

 if((readvoice == "*what is your name#") && (b==1))
 {
   lcd.setCursor(1, 0);
   lcd.print("  AI CHAIR");
   delay (3000);
   lcd.clear();
    
 }
 if((readvoice == "*who made you#") && (b==1))
 {
   lcd.setCursor(1, 0);
   lcd.print(" INVENTED BY ");
   delay (2000);
   lcd.clear();
   lcd.print(" Mr  CHINU ");
   delay (3000);
   lcd.clear();
 }
 if((readvoice == "*today is#") && (b==1))
 {
   lcd.setCursor(1, 0);
   lcd.print(" WEDNESDAY ");
   delay (2000);
   lcd.clear();
 }
 if((readvoice == "*date#") && (b==1))
 {
  lcd.setCursor(1,0);
  lcd.print("17/04/2024");
  delay (2000);
  lcd.clear();
 }
 if((readvoice == "*thank you#") && (a==1))
 {
   lcd.setCursor(1, 0);
   lcd.print(" WELCOME !");
   
   delay (3000);
   lcd.clear();
   lcd.setCursor(1, 0);
   lcd.print("HAVE A GOOD DAY");
   delay (3000);
   lcd.clear();
   b=0;
 }
   

 }} //Reset the variable