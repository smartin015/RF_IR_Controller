#define arrLength 200
int flag = 0;
int temp[arrLength];

#define IRledPin 3
boolean arr = false;
void setup_IR() {
  pinMode(IRledPin, OUTPUT);
  digitalWrite(IRledPin, LOW);
}

void IR_test() {
  digitalWrite(IRledPin, HIGH);
  delay(1000);
  digitalWrite(IRledPin, LOW);
}

void IR_push(int val) {
  temp[flag++] = val;
}

void IR_reset() {
  flag = 0; 
}

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 11 microseconds to happen
   delayMicroseconds(3);
   //digitalWrite(IRledPin, HIGH);
   //delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 11 microseconds
   delayMicroseconds(3);
   //digitalWrite(IRledPin, LOW);
   //delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
}

void delayIR(long microsecs) {
  delayMicroseconds(microsecs);
}
 
void IR_send(int ntimes) {
  cli();
  for (int j = 0; j < ntimes; j++) {
    for (int i = 0; i < flag; i++){
      if (i%2 == 0) {
        pulseIR(temp[i]);
      }  else {
        delayIR(temp[i]);
      }
    }
  }
  sei();
}
