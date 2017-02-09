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

//A3 connects to brightness
int brightPin = A4;

int red = 255;
int green = 255;
int blue = 255;
int brightness = 0;

int knob1Value = 0;
int knob2Value = 0;
int knob3Value = 0;
int brightValue = 0;
int buttonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(knob1Pin, INPUT);
  pinMode(knob2Pin, INPUT);
  pinMode(knob3Pin, INPUT);
  pinMode(brightPin, INPUT);

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
    //read values from three knobs
    int blueVal = analogRead(knob1Pin);
    int greenVal = analogRead(knob2Pin);
    int redVal = analogRead(knob3Pin);
    int brightVal = analogRead(brightPin);
    Serial.print("Brightness: ");
    Serial.println(brightVal);
    int mappedBlue = map(blueVal, 0, 1023, 0, 255);
    int mappedRed = map(redVal, 0, 1023, 0, 255);
    int mappedGreen = map(greenVal, 0, 1023, 0, 255);
    int mappedbright = map(brightVal, 0, 1023, 0, 255);
    float bright = mappedbright * 0.01;
    Serial.print("mapped blue: ");
    Serial.println(mappedBlue);
    Serial.print("mapped bright: ");
    Serial.println(mappedbright);
    displaywithbright(mappedbright, mappedRed, mappedGreen, mappedBlue);
    //    Serial.print("final blue: ");
    //    Serial.println(finalBlue);
    //    Serial.print("final red: ");
    //    Serial.println(finalRed);
    //    Serial.print("final green: ");
    //    Serial.println(finalGreen);
    //    setColor(finalRed, finalBlue, finalGreen);
    delay(30);
  }
}

//
void setColor(int red, int green, int blue)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

//for brightness
void displaywithbright(int l, int red, int green, int blue) {
  int col[3] = {red, green, blue};
  getRGB(255, 255, l, col);
  setColor(red - col[0], green - col[1], blue - col[2]);
}


//Nan introduced this code to me
//credit to http://log.liminastudio.com/itp/physical-computing/arduino-controlling-an-rgb-led-by-hue
void getRGB(int hue, int sat, int val, int colors[3]) {
  // hue: 0-259, sat: 0-255, val (lightness): 0-255
  int r, g, b, base;

  if (sat == 0) { // Achromatic color (gray).
    colors[0] = val;
    colors[1] = val;
    colors[2] = val;
  } else  {
    base = ((255 - sat) * val) >> 8;
    switch (hue / 60) {
      case 0:
        r = val;
        g = (((val - base) * hue) / 60) + base;
        b = base;
        break;
      case 1:
        r = (((val - base) * (60 - (hue % 60))) / 60) + base;
        g = val;
        b = base;
        break;
      case 2:
        r = base;
        g = val;
        b = (((val - base) * (hue % 60)) / 60) + base;
        break;
      case 3:
        r = base;
        g = (((val - base) * (60 - (hue % 60))) / 60) + base;
        b = val;
        break;
      case 4:
        r = (((val - base) * (hue % 60)) / 60) + base;
        g = base;
        b = val;
        break;
      case 5:
        r = val;
        g = base;
        b = (((val - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }
    colors[0] = r;
    colors[1] = g;
    colors[2] = b;
  }
}
