#include <Adafruit_NeoPixel.h>

int ledPin= 3;
int ledNo= 12;

Adafruit_NeoPixel strip= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);


int buzzerPin= 2;
int echoPin= 6;
int trigPin= 5;
int minDistance = 200;
int maxDistance = 300;

void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial. begin(9600);  
  strip.begin();
  for(int i = 0; i < ledNo; i++)
  {
   strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

void loop() 
{
  int distance = calcDistance();
  Serial.println(distance);
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  Serial.println(ledsToGlow);
  if(distance<minDistance)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  int i;

    if(distance>300)
    {
          strip.setPixelColor(12,strip.Color(50,0,0));//green,red,blue
    }
    else if(distance<300 && distance>minDistance)
    {
     for(i=0;i<12;i++)
     {
          strip.setPixelColor(i,strip.Color(50,50,0));//green,red,blue
     }
    }
    else if(distance<minDistance)
    {
      for(i=0;i<12;i++)
      {
         strip.setPixelColor(i,strip.Color(0,50,0));//green,red,blue
      }
    }
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(50,0,0));
  }
  strip.show();
  delay(50);
}

int calcDistance()
{
  long distance,duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;

  return distance;
}