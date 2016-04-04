

#define echoPort1 7 // Echo Pin
#define trigPin1 8 // Trigger Pin
#define LEDPin1 6 // Onboard LED

#define echoPort2 13 // Echo Pin
#define trigPin2 12 // Trigger Pin
#define LEDPin2 9 // Onboard LED

int pass1 = 0;
unsigned int t1 =0;
int pass2 = 0;
unsigned int t2=0;
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
        Serial.println("1 Out of range");
        if(pass1==0){
            t1 = millis();
            pass1=1;

        }
        digitalWrite(LEDPin1, LOW); 
       }
    else{
           if (distance >= maximumRange || distance <= minimumRange){
           /* Send a negative number to computer and Turn LED ON 
           to indicate "out of range" */
           Serial.println("1");
           Serial.println(distance);
           digitalWrite(LEDPin1, HIGH); 
           }
           else {
           /* Send the distance to the computer using Serial protocol, and
           turn LED OFF to indicate successful reading. */
           Serial.println(distance);      
           if(pass1==0){
                      t1 = millis();
                      pass1=1;
          
                  }
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
        Serial.println("2 Out of range");
        if(pass2==0){
                      t2 = millis();
                      pass2=1;
         }
         digitalWrite(LEDPin2, LOW); 
       }
    else{
           if (distance >= maximumRange || distance <= minimumRange){
           /* Send a negative number to computer and Turn LED ON 
           to indicate "out of range" */
           Serial.println("2");
           Serial.println(distance);
           digitalWrite(LEDPin2, HIGH); 
           }
           else {
           Serial.println(distance);
           if(pass2==0){
                      t2 = millis();
                      pass2=1;
           }   
           digitalWrite(LEDPin2, LOW); 
           }
           
           //Delay 50ms before next reading.
           delay(200);         //delay after out of range - to be removed

         }

if(pass1==1 && pass2==1){
  passDuration = t1-t2;
  passDurationMod = abs(passDuration);
  
  if(passDurationMod>maxPassDuration || passDurationMod<minPassDuration){
    Serial.println("error");
  }
  else{
    if(passDuration > 0){
       Serial.println("positive");
    }
    else{
       Serial.println("negative"); 
    }
  }
  pass1=0;
  pass2=0;
  t1=0;
  t2=0;
}
  
         
}
