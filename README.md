# indoor-air-quality-app

Notre solution permet de mésurer la qualté de l'air au Ceri. Elle deploie pour cela une **Raspberry Pi, une carte Arduino Leonardo, des capteurs DHT11 (Température et Humidité) et IAQ Core C (Indoor Air quality sensor)**. On envoie les données capturées vers un serveur **TTN** depuis l'**Arduino Leonardo** via une passerelle *Lora*. Ces données vont ensuite être exploité par un serveur **Node-red** qui se charger de les sauvegarder dans une Base de donnée **InluxDB** et de les affichées sous forme de graphique. 
## Tâches : 
 La réalisation de notre solution se subdivise en plusieurs tâche : 
* **Tâche 2 :** Lire les données **(CO2 et COV)** du capteur **IAQ Core c** depuis la **Raspberry PI**  et les transmettre à l'**Arduino Leonardo**. 
* **Tâche 3 :** Lire les données **(température et humidité)** du capteur **DHT11** depuis la carte **Arduino Leonardo**, recevoir les données du capteur **IAQ Core C** depuis la **Raspberry PI** et envoyer tous les données capturés au serveur **TTN**
* **Tâche 4 :**  Installer et configurer une **passerelle TTN** dans lequel on rajouter une **Application** et on enregistre notre **objet connecté**.
* **Tâche 5 :**  Récupérer les données de captures  depuis le serveur **TTN** vers un serveur en vu de les sauvegarder et  de les rendre compréhensible par une requête HTML.
* **Tâche 6 :** Automatiser le déploiement de notre application.

### Tâche 1 : 
Pour la réalisation de la tâche 1, on va utiliser un code c++ se trouvant dans le fichier **iaqCore.c++**. 
Maintenant, pour rendre ce code exécutable sur la Raspberry Pi on doit le compiler. Pour ce faire, on utilise **g++** qui est un excellent compilateur pour C++.
Pour l'installer, taper : 
``` 
   sudo apt-get update 
   sudo apt-get install g++
```
Pour compiler le code, se localiser dans le dossier source du code **c++** et taper : 
``` 
    g++ /*.c /*.cpp -o final
```
Et pour l'éxecuter, il faut taper : 
``` 
   ./final
```
Ainsi la tâche 1 est réalisée. On peut maintenant lire les données capteur **IAQ Core C** et les envoyer à l'**Arduino Leonardo**.

### Tâche 2 : 
Pour la réalisation de la tâche 2, on a besoin d'installer l'application **arduino** pour pouvoir manipuler les cartes **Arduino**.
Pour l'installer, taper : 
``` 
   sudo apt-get update
   sudo apt-get install arduino
```
On installe maintenant les **library** nécessaire au bon fonctionnement de notre code à savoir : 
- ThethingsNetwork
- Adafruits Unified Sensor
Pour installer une **library**, on clicque sur : 
**Croquis** dans le ménu > puis sur inclure une Bibliothèque > et dans la fénêtre qui s'ouvre on tape le nom de la bibliothèque qu'on veut ajouter .

Une fois ces **Library** installés, on compile le code *DHT_IAQ.ino* et on le téléverse sur l'**arduino**.

### Tâche 3 : 
On va mettre en place notre serveur. On va installer **Node-red**. 
Pour ce faire, on va installer d'abord **nodeJs** avec :
``` 
    sudo apt-get update
    sudo apt-get install nodejs
```
On utilise maintenant **npm** pour installer node-red en mode gloabal et on le lannce.

``` 
    sudo npm install -g node-red
    node-red
```
Une fois **node-red** installé, on va installer les nodes : 
- node-red-contrib-mqtt-broker
- node-red-contrib-influxdb
- node-red-dashboard


Pour insataller un module, il faut proceder comme suite : 
Cliquer sur le menu > cliquer sur Manage >  puis dans l'onglet **install** taper le nom du module >  Et installer le module.

Maintenant, on va importer notre schéma **Node-red**. Voici ci-dessous un aperçu des nodes.

![Image du choix de Manage dans le Menu](/images/1.png)

![Image de recherche du module](/images/2.png)

On importe le fichier **flowns.json** depuis le dossier */flows* . 
Dabord, on télécharge ce fichier. Ensuite on clique sur le **menu>import> puis on selectionne le fichier flowns.json** .

Le serveur **node-red** est en place ! Maintenant il nous faut installer la base de donnée **influxDB**.

Voici [un lien](https://docs.influxdata.com/influxdb/v1.8/introduction/install/) vers comment installer cette base de donnée selon votre OS. 

Une fois la base de donnée créée, on va créer un utilisateur qui nous permettra depuis **node-red** d'accéder à la BDD.
* **username** : alassane_samia
* **password** : alassane_samia

Dans un terminal de la machine serveur, on lance un client **influx**.
Dans le client, on tape : 
```sql
 CREATE USER alassane_samia WITH PASSWORD 'alassane_samia' WITH ALL PRIVILEGES
```
Mainteanant, on peut déploier notre solution **node-red** et après pour y accéder,  on tape dans le navigateur :
```http
http://"adresse du serveur node-red":1800/ui
```
## Tache 4:
Pour installer une passerelle The Things Network, nous devons disposer d'un ordinateur muni d'une carte wifi.
En effet, la seconde étape consiste à se connecter à un réseau wifi fournit par la passerelle.
L'installation se fait en 4 étapes :
 - Enregistrement
 - Connexion
 - Configuration
 - Premier message
Pour procéder à l'enregistrement de la passerelle sur les serveurs de **TheThingsNetwork** (TTN), on connecte à l'adresse suivante : 
```https
https://activate.thethingsnetwork.org/
```
Pour réaliser dans les différentes étapes, on suit le tutoriel vidéo suivant :
```https
https://www.youtube.com/watch?v=cJNK4y1is2Q
```
**Ajout d'une application**

Pour ajouter une application, à partir de la console, on clique sur **APPLICATIONS**.

Par Applications, il faut entendre tout ce que vos objets communiquent sur Internet. On peut également voir
une application comme une collection d'objets (Devices). Pour pouvoir enregistrer un objet connecté sur la
passerelle, il faut nécessairement disposer d'une application dans laquelle le ranger.

Si vous ajouter votre première application, vous pouvez cliquer sur Get started by adding one, sinon cliquez
sur **+ add application**

Voici un tutorial vidéo montrant en détail les étapes à suivre:
```https
    Tutoriel video : https://www.youtube.com/watch?v=JrNjY-pGuno
```
On complète dans le formulaire les champs Application ID et Description. Laissons The Things Network décider
de l'attribution d'un identifiant Application EUI (Extended Unique Identifier).

Cliquez sur le bouton Add application en bas de la page. Nous pouvons maintenant ajouter des objets
connectés à cette application.

**Ajout d'un objet connecté**
Nous allons ajouter les deux capteurs **DHT** et **IAQ** construits autour de la carte The Things Uno
qui intègre une puce LoRa de chez Microchip.

A ce stade, les différentes étapes de configuration sont montrées sur le tutorial suivant:
```https
   https://www.youtube.com/watch?v=28Fh5OF8ev0
```


## Tache 5:
Le bash !



 







