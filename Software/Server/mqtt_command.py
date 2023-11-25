import paho.mqtt.client as mqtt
import threading
import time

# Callback function for successful connection
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    
    # Subscribe to the topic "WSN/response"
    client.subscribe("WSN/response")

# Callback function for receiving response from the command
def on_response(client, userdata, msg):
    global response_received
    response_received = True
    print(f"Received response from topic {msg.topic}: {msg.payload.decode()}")

# Create MQTT Client object
client = mqtt.Client()

# Set callback functions
client.on_connect = on_connect
client.message_callback_add("WSN/response", on_response)

# Connect to the MQTT broker
client.connect("test.mosquitto.org", 1883, 60)

# Start the loop
client.loop_start()

# Global variable to check if a response has been received
response_received = False

# Function to reset the response flag after a timeout
def reset_response_flag():
    global response_received
    time.sleep(10)  # Timeout duration (10 seconds)
    response_received = True

try:
    while True:
        # Get user input
        command = input("Enter command: ").strip()  # Remove newline character
        
        # Publish the command to topic "WSN/command"
        client.publish("WSN/command", command)

        # Start a new thread to reset the response flag after a timeout
        threading.Thread(target=reset_response_flag).start()

        # Wait for a response or timeout
        while not response_received:
            time.sleep(0.1)  # Small delay to avoid busy-waiting

        # Reset the response flag for the next iteration
        response_received = False

except KeyboardInterrupt:
    print("Program terminated by user.")
    client.loop_stop()