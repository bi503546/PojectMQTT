# Projet MQTT - Master 1 Miage - IoT


#Membres du projet 
- Rachida ZONGO 
- Boukadida Imen


# Préparation de l'environnement avant de de faire le téléversement 

1) installer un client/Serveur Mosquitto  "https://mosquitto.org/download/"


2) coté Arduino : 

#-------Code---------# 

    - Ouvrez le fichier "mqtt_full.ino" avec Arduino IDE
    - Allez dans Outils -> Gérer les bibliothéques -> "WiFi", "PubSubClient", "Wire"
    - Dans la ligne 16 du fichier modifiez la variable mqtt_server en mettant votre adresse IP
    - Dans la méthode connect_wifi() -> modifier ssid="votre_nom_de_connexion_WiFi" et password ="mot_de_passe_WiFi"
    
    - dernière configuration : 
    Allez dans votre pare-Feu -> Règles de trafic entrant -> Nouvelle règle -> Port -> Suivant -> TCP -> dans Ports locaux spécfiques ecrivez 1883 -> Suivant -> Autorisez la connexion -> Suivant -> Suivant -> donnez un Nom -> Terminer

#-------Branchement-------#

    - brancher comme suite : 
        portOneWire pour le capteur de température sur le port : 23;
        Led representant le radiateur sur le port : 25;

# Exécution 

1) Dans un invite de commande lancer : 
    cd "Path ou ou vous avez installer mosquitto " exemple :"C:\ProgramFiles\mosquitto"
    puis : mosquitto_sub -t "UCA/Batiments/salles/temp"
2) Dans un autre invite de commande lancer : 
     cd "Path ou ou vous avez installer mosquitto"
     puis : mosquitto_pub -t "UCA/Batiments/salles/temp"
3) Une fois finaliser le branchement de l'ESP32, téleverser le code.