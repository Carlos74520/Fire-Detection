#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int usedPixels[64];
int counter = 0;
int middle = 0;
long duration;
int distance;

#define pwmL 3 // Motor pins
#define dirL 2
#define pwmR 6
#define dirR 12
#define echoPin 7 //range sensor pins
#define trigPin 5

void setup() {
  pinMode(pwmL, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(pwmR, OUTPUT);
  pinMode(dirR, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting");
  delay(50);

  bool status;
  status = amg.begin();
}

void left(int power = 100) {
  /* FOR NOW, TURNING A DIRECTION JUST MEANS ACTIVATING ONE MOTOR
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
  analogWrite(pwmL, 100);
  analogWrite(pwmR, 100);*/
  digitalWrite(dirR, HIGH);
  digitalWrite(dirL, HIGH);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, power);
}

void right(int power = 100) {
  /* FOR NOW, TURNING A DIRECTION JUST MEANS ACTIVATING ONE MOTOR
  digitalWrite(dirL, HIGH); //make left motor fowards
  digitalWrite(dirR, LOW); // made right motor reverse
  analogWrite(pwmL, power);
  analogWrite(pwmR, power); */
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(pwmR, 0);
  analogWrite(pwmL, power);
}

void halt() {
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);
}

void fowards(int power = 100) {
  digitalWrite(dirL, HIGH); //make both motors go fowards
  digitalWrite(dirR, HIGH);
  analogWrite(pwmL, power); // power the motors
  analogWrite(pwmR, power);
}

int getRange() {
  distance = 1001; // setup for while loop
  while (distance > 1000) { // takes away anomalies
    digitalWrite(trigPin, LOW);
    delay(2);

    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    delay(100);
//    Serial.print("distance:  ");
//    Serial.println(distance);
  }
  return distance;
}
void getHeat() {
  delay(100);
  
  counter = 0;
  for(int i = 0; i<64; i++){
    delay(10);
    usedPixels[i] =0;
  }
  //int usedPixels[63];
  amg.readPixels(pixels); //read all the pixels
  for (int x = 0; x <= 63; x++) {
    //Serial.print("in loop getheat");
    if (pixels[x] > 40) {
      counter += 1;
      usedPixels[counter] = x; //append used pixels into sepparate array
    }
  }
  middle = (usedPixels[round(counter / 2)]) % 8; // finds median of the array
}
void loop() {
  Serial.println("");
  //reset variables

  //GET HEAT:
  delay(50);
  getHeat();
  if (counter == 0) { // checks if there actually is a fire
    halt();
    left();
    Serial.print("searching");
  }
  else {

    while (!(middle > 2 && middle < 5)) {
      Serial.println("");
      if (middle > 5) {
        right();
        Serial.print("GOING RIGHT");
      }
      else if (middle < 2) {
        left();
        Serial.print("GOING LEFT");
      }
      else {
        halt();
        Serial.print("STOPPING");
        break;
      }
      getHeat();
      if (counter == 0) {
        break;
      }
    }
    if (getRange() <= 10) {
      halt();
      Serial.print("EXTINGUISHING");
      delay(1000);
      //extinguish
    }
    else {
      fowards();
      Serial.print("going forwards");
    }
  }
}
