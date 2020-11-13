# indoor-air-quality-app

Notre solution permet de mésurer la qualté de l'air au Ceri. Elle deploie pour cela une **Raspberry Pi, une carte Arduino Leonardo, des capteurs DHT11 (Température et Humidité) et IAQ Core C (Indoor Air quality sensor)**. On envoie les données capturées vers un serveur **TTN** depuis l'**Arduino Leonardo** via une passerelle *Lora*. Ces données vont ensuite être exploité par un serveur **Node-red** qui se charger de les sauvegarder dans une Base de donnée **InluxDB** et de les affichées sous forme de graphique. 
## Tâches : 
 La réalisation de notre solution se subdivise en plusieurs tâche : 
* **Tâche 2 :** Lire les données **(CO2 et COV)** du capteur **IAQ Core c** depuis la **Raspberry PI**  et les transmettre à l'**Arduino Leonardo**. 
* **Tâche 3 :** Lire les données **(température et humidité)** du capteur **DHT11** depuis la carte **Arduino Leonardo**, recevoir les données du capteur **IAQ Core C** depuis la **Raspberry PI** et envoyer tous les données capturés au serveur **TTN**.
* **Tâche 4 :**  Récupérer les données de captures  depuis le serveur **TTN** vers un serveur en vu de les sauvegarder et  de les rendre compréhensible par une requête HTML.
* **Tâche 5 :** Automatiser le déploiement de notre application.

### Tâche 1 : 
Pour la réalisation de la tâche 1, on va utiliser un code c++ se trouvant dans le fichier **iaqCore.c++**. 
Maintenant, pour rendre ce code exécutable sur la Raspberry Pi on doit le compiler. Pour ce faire, on utilise **g++** qui est un excellent compilateur pour C++.
Pour l'installer, taper : 
``` sudo apt-get update 
    sudo apt-get install g++
```
Pour compiler le code, se localiser dans le dossier source du code **c++** et taper : 
``` g++ /*.c /*.cpp -o final
```
Et pour l'éxecuter, il faut taper : 
``` ./final
```
Ainsi la tâche 1 est réalisée. On peut maintenant lire les données capteur **IAQ Core C** et les envoyer à l'**Arduino Leonardo**.

### Tâche 2 : 
Pour la réalisation de la tâche 2, on a besoin d'installer l'application **arduino** pour pouvoir manipuler les cartes **Arduino**.
Pour l'installer, taper : 
``` sudo apt-get update
    sudo apt-get install arduino
```
On installe maintenant les **library** nécessaire au bon fonctionnement de notre code à savoir : 
- ThethingsNetwork
- Adafruits Unified Sensor
Pour installer une **library**, on clicque sur : 
**Croquis** dans le ménu > puis sur inclure une Bibliothèque > et dans la fénêtre qui s'ouvre on tape le nom de la bibliothèque qu'on veut ajouter .

Une fois ces **Library** installés, on compile le code *DHT_modifie.ino* et on le téléverse sur l'**arduino**.

### Tâche 3 : 
On va mettre en place notre serveur. On va installer **Node-red**. 
Pour ce faire, on va installer d'abord **nodeJs** avec :
``` sudo apt-get update
    sudo apt-get install nodejs
```
On utilise maintenant **npm** pour installer node-red en mode gloabal et on le lannce.

``` sudo npm install -g node-red
    node-red
```
Une fois **node-red** installé, on va installer les nodes : 
- node-red-contrib-mqtt-broker
- node-red-contrib-influxdb
- node-red-dashboard


Pour insataller un module, il faut proceder comme suite : 
Cliquer sur le menu > cliquer sur Manage >  puis dans l'onglet **install** taper le nom du module >  Et installer le module.

![Image du choix de Manage dans le Menu](https://github.com/alasco-one/indoor-air-quality-app/images/1.png)

![Image de recherche du module](https://github.com/alasco-one/indoor-air-quality-app/images/2.png)








