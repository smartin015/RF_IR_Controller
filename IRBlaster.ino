#define arrLength 200
int flag = 0;
int temp[arrLength];

#define IRledPin 4
boolean arr = false;
void setup_IR() {
  pinMode(IRledPin, OUTPUT);
  digitalWrite(IRledPin, LOW);
}

void IR_push(int val) {
  // TODO: Error?
  temp[flag++] = val;
}

void IR_reset() {
  flag = 0; 
}

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
     
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void IR_send() {
  for (int i = 0; i < sizeof(temp) - 1; i++){
    if (i%2 == 0) {
      pulseIR((int)temp[i]);
    }
    else
    {
      delayMicroseconds((int)temp[i]);
    }
  }
  Serial.println("SENT IR");
}
