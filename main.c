#include <p18f4520.h>
#include <stdio.h>

// Function prototypes
void uart_init(void);
void uart_tx(unsigned char);
void tx_string(const rom char *text); 
void adc_init(void);
unsigned int adc_read(unsigned char); 
void delay_ms(unsigned int ms); // Added custom delay prototype

void main(void)
{
    unsigned char faults;
    unsigned int ldr;
    int i; 
    TRISAbits.TRISA0 = 1;
    TRISB = 0x00; 
    TRISD = 0x7F; // RD0 to RD6 as inputs for fault detection
    LATB = 0x00;
    
    uart_init();
    adc_init();
    
    tx_string("Smart City System Initialized...\r\n");
    
    while(1)
    {
        ldr = adc_read(0); // Read AN0
        
        if(ldr < 512) // Night time
        {
            LATB = 0x7F; // Turn on 7 lamps (RB0 - RB6)
            
            // Mask out the 8th bit since we only care about 7 lamps
            faults = PORTD & 0x7F; 
           
            if(faults == 0)
            {
                tx_string("Status: Night - ALL Lamps are running properly - No Fault\r\n");
            }    
            else
            {
                tx_string("ALERT: Night - Lamp faults detected!\r\n");
            
                for(i = 0; i < 7; i++)
                {
                    if((faults >> i) & 1)
                    {
                        tx_string("---> Lamp "); 
                        uart_tx('1' + i);
                        tx_string(" is broken\r\n"); 
                        
                        // Turn off the specific broken lamp on PORTB
                        LATB &= ~(1U << i); 
                    }            
                }
            }
        }       
        else // Day time
        {
            LATB = 0x00; // Turn off all lamps
            tx_string("Status: Daytime - All lamps OFF \r\n");
        } 
        
        // Replaced __delay_ms with a C18-compatible custom delay function
        delay_ms(2000); 
    }          
}          

void uart_init(void)
{
    TRISCbits.TRISC6 = 0; // TX pin as output
    TRISCbits.TRISC7 = 1; // RX pin as input 
    TXSTA = 0x24;         // TXEN = 1, BRGH = 1
    RCSTA = 0x90;         // SPEN = 1, CREN = 1
    SPBRG = 51;           // 9600 Baud at 8MHz
}    

void uart_tx(unsigned char c)
{
    while(TXSTAbits.TRMT == 0); // Wait for shift register to empty
    TXREG = c;
}    

void tx_string(const rom char *text)
{
    while(*text != '\0')
    {
        uart_tx(*text);
        text++;
    }    
}    

void adc_init(void)
{
    ADCON0 = 0x01; // Enable ADC, Channel 0 (AN0) selected
    ADCON1 = 0x00; // AN0 is Analog, rest are Digital, VREF = VDD/VSS
    ADCON2 = 0x94; // Right justified, 2 TAD, FOSC/32
}

unsigned int adc_read(unsigned char channel)
{
    int j; 
    ADCON0bits.CHS = channel; 
    
    // Quick software acquisition delay for internal capacitor
    for(j = 0; j < 20; j++);    
    
    ADCON0bits.GO = 1;         // Start conversion
    while(ADCON0bits.GO == 1); // Wait for completion
    
    return (((unsigned int)ADRESH << 8) + ADRESL);
}

// Custom 1ms baseline delay loop calibrated for an 8MHz system clock
void delay_ms(unsigned int ms)
{
    unsigned int x;
    int y;
    for(x = 0; x < ms; x++)
    {
        for(y = 0; y < 165; y++); 
    }
}
