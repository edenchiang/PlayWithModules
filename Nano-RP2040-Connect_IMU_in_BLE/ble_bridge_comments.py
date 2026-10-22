'''
 * Description: This is a reimplimentation for an old student project, "Mustick" in 2008 of TU/e.
 * Interaction: The IMU sensor data of Arduino Nano RP2040 Connect will be sent to this Python script,
 *              and the data will be transfer to an internal web server over port 12000. Then in 
 *              Processing, the data will change the speed of playing music or pause the playing if 
 *              the IMU side is not moving.
 *   Technique: I use BLE here, but the original prototype uses the xBee modules for data transmittion.
 *    Hardware: Arduino Nano RP2040 Connect
 *              Seeed Studio Lipo Rider Plus
 *              Lipo battery
 *              Raspberry Pi (I use RPi 4 here) with audio shield
 *                - It's difficult for RPi OS to decode audio file with integrated audio chip, so, I add
 *                  an additional DAC shield for decoding audio signal, which can do the decoding task
 *                  smoothly.
 * Programming: Arduino IDE
 *              Python (This file)
 *              Processing
 *  Created by: I-Tang (Eden) Chiang @ Oct.14, 2026
'''

import asyncio
from bleak import BleakScanner, BleakClient
from pythonosc import udp_client

# This matches the UUID from your Arduino code
# SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"

# Set up local network broadcaster to port 12000 (Processing)
osc_client = udp_client.SimpleUDPClient("127.0.0.1", 12000)

# Connect via bluetooth with MAC address or device name
TARGET_NAME = "Mustick"

# handle incoming data
def notification_handler(sender, data):
    try:
        # Decode the string sent by Arduino RP2040
        decoded_str = data.decode('utf-8')
        accel = decoded_str
        print(f"\nRaw data: {accel}")

        # Instantly forward the individual numbers to Processing
        osc_client.send_message("/accel", [float(accel)])
        print(f"Forwarded: Accel={accel}")
    except Exception as e:
        print(f"Data parsing error: {e}")
        pass

async def main():
    print(f"Scanning for '{TARGET_NAME}'...")
    device = await BleakScanner.find_device_by_name(TARGET_NAME)
    
    if not device:
        print(f"Device - [{TARGET_NAME}] not found! Make sure the board is powered on.")
        return
    
    print(f"Found [{TARGET_NAME}] with MAC address: {device.address}")
    print(f"Connected to {device.address}...")

    # monitoring incoming data
    async with BleakClient(device) as client:
        if client.is_connected:
            print("\nConnected! Starting receiving data of BMI270...")
            print("\nPress Ctrl + C to terminate process securely")
            print("-" * 55)

            await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
            
            # Keep running while connected
            while True:
                await asyncio.sleep(1)
        else:
            print("Fail to connect.")            


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n\n[Notify] Program is stopped by user, BLE is disconnected.")
