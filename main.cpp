#include "mbed.h"


Timer timer;
Serial pc(USBTX,USBRX);

AnalogIn Analog(A0);


float mitattuJannite=0.0;
float resisX = 0.0;   //kOhm
float resisKiintea = 12.0; //kOhm
int kayttoJannite = 3.3;
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
				
				lampotila = -0.0006378702 * resisX * resisX * resisX * resisX + 0.0188925779 * resisX * resisX * resisX - 0.0015604745*resisX * resisX - 5.4012695435*resisX + 66.6828443378;
				pc.printf("%f",lampotila);
				pc.printf("\r\n");
				
				wait(0.5);
        }
}
