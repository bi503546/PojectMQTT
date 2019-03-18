# Projet MQTT 

# Rachida ZONGO 
# Boukadida Imen


# Préparation de l'environnement avant de lancer 

1) installer un client Serveur Mosquitto  "https://mosquitto.org/download/"


2) coté Arduino : 
    brancher comme suite : 
    portOneWire = 23;
    Led sur le port :25
    puis lancer le script "mqtt_full.ino"

# Exécution 

1) Dans un invite de commande lancer : 
    cd "Path ou ou vous avez installer mosquitto " exemple :"C:\ProgramFiles\mosquitto"
    puis : mosquitto_sub -t "UCA/Batiments/salles/temp"
2) Dans un autre invite de commande lancer : 
     cd "Path ou ou vous avez installer mosquitto"
     puis : mosquitto_pub -t "UCA/Batiments/salles/temp"
