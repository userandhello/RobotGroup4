void turnLogic() {


 int* IRvalues;
 IRvalues = readInfrared();  // This will point to the array of sensor values


 // Print the read values to the serial monitor


 // Check to see if a wall has been detected
 if (currentDistance < 8 && wallDetected == false) {
   isTurning = true;
   wallDetected = true;
   turnStartTime = currentMillis;
   initialForwardMotion = true;
 }


 // If the wall hasn't been detected and the robot is not in a turning state
 if (!isTurning && wallDetected == false) {


   // Check the outer two sensors to see if they are triggered, and start the threshold timer
   if (IRvalues[3] == 1 && firstDetectionTime1 == 0) {
     firstDetectionTime1 = currentMillis;
     Serial.println("Detected Left Sensor");
   }
   if (IRvalues[0] == 1 && firstDetectionTime4 == 0) {
     firstDetectionTime4 = currentMillis;
     Serial.println("Detected Right Sensor");
   }


   // Check if both sensors detected a line within the threshold and determine the turn direction


   if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 < sensorCheckThreshold && firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 < sensorCheckThreshold) {
     // If both sensors detect a black line, turn the opposite direction of the last turn
     isTurning = true;
     initialForwardMotion = true;  // Initiate forward motion when turning starts
     turnStartTime = currentMillis;
     // turnDirection = lastTurnDirection == "left" ? "right" : "left";  // Opposite direction of last turn
     turnDirection = lastTurnDirection;
     firstDetectionTime1 = 0;
     firstDetectionTime4 = 0;
     lastTurnDirection = turnDirection;
     Serial.print("Solid Line Detected (Sensors 1 and 4) - turning ");
     Serial.println(turnDirection);
   } else if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 >= sensorCheckThreshold) {
     // If the left sensor detects a black line, start a left turn
     isTurning = true;
     initialForwardMotion = true;  // Initiate forward motion when turning starts
     turnStartTime = currentMillis;
     turnDirection = "left";
     firstDetectionTime1 = 0;  // Reset after decision
     lastTurnDirection = turnDirection;
     Serial.println("Left Turn Detected");
   } else if (firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 >= sensorCheckThreshold) {
     // If the right sensor detects a black line, start a left turn
     isTurning = true;
     initialForwardMotion = true;  // Initiate forward motion when turning starts
     turnStartTime = currentMillis;
     turnDirection = "right";
     firstDetectionTime4 = 0;  // Reset after decision
     lastTurnDirection = turnDirection;
     Serial.println("Right Turn Detected");


   } else {
     // Serial.println("No Turn Logic Detected");
   }
 }
}
void motorLogic() {


 int* IRvalues;
 IRvalues = readInfrared();  // This will point to the array of sensor values


 // Apply robot logic based on sensor readings and turning flags
 if (!isTurning && !wallDetected) {


   //////////// Your existing motorLogic code (Phase 5) goes here. ////////////


 } else if (isTurning && !wallDetected) {


   // Handle the turning based on the direction determined


   if (initialForwardMotion) {
     motorControl(200, 200);  // Continue moving forward for the initial duration
     currentState = "Bumping Out...";
     delay(initialMotionDuration);
     initialForwardMotion = false;  // End initial forward motion after duration


   } else {


     if (turnDirection == "left") {


       if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
         Serial.println("Detected Center IR Sensor after initial turn duration");
         isTurning = false;   // Stop turning if IR2 detects the line again
         motorControl(0, 0);  // Adjust to move forward or stop
         currentState = "Turning Left - Next Line Detected";
         motorControl(turnSpeed, -turnSpeed);  // Counterbalance
         delay(50);
         motorControl(0, 0);
         delay(50);
         currentState = "Forward";
       } else {
         motorControl(-turnSpeed, turnSpeed);  // Continue turning left
         currentState = "Turning Left - No Line Yet Detected";
       }


     } else if (turnDirection == "right") {


       if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[1] == 1) {
         Serial.println("Detected Center IR Sensor");
         isTurning = false;  // Stop turning if IR3 detects the line again
         currentState = "Turning Right - Next Line Detected";
         motorControl(-turnSpeed, turnSpeed);  // Counterbalance
         delay(50);
         motorControl(0, 0);
         delay(50);
         currentState = "Forward";


       } else {


         motorControl(turnSpeed, -turnSpeed);  // Continue turning right
         currentState = "Turning Right - No Line Yet Detected";


       }


     }
   }


   // Turn that is triggered by detecting a wall


 } else if (isTurning && wallDetected) {


   if (initialForwardMotion) {
     motorControl(-200, -200);  // Continue moving forward for the initial duration
     currentState = "Stopping...";
     delay(100);
     initialForwardMotion = false;  // End initial forward motion after duration
   } else {
     // Turn left
     if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
       Serial.println("Detected Center IR Sensor after initial turn duration");
       isTurning = false;  // Stop turning if IR2 detects the line again
       currentState = "Turning Left - Next Line Detected";
       motorControl(turnSpeed, -turnSpeed);  // Counterbalance
       delay(50);
       motorControl(0, 0);
       delay(50);
       wallDetected = false;
       currentState = "Forward";
     } else {
       motorControl(-turnSpeed, turnSpeed);  // Continue turning left
       currentState = "Turning Left - No Line Yet Detected";
     }
   }
 }
}

