#include "stm32f10x.h"
#include <stdio.h>

void ADC_Config(void);
void USART_Config(void);
void USART_SendString(char *str);
void TIM2_Config(void);
void delay_ms(uint32_t ms);

int main(void)
{
    uint16_t adc_value;
    uint32_t voltage;
    char buffer[50];

    ADC_Config();
    USART_Config();
    TIM2_Config();

    while (1)
    {
        // Batdauchuyendoi
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);

        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
        adc_value = ADC_GetConversionValue(ADC1);

        // Tính dienap(mV), Vref = 3.3V
        voltage = (adc_value * 3300) / 4095;

        // In ra terminal
        sprintf(buffer, "ADC = %d, Voltage = %lu mV\r\n", adc_value, voltage);
        USART_SendString(buffer);

        delay_ms(500); // chaytimer
    }
}

void ADC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void USART_SendString(char *str)
{
    while (*str)
    {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void TIM2_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // TIM2 chay 1MHz (1 tick = 1 µs)
    TIM2->PSC = 72 - 1;      
    TIM2->ARR = 0xFFFF;      
    TIM2->CR1 |= TIM_CR1_CEN;
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        TIM2->CNT = 0;             
        while (TIM2->CNT < 1000);  
    }
}
