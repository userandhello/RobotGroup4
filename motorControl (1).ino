float motor1Multiplier = 1.0;
float motor2Multiplier = 1.0;

void motorControl(int speed1, int speed2) {
  int adjustedSpeed1 = speed1 = motor1Multiplier;
  int adjustedSpeed2 = speed2 = Motor2Multiplier;

  adjustedSpeed1 = max(-255, min(255, adjusted speed1));
  adjustedSpeed2 = max(-255, min(255, adjusted speed2));

analogWrite(MOTOR_PIN1, adjustedSpeed1 > 0 ? adjustedSpeed1 : 0);
analogWrite(MOTOR_PIN2, adjustedSpeed1 > 0 ? -adjustedSpeed1 : 0);
analogWrite(MOTOR_PIN3, adjustedSpeed2 > 0 ? adjustedSpeed1 : 0);
analogWrite(MOTOR_PIN4, adjustedSpeed2 > 0 ? -adjustedSpeed1 : 0);



}