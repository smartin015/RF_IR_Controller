
#include "commands.h"

#define ERR_LED_PIN 13
void setup_ERR() {
  // Error LED indicates when error has occurred
  pinMode(ERR_LED_PIN, OUTPUT); 
  digitalWrite(ERR_LED_PIN, LOW);
}

void err(const char* ch) {
  Serial.println(ch);
  digitalWrite(ERR_LED_PIN, HIGH); 
  delay(100);
  digitalWrite(ERR_LED_PIN, LOW);
}

#define FET1_PIN 5
#define FET2_PIN 6
#define RELAY_PIN 4
void setup_SW() {
  // Setup switching (MOSFETs and relay)
  pinMode(FET1_PIN, OUTPUT);
  pinMode(FET2_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(FET1_PIN, LOW);
  digitalWrite(FET2_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

#define RF_ADDRESS "ctrl1"
void setup() {
  Serial.begin(9600);
  setup_IR();
  setup_SW();
  setup_RF(RF_ADDRESS);
  setup_ERR();
}

void loop() {
  rf_wait_for_cmd();
  switch (rf_cmd_type()) {
    case CMD_FET1:
      digitalWrite(FET1_PIN, rf_cmd_val());
      Serial.print("FET1 ");
      Serial.println(rf_cmd_val());
      break;
    case CMD_FET2:
      digitalWrite(FET2_PIN, rf_cmd_val());
      Serial.print("FET2 ");
      Serial.println(rf_cmd_val());
      break;
    case CMD_RELAY:
      digitalWrite(RELAY_PIN, rf_cmd_val());
      Serial.print("RELAY ");
      Serial.println(rf_cmd_val());
      break;
    case CMD_IR_BUFFER:
      IR_push(rf_cmd_val());
      break;
    case CMD_IR_SEND:
      IR_send(rf_cmd_val());
      Serial.println("IR SENT");
      break;
    case CMD_IR_RESET:
      IR_reset();
      Serial.println("IR RESET");
      break;
    case CMD_IR_TEST:
      Serial.println("IR TEST");
      IR_test();
      break;
    default:
      err("INVALID_CMD");
  }
  
  //rf_ack();
}
