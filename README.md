
# Setup of ESP32 with the Arduino

 Prerequisites:
    • PC Ubuntu(version > 16.04)
    • ESP32 Board(WROOM-32)
    • Arduino IDE(Latest version)
 Steps:
    • Install Arduino IDE if not installed.
    • sudo snap install arduino
    • After installation of Arduino IDE, open the IDE and go to file -> preferences
    • Now in the Additional boards manager URLs text box, paste the below links
    ◦ <https://dl.espressif.com/dl/package_esp32_index.json>, <http://arduino.esp8266.com/stable/package_esp8266com_index.json>
    • After pasting the URL click on OK.
    • Now go to Tools->Board->Boards Manager
    ◦ In this board manager, type ESP32 in the text box.
    • It shows esp32 by Espressif systems, select the version (prefer latest one) and then click on install.
    • It will take some time to install
    ◦ After installation, close the window.
    • This completes the ESP32 installation in the Arduino IDE.
 Configuration of ESP32 board in Arduino IDE:
    • Once installation is done, Select your Board in Tools > Board -> ESP32 Arduino -> FireBeetle-ESP32.
    • Then next select the COM port of your ESP32 in Tools-> ports.
    • This completes the ESP32 configuration with Arduino IDE.
    • Now you can write your programs, compile, and flash on ESP32 board through Arduino IDE.

![WhatsApp Image 2022-07-10 at 6 04 29 PM](https://user-images.githubusercontent.com/105910992/178448443-72730d8e-b2e1-4762-b824-2ca43ea28f34.jpeg)
