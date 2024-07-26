#pip install pyserial
import serial
import threading
import time

# Configuration
SERIAL_PORT = 'COM3'  # Adjust as needed
BAUD_RATE = 9600
RECONNECT_DELAY = 5  # Seconds to wait before attempting to reconnect

ser = None
running = True

def setup_serial():
    global ser
    while running:
        try:
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
            print(f"Connected to Arduino on {SERIAL_PORT}")
            return True
        except serial.SerialException:
            print(f"Failed to connect. Retrying in {RECONNECT_DELAY} seconds...")
            time.sleep(RECONNECT_DELAY)
    return False

def listener():
    global ser
    while running:
        if ser and ser.is_open:
            try:
                if ser.in_waiting:
                    message = ser.readline().decode('utf-8', errors='replace').strip()
                    print(f"Received: {message}")
            except serial.SerialException:
                print("Connection lost. Attempting to reconnect...")
                ser.close()
                if not setup_serial():
                    break
        else:
            if not setup_serial():
                break
        time.sleep(0.1)

def encode_data(tempTarget, sunThreshold, waterLevel):
    return f"{tempTarget},{sunThreshold:.1f},{waterLevel}"


# Start the listener thread
listener_thread = threading.Thread(target=listener)
listener_thread.start()

print("Type a message and press Enter to send it.")
print("Type 'exit' to quit.")

try:
    while running:
        message = input()

        if message.lower() == 'exit':
            print("Exiting program.")
            break
        
        if ser and ser.is_open:
            try:
                ser.write((message + '\n').encode('utf-8'))
            except serial.SerialException:
                print("Failed to send message. Connection may be lost.")

except KeyboardInterrupt:
    print("\nProgram interrupted.")

finally:
    running = False
    listener_thread.join()
    if ser and ser.is_open:
        ser.close()

print("Program ended.")