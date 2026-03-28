import paho.mqtt.client as mqtt
import time

BROKER = "broker.hivemq.com"
PORT = 1883
TOPIC = "Vecros/commands"

def connect_mqtt():
    client = mqtt.Client()
    
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker ✅")
        else:
            print("Failed to connect ❌")

    client.on_connect = on_connect
    client.connect(BROKER, PORT, 60)
    return client

def main():
    client = connect_mqtt()
    client.loop_start()

    try:
        while True:
            msg = input("Enter command: ")
            client.publish(TOPIC, msg)
            print(f"Sent: {msg}")

    except KeyboardInterrupt:
        print("\nExiting...")
        client.loop_stop()
        client.disconnect()

if __name__ == "__main__":
    main()