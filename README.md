# Elevator Movement Monitor

This project was focused on developing a solution to monitor and analyze unusual sounds and movements in an elevator. The client, an elevator company, had been receiving complaints from customers about excessive noise from one of their elevators. However, diagnosing the issue was challenging because the noise never occurred when maintenance personnel were present.

Our task was to design a sensor-based system that would continuously record sound and movement data, sending it to a server for further analysis via a REST API. The system monitors the elevator in real-time, logging any unusual behavior. The solution was built using two programming languages: the monitoring system on PlatformIO and the edge device `Adafruit Feather ESP32S3 No PSRAM`, while the server-side processing was developed using Node.js.

Key components of the project include:
- **Sensor**: We used an LIS3DH accelerometer, interfacing with the Adafruit_LIS3DH library to read movement data on the X, Y, and Z axes. We focused primarily on X and Y values, which capture side-to-side and vertical movements.
- **Notification System**: We integrated PushSafer to send alert notifications to designated devices (such as phones) whenever irregular movement was detected in the elevator.
- **Real-Time Data Logging**: Data from the sensor is recorded continuously and sent to the server for processing, ensuring that even intermittent issues are captured and logged.

In conclusion, the system we built allows for effective monitoring and analysis of unexpected sounds and movements in elevators. The solution aids the elevator company by providing timely insights into potential mechanical issues, ultimately improving customer satisfaction and safety.

---
