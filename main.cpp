#include "mbed.h"



Serial pc(USBTX, USBRX, 9600);

AnalogIn Analog(A0);


float mitattuJannite=0.0;
float resisX = 0.0;   //kOhm
float resisKiintea = 12.0; //kOhm
float kayttoJannite = 3.3;
float lampotila = 0.0;

void temp();


	// laskee ja printtaa lämpötilan
 void temp(float mJannite)
 {
	 
	mJannite = mJannite*kayttoJannite / 4095;
	
	resisX = resisKiintea*(kayttoJannite / mJannite - 1);
	
	//kuudennen asteen yhtälö välillä 11-30 celsiusastetta
	
	lampotila =  -0.0000691587 * resisX * resisX * resisX * resisX * resisX * resisX + 0.0051836483 * resisX * resisX * resisX * resisX * resisX - 0.1591504122 * resisX * resisX * resisX * resisX + 2.5476082216 * resisX * resisX * resisX - 22.1794229228 * resisX * resisX + 95.9356475493 * resisX - 121.7370727433;
	pc.printf("%3.1f\n",lampotila);
	
 }	 
 
 

int main()
{

        while(true)
        {
			     
				  
                mitattuJannite = Analog.read() * 4095; 
				temp(mitattuJannite);
								
        }
}
