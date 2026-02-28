import serial
import time 

ARDUINO_PORT = 'COM3' 
BAUD_RATE = 9600

# Initial connection to the Arduino
try:
    arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to Arduino on {ARDUINO_PORT} at {BAUD_RATE} baud.")

    # Give the Arduino some time to initialize
    time.sleep(2)
    print(f"Connected to Arduino on {ARDUINO_PORT} at {BAUD_RATE} baud. Starting to read data...")

    data_buffer = []
    buffer_size = 10

    while True:
        if arduino.in_waiting > 0:
            # Read data, decode from bytes to string, and remove any whitespaces and new lines
            raw_data = arduino.readline().decode('utf-8').rstrip()
            
            # Data validation 
            try:
                distance = float(raw_data)
                print(f"Distance: {distance:.2f} cm")
                # Print control logic here

                data_buffer.append(distance) # Fixed missing parenthesis
                
                if len(data_buffer) > buffer_size:
                    data_buffer.pop(0)
                sorted_buffer = sorted(data_buffer)
                median_distance = sorted_buffer[len(sorted_buffer) // 2]   
                print(f"Smoothed distance: {median_distance:.2f} cm")

            except ValueError:
                pass # Ignores data that cannot be converted to float

except serial.SerialException as e:
    print(f"Serial error: {e}")
    print("Check if the Arduino is properly connected and try again.")
except KeyboardInterrupt:
    print("\nData collection stopped by user. Closing connection.") # Fixed /n to \n
finally:
    # Clean up: Always ensure the port is closed to free it up for other programs
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
        print("Serial port safely closed.")
              


            #
              

              
    