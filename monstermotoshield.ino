#include <IBusBM.h>
IBusBM ibus;                          // Create iBus Object

//channels

long spd = 0;
long CH2 = 0;
long CH3 = 0;
long CH0 = 0;

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

//#define CURRENT_SEN_1 A2
//#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

inline void Forward() __attribute__((always_inline));
inline void Reverse() __attribute__((always_inline));
inline void Left() __attribute__((always_inline));
inline void Right() __attribute__((always_inline));
inline void sharpLeftTurn() __attribute__((always_inline));
inline void sharpRightTurn() __attribute__((always_inline));


void setup() 
{
  Serial.begin(115200);             // Start serial monitor for debugging
  ibus.begin(Serial);               // Attach iBus object to serial port
    
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  
  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

 // pinMode(CURRENT_SEN_1, OUTPUT);
 // pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);

  Stop();

}

void loop() 
{
  
//  CH1 = readChannel(0, -255, 255, 0);   flysky
//  CH2 = readChannel(1, -255, 255, 0);
//  CH3 = readChannel(2, 0, 255, 0);
//  CH4 = readChannel(3, -255, 255, 0);

    // Get RC channel values
  CH0 = readChannel(0, -255, 255, 0);       // Leftshift - Rightshift
  spd = readChannel(1, 0, 255, 0);          // Speed (Acceleration)
  CH2 = readChannel(3, -255, 255, 0);       // Forward - Reverse
  CH3 = readChannel(2, -255, 255, 0);       // Left - Right 

  if(CH2 > 100)
  {
      //Speed = (float)(CH3*CH2)/255;
      Forward();
      Serial.print("Foreward: ");
  }
  else if(CH2 < -100)
  {
    //Speed = abs((float)(CH3*CH2)/255);
      Reverse();
      Serial.print("Reverse: ");
  }
  else if(CH3 > 100)
  {    
    //Speed = (float)(CH3*CH1)/255;
      Right();
      Serial.print("Right: ");
  }
  else if(CH3 < -100)
  {
      Left();
      //Speed = abs((float)(CH3*CH1)/255);
      Serial.print("Left: ");
  }
  else if(CH0 > 100)
  {
      sharpRightTurn();
      //Speed = abs((float)(spd*CH0)/255);
      Serial.print("RightSharpTurn: ");
  }
  else if(CH0 < -100)
  {
      sharpLeftTurn();
      //Speed = abs((float)(spd*CH0)/255);
      Serial.print("LeftSharpTurn: ");
  }
  else 
  {
      Stop();
      Serial.print("Stop: ");
  }
  Serial.print(spd);
  Serial.println();
}

 int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue)
  {
    uint16_t ch = ibus.readChannel(channelInput);
    if (ch < 100) return defaultValue;
    return constrain(map(ch, 1000, 2000, minLimit, maxLimit), minLimit, maxLimit);
    //return map(ch, 1000, 2000, minLimit, maxLimit);
  }


void Forward()
{
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, LOW);
  
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);  

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}

void Reverse()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH);   

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}
void Left()
{
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, LOW);
  
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, HIGH); 

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}
void Right()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}

void Stop()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, LOW);
  
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, LOW);

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}
void sharpLeftTurn()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B2_PIN, LOW);

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}

void sharpRightTurn()
{
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, LOW);
  
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, LOW);

  analogWrite(PWM_MOTOR_1,spd);
  analogWrite(PWM_MOTOR_2,spd);
}
