/*
  comm.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
//*********************************************/
//
//  File:   comm.h
//
//  Author: bing@arduino.org (arduino srl)
//  edit:   andrea@arduino.org (arduino srl)
//
//********************************************/

#ifndef COMM_H
#define COMM_H

#if defined(__AVR_ATmega32U4__) //|| defined(__AVR_ATmega328P__) 
    #include "utility/uart/uart_drv.h"
	class CommDrv : public UartDrv {};
#else
    #include "utility/spi/spi_drv.h"
    class CommDrv : public SpiDrv {};
#endif

extern CommDrv commDrv;

#endif
