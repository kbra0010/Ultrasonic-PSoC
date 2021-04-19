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

int FT_Period_Int;
int FT_Period_uS;
int FT_Resolution;
float FT_Time_Per_Tick_uS;
float FT_Time_Per_Tick;
int SoundSpeed;

CY_ISR(Flight_Timer_ISR) {
    // Triggers once ultrasonic receives a pulse back
    // Once triggered gets timer value, measures distance
    int FT_Count = Flight_Timer_ReadCounter(); // forces capture, returns capture value
    int FlightTime = FT_Count * FT_Time_Per_Tick;
    int Distance = (FlightTime * SoundSpeed) / 2; // 2 as wave travels to object, bounces off it and comes back
}

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    // Initialising hardware modules
    
    PGA_1_Start();
    VDAC8_1_Start();
    Comp_1_Start();
    PGA_1_Start();
    Vssa_Buffer_Start();
    Ultrasonic_Drive_Start();
    //Flight_Timer_Enable();
    
    // Timer value setup
    FT_Period_Int = Flight_Timer_ReadPeriod(); // timer period, 1 = 10uS, therefore periodint * 10 = period in uS, I think
    FT_Period_uS = FT_Period_Int * 10; // period in uS
    FT_Resolution = 16; // 16-bit timer
    FT_Time_Per_Tick_uS = FT_Period_uS / powl(2,FT_Resolution); // might need to use pow (no L) instead here
    FT_Time_Per_Tick = FT_Time_Per_Tick_uS / powl(10,5);
    SoundSpeed = 343; // metres per sec
    // probably don't need to calculate period each ISR, just once when the program starts
    
    
    for(;;) {
        /* Place your application code here. */
        // Using Flight_Timer to find distance to the object
            // Pulse goes off
            // Wait until timer hits capture (through ISR)
            // Measure
    }
    
    

}

/* [] END OF FILE */
