/************************************************************************/
/* Librairie X10 RF pour émission d'ordres X10,                         */
/* Version 1.0 du 27/12/2010                                            */
/* www.domocreation.fr                                                  */
/*                                                                      */
/* This library is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* This library is distributed in the hope that it will be useful, but  */
/* WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     */
/* General Public License for more details.                             */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with this library. If not, see <http://www.gnu.org/licenses/>. */
/************************************************************************/

//#include <wiring.h>
#include "X10RF.h"

const byte house_code[] = { 0x60, 0x70, 0x40, 0x50, 0x80, 0x90, 0xA0, 0xB0, 0xE0, 0xF0, 0xC0, 0xD0, 0x00, 0x10, 0X20, 0x30 } ;
const byte unit_code[] = { 0x00, 0x10, 0x08, 0x18, 0x40, 0x50, 0x48, 0x58 } ;

//pin reliée au module RF
int pinOut;
X10RF::X10RF(int pin)
{
    pinOut=pin;
    return;
}

// -------------------------------------- Fonctions X10 ---------------------------------
// Envoi entête:
void X10RF::x10_sendpreamble(void)
{
	digitalWrite(pinOut,LOW) ;		// X10PIN à 0.
	delay(40) ;
	digitalWrite(pinOut,HIGH) ;		// X10PIN à 1.
	delay(9) ;
	digitalWrite(pinOut, LOW) ;		// X10PIN à 0.
	delay(4) ;
	delayMicroseconds(500) ;
}

// --------------------------------------------------------------------------------------
// Envoi bit:
void X10RF::x10_sendbit(void)
{
	digitalWrite(pinOut,HIGH) ;		// X10PIN à 1.
	delayMicroseconds(560) ;
	digitalWrite(pinOut,LOW) ;		// X10PIN à 0.
	delayMicroseconds(560) ;
}

// -----------------------
// Envoi d'un octet X10 RF
void X10RF::x10_sendbyte(byte X10octet)
{
	byte nobit, valbit;
	for (nobit=0; nobit<=7; nobit++)
	{
		valbit=X10octet & 0x80;
		X10octet=(X10octet << 1);

		x10_sendbit();				// On envoi un bit
		if ( valbit )				// Si bit à 1 pause + longue.
		{
			delayMicroseconds(1200) ;
		}
	}
}

// Envoie trame X10, House Code / Unit Code / Action (ON/OFF/DIM/BRIGHT)
void X10RF::x10_sendcmd(byte House, byte Unit, byte Action)
{
  byte hc, uc ;
  
  hc = house_code[House - 0x41] ; // Lit code correspondant dans tableau house_code.
 
  if(Unit>8)
  {
    hc |= 0x04 ;
    Unit-=8;
  }
  
  uc = unit_code[Unit-1] ;    	  // Lit code correspondant dans tableau unit_code.
 
  if (Action==OFF)
    uc |= 0x20 ;
  else if(Action==BRIGHT)
    uc=0x88;
  else if(Action==DIM)
    uc=0x98;
  
  // Envoie commande X10 hc/uc.
  x10_sendpreamble() ;
  x10_sendbyte(hc) ;		// house code
  x10_sendbyte(~hc) ;		// ~house code
  x10_sendbyte(uc) ;		// unit code
  x10_sendbyte(~uc) ;		// ~unit code
  x10_sendbit() ;
}
