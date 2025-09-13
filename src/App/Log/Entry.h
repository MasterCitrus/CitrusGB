#pragma once

#include "Definitions.h"
#include <string>

struct Entry
{
	std::string instruction;
	u16 PC;
	u16 SP;
	u16 AF;
	u16 BC;
	u16 DE;
	u16 HL;
	u8 OP;
};