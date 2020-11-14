#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <string.h>
#include "rs232.h"
#include "ci2c.h"

#define IAQCOREC_ADDRESS 0x5A  // Device I2C Address

using namespace std;

int itoa(int n, char * dest ){
    if(n==0){
        dest[0]=0;
        return 0;
    }else if(n<10){
        dest[0]='0'+n;
        dest[1]=0;
        return 1;
    }else{
        int index = itoa(n/10, dest);
        dest[index]= n%10+'0';
        dest[index+1]=0;
        return index+1;
    }
}

int main()
{
  int cport_nr=24; //dev/ttyUSB0 
  int bdrate=9600; // 9600 baud
  char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

  int co2, cov, status;
  char co2_c[5],cov_c[2];
  
	unsigned char buff[11];
  
  Ci2c *iaqcorec;
	iaqcorec = new Ci2c('1',IAQCOREC_ADDRESS);
  
  if(RS232_OpenComport(cport_nr, bdrate, mode)){
    cout << "Can not open comport\n" << endl;
    return(0);
  }
  
  //usleep(2000000);
  sleep(2);

  while(1) {
		
		iaqcorec->readFromI2C(buff, 9);
		co2 = buff[0]*256+buff[1];
		cov = buff[7]*256+buff[8];
  
    itoa(co2, co2_c);
    itoa(cov, cov_c);
    strcat(co2_c, "/");
    strcat(co2_c, cov_c);
    
    status = buff[2];
    
    //usleep(3000000);
    sleep(3);
    
		switch(status) {
      
			case 0:
				//cout << "CO2 = " << co2 << " -  COV = " << cov << endl;
        cout << co2_c  << endl;
        RS232_cputs(cport_nr, co2_c );  
        //usleep(5000000);
        //sleep(5);
				break;
			
			case 1: 
				cout << "Busy : wait for updated datas" << endl;
				break;
			
			default: 
				cout << "Error : non-realistic values" << endl;
    }
    //usleep(10000000);
    sleep(22);
  }
  return(0);
}
