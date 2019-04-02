/* 
Omar Vallejo
Programming Assignment 1
1/5/18
*/
   

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9
const int button=7;       //button assigned to pin 7

//Variables
int prValue;          // Store value from photoresistor (0-1023)
int bValue;           //Store value from button


void setup(){
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT); // Set pResistor - A0 pin as an input (optional)
 pinMode(button, INPUT);  //set button as input 
}

void loop(){
  prValue = analogRead(pResistor);  //allows the Aguino Board to read values
  bValue = digitalRead(button);

  //if the button isn't being held down, test for light sensitivity
  if(bValue==0){
    buttonPOWER();
  }
  else{  
    pResistorPOWER(prValue);
  }

  //Print values
  Serial.println("Button Value:" + bValue);
  Serial.println("Photoresistor Value:" + prValue);
  delay(1500);

}
  /*
   * classes for organization
   *
   */
  
  //button function which makes light come on when held down. 
  void buttonPOWER(){
    digitalWrite(ledPin, HIGH); //Turn led on
  }

   //light sensor function which makes light come on during low lighting. 
  void pResistorPOWER(int prValue){
    if(prValue>300){
      digitalWrite(ledPin, LOW);   //LED off   
    }
    else{
      digitalWrite(ledPin, HIGH); //LED on
      
    }
  }
  
  

