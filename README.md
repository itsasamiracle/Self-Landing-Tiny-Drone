# Self-Landing-Tiny-Drone
Open source project for nasa hackclub stardance organization. Contains design files for a tiny drone with self-landing capabilites.

This project is a tiny drone that will be able to land itself by gradually descending as it approaches the ground. The drone detects the ground using a time-of-flight sensor mounted to the bottom that communicates to an onboard ESP32 C3 supermini. An onboard gyro/accelerometer will also stabilize the drone and regulate landings.

<img width="1144" height="675" alt="image" src="https://github.com/user-attachments/assets/8959dcc5-a1a1-4cb5-a308-ba4c2021f4c5" />



Wiring diagram:
<img width="1144" height="710" alt="image" src="https://github.com/user-attachments/assets/3a793beb-1620-4680-b793-dc97124cd59d" />


The code sets up a WiFi server using the ESP32. We remotely connect to the server using an HTML website to control the drone. This currently needs a ton of testing and calibration.

I made this project because it integrates many different aspects of engineering like CAD and sensor usage for a cool project. I also just thought it would be sick to make a drone.
