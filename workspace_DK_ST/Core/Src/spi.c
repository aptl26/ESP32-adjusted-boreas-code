//
// Description: SPI module for ST MCU
//
// Copyright (c) 2021 Boréas Technologies Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <stdint.h>
#include "spi.h"
#include "esp32-hal-spi.h"

// board channel A
#define SS0_PORT (GPIOA)
#define SS0_PIN  (SS0_Pin)
// board channel B
#define SS1_PORT (GPIOE)
#define SS1_PIN  (SS1_Pin)

/********************************************************
*				 FUNCTIONS DEFINTION
********************************************************/

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

void spiInit()
{

}

// Writes data to SPI and reads returned data
uint16_t spiReadWriteReg(uint8_t chipSelect, uint16_t data)
{
	SPI_HandleTypeDef *spiHandle;
	GPIO_TypeDef *gpioPort;
	uint16_t	gpioPin;

	uint16_t DataSend = data;
	uint16_t DataReceive = 0;

	switch(chipSelect)
	{
		case 0:
			spiHandle = &hspi1;
			gpioPort = SS0_PORT;
			gpioPin = SS0_PIN;
			break;
		case 1:
			spiHandle = &hspi4;
			gpioPort = SS1_PORT;
			gpioPin = SS1_PIN;
			break;
		default:
			spiHandle = &hspi1;
			gpioPort = SS0_PORT;
			gpioPin = SS0_PIN;
	}

	HAL_GPIO_WritePin(gpioPort, gpioPin, 0); // Can be replaced with digitalWrite
	// HAL_SPI_TransmitReceive(spiHandle, (uint8_t*)&DataSend, (uint8_t*)&DataReceive, 1, 100); // Can be replaced with spiTransferBytes, we need to specify the spi pointer which should be defined using the spi_t type

	HAL_GPIO_WritePin(gpioPort, gpioPin, 1); // Can be replaced with digitalWrite

	return DataReceive;

}


