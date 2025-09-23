#pragma once

#include "Definitions.h"

struct State
{
	u16 SP = 0x0;
	u8 A = 0x0;
	u8 F = 0x0;
	u8 B = 0x0;
	u8 C = 0x0;
	u8 D = 0x0;
	u8 E = 0x0;
	u8 H = 0x0;
	u8 L = 0x0;
	bool zero = false;
	bool subtract = false;
	bool halfCarry = false;
	bool carry = false;
};