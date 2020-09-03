/*
 * 
 * Description: Program accepts user input, processes the logic, and sends 
 * appropriate calls to circuitry in order to package pills into box.
 * 
 * Preconditions:
 *   1. Character LCD in a PIC socket
 *   2. Co-processor is running default keypad encoder program
 *   3. Arduino Nano is plugged into the board 
 */


/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "global-variables.h"
#include "UART_PIC.h"

/***** Constants *****/
const char keys[] = "123RESMFOABL*N#e";
int done = 0;



void main(void){   
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /********************************* PIN I/O ********************************/
    /* Write outputs to LATx, read inputs from PORTx. Here, all latches (LATx)
     * are being cleared (set low) to ensure a controlled start-up state. */  
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    UART_Init(9600); 
    
    int res = user_interface(); //Obtain user input 
    
    printSummary(); //Print summary of user input
    findMode(); //Find which way box is inserted - 0 or 1
    placeMarkers(); // this places markers in the array where the pills should go
    sendPillRequests(); //send requests to arduino to run appropriate motors 
    
    return;
}


void resetSection(void){
    //resets a section if user made mistake in inputting and requests a redo 
            __lcd_clear();
            
            switch(x){
                case 0: //resetting prescriptions
                    prescription[0] = 'x';
                    prescription[1] = 'x';
                    prescription[2] = 'x';
                    printf("Prescription: ");                    
                    __lcd_newline();
                    break;
                case 1:
                    numPills -= prevPills;
                    num_pills_R_data = '0';
                    printf("# of R pills: ");                    
                    __lcd_newline();
                    break;
                case 2:
                    numPills -= prevPills;
                    num_pills_F_data = '0';
                    printf("# of F pills: ");
                    __lcd_newline();
                    break;
                case 3:
                    num_pills_L_data = '0';
                    numPills -= prevPills;
                    
                    printf("# of L pills: ");
                    __lcd_newline();
                    
                    break;
                case 4:
                    __lcd_clear();
                    frequency_data = '0';
                    printf("Repetition/Day: ");
                    __lcd_newline();
                    break;
                case 5:
                    repetition_data = '0';
                    printf("Day Frequency: ");
                    __lcd_newline();
                    break;
                default:
                    __lcd_clear();
            }
}




int user_interface(void) {
    

    /* Initialize LCD. */
    initLCD();
    
    
    
    /*** USER INTERFACE MAIN CODE ***/
    //x = 0 -- prescription
    //x = 1 -- number of R pills
    //x = 2 -- number of F pills
    //x = 3 -- number of L pills
    //x = 4 -- repetition per day
    //x = 5 -- day frequency
    x = 0; //for reset, ensures program is reset

    while(1){ //prompts user to enter info
        printf("Prescription: ");
        __lcd_newline();

        while(x == 0){ //loop until user enters input - interrupt will set x to 1
                __delay_ms(100);
        }
        if(reset == 1){
            reset = 0;
            continue;
        }

        printf("# of R Pills: ");
        __lcd_newline();

        while(x == 1){
            __delay_ms(100);
        }
        if(reset == 1){
            reset = 0;
            continue;
        }

        printf("# of F Pills: ");
        __lcd_newline();

        while(x == 2){
                __delay_ms(100);
        }
        if(reset == 1){
            reset = 0;
            continue;
        }

        printf("# of L pills: ");
        __lcd_newline();
        
        while(x == 3){
            __delay_ms(100);
        }
        if(num_pills_L_data == '1'){
            __delay_ms(1000); // Wait 1 second
            printf("L3");
            __delay_ms(1000);
            }
        if(reset == 1){
            if(num_pills_L_data == '1'){
            __delay_ms(1000); // Wait 1 second
            printf("L2");
            __delay_ms(1000);
            }
            reset = 0;
            continue;
        }
        if(num_pills_L_data == '1'){
        __delay_ms(1000); // Wait 1 second
        printf("L");
        __delay_ms(1000);
        }
        printf("Repetition/Day: ");
        __lcd_newline();

        while(x == 4){
                __delay_ms(100);
        }
        if(reset == 1){
            reset = 0;
            continue;
        }

        printf("Day Frequency: ");
        __lcd_newline();
        while(x == 5){
            __delay_ms(100);
        }
        if(reset == 1){
            reset = 0;
            continue;
        }       
        break;
    }   
    return 0;
}




void printSummary(void){
     //print summary of information
     if(num_pills_R_data == '0'){
        printf("0 R pills");
    } else if(num_pills_R_data == '1'){
        printf("1 R pill");
    } else if(num_pills_R_data == '2'){
        printf("2 R pills");
    }
    
    __lcd_newline();
    __delay_ms(1000);
    __lcd_clear();
    
    if(num_pills_F_data == '0'){
        printf("0 F pills");        
    } else if(num_pills_F_data == '1'){
        printf("1 F pill");        
    } else if(num_pills_F_data == '2'){
        printf("2 F pills");        
    }
    
    __lcd_newline();
    __delay_ms(1000);
    __lcd_clear();
    
    if(num_pills_L_data == '0'){
        printf("0 L pills"); 
    } else if(num_pills_L_data == '1'){
        printf("1 L pill"); 
    } else if(num_pills_L_data == '2'){
        printf("2 L pills"); 
    }
    
    __lcd_newline();
    __delay_ms(1000);
    __lcd_clear();
    
    
    if(frequency_data == '1'){
        printf("Everyday");
        
    } else if(frequency_data == '2'){
        printf("Alt days - Sunday");
        
    } else if(frequency_data == '3'){
        printf("Alt days - Monday");
        
    }
    
    __lcd_newline();
    __delay_ms(1000);
    __lcd_clear();
    
    if(repetition_data == '1'){
        printf("Morning");
    } else if(repetition_data == '2'){
        printf("Afternoon");
    } else if(repetition_data == '3'){
        printf("Morning & Afternoon");
    } else if(repetition_data == '4'){
        printf("Alt Morn & Aft");
    } 

    __lcd_clear();
    
    
    
}


void interrupt interruptHandler(void){
    
    if(INT1IF){
        /* Interrupt on change handler for RB1. */
        
        /* Write key press data to bottom line of LCD. */
        
        //unsigned char done = 0;
        
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        char k = keys[keypress];
        putch(keys[keypress]);
            
            
            if(x ==0){ //pres mode
                
                if(k == 'R'){ //stores R, F, L into array to be processed later 
                    
                    //putch(keys[keypress]); //display key press
                    //printf("debug3");
                    prescription[0] = 'R';
                    
                    
                } else if (k == 'F'){
                     //display key press
                    prescription[1] = 'F';
                } else if (k == 'L'){
                    //putch(keys[keypress]); //display key press
                    prescription[2] = 'L';
                }         
                 
            } 
            
            
            else if(x == 1) { //updates num of pills
                if(k == '1'){
                    prevPills = numPills;
                    numPills++;
                    //putch(keys[keypress]); //display key press
                    if(numPills < 5){ //check num of pills already in compartment
                        
                            num_pills_R_data = k;
                            //printf("R data saved");
                            __delay_ms(1000);  

                        } else{
                        __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                            resetSection();
                        }      
                } else if (k == '2'){
                    prevPills = numPills;
                    numPills += 2;
                    //putch(keys[keypress]); //display key press
                } else if (k == '3' || k == 'E' || k == 'S' || k == 'M' || k == 'F' || k == 'O' || k == 'A' || k == 'B' || k == 'L' || k == 'N'){
                    __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                    resetSection();
                }
                
                
            } 
            
             else if(x == 2) { //updates num of pills
                if(k == '1'){
                    prevPills = numPills;
                    numPills++;
                    
                   if(numPills < 5){ //check num of pills already in compartment
                            num_pills_F_data = k;
                            
                            __delay_ms(1000);  

                        } else{
                            __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);    
                            resetSection();
                        }
                    
                } else if (k == '2'){
                    prevPills = numPills;
                    numPills += 2;
                    
                } else if(k == '3' || k == 'E' || k == 'S' || k == 'M' || k == 'F' || k == 'O' || k == 'A' || k == 'B' || k == 'L' || k == 'N'){
                    __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                    resetSection();
                }
             }
            else if (x == 3){
                prevPills = numPills;
                 if (k == 'E' || k == 'S' || k == 'M' || k == 'F' || k == 'O' || k == 'A' || k == 'B' || k == 'L' || k == 'N'){
                    __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                    resetSection();
                }
                switch(k){ //updates current number of pills
                    case '1':
                        numPills++;
                        break;
                    case '2':
                        numPills+=2;
                        break;
                    case '3':
                        numPills+=3;
                        break;
                }
                if(numPills < 5){ //check num of pills already in compartment
                            num_pills_L_data = k;
                            if(num_pills_L_data == '1'){
                            //printf("L data saved");
                            __delay_ms(1000);  
                            }
                            
                        } else{
                            __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                            resetSection();
                        }
            }
            else if (x == 4){
                 
                if(k == 'O'){
                    repetition_data = '1';
                } else if(k == 'A'){
                    repetition_data = '2';
                } else if(k == 'B'){
                    repetition_data = '3';
                } else if(k == 'N'){
                    repetition_data = '4';
                } else if(k == '1' || k == '2' || k == '3' || k == 'E' || k == 'S' || k == 'M' || k == 'F' || k == 'L'|| k == 'R'){
                    __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                    resetSection();
                }
                
                
            } else if (x == 5){
                
                if(k == 'E'){
                    frequency_data = '1';
                } else if(k == 'S'){
                    frequency_data = '2';
                } else if(k == 'M'){
                    frequency_data = '3';
                } else if(k == '3' || k == '1' || k == '2' || k == 'R' || k == 'F' || k == 'O' || k == 'A' || k == 'B' || k == 'L' || k == 'N'){
                    __lcd_newline();
                    __delay_ms(100);
                    printf("Invalid input");
                    __delay_ms(2000);
                    resetSection();
                }
            }
            
        
        if(keypress == 0x0F) {            
            //enter was inputted
            unsigned char keypress = (PORTB & 0xF0) >> 4;
            char k = keys[keypress];
            switch(x){
                case 0:
                    __lcd_clear();
                    savePrescriptionInfo();
                    x = 1;
                    break;
                    
                case 1:
                    __lcd_clear();                       
                    x = 2;                    
                    break; 
                    
                case 2:
                    x = 3;
                    break;
                case 3:
                    __lcd_clear();
                    
                    x=4;
                    break;
                case 4:
                    __lcd_clear();
                    x = 5;
                    break;
                case 5:
                    __lcd_clear();
                    x = 6;
                    break;    
                default: 
                    __lcd_clear();
                    x = 6; 
            }        }
        else if (keypress == 0x0E){
            resetSection();
        }
        
        else if (keypress == 0x0C){
            __lcd_clear();
            x = 9;
            reset = 1;
            
        }INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
    }
}


