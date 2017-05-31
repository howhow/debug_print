/*	@file Main.c
 *
 *	Main start point
 *
 *	@Author:	How.Chen
 *	@Version:	3.0
 *	@Date:		9th/Jan/2016
 *	@Note:		- V2.0, add thread
 *	            - V3.0, remove thread
 *	            add debug config
 *	            add debug print
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "debug.h"
#include "driver.h"

#ifdef _DEBUG_
extern UINT32 gDbg_mask;
#endif

/* Example to use DBG print for each component */
#define I2C_PRINT(level, fmt, args...)  DBG_PRINT(I2C, level, fmt, ##args) 
#define SPI_PRINT(level, fmt, args...)  DBG_PRINT(SPI, level, fmt, ##args) 
#define USIF_PRINT(level, fmt, args...) DBG_PRINT(USIF, level, fmt, ##args) 
#define USB_PRINT(level, fmt, args...)  DBG_PRINT(USB, level, fmt, ##args) 

int main(/*@ unused @*/int argc, /*@ unused @*/char *argv[])
{
    int *fd;
    DrvCommInit(&fd, local);

    DbgConfig(I2C,  FATAL);
    DbgConfig(SPI,  FATAL);
    DbgConfig(USIF, FATAL);
    DbgConfig(USB,  FATAL);

    I2C_PRINT(INFO,  "test\n");
    I2C_PRINT(DEBUG, "^g^test\n");
    I2C_PRINT(WARN,  "^y^test\n");
    I2C_PRINT(ALARM, "^y^test\n");
    I2C_PRINT(ERROR, "^r^test\n");
    I2C_PRINT(FATAL, "^r^test\n");
    I2C_PRINT(FATAL, "^x^test\n");

    SPI_PRINT(INFO,  "test\n");
    SPI_PRINT(DEBUG, "^b^test\n");
    SPI_PRINT(WARN,  "^p^test\n");
    SPI_PRINT(ALARM, "^p^test\n");
    SPI_PRINT(ERROR, "^c^test\n");
    SPI_PRINT(FATAL, "^c^test\n");

    USB_PRINT(INFO,  "test\n");
    USB_PRINT(DEBUG, "^a^test\n");
    USB_PRINT(WARN,  "^a^test\n");
    USB_PRINT(ALARM, "^k^test\n");
    USB_PRINT(ERROR, "^k^test\n");
    USB_PRINT(FATAL, "^k^test\n");

    USIF_PRINT(INFO,  "^g^level: %d\n", INFO);
    USIF_PRINT(DEBUG, "^y^level: %d\n", DEBUG);
    USIF_PRINT(WARN,  "^r^level: %d\n", WARN);
    USIF_PRINT(ALARM, "^b^level: %d\n", ALARM);
    USIF_PRINT(ERROR, "^p^level: %d\n", ERROR);
    USIF_PRINT(FATAL, "^c^level: %d\n", FATAL);

    DbgConfig(I2C,  NONE);
    DbgConfig(SPI,  NONE);
    DbgConfig(USIF, NONE);
    DbgConfig(USB,  NONE);

    I2C_PRINT(INFO,  "test, should not print!\n");
    I2C_PRINT(DEBUG, "^g^test, should not print!\n");
    I2C_PRINT(WARN,  "^y^test, should not print!\n");
    I2C_PRINT(ALARM, "^y^test, should not print!\n");
    I2C_PRINT(ERROR, "^r^test, should not print!\n");
    I2C_PRINT(FATAL, "^r^test, should not print!\n");

    DbgConfig(I2C,  INFO);
    DbgConfig(SPI,  WARN);
    DbgConfig(USIF, DEBUG);
    DbgConfig(USB,  FATAL);

    I2C_PRINT(INFO,  "test\n");
    I2C_PRINT(DEBUG, "^g^test\n");
    I2C_PRINT(WARN,  "^y^test\n");
    I2C_PRINT(ALARM, "^y^test\n");
    I2C_PRINT(ERROR, "^r^test\n");
    I2C_PRINT(FATAL, "^r^test\n");

    SPI_PRINT(INFO,  "test\n");
    SPI_PRINT(DEBUG, "^b^test\n");
    SPI_PRINT(WARN,  "^p^test\n");
    SPI_PRINT(ALARM, "^p^test\n");
    SPI_PRINT(ERROR, "^c^test\n");
    SPI_PRINT(FATAL, "^c^test\n");

    USB_PRINT(INFO,  "test\n");
    USB_PRINT(DEBUG, "^a^test\n");
    USB_PRINT(WARN,  "^a^test\n");
    USB_PRINT(ALARM, "^^test\n");
    USB_PRINT(ERROR, "^ ^test\n");
    USB_PRINT(FATAL, "^  ^test\n");
    USB_PRINT(FATAL, "!test\n");

    USIF_PRINT(INFO,  "^g^level: %d\n", INFO);
    USIF_PRINT(DEBUG, "^y^level: %d\n", DEBUG);
    USIF_PRINT(WARN,  "^r^level: %d\n", WARN);
    USIF_PRINT(ALARM, "^b^level: %d\n", ALARM);
    USIF_PRINT(ERROR, "^p^level: %d\n", ERROR);
    USIF_PRINT(FATAL, "^c^level: %d\n", FATAL);

    DbgConfig(I2C,  NONE);
    DbgConfig(SPI,  NONE);
    DbgConfig(USIF, NONE);
    DbgConfig(USB,  NONE);

    return 0;
}
