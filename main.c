/*
 * This program ilustrates how to implement binary search algorithem.
 * The user provide randomal value and the program searchs this value
 * in the given array. If the value is found the led is blinking.
 *
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define N 10    //maximum integers in an array

int PinData=2;  //Set bit two in the PortF (turning on red led)

//-------------Function declarations------------------------
void LedHandler(void); //This function handels led operation
bool BinarySearch(unsigned long *A, unsigned long n, unsigned long data); //Binary search function

//-----------------------MAIN-------------------------------
int main(void)
{
	unsigned char i=0;
	unsigned long array[N];
	unsigned long Data = 8; //Data that needed to be found in the array

	/*The system will be driven by using 16MHz crystal on the main oscilator with
	 * using PLL whose output is 400MHz with a default pre divisor 2 and we devided
	 * by 5 divisor so the system closk is 40MHz
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	//Enable PortF
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//Set pin1 as output (Red Led)
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

	//initialize array with integers
	for(i=0; i < N; i++)
	{
		array[i] = i;
	}

	while(1)
	{
		if(BinarySearch(array, N, Data))
			LedHandler();
	}
}//end main

//=======================Function definitions===============================
/*
 * This function handles red led
 * input: none
 * output: none
 */
void LedHandler(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, PinData); //turn on led
	SysCtlDelay(2000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);    //turn off led
	SysCtlDelay(2000000);
}//end function

/*
 * This function performs binary searching in given array
 * input: pointer to array of integers, size of array, and data to be found
 * output: boolian value, the data exist or not
 */
bool BinarySearch(unsigned long *A, unsigned long n, unsigned long data)
{
	unsigned long Low, High, Mid;
	Low = 0;
	High = N-1;

	//Binary search algorithem
	while(Low <= High)
	{
		Mid =Low + (High - Low)/2;

		if(A[Mid] == data)
			return true; // data has found in given array
		else if(A[Mid] > data)
		{
			High = Mid-1;
		}
		else
		{
			Low = Mid + 1;
		}
	}
	return false;       // data has not found in given array
}//end function

































