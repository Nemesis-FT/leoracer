# leoracer
> Now [THIS](https://youtu.be/8bLkcCZFKvA) Is Podracing  


Leoracer is a making project that aims to create an alternative game controller for the now long forgotten [Pod Racer Game](https://en.wikipedia.org/wiki/Star_Wars_Episode_I:_Racer) developed by LucasArts and recently made available for modern Windows machines through [GoG](https://www.gog.com/en/game/star_wars_episode_i_racer).  
The controller features a double airplane-throttle layout, which can tilt forwards (thus handling the pod's thrust) and tilt sideways (thus handling the pod's tilting): in order to turn left, the player has to reduce throttle to the right side, and vice versa.  
All of this is to provide a more "realistic" control scheme through a D-Input compliant controller, and this is achieved by using the great [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) created by Matthew Heironimus. Kudos to him for the great work he's done on this library. 

This project has been developed for the course "Laboratory of Making" taught by Professor Renzo Davoli and Professor Federico Montori at the University of Bologna, Alma Mater Studiorum.

# Required components
The provided links are provided just for guidance in part-picking. I am not affiliated with "futuranet" or other vendors and I'm not sponsoring them in any way, it's just the store that I used for this project to gather parts.
* An Arduino Leonardo and the Arduino IDE;
* At least 4 variable resistors (I highly suggest you buy spares just in case you damage them during soldering) like this [one](https://futuranet.it/prodotto/potenziometro-lineare-1-kohm/);
* 2 arcade-style buttons like this [one](https://futuranet.it/prodotto/pulsante-arcade-corto-blu/);
* 1 button like this [one](https://futuranet.it/prodotto/pulsante-da-pannello-normalmente-aperto-nero/);
* 1 toggle switch like this [one](https://futuranet.it/prodotto/deviatore-on-on-a-levetta-cs-90/);
* Male to male patch wires and male to female patch wires;
* Some electrical wires;
* PCBs terminal blocks;
* M3 screws of different sizes;
* M3 brass screw sockets;
* 9 suction cups like this [ones](https://www.amazon.it/dp/B084BRH8GP?psc=1&ref=ppx_yo2ov_dt_b_product_details);
* Soldering equipment;
* A multimeter for troubleshooting;
* A 3D printer or a friend with a 3D printer.

# Building the controller
1. Print all the parts, keeping in mind that the two sides share all the components except for the external shell (BodyR and BodyL). I've used a Lotmaxx SC-10 Shark with some random PLA and all of them have printed nicely;
2. Solder all the components to jumper/patch wires, and embed the brass sockets in the prints using the solderer;
3. Assemble all the parts according to the [animation](https://drive.google.com/file/d/1N2wPsxAuo81091dKuf4QRvu4FyjoekB1/view?usp=sharing), which does not include assembly of the buttons, screws and corresponding sockets.;
4. Connect all the wires to the arduino accordingly to the electrical schema;
5. Flash the Arduino Leonardo with the calibration software: to calibrate the controller, move the axises from minimum to maximum in this order: Right Throttle, Right Tilt, Left Tilt, Left Throttle (after each movement, press the right throttle button);
6. Flash the Arduino Leonardo with the firmware, hopefully you should see your controller on your PC (remember to download and add to Arduino IDE the [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary)).