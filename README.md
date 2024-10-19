# SmartGarden

**SmartGarden** is an IoT-based project designed to automate the monitoring and watering of plants in a garden. It uses various sensors to track environmental conditions such as soil moisture, light intensity, temperature, and humidity, and automatically controls a water pump to ensure plants receive the right amount of water.

## Features
- **Soil Moisture Monitoring**: Measures soil moisture levels and triggers watering when needed.
- **Automatic Watering**: Controls a water pump using relays to automate irrigation.
- **Light Intensity Tracking**: Uses an LDR (Light Dependent Resistor) to monitor sunlight and adjust the watering schedule based on light exposure.
- **Temperature & Humidity Sensors**: Monitors environmental conditions to help maintain an ideal environment for plants.
- **ESP8266 Integration**: Wi-Fi-enabled controller for remote monitoring and control via a web interface or mobile app.
- **Low-Power Consumption**: Designed to operate efficiently with minimal energy usage.

## Components
- ESP8266 (or any compatible microcontroller)
- Soil moisture sensor
- LDR (Light sensor)
- DHT11/DHT22 (Temperature and Humidity sensor)
- Relay module for pump control
- Water pump
- Power supply

## How It Works
1. The system continuously reads data from the sensors.
2. Based on the moisture levels, the ESP8266 decides whether to activate the water pump to hydrate the plants.
3. The light sensor tracks sunlight, and environmental conditions are monitored to optimize watering.
4. Data can be viewed and controlled remotely using the ESP8266's Wi-Fi capabilities.

## Future Enhancements
- Integration with weather APIs for advanced scheduling.
- Solar-powered operation for increased sustainability.
- Mobile app for real-time monitoring and control.

## Getting Started
1. Clone this repository to your local machine.
2. Upload the code to your ESP8266 using the Arduino IDE or PlatformIO.
3. Connect the components as per the wiring diagram provided.
4. Customize the threshold values for soil moisture, light, and other conditions in the code.

Feel free to contribute to this project by submitting pull requests or reporting issues!
