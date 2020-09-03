#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H
unsigned char x = 0; //walks through the user interface
unsigned char reset = 0; //global reset variable
unsigned char entryarray[3] = {'0', '0', '0'}; //entries into keypad
unsigned char prescription[3] = {'x', 'x',  'x'}; //prescription
int numPills = 0; //number of pills in the compartment
int prevPills =0;
char pastPres = 'x';
char modeOfOperation = 'x'; //will be 1 or 2 depending on pink or blue for color sensor

int user_interface(void);
char pillBox[14] = {'0', '0', '0', '0','0' ,'0', '0', '0', '0', '0'
                        ,'0', '0', '0', '0'};


char prescription_data = 0; //1-7 correspond to R, F, L, RF, RL, FL, RFL
char num_pills_R_data = '0'; //0, 1, or 2 (can't have 3)
char num_pills_F_data = '0'; //0, 1, or 2 (can't have 3)
char num_pills_L_data = '0'; //0, 1, 2, or 3
char repetition_data = 0; //1, 2, 3, 4 correspond to O, A, B, N
char frequency_data = 0; //1, 2, 3 correspond to E, S, M
char side = 0;

void savePrescriptionInfo(void);
void resetSection(void);
void handleError(void);
void interrupt interruptHandler(void);
void printSummary(void);

int placeMarkers(void);
void findMode(void); //decides which side is which on box 
void sendPillRequests(void);
void emergencyStop(void);
void printSummary(void);



#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALVARIABLES_H */

