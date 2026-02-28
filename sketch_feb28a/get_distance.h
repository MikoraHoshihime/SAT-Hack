const int trigPin = A4; 
const int echoPin = A5;

// Set up the buffer size (equivalent to your buffer_size = 10)
const int BUFFER_SIZE = 10;
float data_buffer[BUFFER_SIZE];
int buffer_index = 0;
bool buffer_full = false;

void setup() {
  Serial.begin(9600); // Keeps the serial connection so you can still print to your laptop monitor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.println("Arduino Initialized. Starting to read sensor data...");
  //delay(1000); // Equivalent to time.sleep(2)
}



// --- HELPER FUNCTIONS ---

// Function to trigger the sensor and calculate distance
float getUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1.0; // Invalid reading
  
  return (duration * 0.0343) / 2.0;
}

// Function to sort the array and find the median (Replaces sorted())
float calculateMedian(float* array, int size) {
  float temp[BUFFER_SIZE];
  
  // Copy the array so we don't mess up the chronological order of our buffer
  for (int i = 0; i < size; i++) {
    temp[i] = array[i];
  }

  // Simple Bubble Sort to order the temporary array
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (temp[j] > temp[j + 1]) {
        float swap = temp[j];
        temp[j] = temp[j + 1];
        temp[j + 1] = swap;
      }
    }
  }

  // Return the middle value
  return temp[size / 2];
}



float get_distance() {
  // 1. Get raw distance directly from the sensor (Replaces reading the COM port)
  float distance = getUltrasonicDistance();
  
  if (distance > 0) { // Basic validation
    // 2. Add to Circular Buffer (Replaces append and pop)
    data_buffer[buffer_index] = distance;
    buffer_index++;
    
    // If we reach the end of the array, loop back to the start
    if (buffer_index >= BUFFER_SIZE) {
      buffer_index = 0; 
      buffer_full = true;
    }

    // 3. Calculate the median once the buffer has data
    int current_size = buffer_full ? BUFFER_SIZE : buffer_index;
    
    if (current_size > 0) {
      float median_distance = calculateMedian(data_buffer, current_size);
      
      Serial.print("Smoothed distance: ");
      Serial.print(median_distance);
      Serial.println(" cm");
      return median_distance / 4.0;
    }
  }
  
  delay(50); // Small delay to prevent ultrasonic echo interference 
}