/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

int count_con = 7;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //Serial.read()
    for (int i = 2; i <= 12; i++) {//using pin2-pin12
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);
  }
}

// the loop routine runs over and over again forever:
void loop() {
 
  
  for (int i = 1; i <= count_con; i++) {
 
    digitalWrite(i+1, LOW); //relay on starting  from pin2
    
    delay(5000);
    
    float sensorValue = analogRead(A0);
    //Serial.println(sensorValue);
 
    float voltage = sensorValue / 204 ; //round 204,6
    //Serial.println(voltage);

    float mg_l_v =  8.02 * voltage  - 7.49; //R=234
   
    Serial.print(i);
    Serial.print(';');
    Serial.println(mg_l_v);   
    delay(2000);

    digitalWrite(i+1, HIGH); //relay off
     if (Serial.available() > 0) {
    char incoming = Serial.parseInt();
    
    count_con = incoming;
    break;
    } 
    //if (i == count_con) i = 1; // оказалось, что и без нее все работает
  }
  
  
}
