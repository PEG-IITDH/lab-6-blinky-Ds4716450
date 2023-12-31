#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
/* SysTick memory-mapped registers */
#define STCTRL *((volatile long *) 0xE000E010)    // control and status
#define STRELOAD *((volatile long *) 0xE000E014)    // reload value
#define STCURRENT *((volatile long *) 0xE000E018)    // current value

#define COUNT_FLAG  (1 << 16)   // bit 16 of CSR automatically set to 1
                                //   when timer expires
#define ENABLE      (1 << 0)    // bit 0 of CSR to enable the timer
#define CLKINT      (1 << 2)    // bit 2 of CSR to specify CPU clock

#define CLOCK_MHZ 16
/**
 * main.c
 */
int main(void)
{

    int x;
    x = 1;
    x = x+1;
//  while (1) ;

    SYSCTL_RCGC2_R |= 0x00000020;;      /* enable clock to GPIOF */
        GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
        GPIO_PORTF_CR_R = 0x01;             /* make PORTF0 configurable */
        GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF3+PORTF2+PORTF1 pin as output (LED) pin */
                                            /* and PORTF4 and PORTF0 as input, SW1 is on PORTF4  and SW2 is PORTF0*/
        GPIO_PORTF_DEN_R = 0x1F;            /* set PORTF pins 4-3-2-1 as digital pins */
        GPIO_PORTF_PUR_R = 0x11;            /* enable pull up for pin 4 and 0 */

        /*GPIO_PORTF_DATA_R = 0x0;
        GPIO_PORTF_DATA_R = 0x2;
        GPIO_PORTF_DATA_R = 0x4;
        GPIO_PORTF_DATA_R = 0x8;
        GPIO_PORTF_DATA_R = 0xE;*/
while(1)
{
    GPIO_PORTF_DATA_R = 0x2;
    Delay(3200);
    GPIO_PORTF_DATA_R = 0x0;
    Delay(12800);
}



}

void Delay(int ms)
{
    STRELOAD = ms;                       // reload value for 'ms' milliseconds
    STCTRL |= (CLKINT | ENABLE);        // set internal clock, enable the timer

    while ((STCTRL & COUNT_FLAG) == 0)  // wait until flag is set
    {
        ;   // do nothing
    }
    STCTRL = 0;                // stop the timer

    return;
}

