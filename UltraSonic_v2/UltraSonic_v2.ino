/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 7 
 Trig to Arduino pin 8
 
 This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
 Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
 on 10 Nov 2012.
 */


#define echoPort 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 6 // Onboard LED

int maximumRange = 310; // Maximum range needed
int minimumRange = -1; // Minimum range needed
long pulseDuration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(5,OUTPUT);
 digitalWrite(5, LOW);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPort, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {// ... this is the reading loop
 
 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
    int tries = 0;
    do
    {
        pulseDuration = pulseIn( echoPort, HIGH, 50000);
        distance = 0.034 * pulseDuration / 2;
        if ( pulseDuration == 0 ) {
            delay(100);
            pinMode(echoPort, OUTPUT);
            digitalWrite(echoPort, LOW);
            delay(100);
            pinMode(echoPort, INPUT);
        }
    } while (pulseDuration == 0 && ++tries < 3);
    if (pulseDuration == 0)
       {
        Serial.println("Out of range");
        digitalWrite(LEDPin, LOW); 
        delay(200);


       }
    else{
           if (distance >= maximumRange || distance <= minimumRange){
           /* Send a negative number to computer and Turn LED ON 
           to indicate "out of range" */
           Serial.println(distance);
           digitalWrite(LEDPin, HIGH); 
           }
           else {
           /* Send the distance to the computer using Serial protocol, and
           turn LED OFF to indicate successful reading. */
           Serial.println(distance);
           digitalWrite(LEDPin, LOW); 
           delay(200);
           }
           
           //Delay 50ms before next reading.
           delay(50);
         }
}
