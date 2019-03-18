# Projet MQTT 

# Rachida ZONGO 
# Boukadida Imen


Préparation de l'environnement avant de lancer 

1) installer un client Serveur Mosquitto  "https://mosquitto.org/download/"

2) Dans un invite de commande lancer : 
    cd "Path ou ou vous avez installer mosquitto " exemple :"C:\ProgramFiles\mosquitto"
    puis : mosquitto_sub -t "UCA/Batiments/salles/temp"
3) Dans un autre invite de commande lancer : 
     cd "Path ou ou vous avez installer mosquitto"
     puis : mosquitto_pub -t "UCA/Batiments/salles/temp"
4) coté Arduino : 
    brancher comme suite : 
    portOneWire = 23;
    Led sur le port :25; 