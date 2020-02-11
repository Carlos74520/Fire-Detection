#define pwmL 3 // Motor pins
#define dirL 2
#define pwmR 6
#define dirR 12


void setup() {
  pinMode(pwmL, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(pwmR, OUTPUT);
  pinMode(dirR, OUTPUT);

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

void straight(int power = 100) {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(pwmL, power);
  analogWrite(pwmR, power);

}
void loop() {
//  digitalWrite(dirL, LOW);
//  digitalWrite(dirL, LOW);
//  analogWrite(pwmL, 100);
//  analogWrite(pwmL, 100);
//    digitalWrite(dirL, HIGH);
//    analogWrite(pwmL, 100);
//    delay(1000);
//    analogWrite(pwmL, 0);
//    delay(1000);
//    digitalWrite(dirL, LOW);
//    analogWrite(pwmL, 100);
//    delay(1000);
//    halt();


//    straight();
//    delay(1000);
//    left();
//    delay(1000);
//    right();
//    delay(1000);
    digitalWrite(dirL, HIGH);
    analogWrite(pwmL, 70);
}
