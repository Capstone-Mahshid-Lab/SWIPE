/*!
 *****************************************************************************
 @file:    AD5940Main.h
 @author:  Neo Xu
 @brief:   Header file for AD5940Main.c
 -----------------------------------------------------------------------------

Copyright (c) 2017-2019 Analog Devices, Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
By using this software you agree to the terms of the associated
Analog Devices Software License Agreement.

*****************************************************************************/

#ifndef AD5940_MAIN_H
#define AD5940_MAIN_H

#include "RampTest.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Buffer size for application */
#define APPBUFF_SIZE 1024

/* Global variables */
extern uint32_t AppBuff[APPBUFF_SIZE];
extern float LFOSCFreq;    /* Measured LFOSC frequency */

/* Function prototypes */
int32_t RampShowResult(float *pData, uint32_t DataCount);
int32_t AD5940PlatformCfg(void);
void AD5940RampStructInit(void);
void AD5940_Main(void);
#ifdef __cplusplus
}
#endif

#endif /* AD5940_MAIN_H */
