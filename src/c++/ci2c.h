/***************************************************************
*   Classe de bas niveau de gestion du bus i2c
*
*   - fileI2c : Descripteur du pseudo-fichier i2c (/dev/i2c-*)
*   - addrSlave :Adresse de l'esclave sur le bus i2c
*   - Ci2c : Nécessite le numéro du bus et l'adresse de l'esclave
*   - readFromI2c : lecture de données sur le bus
*   - writeToI2c : écriture de données sur le bus
* 
*   Auteur : Marc Silanus
*   date : 04/04/2016
*   rev 0
*
***************************************************************/ 

#ifndef CI2C_H
#define CI2C_H

#include <unistd.h>			//Needed for I2C port
#include <fcntl.h>			//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <iostream>
#include <string.h>

class Ci2c
{
public:
    int fileI2c;
    int addrSlave;

    Ci2c(char i2cBus, int addr);
    ~Ci2c();
    int readFromI2C(unsigned char *buffer,int length);
    int writeToI2C(unsigned char *buffer, int length);
};

#endif // CI2C_H
