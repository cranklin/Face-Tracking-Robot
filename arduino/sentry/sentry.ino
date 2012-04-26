#include <Servo.h>
Servo servo1;
Servo servo2;
int targetx[3];
int targety[3];
int posx=90;
int posy=90;
int xory = 0;
int index = 0;
int serialread;

void setup()
{
  servo1.attach(8);
  servo2.attach(7);
  moveto(servo1,posx);
  moveto(servo2,posy);
  delay(3000);
  Serial.begin(19200);
}
  
void loop()
{
  while(Serial.available() > 0)
  {
    posx = 0;
    posy = 0;
    serialread = Serial.read();
    if(serialread == 120)/* x */
    {
      int multiplier = 1;
      for(int i=index-1;i>=0;i--){
        if(i < index-1)
        {
          multiplier *= 10;
        }
        posx += targetx[i]*multiplier;
      }
      index = 0;
      xory = 1;
      moveto(servo1,posx);
      Serial.print("x:");
      Serial.println(posx);
    }
    else if(serialread == 121)/* y */
    {
      int multiplier = 1;
      for(int i=index-1;i>=0;i--){
        if(i < index-1)
        {
          multiplier *= 10;
        }
        posy += targety[i]*multiplier;
      }
      index = 0;
      xory = 0;
      moveto(servo2,posy);
      Serial.print("y:");
      Serial.println(posy);
    }
    else
    {
      if(xory==0)
      {
        targetx[index] = serialread-48;
      }
      else
      {
        targety[index] = serialread-48;
      }
      index++;
    }
  }
  /*delay(400);*/
}

void moveto(Servo whichservo,int position){
  whichservo.write(position);
  /*delay(15);*/
}

