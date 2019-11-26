#include "mbed.h"
#include "ultrasonic.h"

Timer timer;
//Serial pc(PC_4, PC_5, 9600); //datan lahettamista nucleolle varten vaihdettu USBRX,USBTX
Serial pc(USBTX, USBRX, 9600);
AnalogIn Analog(A0);


float mitattuJannite=0.0;
float resisX = 0.0;   //kOhm
float resisKiintea = 12.0; //kOhm
float kayttoJannite = 3.3;
float lampotila = 0.0;
void dist();

 void dist(int distance)
{
    
	if(distance >= 200)
	{
		pc.printf("xD\r\n");
	}
	//put code here to happen when the distance is changed
    pc.printf("Distance changed to %dmm\r\n", distance);
	
}
 
 
 ultrasonic mu(D8, D9, .1, 1, &dist);    //Set the trigger pin to D8 and the echo pin to D9
                                        //have updates every .1 seconds and a timeout after 1
                                        //second, and call dist when the distance changes

int main()
{

timer.start();
timer.reset();
mu.startUpdates();//start mesuring the distance
        while(true)
        {
			      
                mitattuJannite = Analog.read() * 4095;  
				mitattuJannite = mitattuJannite*kayttoJannite / 4095;
				
				resisX = resisKiintea*(kayttoJannite / mitattuJannite - 1);
				
				//kuudennen asteen yhtälö välillä 11-30 celsiusastetta
				lampotila =  -0.0000691587 * resisX * resisX * resisX * resisX * resisX * resisX + 0.0051836483 * resisX * resisX * resisX * resisX * resisX - 0.1591504122 * resisX * resisX * resisX * resisX + 2.5476082216 * resisX * resisX * resisX - 22.1794229228 * resisX * resisX + 95.9356475493 * resisX - 121.7370727433;
				pc.printf("%3.3f",lampotila);
				pc.printf("\r\n");
				
				mu.checkDistance();     //call checkDistance() as much as possible, as this is where
                                //the class checks if dist needs to be called.
				wait(0.1);
        }
}
