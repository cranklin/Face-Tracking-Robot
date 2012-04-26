#include <Servo.h>
Servo servo1;
Servo servo2;
int movedirection;
int currentX = 90;
int currentY = 90;
int moved = 0;

void setup()
{
  servo2.attach(7);
  servo1.attach(8);
  moveto(servo1,currentX);
  moveto(servo2,currentY);
  delay(3000);
  Serial.begin(19200);
}
  
void loop()
{
  if(Serial.available()>0){
    movedirection = Serial.read();
    //Serial.print(movedirection);
    switch(movedirection){ /* clock notation but *10 to move faster */
      case 49:
        /*1 move up*/
        currentY = currentY>1 ? currentY+5 : 0;
        moveto(servo2,currentY);
        break;
      case 50:
        /*2 move right*/
        currentX = currentX<179 ? currentX+5 : 180;
        moveto(servo1,currentX);
        break;
      case 51:
        /*3 move down*/
        currentY = currentY<179 ? currentY-5 : 180;
        moveto(servo2,currentY);
        break;
      case 52:
        /*4 move left */
        currentX = currentX>1 ? currentX-5 : 0;
        moveto(servo1,currentX);
        break;
      default:
        //Serial.print("wth");
        currentX = 90;
        currentY = 90;
        moveto(servo1,currentX);
        moveto(servo2,currentY);
    }
  }
  /*delay(400);*/
}

void moveto(Servo whichservo,int position){
  whichservo.write(position);
  /*delay(15);*/
}

