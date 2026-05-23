const int pinX = 34;
const int pinY = 35;

const int btnColor = 26;
const int btnReset = 27;

bool lastBtnColor = HIGH;
bool lastBtnReset = HIGH;

void setup() {

  Serial.begin(115200);

  analogReadResolution(12);

  pinMode(btnColor, INPUT_PULLUP);
  pinMode(btnReset, INPUT_PULLUP);
}

void loop() {

  // =========================
  // JOYSTICK
  // =========================

  int x = analogRead(pinX);
  int y = analogRead(pinY);

  float normX = (x - 2048) / 2048.0;
  float normY = (y - 2048) / 2048.0;

  normX = constrain(normX, -1.0, 1.0);
  normY = constrain(normY, -1.0, 1.0);

  // =========================
  // BOTONES
  // =========================

  bool currentBtnColor = digitalRead(btnColor);
  bool currentBtnReset = digitalRead(btnReset);

  bool colorPressed = false;
  bool resetPressed = false;

  // Detectar flanco
  if (lastBtnColor == HIGH && currentBtnColor == LOW) {
    colorPressed = true;
  }

  if (lastBtnReset == HIGH && currentBtnReset == LOW) {
    resetPressed = true;
  }

  lastBtnColor = currentBtnColor;
  lastBtnReset = currentBtnReset;

  // =========================
  // JSON
  // =========================

  Serial.print("{");

  Serial.print("\"x\":");
  Serial.print(normX, 3);

  Serial.print(",");

  Serial.print("\"y\":");
  Serial.print(normY, 3);

  Serial.print(",");

  Serial.print("\"color\":");
  Serial.print(colorPressed ? 1 : 0);

  Serial.print(",");

  Serial.print("\"reset\":");
  Serial.print(resetPressed ? 1 : 0);

  Serial.println("}");

  delay(16);
}