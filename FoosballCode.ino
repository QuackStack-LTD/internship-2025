// Свързване според твоята конфигурация:
// 1 2 (3 e GND) 4 5 6 7 (8 e GND) 9 10 → D2 D3 D4 D5 D6 D7 D8 D9

const int segmentPins[8] = {
  2, // gore nai lqvo D2
  3, // gore vtoro nai lqvo D3
  4, // gore vtoro nai dqsno D4
  5, // gore nai dqsno D5
  6, // dolu nai dqsno D6
  7, // dolu vtoro nai dqsno D7
  8, // dolu vtoro nai lqvo D8
  9  // dolu nai lqvo D9
};

const byte digits[10][8] = {
  {0,1,1,1,1,1,1,1}, // 0
  {0,0,0,1,0,1,0,0}, // 1
  {1,0,1,1,1,0,1,1}, // 2
  {1,0,1,1,1,1,1,0}, // 3
  {1,1,0,1,1,1,0,0}, // 4
  {1,1,1,0,1,1,1,0}, // 5
  {1,1,1,0,1,1,1,1}, // 6
  {0,0,1,1,1,1,0,0}, // 7
  {1,1,1,1,1,1,1,1}, // 8
  {1,1,1,1,1,1,1,0}  // 9
};

const int sensorPin = A0;
const int triggerThreshold = 800;   // Над тази стойност се смята за прекъснат лъч
const int resetThreshold = 750;     // Под тази стойност се разрешава следващ гол
const int cooldown = 6000;          // минимално време между голове

int counter = 0;
bool beamBroken = false;
unsigned long lastTriggerTime = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  unsigned long currentTime = millis();

  if (sensorValue > triggerThreshold && !beamBroken && 
      (currentTime - lastTriggerTime > cooldown)) {
    counter++;
    if (counter > 9) counter = 0;
    beamBroken = true;
    lastTriggerTime = currentTime;
  }

  // Ако обектът вече не прекъсва лъча → разреши ново броене
  if (sensorValue < resetThreshold) {
    beamBroken = false;
  }

  displayDigit(counter);
}

void displayDigit(int num) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}
