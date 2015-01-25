#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "esp.h"

uint32_t ICACHE_FLASH_ATTR readReg(uint32_t nRegister)
{
    return (*((volatile uint32_t *)(nRegister)));
}

void ICACHE_FLASH_ATTR writeReg(uint32_t nRegister, uint32_t nValue)
{
    (*((volatile uint32_t *)(nRegister))) = nValue;
}

void ICACHE_FLASH_ATTR clearRegBits(uint32_t nRegister, uint32_t nMask)
{
    writeReg(nRegister, readReg(nRegister) & (~nMask));
}

void ICACHE_FLASH_ATTR setRegBits(uint32_t nRegister, uint32_t nMask)
{
    writeReg(nRegister, readReg(nRegister) | nMask);
}

void ICACHE_FLASH_ATTR setRegBitsShifted(uint32_t nRegister, uint32_t nValue, uint32_t nMask, uint8_t nShift)
{
	uint32_t nReadValue = readReg(nRegister);
	uint32_t nRealMask = ~(nMask << nShift);
	uint32_t nRealValue = (nValue << nShift);
	writeReg(nRegister, (nReadValue & nRealMask) | nRealValue);
}

uint32_t ICACHE_FLASH_ATTR getRegBitsShifted(uint32_t nRegister, uint32_t nMask, uint8_t nShift)
{
	uint32_t nRealMask = nMask << nShift;
	uint32_t nValue = readReg(nRegister) & nRealMask;
	return (nValue >> nShift);
}

void ICACHE_FLASH_ATTR selectFunction(uint32_t nRegister, uint32_t nFunction)
{
    setRegBitsShifted(nRegister, 0x00, PERIPHS_IO_MUX_FUNC, PERIPHS_IO_MUX_FUNC_S);
    setRegBitsShifted(nRegister, ((nFunction & BIT2) << 2), (nFunction & 0x3), PERIPHS_IO_MUX_FUNC_S);
}

void ICACHE_FLASH_ATTR enableInterrupts(uint8_t nType)
{
	_xt_isr_unmask(1 << nType);
}

void ICACHE_FLASH_ATTR disableInterrupts(uint8_t nType)
{
	_xt_isr_mask(1 << nType);
}
