# Smart Home Automation with Tiva-C

This project demonstrates a Smart Home Automation system built using the Tiva-C microcontroller. The system integrates hardware components like relays, temperature sensors, and Bluetooth modules with a mobile application, allowing users to remotely control appliances, monitor environmental conditions, and track events.

---

## Team Members

| Name              | Contributions                                 |
| ----------------- | --------------------------------------------- |
| **Mohamed Salah** | UART communication, system interrupts         |
| **Seif Yasser**   | Mobile application development, UI design     |
| **Youssef Tamer** | SysTick implementation, system timing         |
| **Salma Mohamed** | ADC for temperature sensing, data acquisition |
| **Salma Hisham**  | GPIO drivers, relay and buzzer control        |

---

## Project Functionalities

- **Appliance Control:** Turn lamps and plugs on/off using a mobile application.
- **Temperature Monitoring:** Real-time temperature readings with alarm triggers.
- **Door Status Tracking:** Monitor door status (open/closed) with timestamps.
- **Event Logging:** Keep logs of actions for better accountability.
- **Mobile Application:** A user-friendly interface for seamless control and monitoring via Bluetooth.

---

## Project Installation and Setup

### Requirements

- **Hardware:**
  - Tiva-C LaunchPad (TM4C123G)
  - LM35 Temperature Sensor
  - Relay Module
  - Bluetooth Module (HC-05/06)
  - Buzzer
  - Push Button
  - Magnetic Door Sensor
- **Software:**
  - Code Composer Studio (or equivalent IDE for Tiva-C)
  - MIT App Inventor (for mobile app development)

### Steps

1. **Hardware Setup:**

   - Connect the LM35, relay, Bluetooth module, and other components to the Tiva-C GPIO pins as per the wiring diagram.

2. **Software Setup:**

   - Clone the repository:
     ```bash
     git clone https://github.com/your-repo/smart-home-tiva-c.git
     ```
   - Import the project into Code Composer Studio or your preferred IDE.

3. **Build and Flash:**

   - Compile the project and flash the firmware onto the Tiva-C microcontroller.

4. **Mobile Application:**

   - Download and install the `SmartHome.apk` from the `MobileApp` folder onto your Android device.

5. **Connect and Test:**
   - Pair the mobile app with the Bluetooth module.
   - Use the app to control appliances and monitor system data.

---

## Future Improvements

- Add support for Wi-Fi communication to expand system reach.
- Integrate additional sensors for enhanced home automation.
- Optimize power consumption for greater energy efficiency.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

Feel free to contribute to this project by creating a pull request or opening an issue for suggestions!
