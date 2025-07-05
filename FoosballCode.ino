// Сегментите: A, B, C, D, E, F, G
int segmentPins[] = {3, 4, 5, 6, 7, 8, 9};

// Бутон на пин 2
const int buttonPin = 2;

int score = 0;
bool lastButtonState = HIGH;  // с INPUT_PULLUP, неактивно е HIGH

// Цифри за общ катоден 7-сегментен дисплей
const byte digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {
  // Пинове за 7-сегментен дисплей
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Бутон
  pinMode(buttonPin, INPUT_PULLUP); // без външен резистор
  displayDigit(score); // започваме от 0
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  // Засичане на преход от HIGH → LOW (бутон натиснат)
  if (lastButtonState == HIGH && currentState == LOW) {
    score++;
    if (score > 9) score = 0;
    displayDigit(score);
    delay(250); // debounce
  }

  lastButtonState = currentState;
}

// Функция за показване на цифра
void displayDigit(int number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[number][i]);
  }
}
