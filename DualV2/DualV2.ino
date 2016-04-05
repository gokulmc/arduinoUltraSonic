

#define echoPort1 7 // Echo Pin
#define trigPin1 8 // Trigger Pin
#define LEDPin1 6 // Onboard LED

#define echoPort2 13 // Echo Pin
#define trigPin2 12 // Trigger Pin
#define LEDPin2 6 // Onboard LED

int p=0;
int pass1 = 0;
int pass2 = 0;
int state=0;
unsigned long passDuration,passDurationMod;
unsigned long maxPassDuration = 10000;
unsigned long minPassDuration=200;



int parked=0;
int maximumRange = 200; // Maximum range needed - to be changed
int minimumRange = 0; // Minimum range needed
long pulseDuration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(5,OUTPUT);
 digitalWrite(5, LOW);
 pinMode(10,OUTPUT);  //pin 5 and 10 are ground for LED outputs which display if +1 or -1
 digitalWrite(10, LOW);

 pinMode(trigPin1, OUTPUT);
 pinMode(echoPort1, INPUT);
 pinMode(LEDPin1, OUTPUT); // Use LED indicator (if required)
 
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPort2, INPUT);
 pinMode(LEDPin2, OUTPUT); // Use LED indicator (if required)
}

void loop() {// ... this is the reading loop
 
 
 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin1, LOW);
    int tries = 0;
    do
    {
        pulseDuration = pulseIn( echoPort1, HIGH, 50000);
        distance = 0.034 * pulseDuration / 2;
        if ( pulseDuration == 0 ) {
            delay(100);
            pinMode(echoPort1, OUTPUT);
            digitalWrite(echoPort1, LOW);
            delay(100);
            pinMode(echoPort1, INPUT);
        }
    } while (pulseDuration == 0 && ++tries < 3);
    if (pulseDuration == 0)
       {
//        Serial.println("1 Out of range");
        pass1=1;
        digitalWrite(LEDPin1, LOW); 
       }
    else{
           if (distance >= maximumRange || distance <= minimumRange){
           /* Send a negative number to computer and Turn LED ON 
           to indicate "out of range" */
//           Serial.println("1");
//           Serial.println(distance);
           digitalWrite(LEDPin1, HIGH); 
           pass1=0;
           }
           else {
           /* Send the distance to the computer using Serial protocol, and
           turn LED OFF to indicate successful reading. */
//           Serial.println(distance);      
           pass1=1;
           digitalWrite(LEDPin1, LOW); 
           }
           
           //Delay 50ms before next reading.
           delay(200);
         }


         
 digitalWrite(trigPin2, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin2, LOW);
    do
    {
        pulseDuration = pulseIn( echoPort2, HIGH, 50000);
        distance = 0.034 * pulseDuration / 2;
        if ( pulseDuration == 0 ) {
            delay(100);
            pinMode(echoPort2, OUTPUT);
            digitalWrite(echoPort2, LOW);
            delay(100);
            pinMode(echoPort2, INPUT);
        }
    } while (pulseDuration == 0 && ++tries < 3);
    if (pulseDuration == 0)
       {
//        Serial.println("2 Out of range");
        pass2=1;
         digitalWrite(LEDPin2, LOW); 
       }
    else{
           if (distance >= maximumRange || distance <= minimumRange){
           /* Send a negative number to computer and Turn LED ON 
           to indicate "out of range" */
//           Serial.println("2");
//           Serial.println(distance);
           digitalWrite(LEDPin2, HIGH); 
           pass2=0;
           }
           else {
//           Serial.println(distance);  
           pass2=1;
           digitalWrite(LEDPin2, LOW); 
           }
           
           //Delay 50ms before next reading.
           delay(200);         //delay after out of range - to be removed

         }

  switch (pass2*2 + pass1) {
    case 0: state =0;
           break;
    case 1: switch(state){
      case 0: state = 1; break;
      case 1: break;
      case 2: state=0; break;
      case 3: parked = parked +1; 
      Serial.println("parked + 1");  
      state = 1;
    break;
    } break;
    case 2: switch(state){
      case 0: state = 2; break;
      case 1: state=0; break;
      case 2: break;
      case 3:
      parked = parked -1;
      Serial.println("parked - 1");  
      state = 2;
      break;
    } break;
    case 3: state = 3; break;
  }
  Serial.println("State");
  Serial.println(state);  

}
