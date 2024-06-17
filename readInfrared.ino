int* readInfrared(_) {
  static in IRvaules[4];

  IRvaulues[0] = digitalRead(IR_1);
  IRvaulues[1] = digitalRead(IR_2);
  IRvaulues[2] = digitalRead(IR_3);
  IRvaulues[3] = digitalRead(IR_4);

  Serial.print("IR_1: ");
  Serial.print(IRvalues[0]);
  Serial.print(", IR_2: ");
  Serial.print(IRvalues[1]);
  Serial.print(", IR_3: ");
  Serial.print(IRvalues[2]);
  Serial.print(", IR_4: ");
  Serial.println(IRvalues[3]);

  return IRvalues; 



}