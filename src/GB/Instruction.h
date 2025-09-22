#pragma once

#include "Definitions.h"

#include <string>

struct Instruction
{
	std::string mnemonic;
	u16 address;
	u16 opcode;
};