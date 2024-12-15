//This project uses an Arduino Uno, a rain detector, and a buzzer. 
const int rainPin = A0;
const int buzzerPin = 2;
const int ledPin = 7;
int rainVal = 1023;
int max = 158;
int min = 415;

void setup() {

  //Pin specifications
  pinMode(rainPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //Starting serial console
  Serial.begin(9600);
}

void loop() {

  // Detecting the rain intensity and assigns is a variable.
  int newVal = analogRead(rainPin);
  if((rainVal - newVal) < -30)
  {
    Serial.println("RAIN INTENSITY DROPPED...");
  }
  else if((rainVal - newVal) > 30)
  {
    Serial.println("RAIN INTENSITY INCREASED...");
  }
  else
  {
    Serial.println("Rain intensity did not change...");
  }
  rainVal = newVal;
  if(rainVal < max)
  {
    Serial.println("NEW MAX INTENSITY RECORD!");
    max = rainVal;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  if(rainVal > min)
  {
    Serial.println("NEW MIN INTENSITY RECORD!");
    min = rainVal;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  Serial.print(rainVal);
  Serial.print(" -> ");

  if(rainVal > 800)
  {
    Serial.println("It is barely raining or not raining at all ");
    digitalWrite(ledPin, LOW);
  }

  else if(rainVal <= 800)
  {
    digitalWrite(ledPin, HIGH);
    
    if(rainVal > 600)
    {
      Serial.println("Light rain!");
    }
    else if(rainVal > 340)
    {
      Serial.println("Moderate rain!");
    }
    else
    {
      Serial.println("Driving Rain!");
    }
  }
  //buzzer kontrolü
  /*if(rainVal < 340)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }*/
  Serial.print("(Max:");
  Serial.print(max);
  Serial.print(" Min:");
  Serial.print(min);
  Serial.println(")");
  Serial.println("***********************************");
  delay(10000);
}
