## Overview
A compact camera device that takes a photo upon pressing a button and sends it to a connected phone/device via Bluetooth.

### System Architecture
`OV7670 Camera Module` + `Button` -> `ESP32` --(Bluetooth)--> `Phone / Mobile Device`

## Known Technical Issues & Challenges
- **Lack of Hardware Buffer (FIFO):** Since the selected OV7670 module lacks an onboard FIFO chip, frame data must be captured directly into the ESP32's internal RAM in real-time.
- **RAM Constraint with Bluetooth Stack:** The OV7670 outputs raw uncompressed image data (YUV/RGB), requiring a large frame buffer. Running the Bluetooth stack simultaneously consumes a significant amount of SRAM, leading to memory allocation failures (`out of memory`) on standard ESP32 chips without PSRAM.
- **Proposed Solutions / Next Steps:**
  - Upgrade to an **ESP32 module with PSRAM** (e.g., ESP32-WROVER or ESP32-CAM).
  - Switch to a camera module with hardware JPEG compression support (e.g., **OV2640**).
