#include <xc.h>
#include "configBits.h"
#include "global-variables.h"
#include "lcd.h"
#include "UART_PIC.h"
void findMode(void){
   unsigned char arr[1] = {'Z'}; 
    __delay_ms(1000);
    uartTransmitBlocking(arr, 1);
    LATCbits.LATC6 = 0; //input
    int input = PORTCbits.RC6;
    int flag = 1;
    while(flag == 1){
        if(input == 1){
            modeOfOperation = '1';
            break;
        } else{
            modeOfOperation = '0';
            break;
        }
    }
    
     
    
}

void savePrescriptionInfo(void){ //saves info from prescription array to data variable
    //printf("debug");
    if(prescription[0] == 'R' && prescription[1] == 'x' && prescription[2] == 'x'){ //just R
        //printf("debug2");
        prescription_data = '1';
    } else if(prescription[0] == 'x' && prescription[1] == 'F' && prescription[2] == 'x'){ //just F
        prescription_data = '2';
    } else if(prescription[0] == 'x' && prescription[1] == 'x' && prescription[2] == 'L'){ //just L
        prescription_data = '3';
    } else if(prescription[0] == 'R' && prescription[1] == 'F' && prescription[2] == 'x'){ //RF
        prescription_data = '4';
    } else if(prescription[0] == 'R' && prescription[1] == 'L' && prescription[2] == 'x'){ //RL
        prescription_data = '5';
    } else if(prescription[0] == 'x' && prescription[1] == 'F' && prescription[2] == 'L'){ //FL
        prescription_data = '6';
    } else if(prescription[0] == 'R' && prescription[1] == 'F' && prescription[2] == 'L'){ //RFL
        prescription_data = '7';
    }
}


int placeMarkers(void){
    switch(modeOfOperation){
        
        case '1': //sat-sun
            if(repetition_data == '1'){ //O - morning
                if(frequency_data == '1'){ //E - everyday
                pillBox[0] = 'y';
                pillBox[2] = 'y';
                pillBox[4] = 'y';
                pillBox[6] = 'y';
                pillBox[8] = 'y';
                pillBox[10] = 'y';
                pillBox[12] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[12] = 'y';
                pillBox[8] = 'y';
                pillBox[4] = 'y';
                pillBox[0] = 'y';
                }else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[10] = 'y';
                pillBox[6] = 'y';
                pillBox[2] = 'y';
                }
            }             
            
            else if(repetition_data == '2'){ //A - afternoon
                if(frequency_data == '1'){ //E - everyday
                pillBox[1] = 'y';
                pillBox[3] = 'y';
                pillBox[5] = 'y';
                pillBox[7] = 'y';
                pillBox[9] = 'y';
                pillBox[11] = 'y';
                pillBox[13] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[13] = 'y';
                pillBox[9] = 'y';
                pillBox[5] = 'y';
                pillBox[1] = 'y';
                } 
                else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[11] = 'y';
                pillBox[7] = 'y';
                pillBox[3] = 'y';
                }    
            } 
           
            else if(repetition_data == '3'){ //B - both morning and afternoon
                if(frequency_data == '1'){ //E - everyday
                pillBox[0] = 'y';
                pillBox[2] = 'y';
                pillBox[4] = 'y';
                pillBox[6] = 'y';
                pillBox[8] = 'y';
                pillBox[10] = 'y';
                pillBox[12] = 'y';
                pillBox[1] = 'y';
                pillBox[3] = 'y';
                pillBox[5] = 'y';
                pillBox[7] = 'y';
                pillBox[9] = 'y';
                pillBox[11] = 'y';
                pillBox[13] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[13] = 'y';
                pillBox[9] = 'y';
                pillBox[5] = 'y';
                pillBox[1] = 'y';
                pillBox[12] = 'y';
                pillBox[8] = 'y';
                pillBox[4] = 'y';
                pillBox[0] = 'y';
                } 
                else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[11] = 'y';
                pillBox[7] = 'y';
                pillBox[3] = 'y';
                pillBox[10] = 'y';
                pillBox[6] = 'y';
                pillBox[2] = 'y';
                } 
            } 
            else if(repetition_data == '4') { //N - alternate morning and afternoon
                if(frequency_data == '1'){ //E - everyday
                    pillBox[12] = 'y';
                    pillBox[11] = 'y';
                    pillBox[8] = 'y';
                    pillBox[7] = 'y';
                    pillBox[4] = 'y';
                    pillBox[3] = 'y';
                    pillBox[0] = 'y';
                } 
                else if(frequency_data == '2'){ //S - every other day starting sunday
                    pillBox[12] = 'y';
                    pillBox[9] = 'y';
                    pillBox[4] = 'y';
                    pillBox[1] = 'y';
                }
                else if(frequency_data == '3'){ //M - every other day starting monday
                    pillBox[10] = 'y';
                    pillBox[7] = 'y';
                    pillBox[2] = 'y';
                }
            }
        
        case '2': //sun-sat
            if(repetition_data == '1'){ //O - morning
                if(frequency_data == '1'){ //E - everyday
                pillBox[0] = 'y';
                pillBox[2] = 'y';
                pillBox[4] = 'y';
                pillBox[6] = 'y';
                pillBox[8] = 'y';
                pillBox[10] = 'y';
                pillBox[12] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[12] = 'y';
                pillBox[8] = 'y';
                pillBox[4] = 'y';
                pillBox[0] = 'y';
                }else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[10] = 'y';
                pillBox[6] = 'y';
                pillBox[2] = 'y';
                }
            }             
            
            else if(repetition_data == '2'){ //A - afternoon
                if(frequency_data == '1'){ //E - everyday
                pillBox[1] = 'y';
                pillBox[3] = 'y';
                pillBox[5] = 'y';
                pillBox[7] = 'y';
                pillBox[9] = 'y';
                pillBox[11] = 'y';
                pillBox[13] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[13] = 'y';
                pillBox[9] = 'y';
                pillBox[5] = 'y';
                pillBox[1] = 'y';
                } 
                else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[11] = 'y';
                pillBox[7] = 'y';
                pillBox[3] = 'y';
                }    
            } 
           
            else if(repetition_data == '3'){ //B - both morning and afternoon
                if(frequency_data == '1'){ //E - everyday
                pillBox[0] = 'y';
                pillBox[2] = 'y';
                pillBox[4] = 'y';
                pillBox[6] = 'y';
                pillBox[8] = 'y';
                pillBox[10] = 'y';
                pillBox[12] = 'y';
                pillBox[1] = 'y';
                pillBox[3] = 'y';
                pillBox[5] = 'y';
                pillBox[7] = 'y';
                pillBox[9] = 'y';
                pillBox[11] = 'y';
                pillBox[13] = 'y'; }
                else if(frequency_data == '2'){ //S - every other day starting sunday
                pillBox[13] = 'y';
                pillBox[9] = 'y';
                pillBox[5] = 'y';
                pillBox[1] = 'y';
                pillBox[12] = 'y';
                pillBox[8] = 'y';
                pillBox[4] = 'y';
                pillBox[0] = 'y';
                } 
                else if(frequency_data == '3'){ //M - every other day starting monday
                pillBox[11] = 'y';
                pillBox[7] = 'y';
                pillBox[3] = 'y';
                pillBox[10] = 'y';
                pillBox[6] = 'y';
                pillBox[2] = 'y';
                } 
            } 
            else if(repetition_data == '4') { //N - alternate morning and afternoon
                if(frequency_data == '1'){ //E - everyday
                    pillBox[12] = 'y';
                    pillBox[11] = 'y';
                    pillBox[8] = 'y';
                    pillBox[7] = 'y';
                    pillBox[4] = 'y';
                    pillBox[3] = 'y';
                    pillBox[0] = 'y';
                } 
                else if(frequency_data == '2'){ //S - every other day starting sunday
                    pillBox[13] = 'y';
                    pillBox[8] = 'y';
                    pillBox[5] = 'y';
                    pillBox[0] = 'y';
                }
                else if(frequency_data == '3'){ //M - every other day starting monday
                    pillBox[10] = 'y';
                    pillBox[7] = 'y';
                    pillBox[2] = 'y';
                }
            }             
    } 
    return 0;
}


void sendPillRequests(void){
    unsigned char arr[1] = {'x'};    
    LATCbits.LATC7 = 0; //input
    int input = PORTCbits.RC7;
    for(int i=0; i < sizeof(pillBox); i++){
        if(pillBox[i] == 'y'){ // if there is a marker placed in this spot to place a pill
            if(num_pills_R_data == '1'){
                arr[0] = ('B');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            
                            printf("received 2");
                            __delay_ms(1000);
                            break;
                        }
                    }
            } else if(num_pills_R_data == '2'){
                arr[0] = ('C');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 3");
                            __delay_ms(1000);
                            break;
                        }
                    }
            }         
            
            if(num_pills_F_data == '1'){
                arr[0] = ('D');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 4");
                            __delay_ms(1000);
                            break;
                        }
                    }
            } else if(num_pills_F_data == '2'){
                arr[0] = ('E');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 5");
                            __delay_ms(1000);
                            break;
                        }
                    }
            }
            
            if(num_pills_L_data == '1'){
                          
                arr[0] = ('F');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 6");
                            __delay_ms(1000);
                            break;
                        }
                    }
            } else if(num_pills_L_data == '2'){
                arr[0] = ('G');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 7");
                            __delay_ms(1000);
                            break;
                        }
                    }
            } else if(num_pills_L_data == '3'){
                arr[0] = ('H');
                __delay_ms(1000);
                uartTransmitBlocking(arr, 1);
                __delay_ms(1000); // Wait 1 second
                while(1){
                    __delay_ms(100);
                        if(input == 1){ //wait for arduino to send done signal
                            __lcd_clear();
                            __delay_ms(100);
                            printf("received 8");
                            __delay_ms(1000);
                            break;
                        }
                    }
            }            
        } }
    
    arr[0] = ('e');
    __delay_ms(1000);
    uartTransmitBlocking(arr, 1);
    __delay_ms(1000);
    
}



