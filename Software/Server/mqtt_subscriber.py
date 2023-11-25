# Import necessary libraries
import paho.mqtt.client as mqtt
import json
import psycopg2

# Callback function for successful connection
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    
    # Subscribe to the topic "WSN/sensor_data"
    client.subscribe("WSN/sensor_data")

# Callback function for receiving data from the topic
def on_message(client, userdata, msg):
    print(f"Received message from topic {msg.topic}: {msg.payload.decode()}")
    
    # Parse JSON data from the received message payload
    data_json = json.loads(msg.payload.decode())
    
    # Connect to the PostgreSQL database
    connection = psycopg2.connect(
        database="wsn",
        user="postgres",
        password="1",
        host="localhost",
        port="5432"
    )

    cursor = connection.cursor()

    # Execute the query to insert data into the database
    cursor.execute("""
        INSERT INTO sensor_data (node_id, unixtime, temp, x_axis, y_axis, room_id)
        VALUES (%s, %s, %s, %s, %s, %s)
    """, (
        data_json["node_id"],
        data_json["unixtime"],
        data_json["temp"],
        data_json["x_axis"],
        data_json["y_axis"],
        data_json["room_id"]
    ))

    # Commit changes and close the connection
    connection.commit()
    connection.close()

# Create MQTT Client object
client = mqtt.Client()

# Set callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect("test.mosquitto.org", 1883, 60)

# Start the loop
client.loop_forever()