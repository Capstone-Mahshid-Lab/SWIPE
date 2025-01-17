#include "SPITest.hpp"

void runSpiTest(void) {
  //SPI_RawTest();
  SPI_RW_REG();
  // SPI_RW_TEMPERATURE();
}

static int32_t AD5940PlatformCfg2(void){
    //Clock config
    CLKCfg_Type clk_cfg;
    clk_cfg.ADCClkDiv = ADCCLKDIV_1;
    clk_cfg.ADCCLkSrc = ADCCLKSRC_HFOSC;
    clk_cfg.SysClkDiv = SYSCLKDIV_1;
    clk_cfg.SysClkSrc = SYSCLKSRC_HFOSC;
    clk_cfg.HfOSC32MHzMode = bFALSE;
    clk_cfg.HFOSCEn = bTRUE;
    clk_cfg.HFXTALEn = bFALSE;
    clk_cfg.LFOSCEn = bTRUE;
    AD5940_CLKCfg(&clk_cfg);
    return 0;
}

void _ad5940_analog_init2(void) {
    AFERefCfg_Type aferef_cfg;
    ADCBaseCfg_Type adc_base;
    ADCFilterCfg_Type adc_filter;

    // Disable all AFE controls to start from a clean slate
    AD5940_AFECtrlS(AFECTRL_ALL, bFALSE);

    // Configure AFE references
    aferef_cfg.HpBandgapEn = bTRUE;
    aferef_cfg.Hp1V1BuffEn = bTRUE;
    aferef_cfg.Hp1V8BuffEn = bTRUE;       // High-speed buffers are used during operation
    aferef_cfg.Disc1V1Cap = bFALSE;
    aferef_cfg.Disc1V8Cap = bFALSE;
    aferef_cfg.Hp1V8ThemBuff = bFALSE;
    aferef_cfg.Hp1V8Ilimit = bFALSE;
    aferef_cfg.Lp1V1BuffEn = bFALSE;
    aferef_cfg.Lp1V8BuffEn = bFALSE;
    aferef_cfg.LpBandgapEn = bFALSE;
    aferef_cfg.LpRefBufEn = bFALSE;
    aferef_cfg.LpRefBoostEn = bFALSE;
    AD5940_REFCfgS(&aferef_cfg);

    // Configure the ADC for temperature measurement
    adc_base.ADCMuxP = ADCMUXP_TEMPP;  // Select positive input as the temperature sensor
    adc_base.ADCMuxN = ADCMUXN_TEMPN;  // Select negative input as the temperature sensor
    adc_base.ADCPga = ADCPGA_1P5;      // Set the ADC gain
    AD5940_ADCBaseCfgS(&adc_base);

    // Configure ADC filters
    adc_filter.ADCSinc3Osr = ADCSINC3OSR_2;      // Set SINC3 oversampling ratio
    adc_filter.ADCSinc2Osr = ADCSINC2OSR_22;     // Set SINC2 oversampling ratio
    adc_filter.ADCAvgNum = ADCAVGNUM_2;       // Averaging is not critical here
    adc_filter.ADCRate = ADCRATE_800KHZ;      // Set ADC rate
    adc_filter.BpNotch = bTRUE;               // Bypass Notch filter
    adc_filter.BpSinc3 = bFALSE;              // Use SINC3 filter
    adc_filter.Sinc2NotchEnable = bTRUE;      // Enable SINC2+Notch filter
    AD5940_ADCFilterCfgS(&adc_filter);

    // Enable the temperature sensor
    AD5940_AFECtrlS(AFECTRL_TEMPSPWR, bTRUE);
}


void SPI_RW_TEMPERATURE(void) {
    AD5940_HWReset();
    AD5940_Initialize();
    Serial.println("run platform config");
    AD5940PlatformCfg2();
    Serial.println("run analog init 2");
    _ad5940_analog_init2();

    // Enable temperature sensor and start ADC conversion
    uint32_t mask = (1 << BITP_AFE_AFECON_ALDOILIMITEN) |
                    (1 << BITP_AFE_AFECON_TEMPCONVEN)   | 
                    (1 << BITP_AFE_AFECON_TEMPSENSEN)   | 
                    (1 << BITP_AFE_AFECON_ADCCONVEN)    |
                    (1 << BITP_AFE_AFECON_ADCEN);
    Serial.println("run WriteReg");
    AD5940_WriteReg(REG_AFE_AFECON, mask);

    // Wait for ADC conversion to complete
    delayMicroseconds(200); // Adjust delay as per datasheet timing specs

    // Read AFECON register to verify settings
    uint32_t afecon_val = AD5940_ReadReg(REG_AFE_AFECON);
    if (!(afecon_val & mask)) {
        Serial.println("Error: AFECON settings not applied.");
        return;
    }
    Serial.print("AFECON register value: ");
    Serial.println(afecon_val, HEX);

    // Read temperature sensor result
    uint32_t temp_result = AD5940_ReadAfeResult(AFERESULT_TEMPSENSOR);
    Serial.print("Temperature sensor result: ");
    Serial.println(temp_result);
}

void SPI_RawTest(void) {
    uint8_t tx_buffer[3] = {0x00, 0x00, REG_AFECON_ADIID};  // Command to read register 0x00
    uint8_t rx_buffer[3] = {0};

    // Pull CS low and send command
    AD5940_CsClr();
    AD5940_ReadWriteNBytes(tx_buffer, rx_buffer, 3);
    AD5940_CsSet();

    // Display received data
    Serial.print("Raw SPI response: ");
    for (int i = 0; i < 3; i++) {
        Serial.print(rx_buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}



void SPI_RW_REG(void) {
    AD5940_HWReset();
    AD5940_Initialize();
    Serial.println("INIT COMPLETE");


    // Read ADI ID register (REG_AFECON_ADIID)
    uint32_t device_id = AD5940_ReadReg(REG_AFECON_ADIID);
    Serial.print("Device ID: ");
    Serial.println(device_id, HEX);

    // // Enable temperature sensor and start ADC conversion
    // uint32_t mask = 3;
    // Serial.println("run WriteReg");
    // AD5940_WriteReg(REG_AFE_AFECON, mask);

    // // Wait for ADC conversion to complete
    // delayMicroseconds(300); // Adjust delay as per datasheet timing specs

    // // Read AFECON register to verify settings
    // uint32_t afecon_val = AD5940_ReadReg(REG_AFE_AFECON);
    // if (!(afecon_val & mask)) {
    //     Serial.println("Error: AFECON settings not applied.");
    // }
    // Serial.print("AFECON register value: ");
    // Serial.println(afecon_val, HEX);
}