/************************************************************************/
/* Librairie X10 RF pour �mission d'ordres X10,                         */
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

#ifndef X10RF_H
#define X10RF_H

#include <Arduino.h>

#define OFF 0x00
#define ON 0x01
#define BRIGHT 0x02
#define DIM 0x03

extern const byte house_code[];
extern const byte unit_code[];

class X10RF
{
  public:
    X10RF(int);
    void x10_sendcmd(byte, byte, byte);
  
  private:
    void x10_sendpreamble(void);
    void x10_sendbit(void);
    void x10_sendbyte(byte);
};
#endif
