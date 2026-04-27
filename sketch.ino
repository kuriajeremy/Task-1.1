// Task1.1Lights_ON.ino
// SIT210 - Embedded Systems Development
// Description: Modular program to switch ON porch light (30s) and hallway light (60s)
// when a push button is pressed. Uses Arduino Nano 33 IoT.

// ─── PIN DEFINITIONS ────────────────────────────────────────────────────────
const int BUTTON_PIN  = 2;    // Push button input pin
const int PORCH_LED   = 4;    // Porch light LED
const int HALLWAY_LED = 5;    // Hallway light LED

// ─── TIMING CONSTANTS ───────────────────────────────────────────────────────
const unsigned long PORCH_DURATION   = 30000;  // 30 seconds in ms
const unsigned long HALLWAY_DURATION = 60000;  // 60 seconds in ms

// ─── STATE VARIABLES ────────────────────────────────────────────────────────
unsigned long porchStartTime   = 0;
unsigned long hallwayStartTime = 0;
bool porchActive   = false;
bool hallwayActive = false;
int  lastButtonState = HIGH;

// ─── SETUP ──────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  setupPins();
  Serial.println("System ready. Press button to activate lights.");
}

// ─── MAIN LOOP ──────────────────────────────────────────────────────────────
void loop() {
  checkButton();
  managePorchLight();
  manageHallwayLight();
}

// ─── MODULE: Pin Initialisation ─────────────────────────────────────────────
// Configures input and output pins
void setupPins() {
  pinMode(BUTTON_PIN,  INPUT_PULLUP);
  pinMode(PORCH_LED,   OUTPUT);
  pinMode(HALLWAY_LED, OUTPUT);
  digitalWrite(PORCH_LED,   LOW);
  digitalWrite(HALLWAY_LED, LOW);
}

// ─── MODULE: Button Detection ───────────────────────────────────────────────
// Detects a button press (falling edge) and triggers both lights
void checkButton() {
  int currentState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentState == LOW) {
    Serial.println("Button pressed — activating porch and hallway lights.");
    activateLights();
  }
  lastButtonState = currentState;
  delay(50); // debounce
}

// ─── MODULE: Light Activation ───────────────────────────────────────────────
// Turns both LEDs on and records start times
void activateLights() {
  unsigned long now = millis();
  digitalWrite(PORCH_LED,   HIGH);
  digitalWrite(HALLWAY_LED, HIGH);
  porchStartTime   = now;
  hallwayStartTime = now;
  porchActive   = true;
  hallwayActive = true;
  Serial.println("Porch light ON (30s) | Hallway light ON (60s)");
}

// ─── MODULE: Porch Light Timer ──────────────────────────────────────────────
// Turns off porch light after 30 seconds
void managePorchLight() {
  if (porchActive && (millis() - porchStartTime >= PORCH_DURATION)) {
    digitalWrite(PORCH_LED, LOW);
    porchActive = false;
    Serial.println("Porch light OFF.");
  }
}

// ─── MODULE: Hallway Light Timer ────────────────────────────────────────────
// Turns off hallway light after 60 seconds
void manageHallwayLight() {
  if (hallwayActive && (millis() - hallwayStartTime >= HALLWAY_DURATION)) {
    digitalWrite(HALLWAY_LED, LOW);
    hallwayActive = false;
    Serial.println("Hallway light OFF.");
  }
}
