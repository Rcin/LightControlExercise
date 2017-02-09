int buttonPin = 2;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

//A0 connects to Red
int knob1Pin = A0;
//A1 connects to Blue
int knob2Pin = A1;
//A2 connects to Green
int knob3Pin = A2;

int red = 255;
int green = 255;
int blue = 255;

int knob1Value = 0;
int knob2Value = 0;
int knob3Value = 0;
int buttonState = HIGH;
int prevbtnState = LOW;
int lightState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(knob1Pin, INPUT);
  pinMode(knob2Pin, INPUT);
  pinMode(knob3Pin, INPUT);

  Serial.begin(9600);
}

void loop() {
  //read button value
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.print("Button: ");
    Serial.println(buttonState);
    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
  } else {
    int blueVal = analogRead(knob1Pin);
    int greenVal = analogRead(knob2Pin);
    int redVal = analogRead(knob3Pin);
    Serial.print("Blue value: ");
    Serial.println(blueVal);
    int mappedBlue = map(blueVal, 0, 1023, 0, 255);
    int mappedRed = map(redVal, 0, 1023, 0, 255);
    int mappedGreen = map(greenVal, 0, 1023, 0, 255);
    Serial.print("mapped val: ");
    Serial.println(mappedBlue);
    setColor(mappedRed, mappedBlue, mappedGreen);
    delay(30);
  }
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
