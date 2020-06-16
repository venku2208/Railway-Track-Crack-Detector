int ENA1 = 10;
int ENA2 = 11;
int IN1 = 9;
int IN2 = 8;
int IN3 = 7;
int IN4 = 6;

const int pingPin1 = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 3; // Echo Pin of Ultrasonic Sensor

const int pingPin2 = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 5; // Echo Pin of Ultrasonic Sensor
char ph_no[] = "1234567890";
void setup()
{
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  long duration1, duration2, inches, cm1, cm2 ;
  pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2000);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(pingPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2000);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(pingPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  //inches = microsecondsToInches(duration);
  cm1 = microsecondsToCentimeters(duration1);
  cm2 = microsecondsToCentimeters(duration2);
  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm1);
  Serial.print("cm1");
  Serial.println();
  delay(1000);
  Serial.print(cm2);
  Serial.print("cm2");
  Serial.println();
  delay(1000);
  if (cm1 <= 5 || cm2 <= 4)
  {
    forward();
  }
  else
  {
    stop();
    Serial.println("AT");
    Serial.print("ATD");
    Serial.print(ph_no);
    Serial.println(";");
    delay(10000);
    Serial.println("ATH");
    delay(1000);
    Serial.println("AT+CMGF=1");
    delay(2400);
    delay(1500);
    Serial.print("AT+CMGS=\"");
    Serial.print(ph_no);
    Serial.println("\"");
    while (Serial.read() != '>')
    {
      Serial.print("Crack detected on Track!!!!!!");
      delay(2000);
      Serial.write(0x1A);
      Serial.write(0x0D);
      Serial.write(0x0A);
      delay(2000);
      break;
    }
  }
}
void forward()
{
  digitalWrite(IN1, 0);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA1, 153);
  analogWrite(ENA2, 153);
}
void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
