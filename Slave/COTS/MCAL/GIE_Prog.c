////Author: Seif Bassiouny
////Date: 15/9/2022
////Version: 1.4
////Module: GIE

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "GIE_Int.h"
#include "GIE_Priv.h"

void GIE_void_Enable(void)
{
	SET_BIT(SREG, GIE_Uint8_IFLAG);
}

void GIE_void_Disable(void)
{
	CLEAR_BIT(SREG, GIE_Uint8_IFLAG);
}

