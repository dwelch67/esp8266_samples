
#define GPIO_ENSET     (*((volatile unsigned int *)0x60000310 ))
#define GPIO_OUTSET     (*((volatile unsigned int *)0x60000304 ))
#define GPIO_OUTCLR     (*((volatile unsigned int *)0x60000308 ))
#define IOMUX_GPIO2 (*((volatile unsigned int *)0x60000838 ))
void notmain ( void )
{
    IOMUX_GPIO2 &= ~0x130;
    GPIO_ENSET = 1<<2;
    GPIO_OUTSET = 1<<2;
    while(1) continue;
}


