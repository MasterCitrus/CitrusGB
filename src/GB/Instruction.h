#pragma once

#include "State.h"

#include <string>

struct Instruction
{
	std::string mnemonic;
	State state;
	u16 address;
	u16 opcode;
};