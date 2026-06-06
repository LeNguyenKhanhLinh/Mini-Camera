import serial
from PIL import Image

ser = serial.Serial('COM9', 115200, timeout=5)

WIDTH = 120
HEIGHT = 120
BYTES_IN = WIDTH * HEIGHT

while True:
    start = ser.read_until(b"START")

    if not start.endswith(b"START"):
        continue

    print("START received")

    raw_data = b''

    while len(raw_data) < BYTES_IN:
        chunk = ser.read(BYTES_IN - len(raw_data))

        if not chunk:
            break

        raw_data += chunk

    print("Received:", len(raw_data))

    end_signal = ser.read_until(b"END")
    print("End signal:", end_signal)

    if len(raw_data) == BYTES_IN:
        img = Image.frombytes('L', (WIDTH, HEIGHT), raw_data)
        img.save("frame.png")
        img.show()
        print("Saved frame.png")