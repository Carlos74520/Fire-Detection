#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int usedPixels[63];
int counter = 0;
int middle = 0;
//int pixels[] = {10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10};
void setup() {
  Serial.begin(9600);

  bool status;

  status = amg.begin();

  delay(100); // let sensor boot up
}


void loop() {
  //reset variables
  counter = 0;
  int usedPixels[63];
  //read all the pixels
  amg.readPixels(pixels);

  for (int x = 0; x <= 63; x++) {
    if (pixels[x] > 40) {
      counter += 1;
      usedPixels[counter] = x;
    }
  }
  Serial.println("");
  //find where the middle is
  if (counter > 0) {
    middle = (usedPixels[round(counter / 2)]) % 8;
    if (middle < 3 ) Serial.print("FIRE ON LEFT");
    else if (middle > 4) Serial.print("FIRE ON RIGHT");
    else Serial.print("FIRE IS IN FRONT");
  }
  else Serial.print("NO FIRE DETECTED");
  delay(500);

}
