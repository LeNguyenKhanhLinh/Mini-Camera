# Mini-Camera
A mini camera that takes picture when you push the button and send the image through your phone. The idea is:
OV7670 Camera Module +Button -> ESP32 -- Bluetooth --> Phone or device that connect to the bluetooth
-- Problems --
- Since my camera doesn't have a FIFO to store the pics before sending it, The camera has to use ESP's RAM. Therefore, due to lack of Storage space (Bluetooth Connection do take a lot), I may have to try to find another solution
