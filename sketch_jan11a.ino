#include <IRremote.h>


int IR_Recv = 2;   
int redPin = 9;
int Intensitate = 0;    
int fadeAmount = 25.6;
bool mod_manual;


IRrecv irrecv(IR_Recv);
decode_results results;

void reglare_automatica() {
    
  int lightVal = analogRead(A0);
  Serial.println(lightVal);
  delay(250);
  if (lightVal > 25){
    digitalWrite(redPin, LOW);  //Turn led off
  }
  else{
    digitalWrite(redPin, HIGH); //Turn led on
  }
}

void preluare_semnal() {
    if (irrecv.decode(&results)){
    long int decCode = results.value;
    Serial.println(results.value);
    //switch case to use the selected remote control button
    switch (results.value){
      case 551486205:
      analogWrite(9, Intensitate);   
        Intensitate = Intensitate + fadeAmount;
        if (Intensitate == 0 || Intensitate == 80) {
        }    
        Serial.println("====== adaug ======");
        Serial.println(Intensitate);
        Serial.println("===================");
        break;   
      case 551542815: 
        analogWrite(9, Intensitate);   
        Intensitate = Intensitate - fadeAmount;
        if (Intensitate == 0 || Intensitate == 80) {
        }    
        Serial.println("===== scad ======");
        Serial.println(Intensitate);
        Serial.println("==================="); 
        break;
        }
    irrecv.resume(); // Receives the next value from the button you press
  }
}

 
void setup(){
  mod_manual = false;
  Serial.begin(9600);  
  irrecv.enableIRIn(); // Starts the receiver
}
 
void loop() {
      if (irrecv.decode(&results)){
    long int decCode = results.value;
    Serial.println(results.value);
    //switch case to use the selected remote control button
    switch (results.value){
      case 551518845:
        if (mod_manual == false) {
          mod_manual = true;
          Intensitate = 0;
        }
        else if (mod_manual == true) {
          mod_manual = false;
          Intensitate = 0;
        }
        Serial.println("============modul sa schimbat===========");
        Serial.println(mod_manual);
        Serial.println("==================="); 
        break;
        }
    irrecv.resume(); // Receives the next value from the button you press
  }
  
  if (mod_manual == true) {
  preluare_semnal();
  }
  else if (mod_manual == false) {
  reglare_automatica();
  }
}
