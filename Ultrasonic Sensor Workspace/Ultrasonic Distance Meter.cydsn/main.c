/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "tgmath.h"

// Ultrasonic variables
int FT_Period_Int;
int FT_Period_uS;
int FT_Resolution;
float FT_Time_Per_Tick_uS;
float FT_Time_Per_Tick;
int SoundSpeed;

// 7 Segment setups
int Seg1000Count;
int Seg100Count;
int Seg10Count;
int Seg1Count;
int decimalPlaces;

// hex values to be sent to 7 seg display for active low
// these could be preprocessor commands instead (#define)
int zero = 0xC0;
int one = 0xF9;
int two = 0xA4;
int three = 0xB0;
int four = 0x99;
int five = 0x92;
int six = 0x82;
int seven = 0xF8;
int eight = 0x80;
int nine = 0x98;

// digit variables (not completely necessary, but a good indicator of one-hot display encoding)
int digitThree = 1;
int digitTwo = 2;
int digitOne = 4;
int digitZero = 8;

int test;
int dotFlag;

long unsigned int displayData[4]; // 0 = ones digit, MSB = decimal point, bits 0 to 7 are the number

// button variables etc
int fiveMillisecCount = 5;
long unsigned int milli = 0;
int oneSecondCount = 1000;
int units = 0; //0 = metric, 1 = imperial

int digit[4]; // should be a local var

void getDigits(float FlightTime);
void saveDigitsToRAM();
void checkMeasurementButton();
void pulseDot();

CY_ISR(Flight_Timer_ISR) {
    // Triggers once ultrasonic receives a pulse back
    // Once triggered gets timer value, measures distance
    int FT_Count = Flight_Timer_ReadPeriod(); // forces capture, returns capture value
    float FlightTime = (10000 - FT_Count) * FT_Time_Per_Tick;
    // should be max period - read period
    
    getDigits(FlightTime);
    saveDigitsToRAM();
    isr_1_ClearPending();
    
    // function to get average distance goes here
    
    
    Flight_Timer_Reset_Reg_Write(1);
    Flight_Timer_ReadStatusRegister();
    Flight_Timer_Reset_Reg_Write(0);
    
    //Flight_Timer_Stop();
    //Flight_Timer_Start();
    
    
    
    //Flight_Timer_Reset_Reg_Write(0);
    // write reg zero when starting pulses
    
    //FT_Count = Flight_Timer_ReadCapture();
    //FT_Count = Flight_Timer_ReadCapture();
    //FT_Count = Flight_Timer_ReadCapture();
    // Timer_1_ReadStatusRegister()
}

CY_ISR(Millisec_ISR) { // triggered every millisecond
    // stuff
    // check buttons
    // check the state (if measuring or not)
    // do stuff depending on state
    
    if(fiveMillisecCount == 0) {
        // do stuff
        checkMeasurementButton();
        fiveMillisecCount = 5;
    }
    if(oneSecondCount == 0) {
        // do stuff
        pulseDot();
        oneSecondCount = 1000;
    }
    milli++;
    fiveMillisecCount--;
    oneSecondCount--;
    //Five_Millisec_Timer_WriteCounter(0);
}

/*
CY_ISR(Measurement_ISR) { //ISR to start ultrasonic pulses when button pushed
    // this ISR triggered when S1_1 goes high (measurement button pushed)
}
*/





int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_ClearPending();               // Cancel any pending isr_1 interrupts 
    isr_1_StartEx(Flight_Timer_ISR);    //Enable the interrupt service routine
    isr_2_ClearPending();               // Cancel any pending isr_1 interrupts 
    isr_2_StartEx(Millisec_ISR);        //Enable the interrupt service routine
    /*
    isr_3_ClearPending();               // Cancel any pending isr_1 interrupts 
    isr_3_StartEx(Measurement_ISR);     //Enable the interrupt service routine
    */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    // Initialising hardware modules
    
    Button_Tie_High_Write(1); // pin for pulling buttons high when pushed
    
    PGA_1_Start();
    VDAC8_1_Start();
    Comp_1_Start();
    Vssa_Buffer_Start();
    Ultrasonic_Drive_Start();
    Flight_Timer_Enable();
    Flight_Timer_Start();
    Five_Millisec_Timer_Enable();
    Five_Millisec_Timer_Start();
    
    // read status register for timers
    Ultrasonic_Drive_Enable();
    Ultrasonic_Drive_Start();
    //Ultrasonic_Pulse_Counter_Enable();
    Ultrasonic_Pulse_Counter_Start();
    Flight_Timer_Clock_Enable();
    Flight_Timer_Clock_Start();
    
    EEPROM_Start();
    //EEPROM_WriteByte(12,0); // team number
    //EEPROM_WriteByte(units,1);
    

    
    // Timer value setup
    FT_Period_Int = Flight_Timer_ReadPeriod(); // timer period, 1 = 10uS, therefore periodint * 10 = period in uS, I think
    FT_Period_uS = FT_Period_Int * 10; // period in uS
    FT_Resolution = 16; // 16-bit timer
    FT_Time_Per_Tick_uS = FT_Period_uS / powl(2,FT_Resolution); // might need to use pow (no L) instead here
    FT_Time_Per_Tick = FT_Time_Per_Tick_uS / powl(10,5);
    SoundSpeed = 343; // metres per sec
    // probably don't need to calculate period each ISR, just once when the program starts
    
    // todo turn on timer interrupt
    // todo reset timer ISR once triggered
    for(;;) {
        /* Place your application code here. */
        // Using Flight_Timer to find distance to the object
            // Pulse goes off
            // Wait until timer hits capture (through ISR)
            // Measure
        // todo loop printing digits to the screen until off
        
        //Digit_Reg_Write(2);
        //Seven_Segment_Reg_Write(0x99);
        //Decimal_Place_Reg_Write(0);
        
        
        //saveDigitsToRAM();
        //Digit_Reg_Write(digitZero);
        //Seven_Segment_Reg_Write(zero);
        // test number write function
        int testing = EEPROM_ReadByte(0);
        CyDelay(10);
        int test = 1;
        for(;;) {
            for(int index = 0; index < 4; index++) { // loop through digits 0 to 3
                int currentDigit = powl(2,index);
                int currentDigitInverted = powl(2,8)-1 - currentDigit;
                
                
                
                Digit_Reg_Write(currentDigitInverted); // correct way, just inverts bits
                //Digit_Reg_Write(15);
                
                Seven_Segment_Reg_Write(displayData[index]);
                CyDelay(1);
            }
        }
    }
}

/* [] END OF FILE */


void getDigits(float FlightTime) { // puts distance in mm into digits[] array
    // read EEPROM for which kind of distance it is
    // calc distance
    // readEEPROM
    // 1 = mm
    // 2 = cm
    // 3 = inches
    
    // EEPROM GO HERE *********************************************************
    
    //int distanceMode = 1;
    int distanceMM;
    //float distanceCM;
    //float distanceInch;
    
    distanceMM = ((FlightTime * SoundSpeed) / 2) * 1000; // dist in mm, an integer
    //distanceCM = ((FlightTime * SoundSpeed) / 2) * 100; // dist in cm
    //distanceInch = ((FlightTime * SoundSpeed) / 2) / 39.3701; // dist in inches
    
    int index = 0;
    // 0 = ones
    // 1 = tens
    // 2 = hundreds
    // 3 = thousands
    digit[0] = distanceMM;
    while(digit[index] >= 10) {
        digit[index] = digit[index] % 10;
        
        index += 1; // increment index
        digit[index] = floor(digit[index] / 10); // move to next number
    }
    
    /*
    switch(distanceMode) {
        case 1: //mm
            decimalPlaces = 0; // no decimal place
            break;
        case 2: //cm
            decimalPlaces = 1; // 1 decimal place
            break;
        case 3: //inches
            decimalPlaces = 2; // 2 decimal place
            break;
    }
    */
}

void saveDigitsToRAM() {
    for(int index = 0; index < 4; index++) { // loop through digits 0 to 3
        //int currentDigit = powl(2,index);
        //Digit_Reg_Write(currentDigit);
        
        switch(digit[index]) {
        case 0:
            //Seven_Segment_Reg_Write(zero);
            displayData[index] = zero;
            break;
        case 1:
            //Seven_Segment_Reg_Write(one);
            displayData[index] = one;
            break;
        case 2:
            //Seven_Segment_Reg_Write(two);
            displayData[index] = two;
            break;
        case 3:
            //Seven_Segment_Reg_Write(three);
            displayData[index] = three;
            break;
        case 4:
            //Seven_Segment_Reg_Write(four);
            displayData[index] = four;
            break;
        case 5:
            //Seven_Segment_Reg_Write(five);
            displayData[index] = five;
            break;
        case 6:
            //Seven_Segment_Reg_Write(six);
            displayData[index] = six;
            break;
        case 7:
            //Seven_Segment_Reg_Write(seven);
            displayData[index] = seven;
            break;
        case 8:
            //Seven_Segment_Reg_Write(eight);
            displayData[index] = eight;
            break;
        case 9:
            //Seven_Segment_Reg_Write(nine);
            displayData[index] = nine;
            break;
        }
        
        if(index == 1) { // 2nd most significant digit
            displayData[index] = displayData[index] + powl(2,7); //works
        }
    }
    
    // digit pin high = digit SELECTED
    // segment pin low = segment ILLUMINATED
}

void checkMeasurementButton() {// if button pressed, do ultrasonic pulsing stuff
    test = S1_1_Read();
    if(S1_1_Read() == 1) { // if button is HIGH (pushed)
        Ultrasonic_Drive_Stop(); // stop pulsing ultrasonic
        Ultrasonic_Pulse_Counter_WriteCounter(0); // reset counter
        Ultrasonic_Set_Reg_Write(0); // set counter reset line low
        //(can remove this reg and just use WriteCounter command to reset)
        Ultrasonic_Drive_Start();
        
        Flight_Timer_Reset_Reg_Write(0);
        
        R3_2_Reg_Write(0);
        J1_2_Reg_Write(1);
        // send 10 pulses
        // ISR waits for response
        // main loop displays code
    }
}

void pulseDot() {
    if(dotFlag == 0) { // dot is off
        displayData[3] = displayData[3] + powl(2,7);
        dotFlag = 1;
    }
    else if(dotFlag == 1) {
        displayData[3] = displayData[3] - powl(2,7);
        dotFlag = 0;
    }
}














/*
// test number write function
        digit[0] = 1;
        digit[1] = 2;
        digit[2] = 3;
        digit[3] = 4;
        saveDigitsToRAM();
        
        for(;;) {
            for(int index = 0; index < 4; index++) { // loop through digits 0 to 3
                int currentDigit = powl(2,index);
                int currentDigitInverted = powl(2,8)-1 - currentDigit;
                
                
                
                Digit_Reg_Write(currentDigitInverted); // correct way, just inverts bits
                //Digit_Reg_Write(15);
                
                Seven_Segment_Reg_Write(displayData[index]);
                CyDelay(1);
            }
        }
*/
