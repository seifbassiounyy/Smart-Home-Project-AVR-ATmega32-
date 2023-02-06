////Author: Seif Bassiouny
////Date: 4/9/2022
////Version: 1.1
////Module: Services

#ifndef BIT_MATHS_H_
#define BIT_MATHS_H_

#define SET_BIT(REG, BIT)			(REG |= (1<<BIT))
#define CLEAR_BIT(REG, BIT)			(REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG, BIT)		(REG ^= (1<<BIT))
#define GET_BIT(REG, BIT)			((REG >> BIT) & 0X01)
#define SET_REG_VALUE(REG, VALUE)	(REG = VALUE)
#define CLEAR_REG(REG)				(REG = 0x00)
#define TOGGLE_REG(REG)				(REG ^= 0xFF)
#define GET_REG(REG)				(REG)
#define CONCATENATE_BITS(B7, B6, B5, B4, B3, B2, B1, B0)	CONCATENATE_HELP(B7, B6, B5, B4, B3, B2, B1, B0)
#define CONCATENATE_HELP(B7, B6, B5, B4, B3, B2, B1, B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0

#endif /* BIT_MATHS_H_ */