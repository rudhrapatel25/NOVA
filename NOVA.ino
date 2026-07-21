enum Mode
{
    STUDY,
    GAMING,
    NIGHT,
    IDLE
};

Mode currentMode = STUDY;

int brightness = 0;
int knobValue = 0;
bool lastButtonState = HIGH;

const int buttonPin = 10;
const int redPin = 3;
const int greenPin = 6;
const int bluePin = 9;
const int potPin = A0;


void updateRGB() {
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  switch (currentMode) {
    case STUDY:
      blueValue = brightness;
      break;

    case GAMING:
      redValue = brightness;
      break;

    case NIGHT:
      redValue = brightness / 6;
      blueValue = brightness;
      break;

    case IDLE:
      greenValue = brightness;
      break;
  }

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}



void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  knobValue = analogRead(potPin);
  brightness = map(knobValue, 0, 1023, 0, 255);
  
  //Button holding
  bool currentButtonState = digitalRead(buttonPin);
  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    currentMode = static_cast<Mode>((currentMode + 1) % 4);
    
    Serial.print("Mode = ");
    Serial.println(currentMode);
  }

  lastButtonState = currentButtonState;
  
  
 updateRGB();
  
  
}