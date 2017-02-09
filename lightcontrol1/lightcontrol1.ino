int buttonPin = 2;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int knobPin = A0;

int red = 255;
int green = 255;
int blue = 255;

int knobValue = 0;
int outputValue = 0;
int buttonState = HIGH;
int prevbtnState = LOW;
int lightState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(knobPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  //read button value
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
  } else {
    int currentVal = analogRead(knobPin);
    Serial.print("value: ");
    Serial.println(currentVal);
    int mapped = map(currentVal, 0, 1023, 0, 255);
    Serial.print("mapped val: ");
    Serial.println(mapped);
    setColor(mapped, 0, 0);
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
