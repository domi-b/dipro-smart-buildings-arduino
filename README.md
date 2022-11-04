# Plants in Smart Buildings

Arduino project for an integration of plants in smart buildings.

## Project Summary

For the module "Digital Project" we created an integration of plants in smart buildings. We worked in an interdisciplinary team of six people. With three people dedicated to design and three people in the development team.

The products of our project were a High-Fidelity Prototype in Figma and a full-stack Web-App. We built our own semantic model of a building using [Brick Schema](https://brickschema.org/) and stored it using [GraphDB](https://graphdb.ontotext.com/). For live sensor data we built a small arduino prototype with different sensors and stored the sensor data with [InfluxDB](https://www.influxdata.com/). The notifications that show up on the frontend are stored in a [MySQL](https://www.mysql.com/) Database. Finally to acces all the data and send it to the frontend we created a NodeJS backend.

The backend is hosted on our university-own [EnterpriseLab](https://eportal.enterpriselab.ch/) and the frontend was deployed on [Netlify](https://www.netlify.com/).

## Quick Links

- [Frontend Repository](https://github.com/gina6/dipro-smart-buildings-frontend)
  - [View Demo Site](https://dipro-smart-building.netlify.app/) (preferably on mobile)
- [Backend Repository](https://github.com/patriciqa/dipro-smart-gardening-backend)
- [Figma Prototype](https://www.figma.com/proto/ohBlXQhGunPGbnQFVygLhO/DIPRO---Design-Konzept?node-id=738%3A8435&scaling=scale-down&page-id=609%3A2480&starting-point-node-id=738%3A8435&show-proto-sidebar=1)

## Technology Stack

### Hardware

#### Board

- [Arduino Uno WiFi Rev2](https://docs.arduino.cc/hardware/uno-wifi-rev2)

#### Sensors

- [DFRobot Soil Moisture Sensors](https://wiki.dfrobot.com/Moisture_Sensor__SKU_SEN0114_)
- [SGP30 Gas Sensor](https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor)
- [DHT11 Temperature & Humidity Sensor](https://service.allnet.de/index.php?/Knowledgebase/Article/View/287/0/allnet-4duino-sensor-temperatur--luftfeuchte-dht11)

### Arduino Libraries

| Name                  | Description                                               |
| --------------------- | --------------------------------------------------------- |
| WiFiNINA              | Connecting to a WiFi network and sending data to a server |
| DHT sensor library    | Reading temperature and humidity from the sensor          |
| Adafruit SGP30 Sensor | Reading air quality from the sensor                       |

## Run Locally

### Clone Repo

```
git clone https://github.com/domi-b/dipro-smart-buildings-arduino.git
```

### Install dependencies

Use the Arduino Library Manager to install the libraries described above.

### WiFi credentials

Provide your WiFi credentials in `login.h` inside the folder `smart_gardening` based on the following content:

```cpp
const char* ssid = "<Your SSID>";
const char* username = "<Username>";
const char* password = "<Password>";
```

### Run

Compile and upload the code to your Arduino board.
