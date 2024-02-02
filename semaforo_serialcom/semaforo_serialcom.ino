#define red_pin1 11
#define yellow_pin1 10
#define green_pin1 9
#define red_pin2 4
#define yellow_pin2 3
#define green_pin2 2

int pins[6] = {2, 3, 4, 9, 10, 11};

bool ledState;
String state;

void setup() {

  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
  }

  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }

}

void setLED_combination() {
  for (int i = 0; i < 6; i++) {
    if (state[i] == '0') {
      ledState = 0;
    }
    if (state[i] == '1'){
      ledState = 1;
    }
    digitalWrite(pins[i], ledState);
  }
}

void loop() {

  if (Serial.available() > 0) {
    state = Serial.readStringUntil('#');
  }

  setLED_combination();

}
