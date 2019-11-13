#include "mbed.h"


Timer timer;
Serial pc(PC_4, PC_5, 9600); //datan lahettamista nucleolle varten vaihdettu USBRX,USBTX

AnalogIn Analog(A0);


float mitattuJannite=0.0;
float resisX = 0.0;   //kOhm
float resisKiintea = 12.0; //kOhm
float kayttoJannite = 3.3;
float lampotila = 0.0;

int main()
{

timer.start();
timer.reset();
        while(true)
        {
			      
                mitattuJannite = Analog.read() * 4095;  
				mitattuJannite = mitattuJannite*kayttoJannite / 4095;
				
				resisX = resisKiintea*(kayttoJannite / mitattuJannite - 1);
				
				//kuudennen asteen yhtälö välillä 11-30 celsiusastetta
				lampotila =  -0.0000691587 * resisX * resisX * resisX * resisX * resisX * resisX + 0.0051836483 * resisX * resisX * resisX * resisX * resisX - 0.1591504122 * resisX * resisX * resisX * resisX + 2.5476082216 * resisX * resisX * resisX - 22.1794229228 * resisX * resisX + 95.9356475493 * resisX - 121.7370727433;
				pc.printf("%3.3f",lampotila);
				pc.printf("\r\n");
				
				//wait(0.5);
        }
}
