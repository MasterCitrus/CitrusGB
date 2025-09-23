#include "CPU.h"
#include "Memory.h"

#include <format>
#include <iostream>

CPU::CPU(Memory* memory)
	: memory(memory), PC(0x00), SP(0x00), IME(false), zero(false), subtract(false), halfCarry(false), carry(false),
	AF(0x0), BC(0x0), DE(0x0), HL(0x0), OP(0x0)
{
	instructions.reserve(0x10000);
}

CPU::~CPU()
{
}

void CPU::SkipBootROM(GameBoyMode mode)
{
	// TODO set values for DMG0, MGB and SGB2 for original Game Boy
	// Set values for CGB(DMG) and CGB for Game Boy Colour
	// AGB(DMG) and AGB modes for Game Boy Advance possibly in future
	switch (mode)
	{
		case GameBoyMode::DMG:
			AF.SetRegister(0x0180);
			BC.SetRegister(0x13);
			DE.SetRegister(0x0);
			HL.SetRegister(0x014D);
			PC = 0x100;
			SP = 0xFFFE;
			zero = true;
			subtract = false;
			halfCarry = false;
			carry = false;
			break;
		case GameBoyMode::CGB:
			// TODO
			break;
		case GameBoyMode::SGB:
			// TODO
			break;
	}
}

void CPU::Step()
{
	currentInstruction.address = PC;
	Decode();
	instructions.push_back(currentInstruction);
}

void CPU::Decode()
{
	OP = FetchByte();
	currentInstruction.opcode = OP;
	switch (OP)
	{
		case 0x00:
			NOP();
			break;
		case 0x01:
			LD(RegisterTarget::BC, RegisterTarget::Word);
			break;
		case 0x02:
			LD(RegisterTarget::MemBC, RegisterTarget::A);
			break;
		case 0x03:
			INC(RegisterTarget::BC);
			break;
		case 0x04:
			INC(RegisterTarget::B);
			break;
		case 0x05:
			DEC(RegisterTarget::B);
			break;
		case 0x06:
			LD(RegisterTarget::B, RegisterTarget::Byte);
			break;
		case 0x07:
			RLCA();
			break;
		case 0x08:
			LD(RegisterTarget::Word, RegisterTarget::SP);
			break;
		case 0x09:
			ADD(RegisterTarget::BC, RegisterTarget::HL);
			break;
		case 0x0A:
			LD(RegisterTarget::A, RegisterTarget::MemBC);
			break;
		case 0x0B:
			DEC(RegisterTarget::BC);
			break;
		case 0x0C:
			INC(RegisterTarget::C);
			break;
		case 0x0D:
			DEC(RegisterTarget::C);
			break;
		case 0x0E:
			LD(RegisterTarget::C, RegisterTarget::Byte);
			break;
		case 0x0F:
			RRCA();
			break;
		case 0x10:
			currentInstruction.mnemonic = "STOP - Unimplemented";
			break;
		case 0x11:
			LD(RegisterTarget::DE, RegisterTarget::Word);
			break;
		case 0x12:
			LD(RegisterTarget::MemDE, RegisterTarget::A);
			break;
		case 0x13:
			INC(RegisterTarget::DE);
			break;
		case 0x14:
			INC(RegisterTarget::D);
			break;
		case 0x15:
			DEC(RegisterTarget::E);
			break;
		case 0x16:
			LD(RegisterTarget::D, RegisterTarget::Byte);
			break;
		case 0x17:
			RLA();
			break;
		case 0x18:
			JR(Condition::None);
			break;
		case 0x19:
			ADD(RegisterTarget::DE, RegisterTarget::HL);
			break;
		case 0x1A:
			LD(RegisterTarget::A, RegisterTarget::MemDE);
			break;
		case 0x1B:
			DEC(RegisterTarget::DE);
			break;
		case 0x1C:
			INC(RegisterTarget::E);
			break;
		case 0x1D:
			DEC(RegisterTarget::E);
			break;
		case 0x1E:
			LD(RegisterTarget::E, RegisterTarget::Byte);
			break;
		case 0x1F:
			RRA();
			break;
		case 0x20:
			JR(Condition::NotZero);
			break;
		case 0x21:
			LD(RegisterTarget::HL, RegisterTarget::Word);
			break;
		case 0x22:
			LD(RegisterTarget::MemHLInc, RegisterTarget::A);
			break;
		case 0x23:
			INC(RegisterTarget::HL);
			break;
		case 0x24:
			INC(RegisterTarget::H);
			break;
		case 0x25:
			DEC(RegisterTarget::H);
			break;
		case 0x26:
			LD(RegisterTarget::H, RegisterTarget::Byte);
			break;
		case 0x27:
			currentInstruction.mnemonic = "DAA - Unimplemented";
			break;
		case 0x28:
			JR(Condition::Zero);
			break;
		case 0x29:
			ADD(RegisterTarget::HL, RegisterTarget::HL);
			break;
		case 0x2A:
			LD(RegisterTarget::A, RegisterTarget::MemHLInc);
			break;
		case 0x2B:
			DEC(RegisterTarget::HL);
			break;
		case 0x2C:
			INC(RegisterTarget::L);
			break;
		case 0x2D:
			DEC(RegisterTarget::L);
			break;
		case 0x2E:
			LD(RegisterTarget::L, RegisterTarget::Byte);
			break;
		case 0x2F:
			CPL();
			break;
		case 0x30:
			JR(Condition::NotCarry);
			break;
		case 0x31:
			LD(RegisterTarget::SP, RegisterTarget::Word);
			break;
		case 0x32:
			LD(RegisterTarget::MemHLDec, RegisterTarget::A);
			break;
		case 0x33:
			INC(RegisterTarget::SP);
			break;
		case 0x34:
			INC(RegisterTarget::MemHL);
			break;
		case 0x35:
			DEC(RegisterTarget::MemHL);
			break;
		case 0x36:
			LD(RegisterTarget::MemHL, RegisterTarget::Byte);
			break;
		case 0x37:
			SCF();
			break;
		case 0x38:
			JR(Condition::Carry);
			break;
		case 0x39:
			ADD(RegisterTarget::SP, RegisterTarget::HL);
			break;
		case 0x3A:
			LD(RegisterTarget::A, RegisterTarget::MemHLDec);
			break;
		case 0x3B:
			DEC(RegisterTarget::SP);
			break;
		case 0x3C:
			INC(RegisterTarget::A);
			break;
		case 0x3D:
			DEC(RegisterTarget::A);
			break;
		case 0x3E:
			LD(RegisterTarget::A, RegisterTarget::Byte);
			break;
		case 0x3F:
			CCF();
			break;
		case 0x40:
			LD(RegisterTarget::B, RegisterTarget::B);
			break;
		case 0x41:
			LD(RegisterTarget::B, RegisterTarget::C);
			break;
		case 0x42:
			LD(RegisterTarget::B, RegisterTarget::D);
			break;
		case 0x43:
			LD(RegisterTarget::B, RegisterTarget::E);
			break;
		case 0x44:
			LD(RegisterTarget::B, RegisterTarget::H);
			break;
		case 0x45:
			LD(RegisterTarget::B, RegisterTarget::L);
			break;
		case 0x46:
			LD(RegisterTarget::B, RegisterTarget::MemHL);
			break;
		case 0x47:
			LD(RegisterTarget::B, RegisterTarget::A);
			break;
		case 0x48:
			LD(RegisterTarget::C, RegisterTarget::B);
			break;
		case 0x49:
			LD(RegisterTarget::C, RegisterTarget::C);
			break;
		case 0x4A:
			LD(RegisterTarget::C, RegisterTarget::D);
			break;
		case 0x4B:
			LD(RegisterTarget::C, RegisterTarget::E);
			break;
		case 0x4C:
			LD(RegisterTarget::C, RegisterTarget::H);
			break;
		case 0x4D:
			LD(RegisterTarget::C, RegisterTarget::L);
			break;
		case 0x4E:
			LD(RegisterTarget::C, RegisterTarget::MemHL);
			break;
		case 0x4F:
			LD(RegisterTarget::C, RegisterTarget::A);
			break;
		case 0x50:
			LD(RegisterTarget::D, RegisterTarget::B);
			break;
		case 0x51:
			LD(RegisterTarget::D, RegisterTarget::C);
			break;
		case 0x52:
			LD(RegisterTarget::D, RegisterTarget::D);
			break;
		case 0x53:
			LD(RegisterTarget::D, RegisterTarget::E);
			break;
		case 0x54:
			LD(RegisterTarget::D, RegisterTarget::H);
			break;
		case 0x55:
			LD(RegisterTarget::D, RegisterTarget::L);
			break;
		case 0x56:
			LD(RegisterTarget::D, RegisterTarget::MemHL);
			break;
		case 0x57:
			LD(RegisterTarget::D, RegisterTarget::A);
			break;
		case 0x58:
			LD(RegisterTarget::E, RegisterTarget::B);
			break;
		case 0x59:
			LD(RegisterTarget::E, RegisterTarget::C);
			break;
		case 0x5A:
			LD(RegisterTarget::E, RegisterTarget::D);
			break;
		case 0x5B:
			LD(RegisterTarget::E, RegisterTarget::E);
			break;
		case 0x5C:
			LD(RegisterTarget::E, RegisterTarget::H);
			break;
		case 0x5D:
			LD(RegisterTarget::E, RegisterTarget::L);
			break;
		case 0x5E:
			LD(RegisterTarget::E, RegisterTarget::MemHL);
			break;
		case 0x5F:
			LD(RegisterTarget::E, RegisterTarget::A);
			break;
		case 0x60:
			LD(RegisterTarget::H, RegisterTarget::B);
			break;
		case 0x61:
			LD(RegisterTarget::H, RegisterTarget::C);
			break;
		case 0x62:
			LD(RegisterTarget::H, RegisterTarget::D);
			break;
		case 0x63:
			LD(RegisterTarget::H, RegisterTarget::E);
			break;
		case 0x64:
			LD(RegisterTarget::H, RegisterTarget::H);
			break;
		case 0x65:
			LD(RegisterTarget::H, RegisterTarget::L);
			break;
		case 0x66:
			LD(RegisterTarget::H, RegisterTarget::MemHL);
			break;
		case 0x67:
			LD(RegisterTarget::H, RegisterTarget::A);
			break;
		case 0x68:
			LD(RegisterTarget::L, RegisterTarget::B);
			break;
		case 0x69:
			LD(RegisterTarget::L, RegisterTarget::C);
			break;
		case 0x6A:
			LD(RegisterTarget::L, RegisterTarget::D);
			break;
		case 0x6B:
			LD(RegisterTarget::L, RegisterTarget::E);
			break;
		case 0x6C:
			LD(RegisterTarget::L, RegisterTarget::H);
			break;
		case 0x6D:
			LD(RegisterTarget::L, RegisterTarget::L);
			break;
		case 0x6E:
			LD(RegisterTarget::L, RegisterTarget::MemHL);
			break;
		case 0x6F:
			LD(RegisterTarget::L, RegisterTarget::A);
			break;
		case 0x70:
			LD(RegisterTarget::MemHL, RegisterTarget::B);
			break;
		case 0x71:
			LD(RegisterTarget::MemHL, RegisterTarget::C);
			break;
		case 0x72:
			LD(RegisterTarget::MemHL, RegisterTarget::D);
			break;
		case 0x73:
			LD(RegisterTarget::MemHL, RegisterTarget::E);
			break;
		case 0x74:
			LD(RegisterTarget::MemHL, RegisterTarget::H);
			break;
		case 0x75:
			LD(RegisterTarget::MemHL, RegisterTarget::L);
			break;
		case 0x76:
			currentInstruction.mnemonic = "HALT - Unimplemented";
			break;
		case 0x77:
			LD(RegisterTarget::MemHL, RegisterTarget::A);
			break;
		case 0x78:
			LD(RegisterTarget::A, RegisterTarget::B);
			break;
		case 0x79:
			LD(RegisterTarget::A, RegisterTarget::C);
			break;
		case 0x7A:
			LD(RegisterTarget::A, RegisterTarget::D);
			break;
		case 0x7B:
			LD(RegisterTarget::A, RegisterTarget::E);
			break;
		case 0x7C:
			LD(RegisterTarget::A, RegisterTarget::H);
			break;
		case 0x7D:
			LD(RegisterTarget::A, RegisterTarget::L);
			break;
		case 0x7E:
			LD(RegisterTarget::A, RegisterTarget::MemHL);
			break;
		case 0x7F:
			LD(RegisterTarget::A, RegisterTarget::A);
			break;
		case 0x80:
			ADD(RegisterTarget::B);
			break;
		case 0x81:
			ADD(RegisterTarget::C);
			break;
		case 0x82:
			ADD(RegisterTarget::D);
			break;
		case 0x83:
			ADD(RegisterTarget::E);
			break;
		case 0x84:
			ADD(RegisterTarget::H);
			break;
		case 0x85:
			ADD(RegisterTarget::L);
			break;
		case 0x86:
			ADD(RegisterTarget::MemHL);
			break;
		case 0x87:
			ADD(RegisterTarget::A);
			break;
		case 0x88:
			ADC(RegisterTarget::B);
			break;
		case 0x89:
			ADC(RegisterTarget::C);
			break;
		case 0x8A:
			ADC(RegisterTarget::D);
			break;
		case 0x8B:
			ADC(RegisterTarget::E);
			break;
		case 0x8C:
			ADC(RegisterTarget::H);
			break;
		case 0x8D:
			ADC(RegisterTarget::L);
			break;
		case 0x8E:
			ADC(RegisterTarget::MemHL);
			break;
		case 0x8F:
			ADC(RegisterTarget::A);
			break;
		case 0x90:
			SUB(RegisterTarget::B);
			break;
		case 0x91:
			SUB(RegisterTarget::C);
			break;
		case 0x92:
			SUB(RegisterTarget::D);
			break;
		case 0x93:
			SUB(RegisterTarget::E);
			break;
		case 0x94:
			SUB(RegisterTarget::H);
			break;
		case 0x95:
			SUB(RegisterTarget::L);
			break;
		case 0x96:
			SUB(RegisterTarget::MemHL);
			break;
		case 0x97:
			SUB(RegisterTarget::A);
			break;
		case 0x98:
			SBC(RegisterTarget::B);
			break;
		case 0x99:
			SBC(RegisterTarget::C);
			break;
		case 0x9A:
			SBC(RegisterTarget::D);
			break;
		case 0x9B:
			SBC(RegisterTarget::E);
			break;
		case 0x9C:
			SBC(RegisterTarget::H);
			break;
		case 0x9D:
			SBC(RegisterTarget::L);
			break;
		case 0x9E:
			SBC(RegisterTarget::MemHL);
			break;
		case 0x9F:
			SBC(RegisterTarget::A);
			break;
		case 0xA0:
			AND(RegisterTarget::B);
			break;
		case 0xA1:
			AND(RegisterTarget::C);
			break;
		case 0xA2:
			AND(RegisterTarget::D);
			break;
		case 0xA3:
			AND(RegisterTarget::E);
			break;
		case 0xA4:
			AND(RegisterTarget::H);
			break;
		case 0xA5:
			AND(RegisterTarget::L);
			break;
		case 0xA6:
			AND(RegisterTarget::MemHL);
			break;
		case 0xA7:
			AND(RegisterTarget::A);
			break;
		case 0xA8:
			XOR(RegisterTarget::B);
			break;
		case 0xA9:
			XOR(RegisterTarget::C);
			break;
		case 0xAA:
			XOR(RegisterTarget::D);
			break;
		case 0xAB:
			XOR(RegisterTarget::E);
			break;
		case 0xAC:
			XOR(RegisterTarget::H);
			break;
		case 0xAD:
			XOR(RegisterTarget::L);
			break;
		case 0xAE:
			XOR(RegisterTarget::MemHL);
			break;
		case 0xAF:
			XOR(RegisterTarget::A);
			break;
		case 0xB0:
			OR(RegisterTarget::B);
			break;
		case 0xB1:
			OR(RegisterTarget::C);
			break;
		case 0xB2:
			OR(RegisterTarget::D);
			break;
		case 0xB3:
			OR(RegisterTarget::E);
			break;
		case 0xB4:
			OR(RegisterTarget::H);
			break;
		case 0xB5:
			OR(RegisterTarget::L);
			break;
		case 0xB6:
			OR(RegisterTarget::MemHL);
			break;
		case 0xB7:
			OR(RegisterTarget::A);
			break;
		case 0xB8:
			CP(RegisterTarget::B);
			break;
		case 0xB9:
			CP(RegisterTarget::C);
			break;
		case 0xBA:
			CP(RegisterTarget::D);
			break;
		case 0xBB:
			CP(RegisterTarget::E);
			break;
		case 0xBC:
			CP(RegisterTarget::H);
			break;
		case 0xBD:
			CP(RegisterTarget::L);
			break;
		case 0xBE:
			CP(RegisterTarget::MemHL);
			break;
		case 0xBF:
			CP(RegisterTarget::A);
			break;
		case 0xC0:
			RET(Condition::NotZero);
			break;
		case 0xC1:
			POP(RegisterTarget::BC);
			break;
		case 0xC2:
			JP(Condition::NotZero);
			break;
		case 0xC3:
			JP(Condition::None);
			break;
		case 0xC4:
			CALL(Condition::NotZero);
			break;
		case 0xC5:
			PUSH(RegisterTarget::BC);
			break;
		case 0xC6:
			ADD(RegisterTarget::Byte);
			break;
		case 0xC7:
			RST(0);
			break;
		case 0xC8:
			RET(Condition::Zero);
			break;
		case 0xC9:
			RET(Condition::None);
			break;
		case 0xCA:
			JP(Condition::Zero);
			break;
		case 0xCB:
			Prefix();
			break;
		case 0xCC:
			CALL(Condition::Zero);
			break;
		case 0xCD:
			CALL(Condition::None);
			break;
		case 0xCE:
			ADC(RegisterTarget::Byte);
			break;
		case 0xCF:
			RST(1);
			break;
		case 0xD0:
			RET(Condition::NotCarry);
			break;
		case 0xD1:
			POP(RegisterTarget::DE);
			break;
		case 0xD2:
			JP(Condition::NotCarry);
			break;
		case 0xD3:
			currentInstruction.mnemonic = "D3 - INVALID";
			break;
		case 0xD4:
			CALL(Condition::NotCarry);
			break;
		case 0xD5:
			PUSH(RegisterTarget::DE);
			break;
		case 0xD6:
			SUB(RegisterTarget::Byte);
			break;
		case 0xD7:
			RST(2);
			break;
		case 0xD8:
			RET(Condition::Carry);
			break;
		case 0xD9:
			RET(Condition::Interrupt);
			break;
		case 0xDA:
			JP(Condition::Carry);
			break;
		case 0xDB:
			currentInstruction.mnemonic = "DB - INVALID";
			break;
		case 0xDC:
			CALL(Condition::Carry);
			break;
		case 0xDD:
			currentInstruction.mnemonic = "DD - INVALID";
			break;
		case 0xDE:
			SBC(RegisterTarget::Byte);
			break;
		case 0xDF:
			RST(3);
			break;
		case 0xE0:
			LD(RegisterTarget::Offset, RegisterTarget::A);
			break;
		case 0xE1:
			POP(RegisterTarget::HL);
			break;
		case 0xE2:
			LD(RegisterTarget::OffsetC, RegisterTarget::A);
			break;
		case 0xE3:
			currentInstruction.mnemonic = "E3 - INVALID";
			break;
		case 0xE4:
			currentInstruction.mnemonic = "E4 - INVALID";
			break;
		case 0xE5:
			PUSH(RegisterTarget::HL);
			break;
		case 0xE6:
			AND(RegisterTarget::Byte);
			break;
		case 0xE7:
			RST(4);
			break;
		case 0xE8:
			ADD(RegisterTarget::Offset, RegisterTarget::SP);
			break;
		case 0xE9:
			JP(Condition::HL);
			break;
		case 0xEA:
			LD(RegisterTarget::Word, RegisterTarget::A);
			break;
		case 0xEB:
			currentInstruction.mnemonic = "EB - INVALID";
			break;
		case 0xEC:
			currentInstruction.mnemonic = "EC - INVALID";
			break;
		case 0xED:
			currentInstruction.mnemonic = "ED - INVALID";
			break;
		case 0xEE:
			XOR(RegisterTarget::Byte);
			break;
		case 0xEF:
			RST(5);
			break;
		case 0xF0:
			LD(RegisterTarget::A, RegisterTarget::Offset);
			break;
		case 0xF1:
			POP(RegisterTarget::AF);
			break;
		case 0xF2:
			LD(RegisterTarget::A, RegisterTarget::OffsetC);
			break;
		case 0xF3:
			currentInstruction.mnemonic = "DI - Unimplemented";
			break;
		case 0xF4:
			currentInstruction.mnemonic = "F4 - INVALID";
			break;
		case 0xF5:
			PUSH(RegisterTarget::AF);
			break;
		case 0xF6:
			OR(RegisterTarget::Byte);
			break;
		case 0xF7:
			RST(6);
			break;
		case 0xF8:
			// LD(RegisterTarget::HL, )
			currentInstruction.mnemonic = "LD HL, SP + s8 - Unimplemented";
			break;
		case 0xF9:
			LD(RegisterTarget::SP, RegisterTarget::HL);
			break;
		case 0xFA:
			LD(RegisterTarget::A, RegisterTarget::Word);
			break;
		case 0xFB:
			currentInstruction.mnemonic = "EI - Unimplemented";
			break;
		case 0xFC:
			currentInstruction.mnemonic = "FC - INVALID";
			break;
		case 0xFD:
			currentInstruction.mnemonic = "FD - INVALID";
			break;
		case 0xFE:
			CP(RegisterTarget::Byte);
			break;
		case 0xFF:
			RST(7);
			break;
		default:
			std::cout << std::hex << "Unsupported instruction " << OP << " at " << PC << '\n';
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::Reset()
{
	mCycles = 0;
	tCycles = 0;
	OP = 0x0;
	instructions.clear();
	if (memory->GetBootROMEnabled())
	{
		AF = 0x00;
		BC = 0x00;
		DE = 0x00;
		HL = 0x00;
		zero = false;
		subtract = false;
		halfCarry = false;
		carry = false;
		IME = false;
		PC = 0x00;
		SP = 0x0;
	}
	else
	{
		SkipBootROM(GameBoyMode::DMG);
	}
	
}

u8 CPU::FetchByte()
{
	return memory->Read(PC++);
}

u16 CPU::FetchWord()
{
	u8 low = FetchByte();
	u8 high = FetchByte();
	return (high << 8) | low;
}

void CPU::SetFlag(Flag flag, bool enabled)
{
	u8& flags = AF.GetLowByte();
	flags = (flags & ~((u8)1 << (u8)flag)) | ((u8)enabled << (u8)flag);
	switch (flag)
	{
		case Flag::Zero:
			zero = enabled;
			break;
		case Flag::Subtract:
			subtract = enabled;
			break;
		case Flag::HalfCarry:
			halfCarry = enabled;
			break;
		case Flag::Carry:
			carry = enabled;
			break;
	}
}

void CPU::Prefix()
{
	u8 code = FetchByte();
	currentInstruction.opcode = currentInstruction.opcode << 8 | code;
	switch (code)
	{
		case 0x00:
			RLC(RegisterTarget::B);
			break;
		case 0x01:
			RLC(RegisterTarget::C);
			break;
		case 0x02:
			RLC(RegisterTarget::D);
			break;
		case 0x03:
			RLC(RegisterTarget::E);
			break;
		case 0x04:
			RLC(RegisterTarget::H);
			break;
		case 0x05:
			RLC(RegisterTarget::L);
			break;
		case 0x06:
			RLC(RegisterTarget::MemHL);
			break;
		case 0x07:
			RLC(RegisterTarget::A);
			break;
		case 0x08:
			RRC(RegisterTarget::B);
			break;
		case 0x09:
			RRC(RegisterTarget::C);
			break;
		case 0x0A:
			RRC(RegisterTarget::D);
			break;
		case 0x0B:
			RRC(RegisterTarget::E);
			break;
		case 0x0C:
			RRC(RegisterTarget::H);
			break;
		case 0x0D:
			RRC(RegisterTarget::L);
			break;
		case 0x0E:
			RRC(RegisterTarget::MemHL);
			break;
		case 0x0F:
			RRC(RegisterTarget::A);
			break;
		case 0x10:
			RL(RegisterTarget::B);
			break;
		case 0x11:
			RL(RegisterTarget::C);
			break;
		case 0x12:
			RL(RegisterTarget::D);
			break;
		case 0x13:
			RL(RegisterTarget::E);
			break;
		case 0x14:
			RL(RegisterTarget::H);
			break;
		case 0x15:
			RL(RegisterTarget::L);
			break;
		case 0x16:
			RL(RegisterTarget::MemHL);
			break;
		case 0x17:
			RL(RegisterTarget::A);
			break;
		case 0x18:
			RR(RegisterTarget::B);
			break;
		case 0x19:
			RR(RegisterTarget::C);
			break;
		case 0x1A:
			RR(RegisterTarget::D);
			break;
		case 0x1B:
			RR(RegisterTarget::E);
			break;
		case 0x1C:
			RR(RegisterTarget::H);
			break;
		case 0x1D:
			RR(RegisterTarget::L);
			break;
		case 0x1E:
			RR(RegisterTarget::MemHL);
			break;
		case 0x1F:
			RR(RegisterTarget::A);
			break;
		case 0x20:
			SLA(RegisterTarget::B);
			break;
		case 0x21:
			SLA(RegisterTarget::C);
			break;
		case 0x22:
			SLA(RegisterTarget::D);
			break;
		case 0x23:
			SLA(RegisterTarget::E);
			break;
		case 0x24:
			SLA(RegisterTarget::H);
			break;
		case 0x25:
			SLA(RegisterTarget::L);
			break;
		case 0x26:
			SLA(RegisterTarget::MemHL);
			break;
		case 0x27:
			SLA(RegisterTarget::A);
			break;
		case 0x28:
			SRA(RegisterTarget::B);
			break;
		case 0x29:
			SRA(RegisterTarget::C);
			break;
		case 0x2A:
			SRA(RegisterTarget::D);
			break;
		case 0x2B:
			SRA(RegisterTarget::E);
			break;
		case 0x2C:
			SRA(RegisterTarget::H);
			break;
		case 0x2D:
			SRA(RegisterTarget::L);
			break;
		case 0x2E:
			SRA(RegisterTarget::MemHL);
			break;
		case 0x2F:
			SRA(RegisterTarget::A);
			break;
		case 0x30:
			SWAP(RegisterTarget::B);
			break;
		case 0x31:
			SWAP(RegisterTarget::C);
			break;
		case 0x32:
			SWAP(RegisterTarget::D);
			break;
		case 0x33:
			SWAP(RegisterTarget::E);
			break;
		case 0x34:
			SWAP(RegisterTarget::H);
			break;
		case 0x35:
			SWAP(RegisterTarget::L);
			break;
		case 0x36:
			SWAP(RegisterTarget::MemHL);
			break;
		case 0x37:
			SWAP(RegisterTarget::A);
			break;
		case 0x38:
			SRL(RegisterTarget::B);
			break;
		case 0x39:
			SRL(RegisterTarget::C);
			break;
		case 0x3A:
			SRL(RegisterTarget::D);
			break;
		case 0x3B:
			SRL(RegisterTarget::E);
			break;
		case 0x3C:
			SRL(RegisterTarget::H);
			break;
		case 0x3D:
			SRL(RegisterTarget::L);
			break;
		case 0x3E:
			SRL(RegisterTarget::MemHL);
			break;
		case 0x3F:
			SRL(RegisterTarget::A);
			break;
		case 0x40:
			BIT(RegisterTarget::B, 0);
			break;
		case 0x41:
			BIT(RegisterTarget::C, 0);
			break;
		case 0x42:
			BIT(RegisterTarget::D, 0);
			break;
		case 0x43:
			BIT(RegisterTarget::E, 0);
			break;
		case 0x44:
			BIT(RegisterTarget::H, 0);
			break;
		case 0x45:
			BIT(RegisterTarget::L, 0);
			break;
		case 0x46:
			BIT(RegisterTarget::MemHL, 0);
			break;
		case 0x47:
			BIT(RegisterTarget::A, 0);
			break;
		case 0x48:
			BIT(RegisterTarget::B, 1);
			break;
		case 0x49:
			BIT(RegisterTarget::C, 1);
			break;
		case 0x4A:
			BIT(RegisterTarget::D, 1);
			break;
		case 0x4B:
			BIT(RegisterTarget::E, 1);
			break;
		case 0x4C:
			BIT(RegisterTarget::H, 1);
			break;
		case 0x4D:
			BIT(RegisterTarget::L, 1);
			break;
		case 0x4E:
			BIT(RegisterTarget::MemHL, 1);
			break;
		case 0x4F:
			BIT(RegisterTarget::A, 1);
			break;
		case 0x50:
			BIT(RegisterTarget::B, 2);
			break;
		case 0x51:
			BIT(RegisterTarget::C, 2);
			break;
		case 0x52:
			BIT(RegisterTarget::D, 2);
			break;
		case 0x53:
			BIT(RegisterTarget::E, 2);
			break;
		case 0x54:
			BIT(RegisterTarget::H, 2);
			break;
		case 0x55:
			BIT(RegisterTarget::L, 2);
			break;
		case 0x56:
			BIT(RegisterTarget::MemHL, 2);
			break;
		case 0x57:
			BIT(RegisterTarget::A, 2);
			break;
		case 0x58:
			BIT(RegisterTarget::B, 3);
			break;
		case 0x59:
			BIT(RegisterTarget::C, 3);
			break;
		case 0x5A:
			BIT(RegisterTarget::D, 3);
			break;
		case 0x5B:
			BIT(RegisterTarget::E, 3);
			break;
		case 0x5C:
			BIT(RegisterTarget::H, 3);
			break;
		case 0x5D:
			BIT(RegisterTarget::L, 3);
			break;
		case 0x5E:
			BIT(RegisterTarget::MemHL, 3);
			break;
		case 0x5F:
			BIT(RegisterTarget::A, 3);
			break;
		case 0x60:
			BIT(RegisterTarget::B, 4);
			break;
		case 0x61:
			BIT(RegisterTarget::C, 4);
			break;
		case 0x62:
			BIT(RegisterTarget::D, 4);
			break;
		case 0x63:
			BIT(RegisterTarget::E, 4);
			break;
		case 0x64:
			BIT(RegisterTarget::H, 4);
			break;
		case 0x65:
			BIT(RegisterTarget::L, 4);
			break;
		case 0x66:
			BIT(RegisterTarget::MemHL, 4);
			break;
		case 0x67:
			BIT(RegisterTarget::A, 4);
			break;
		case 0x68:
			BIT(RegisterTarget::B, 5);
			break;
		case 0x69:
			BIT(RegisterTarget::C, 5);
			break;
		case 0x6A:
			BIT(RegisterTarget::D, 5);
			break;
		case 0x6B:
			BIT(RegisterTarget::E, 5);
			break;
		case 0x6C:
			BIT(RegisterTarget::H, 5);
			break;
		case 0x6D:
			BIT(RegisterTarget::L, 5);
			break;
		case 0x6E:
			BIT(RegisterTarget::MemHL, 5);
			break;
		case 0x6F:
			BIT(RegisterTarget::A, 5);
			break;
		case 0x70:
			BIT(RegisterTarget::B, 6);
			break;
		case 0x71:
			BIT(RegisterTarget::C, 6);
			break;
		case 0x72:
			BIT(RegisterTarget::D, 6);
			break;
		case 0x73:
			BIT(RegisterTarget::E, 6);
			break;
		case 0x74:
			BIT(RegisterTarget::H, 6);
			break;
		case 0x75:
			BIT(RegisterTarget::L, 6);
			break;
		case 0x76:
			BIT(RegisterTarget::MemHL, 6);
			break;
		case 0x77:
			BIT(RegisterTarget::A, 6);
			break;
		case 0x78:
			BIT(RegisterTarget::B, 7);
			break;
		case 0x79:
			BIT(RegisterTarget::C, 7);
			break;
		case 0x7A:
			BIT(RegisterTarget::D, 7);
			break;
		case 0x7B:
			BIT(RegisterTarget::E, 7);
			break;
		case 0x7C:
			BIT(RegisterTarget::H, 7);
			break;
		case 0x7D:
			BIT(RegisterTarget::L, 7);
			break;
		case 0x7E:
			BIT(RegisterTarget::MemHL, 7);
			break;
		case 0x7F:
			BIT(RegisterTarget::A, 7);
			break;
		case 0x80:
			RES(RegisterTarget::B, 0);
			break;
		case 0x81:
			RES(RegisterTarget::C, 0);
			break;
		case 0x82:
			RES(RegisterTarget::D, 0);
			break;
		case 0x83:
			RES(RegisterTarget::E, 0);
			break;
		case 0x84:
			RES(RegisterTarget::H, 0);
			break;
		case 0x85:
			RES(RegisterTarget::L, 0);
			break;
		case 0x86:
			RES(RegisterTarget::MemHL, 0);
			break;
		case 0x87:
			RES(RegisterTarget::A, 0);
			break;
		case 0x88:
			RES(RegisterTarget::B, 1);
			break;
		case 0x89:
			RES(RegisterTarget::C, 1);
			break;
		case 0x8A:
			RES(RegisterTarget::D, 1);
			break;
		case 0x8B:
			RES(RegisterTarget::E, 1);
			break;
		case 0x8C:
			RES(RegisterTarget::H, 1);
			break;
		case 0x8D:
			RES(RegisterTarget::L, 1);
			break;
		case 0x8E:
			RES(RegisterTarget::MemHL, 1);
			break;
		case 0x8F:
			RES(RegisterTarget::A, 1);
			break;
		case 0x90:
			RES(RegisterTarget::B, 2);
			break;
		case 0x91:
			RES(RegisterTarget::C, 2);
			break;
		case 0x92:
			RES(RegisterTarget::D, 2);
			break;
		case 0x93:
			RES(RegisterTarget::E, 2);
			break;
		case 0x94:
			RES(RegisterTarget::H, 2);
			break;
		case 0x95:
			RES(RegisterTarget::L, 2);
			break;
		case 0x96:
			RES(RegisterTarget::MemHL, 2);
			break;
		case 0x97:
			RES(RegisterTarget::A, 2);
			break;
		case 0x98:
			RES(RegisterTarget::B, 3);
			break;
		case 0x99:
			RES(RegisterTarget::C, 3);
			break;
		case 0x9A:
			RES(RegisterTarget::D, 3);
			break;
		case 0x9B:
			RES(RegisterTarget::E, 3);
			break;
		case 0x9C:
			RES(RegisterTarget::H, 3);
			break;
		case 0x9D:
			RES(RegisterTarget::L, 3);
			break;
		case 0x9E:
			RES(RegisterTarget::MemHL, 3);
			break;
		case 0x9F:
			RES(RegisterTarget::A, 3);
			break;
		case 0xA0:
			RES(RegisterTarget::B, 4);
			break;
		case 0xA1:
			RES(RegisterTarget::C, 4);
			break;
		case 0xA2:
			RES(RegisterTarget::D, 4);
			break;
		case 0xA3:
			RES(RegisterTarget::E, 4);
			break;
		case 0xA4:
			RES(RegisterTarget::H, 4);
			break;
		case 0xA5:
			RES(RegisterTarget::L, 4);
			break;
		case 0xA6:
			RES(RegisterTarget::MemHL, 4);
			break;
		case 0xA7:
			RES(RegisterTarget::A, 4);
			break;
		case 0xA8:
			RES(RegisterTarget::B, 5);
			break;
		case 0xA9:
			RES(RegisterTarget::C, 5);
			break;
		case 0xAA:
			RES(RegisterTarget::D, 5);
			break;
		case 0xAB:
			RES(RegisterTarget::E, 5);
			break;
		case 0xAC:
			RES(RegisterTarget::H, 5);
			break;
		case 0xAD:
			RES(RegisterTarget::L, 5);
			break;
		case 0xAE:
			RES(RegisterTarget::MemHL, 5);
			break;
		case 0xAF:
			RES(RegisterTarget::A, 5);
			break;
		case 0xB0:
			RES(RegisterTarget::B, 6);
			break;
		case 0xB1:
			RES(RegisterTarget::C, 6);
			break;
		case 0xB2:
			RES(RegisterTarget::D, 6);
			break;
		case 0xB3:
			RES(RegisterTarget::E, 6);
			break;
		case 0xB4:
			RES(RegisterTarget::H, 6);
			break;
		case 0xB5:
			RES(RegisterTarget::L, 6);
			break;
		case 0xB6:
			RES(RegisterTarget::MemHL, 6);
			break;
		case 0xB7:
			RES(RegisterTarget::A, 6);
			break;
		case 0xB8:
			RES(RegisterTarget::B, 7);
			break;
		case 0xB9:
			RES(RegisterTarget::C, 7);
			break;
		case 0xBA:
			RES(RegisterTarget::D, 7);
			break;
		case 0xBB:
			RES(RegisterTarget::E, 7);
			break;
		case 0xBC:
			RES(RegisterTarget::H, 7);
			break;
		case 0xBD:
			RES(RegisterTarget::L, 7);
			break;
		case 0xBE:
			RES(RegisterTarget::MemHL, 7);
			break;
		case 0xBF:
			RES(RegisterTarget::A, 7);
			break;
		case 0xC0:
			SET(RegisterTarget::B, 0);
			break;
		case 0xC1:
			SET(RegisterTarget::C, 0);
			break;
		case 0xC2:
			SET(RegisterTarget::D, 0);
			break;
		case 0xC3:
			SET(RegisterTarget::E, 0);
			break;
		case 0xC4:
			SET(RegisterTarget::H, 0);
			break;
		case 0xC5:
			SET(RegisterTarget::L, 0);
			break;
		case 0xC6:
			SET(RegisterTarget::MemHL, 0);
			break;
		case 0xC7:
			SET(RegisterTarget::A, 0);
			break;
		case 0xC8:
			SET(RegisterTarget::B, 1);
			break;
		case 0xC9:
			SET(RegisterTarget::C, 1);
			break;
		case 0xCA:
			SET(RegisterTarget::D, 1);
			break;
		case 0xCB:
			SET(RegisterTarget::E, 1);
			break;
		case 0xCC:
			SET(RegisterTarget::H, 1);
			break;
		case 0xCD:
			SET(RegisterTarget::L, 1);
			break;
		case 0xCE:
			SET(RegisterTarget::MemHL, 1);
			break;
		case 0xCF:
			SET(RegisterTarget::A, 1);
			break;
		case 0xD0:
			SET(RegisterTarget::B, 2);
			break;
		case 0xD1:
			SET(RegisterTarget::C, 2);
			break;
		case 0xD2:
			SET(RegisterTarget::D, 2);
			break;
		case 0xD3:
			SET(RegisterTarget::E, 2);
			break;
		case 0xD4:
			SET(RegisterTarget::H, 2);
			break;
		case 0xD5:
			SET(RegisterTarget::L, 2);
			break;
		case 0xD6:
			SET(RegisterTarget::MemHL, 2);
			break;
		case 0xD7:
			SET(RegisterTarget::A, 2);
			break;
		case 0xD8:
			SET(RegisterTarget::B, 3);
			break;
		case 0xD9:
			SET(RegisterTarget::C, 3);
			break;
		case 0xDA:
			SET(RegisterTarget::D, 3);
			break;
		case 0xDB:
			SET(RegisterTarget::E, 3);
			break;
		case 0xDC:
			SET(RegisterTarget::H, 3);
			break;
		case 0xDD:
			SET(RegisterTarget::L, 3);
			break;
		case 0xDE:
			SET(RegisterTarget::MemHL, 3);
			break;
		case 0xDF:
			SET(RegisterTarget::A, 3);
			break;
		case 0xE0:
			SET(RegisterTarget::B, 4);
			break;
		case 0xE1:
			SET(RegisterTarget::C, 4);
			break;
		case 0xE2:
			SET(RegisterTarget::D, 4);
			break;
		case 0xE3:
			SET(RegisterTarget::E, 4);
			break;
		case 0xE4:
			SET(RegisterTarget::H, 4);
			break;
		case 0xE5:
			SET(RegisterTarget::L, 4);
			break;
		case 0xE6:
			SET(RegisterTarget::MemHL, 4);
			break;
		case 0xE7:
			SET(RegisterTarget::A, 4);
			break;
		case 0xE8:
			SET(RegisterTarget::B, 5);
			break;
		case 0xE9:
			SET(RegisterTarget::C, 5);
			break;
		case 0xEA:
			SET(RegisterTarget::D, 5);
			break;
		case 0xEB:
			SET(RegisterTarget::E, 5);
			break;
		case 0xEC:
			SET(RegisterTarget::H, 5);
			break;
		case 0xED:
			SET(RegisterTarget::L, 5);
			break;
		case 0xEE:
			SET(RegisterTarget::MemHL, 5);
			break;
		case 0xEF:
			SET(RegisterTarget::A, 5);
			break;
		case 0xF0:
			SET(RegisterTarget::B, 6);
			break;
		case 0xF1:
			SET(RegisterTarget::C, 6);
			break;
		case 0xF2:
			SET(RegisterTarget::D, 6);
			break;
		case 0xF3:
			SET(RegisterTarget::E, 6);
			break;
		case 0xF4:
			SET(RegisterTarget::H, 6);
			break;
		case 0xF5:
			SET(RegisterTarget::L, 6);
			break;
		case 0xF6:
			SET(RegisterTarget::MemHL, 6);
			break;
		case 0xF7:
			SET(RegisterTarget::A, 6);
			break;
		case 0xF8:
			SET(RegisterTarget::B, 7);
			break;
		case 0xF9:
			SET(RegisterTarget::C, 7);
			break;
		case 0xFA:
			SET(RegisterTarget::D, 7);
			break;
		case 0xFB:
			SET(RegisterTarget::E, 7);
			break;
		case 0xFC:
			SET(RegisterTarget::H, 7);
			break;
		case 0xFD:
			SET(RegisterTarget::L, 7);
			break;
		case 0xFE:
			SET(RegisterTarget::MemHL, 7);
			break;
		case 0xFF:
			SET(RegisterTarget::A, 7);
			break;
		default:
			std::cout << std::hex << "Unsupported prefix instruction " << code << " at " << PC << '\n';
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::NOP()
{
	currentInstruction.mnemonic = "NOP";
	tCycles = 4;
	mCycles = 1;
}

void CPU::LD(RegisterTarget to, RegisterTarget from)
{
	switch (to)
	{
		case RegisterTarget::A:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD A, A";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD A, B";
					AF.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD A, C";
					AF.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD A, D";
					AF.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD A, E";
					AF.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD A, H";
					AF.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD A, L";
					AF.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD A, d8";
					AF.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemBC:
					currentInstruction.mnemonic = "LD A, (BC)";
					AF.SetHighByte(memory->Read(BC.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemDE:
					currentInstruction.mnemonic = "LD A, (DE)";
					AF.SetHighByte(memory->Read(DE.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD A, (HL)";
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHLDec:
					currentInstruction.mnemonic = "LD A, (HL-)";
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					HL--;
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHLInc:
					currentInstruction.mnemonic = "LD A, (HL+)";
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					HL++;
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::OffsetC:
					currentInstruction.mnemonic = "LD A, $FF00 + C";
					AF.SetHighByte(memory->Read(0xFF00 + BC.GetLowByte()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::Offset:
					currentInstruction.mnemonic = "LD A, $FF00 + d8";
					AF.SetHighByte(memory->Read(0xFF00 + FetchByte()));
					tCycles = 12;
					mCycles = 3;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::B:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD B, A";
					BC.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD B, B";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD B, C";
					BC.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD B, D";
					BC.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD B, E";
					BC.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD B, H";
					BC.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD B, L";
					BC.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD B, d8";
					BC.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD B, (HL)";
					BC.SetHighByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::C:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD C, A";
					BC.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD C, B";
					BC.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD C, C";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD C, D";
					BC.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD C, E";
					BC.SetLowByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD C, H";
					BC.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD C, L";
					BC.SetLowByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD C, d8";
					BC.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD C, (HL)";
					BC.SetLowByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::BC:
			switch (from)
			{
				case RegisterTarget::Word:
					currentInstruction.mnemonic = "LD BC, d16";
					BC.SetRegister(FetchWord());
					tCycles = 12;
					mCycles = 3;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::D:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD D, A";
					DE.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD D, B";
					DE.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD D, C";
					DE.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD D, D";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD D, E";
					DE.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD D, H";
					DE.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD D, L";
					DE.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD D, d8";
					DE.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD D, (HL)";
					DE.SetHighByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::E:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD E, A";
					DE.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD E, B";
					DE.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD E, C";
					DE.SetLowByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD E, D";
					DE.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD E, E";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD E, H";
					DE.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD E, L";
					DE.SetLowByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD E, d8";
					DE.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD E, (HL)";
					DE.SetLowByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::DE:
			switch (from)
			{
				case RegisterTarget::Word:
					currentInstruction.mnemonic = "LD DE, d16";
					DE.SetRegister(FetchWord());
					tCycles = 12;
					mCycles = 3;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::H:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD H, A";
					HL.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD H, B";
					HL.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD H, C";
					HL.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD H, D";
					HL.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD H, E";
					HL.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD H, H";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD H, L";
					HL.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD H, d8";
					HL.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD H, (HL)";
					HL.SetHighByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::L:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD L, A";
					HL.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD L, B";
					HL.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD L, C";
					HL.SetLowByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD L, D";
					HL.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD L, E";
					HL.SetLowByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD L, H";
					HL.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD L, L";
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					currentInstruction.mnemonic = "LD L, d8";
					HL.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "LD L, (HL)";
					HL.SetLowByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::HL:
			switch (from)
			{
				case RegisterTarget::Word:
					currentInstruction.mnemonic = "LD HL, d16";
					HL.SetRegister(FetchWord());
					tCycles = 12;
					mCycles = 3;
					break;
					// TODO LD HL, SP+s8
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::SP:
			switch (from)
			{
				case RegisterTarget::Word:
					currentInstruction.mnemonic = "LD SP, d16";
					SP = FetchWord();
					tCycles = 12;
					mCycles = 3;
					break;
				case RegisterTarget::HL:
					currentInstruction.mnemonic = "LD SP, HL";
					SP = HL.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::Word:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD d16, A";
					memory->Write(FetchWord(), AF.GetHighByte());
					tCycles = 16;
					mCycles = 4;
					break;
				case RegisterTarget::SP:
				{
					currentInstruction.mnemonic = "LD d16, SP";
					u16 address = FetchWord();
					u8 low = SP & 0xFF;
					u8 high = SP >> 8;
					memory->Write(address, low);
					memory->Write(address + 1, high);
					tCycles = 20;
					mCycles = 5;
					break;
				}
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::MemBC:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD (BC), A";
					memory->Write(BC.GetRegister(), AF.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::MemDE:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD DE, A";
					memory->Write(DE.GetRegister(), AF.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::MemHL:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD (HL), A";
					memory->Write(HL.GetRegister(), AF.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "LD (HL), B";
					memory->Write(HL.GetRegister(), BC.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "LD (HL), C";
					memory->Write(HL.GetRegister(), BC.GetLowByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "LD (HL), D";
					memory->Write(HL.GetRegister(), DE.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "LD (HL), E";
					memory->Write(HL.GetRegister(), DE.GetLowByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "LD (HL), H";
					memory->Write(HL.GetRegister(), HL.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "LD (HL), L";
					memory->Write(HL.GetRegister(), HL.GetLowByte());
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::MemHLDec:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD (HL-), A";
					memory->Write(HL.GetRegister(), AF.GetHighByte());
					HL--;
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::MemHLInc:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD (HL+), A";
					memory->Write(HL.GetRegister(), AF.GetHighByte());
					HL++;
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::OffsetC:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD $FF00 + C, A";
					memory->Write(0xFF00 + BC.GetLowByte(), AF.GetHighByte());
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::Offset:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "LD $FF00 + d8, A";
					memory->Write(0xFF00 + FetchByte(), AF.GetHighByte());
					tCycles = 12;
					mCycles = 3;
					break;
				default:
					std::cout << "Unsupported or Invalid Load Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		default:
			std::cout << "Unsupported or Invalid Load Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}


void CPU::INC(RegisterTarget reg)
{
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "INC A";
			SetFlag(Flag::Subtract, false);
			((AF.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			AF.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "INC B";
			SetFlag(Flag::Subtract, false);
			((BC.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "INC C";
			SetFlag(Flag::Subtract, false);
			((BC.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::BC:
			currentInstruction.mnemonic = "INC BC";
			BC++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "INC D";
			SetFlag(Flag::Subtract, false);
			((DE.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((DE.GetHighByte() & 0x0F) + 1 & 0x0F) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "INC E";
			SetFlag(Flag::Subtract, false);
			((DE.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::DE:
			currentInstruction.mnemonic = "INC DE";
			DE++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "INC H";
			SetFlag(Flag::Subtract, false);
			((HL.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "INC L";
			SetFlag(Flag::Subtract, false);
			((HL.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::HL:
			currentInstruction.mnemonic = "INC HL";
			HL++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "INC (HL)";
			SetFlag(Flag::Subtract, false);
			((memory->Read(HL.GetRegister()) + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((memory->Read(HL.GetRegister()) & 0x0F) + 1 & 0x0F) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) + 1);
			tCycles = 12;
			mCycles = 3;
			break;
		default:
			std::cout << "Unsupported or Invalid Increment Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::DEC(RegisterTarget reg)
{
	switch (reg)
	{
		currentInstruction.mnemonic = "DEC A";
		case RegisterTarget::A:
			SetFlag(Flag::Subtract, true);
			((AF.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			AF.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "DEC B";
			SetFlag(Flag::Subtract, true);
			((BC.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "DEC C";
			SetFlag(Flag::Subtract, true);
			((BC.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::BC:
			currentInstruction.mnemonic = "DEC BC";
			BC--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "DEC D";
			SetFlag(Flag::Subtract, true);
			((DE.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "DEC E";
			SetFlag(Flag::Subtract, true);
			((DE.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::DE:
			currentInstruction.mnemonic = "DEC DE";
			DE--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "DEC H";
			SetFlag(Flag::Subtract, true);
			((HL.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "DEC L";
			SetFlag(Flag::Subtract, true);
			((HL.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::HL:
			currentInstruction.mnemonic = "DEC HL";
			HL--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "DEC (HL)";
			SetFlag(Flag::Subtract, true);
			((memory->Read(HL.GetRegister()) - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((memory->Read(HL.GetRegister()) & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) - 1);
			tCycles = 12;
			mCycles = 3;
			break;
		default:
			std::cout << "Unsupported or Invalid Decrement Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::JP(Condition condition)
{
	u16 address = FetchWord();
	switch (condition)
	{
		case Condition::None:
			currentInstruction.mnemonic = "JP a16";
			PC = address;
			tCycles = 16;
			mCycles = 4;
			break;
		case Condition::Zero:
			currentInstruction.mnemonic = "JP Z a16";
			if (zero)
			{
				PC = address;
				tCycles = 16;
				mCycles = 4;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::NotZero:
			currentInstruction.mnemonic = "JP NZ a16";
			if (!zero)
			{
				PC = address;
				tCycles = 16;
				mCycles = 4;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::Carry:
			currentInstruction.mnemonic = "JP C a16";
			if (carry)
			{
				PC = address;
				tCycles = 16;
				mCycles = 4;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::NotCarry:
			currentInstruction.mnemonic = "JP NC a16";
			if (!carry)
			{
				PC = address;
				tCycles = 16;
				mCycles = 4;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::HL:
			currentInstruction.mnemonic = "JP HL";
			PC = HL.GetRegister();
			tCycles = 4;
			mCycles = 1;
			break;
		default:
			std::cout << "Unsupported or Invalid Jump Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::JR(Condition condition)
{
	s8 offset = FetchByte();
	switch (condition)
	{
		case Condition::None:
		{
			currentInstruction.mnemonic = "JR s8";
			PC += offset;
			tCycles = 12;
			mCycles = 3;
			break;
		}
		case Condition::Zero:
			currentInstruction.mnemonic = "JR Z s8";
			if (zero)
			{
				PC += offset;
				tCycles = 12;
				mCycles = 3;
			}
			else
			{
				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::NotZero:
			currentInstruction.mnemonic = "JR NZ s8";
			if (!zero)
			{
				PC += offset;
				tCycles = 12;
				mCycles = 3;
			}
			else
			{
				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::Carry:
			currentInstruction.mnemonic = "JR C s8";
			if (carry)
			{
				PC += offset;
				tCycles = 12;
				mCycles = 3;
			}
			else
			{
				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::NotCarry:
			currentInstruction.mnemonic = "JR NC s8";
			if (!carry)
			{
				PC += offset;
				tCycles = 12;
				mCycles = 3;
			}
			else
			{
				tCycles = 8;
				mCycles = 2;
			}
			break;
		default:
			std::cout << "Unsupported or Invalid Jump Relative Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::ADD(RegisterTarget from, RegisterTarget to)
{
	SetFlag(Flag::Subtract, false);
	switch (to)
	{
		case RegisterTarget::A:
			switch (from)
			{
				case RegisterTarget::A:
					currentInstruction.mnemonic = "ADD A, A";
					((AF.GetHighByte() + AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (AF.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + AF.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += AF.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					currentInstruction.mnemonic = "ADD A, B";
					((AF.GetHighByte() + BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (BC.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + BC.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += BC.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					currentInstruction.mnemonic = "ADD A, C";
					((AF.GetHighByte() + BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (BC.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + BC.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += BC.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					currentInstruction.mnemonic = "ADD A, D";
					((AF.GetHighByte() + DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (DE.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + DE.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += DE.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					currentInstruction.mnemonic = "ADD A, E";
					((AF.GetHighByte() + DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (DE.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + DE.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += DE.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					currentInstruction.mnemonic = "ADD A, H";
					((AF.GetHighByte() + HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (HL.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + HL.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += HL.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					currentInstruction.mnemonic = "ADD A, L";
					((AF.GetHighByte() + HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (HL.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + HL.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += HL.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::MemHL:
					currentInstruction.mnemonic = "ADD A, (HL)";
					((AF.GetHighByte() + memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (memory->Read(HL.GetRegister()) & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + memory->Read(HL.GetRegister())) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += memory->Read(HL.GetRegister());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::Byte:
				{
					currentInstruction.mnemonic = "ADD A, d8";
					u8 byte = FetchByte();
					((AF.GetHighByte() + byte) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (byte & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + byte) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += byte;
					tCycles = 8;
					mCycles = 2;
					break;
				}
				default:
					std::cout << "Unsupported or Invalid Add Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::HL:
			switch (from)
			{
				case RegisterTarget::BC:
					currentInstruction.mnemonic = "ADD HL, BC";
					(((HL.GetRegister() & 0x0FFF) + (BC.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + BC.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += BC.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::DE:
					currentInstruction.mnemonic = "ADD HL, DE";
					(((HL.GetRegister() & 0x0FFF) + (DE.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + DE.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += DE.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::HL:
					currentInstruction.mnemonic = "ADD HL, HL";
					(((HL.GetRegister() & 0x0FFF) + (HL.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + HL.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += HL.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::SP:
					currentInstruction.mnemonic = "ADD HL, SP";
					(((HL.GetRegister() & 0x0FFF) + (SP & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + SP) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += SP;
					tCycles = 8;
					mCycles = 2;
					break;
				default:
					std::cout << "Unsupported or Invalid Add Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		case RegisterTarget::SP:
			switch (from)
			{
				case RegisterTarget::Offset:
				{
					currentInstruction.mnemonic = "ADD SP, s8";
					s8 offset = FetchByte();
					SetFlag(Flag::Zero, false);
					((SP & 0x0F) + (offset & 0x0F) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((SP & 0xFF) + (offset & 0xFF) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					SP += offset;
					tCycles = 16;
					mCycles = 4;
					break;
				}
				default:
					std::cout << "Unsupported or Invalid Add Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
			break;
		default:
			std::cout << "Unsupported or Invalid Add Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::ADC(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	bool temp = GetCarryFlag();
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "ADC A, A";
			((AF.GetHighByte() + AF.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (AF.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + AF.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += AF.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "ADC A, B";
			((AF.GetHighByte() + BC.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (BC.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + BC.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += BC.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "ADC A, C";
			((AF.GetHighByte() + BC.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (BC.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + BC.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += BC.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "ADC A, D";
			((AF.GetHighByte() + DE.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (DE.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + DE.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "ADC A, E";
			((AF.GetHighByte() + DE.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (DE.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + DE.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "ADC A, H";
			((AF.GetHighByte() + HL.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (HL.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + HL.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += HL.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "ADC A, L";
			((AF.GetHighByte() + HL.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (HL.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + HL.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += HL.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "ADC A, (HL)";
			((AF.GetHighByte() + memory->Read(HL.GetRegister()) + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (memory->Read(HL.GetRegister()) & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + memory->Read(HL.GetRegister()) + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += memory->Read(HL.GetRegister()) + (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "ADC A, d8";
			u8 byte = FetchByte();
			((AF.GetHighByte() + byte + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (byte & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + byte + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += byte + (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid Add Carry Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SUB(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, true);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SUB A, A";
			((AF.GetHighByte() - AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (AF.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < AF.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SUB A, B";
			((AF.GetHighByte() - BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SUB A, C";
			((AF.GetHighByte() - BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SUB A, D";
			((AF.GetHighByte() - DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SUB A, E";
			((AF.GetHighByte() - DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SUB A, H";
			((AF.GetHighByte() - HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SUB A, L";
			((AF.GetHighByte() - HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SUB A, (HL)";
			((AF.GetHighByte() - memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (memory->Read(HL.GetRegister()) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < memory->Read(HL.GetRegister())) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= memory->Read(HL.GetRegister());
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "SUB A, d8";
			u8 byte = FetchByte();
			((AF.GetHighByte() - byte) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (byte & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < byte) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= byte;
			tCycles = 8;
			mCycles = 2;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid Subtract Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SBC(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, true);
	bool temp = GetCarryFlag();
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SBC A, A";
			((AF.GetHighByte() - (AF.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((AF.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (AF.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= AF.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SBC A, B";
			((AF.GetHighByte() - (BC.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((BC.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (BC.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SBC A, C";
			((AF.GetHighByte() - (BC.GetLowByte() + (u8)temp))) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((BC.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (BC.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SBC A, D";
			((AF.GetHighByte() - (DE.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((DE.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (DE.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SBC A, E";
			((AF.GetHighByte() - (DE.GetLowByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((DE.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (DE.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SBC A, H";
			((AF.GetHighByte() - (HL.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((HL.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (HL.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SBC A, L";
			((AF.GetHighByte() - (HL.GetLowByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((HL.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (HL.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SBC A, (HL)";
			((AF.GetHighByte() - (memory->Read(HL.GetRegister()) + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((memory->Read(HL.GetRegister() + (u8)temp)) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (memory->Read(HL.GetRegister()) + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= memory->Read(HL.GetRegister()) - (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "SBC A, d8";
			u8 byte = FetchByte();
			((AF.GetHighByte() - (byte + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((byte & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (byte + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= byte - (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid Subtract Carry Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::AND(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::Carry, false);
	SetFlag(Flag::HalfCarry, true);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "AND A";
			(AF.GetHighByte() & AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "AND B";
			(AF.GetHighByte() & BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "AND C";
			(AF.GetHighByte() & BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "AND D";
			(AF.GetHighByte() & DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "AND E";
			(AF.GetHighByte() & DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "AND H";
			(AF.GetHighByte() & HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "AND L";
			(AF.GetHighByte() & HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "AND (HL)";
			(AF.GetHighByte() & memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "AND d8";
			u8 byte = FetchByte();
			(AF.GetHighByte() & byte) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= byte;
			tCycles = 4;
			mCycles = 1;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid AND Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::XOR(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::Carry, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "XOR A";
			(AF.GetHighByte() ^ AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "XOR B";
			(AF.GetHighByte() ^ BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "XOR C";
			(AF.GetHighByte() ^ BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "XOR D";
			(AF.GetHighByte() ^ DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "XOR E";
			(AF.GetHighByte() ^ DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "XOR H";
			(AF.GetHighByte() ^ HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "XOR L";
			(AF.GetHighByte() ^ HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "XOR (HL)";
			(AF.GetHighByte() ^ memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "XOR d8";
			u8 byte = FetchByte();
			(AF.GetHighByte() ^ byte) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= byte;
			tCycles = 4;
			mCycles = 1;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid XOR Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::OR(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::Carry, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "OR A";
			(AF.GetHighByte() | AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "OR B";
			(AF.GetHighByte() | BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "OR C";
			(AF.GetHighByte() | BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "OR D";
			(AF.GetHighByte() | DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "OR E";
			(AF.GetHighByte() | DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "OR H";
			(AF.GetHighByte() | HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "OR L";
			(AF.GetHighByte() | HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "OR (HL)";
			(AF.GetHighByte() | memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "OR d8";
			u8 byte = FetchByte();
			(AF.GetHighByte() | byte) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= byte;
			tCycles = 4;
			mCycles = 1;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid OR Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::CP(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, true);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "CP A";
			((AF.GetHighByte() - AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (AF.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < AF.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "CP B";
			((AF.GetHighByte() - BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "CP C";
			((AF.GetHighByte() - BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "CP D";
			((AF.GetHighByte() - DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "CP E";
			((AF.GetHighByte() - DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "CP H";
			((AF.GetHighByte() - HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "CP L";
			((AF.GetHighByte() - HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "CP (HL)";
			((AF.GetHighByte() - memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (memory->Read(HL.GetRegister()) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < memory->Read(HL.GetRegister())) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
			currentInstruction.mnemonic = "CP d8";
			u8 byte = FetchByte();
			((AF.GetHighByte() - byte) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (byte & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < byte) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 8;
			mCycles = 2;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid CP Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::CALL(Condition condition)
{
	u16 address = FetchWord();
	switch (condition)
	{
		case Condition::None:
			currentInstruction.mnemonic = "CALL a16";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = address;
			tCycles = 24;
			mCycles = 6;
			break;
		case Condition::Zero:
			currentInstruction.mnemonic = "CALL Z a16";
			if (zero)
			{
				memory->Write(--SP, PC >> 8);
				memory->Write(--SP, PC & 0xFF);
				PC = address;
				tCycles = 24;
				mCycles = 6;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::NotZero:
			currentInstruction.mnemonic = "CALL NZ a16";
			if (!zero)
			{
				memory->Write(--SP, PC >> 8);
				memory->Write(--SP, PC & 0xFF);
				PC = address;
				tCycles = 24;
				mCycles = 6;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::Carry:
			currentInstruction.mnemonic = "CALL C a16";
			if (carry)
			{
				memory->Write(--SP, PC >> 8);
				memory->Write(--SP, PC & 0xFF);
				PC = address;
				tCycles = 24;
				mCycles = 6;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		case Condition::NotCarry:
			currentInstruction.mnemonic = "CALL NC a16";
			if (!carry)
			{
				memory->Write(--SP, PC >> 8);
				memory->Write(--SP, PC & 0xFF);
				PC = address;
				tCycles = 24;
				mCycles = 6;
			}
			else
			{
				tCycles = 12;
				mCycles = 3;
			}
			break;
		default:
			std::cout << "Unsupported or Invalid CALL Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::POP(RegisterTarget reg)
{
	switch (reg)
	{
		case RegisterTarget::BC:
			currentInstruction.mnemonic = "POP BC";
			BC.SetLowByte(memory->Read(SP++));
			BC.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::DE:
			currentInstruction.mnemonic = "POP DE";
			DE.SetLowByte(memory->Read(SP++));
			DE.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::HL:
			currentInstruction.mnemonic = "POP HL";
			HL.SetLowByte(memory->Read(SP++));
			HL.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::AF:
			currentInstruction.mnemonic = "POP AF";
			AF.SetLowByte(memory->Read(SP++));
			AF.SetHighByte(memory->Read(SP++));
			break;
		default:
			std::cout << "Unsupported or Invalid POP Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
	tCycles = 12;
	mCycles = 3;
}

void CPU::PUSH(RegisterTarget reg)
{
	switch (reg)
	{
		case RegisterTarget::BC:
			currentInstruction.mnemonic = "PUSH BC";
			memory->Write(--SP, BC.GetHighByte());
			memory->Write(--SP, BC.GetLowByte());
			break;
		case RegisterTarget::DE:
			currentInstruction.mnemonic = "PUSH DE";
			memory->Write(--SP, DE.GetHighByte());
			memory->Write(--SP, DE.GetLowByte());
			break;
		case RegisterTarget::HL:
			currentInstruction.mnemonic = "PUSH HL";
			memory->Write(--SP, HL.GetHighByte());
			memory->Write(--SP, HL.GetLowByte());
			break;
		case RegisterTarget::AF:
			currentInstruction.mnemonic = "PUSH AF";
			memory->Write(--SP, AF.GetHighByte());
			memory->Write(--SP, AF.GetLowByte());
			break;
		default:
			std::cout << "Unsupported or Invalid PUSH Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
	tCycles = 16;
	mCycles = 4;
}

void CPU::RET(Condition condition)
{
	switch (condition)
	{
		case Condition::None:
		{
			currentInstruction.mnemonic = "RET";
			u8 low = memory->Read(SP++);
			u8 high = memory->Read(SP++);
			PC = (high << 8) | low;
			tCycles = 16;
			mCycles = 4;
			break;
		}
		case Condition::Zero:
			currentInstruction.mnemonic = "RET Z";
			if (zero)
			{
				u8 low = memory->Read(SP++);
				u8 high = memory->Read(SP++);
				PC = (high << 8) | low;
				tCycles = 20;
				mCycles = 5;
			}
			else
			{

				tCycles = 8;
				mCycles = 2;
				break;
			}
			break;
		case Condition::NotZero:
			currentInstruction.mnemonic = "RET NZ";
			if (!zero)
			{
				u8 low = memory->Read(SP++);
				u8 high = memory->Read(SP++);
				PC = (high << 8) | low;
				tCycles = 20;
				mCycles = 5;
			}
			else
			{

				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::Carry:
			currentInstruction.mnemonic = "RET C";
			if (carry)
			{
				u8 low = memory->Read(SP++);
				u8 high = memory->Read(SP++);
				PC = (high << 8) | low;
				tCycles = 20;
				mCycles = 5;
			}
			else
			{

				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::NotCarry:
			currentInstruction.mnemonic = "RET NC";
			if (!carry)
			{
				u8 low = memory->Read(SP++);
				u8 high = memory->Read(SP++);
				PC = (high << 8) | low;
				tCycles = 20;
				mCycles = 5;
			}
			else
			{

				tCycles = 8;
				mCycles = 2;
			}
			break;
		case Condition::Interrupt:
		{
			currentInstruction.mnemonic = "RETI";
			u8 low = memory->Read(SP++);
			u8 high = memory->Read(SP++);
			PC = (high << 8) | low;
			tCycles = 16;
			mCycles = 4;
			break;
		}
		default:
			std::cout << "Unsupported or Invalid RET instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RST(int num)
{
	switch (num)
	{
		case 0:
			currentInstruction.mnemonic = "RST 0";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x00;
			tCycles = 16;
			mCycles = 4;
			break;
		case 1:
			currentInstruction.mnemonic = "RST 1";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x08;
			tCycles = 16;
			mCycles = 4;
			break;
		case 2:
			currentInstruction.mnemonic = "RST 2";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x10;
			tCycles = 16;
			mCycles = 4;
			break;
		case 3:
			currentInstruction.mnemonic = "RST 3";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x18;
			tCycles = 16;
			mCycles = 4;
			break;
		case 4:
			currentInstruction.mnemonic = "RST 4";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x20;
			tCycles = 16;
			mCycles = 4;
			break;
		case 5:
			currentInstruction.mnemonic = "RST 5";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x28;
			tCycles = 16;
			mCycles = 4;
			break;
		case 6:
			currentInstruction.mnemonic = "RST 6";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x30;
			tCycles = 16;
			mCycles = 4;
			break;
		case 7:
			currentInstruction.mnemonic = "RST 7";
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = 0x38;
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RST instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SCF()
{
	currentInstruction.mnemonic = "SCF";
	SetFlag(Flag::HalfCarry, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::Carry, true);
	tCycles = 4;
	mCycles = 1;
}

void CPU::RLCA()
{
	currentInstruction.mnemonic = "RLCA";
	SetFlag(Flag::Zero, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
	AF.GetHighByte() <<= 1 | (u8)GetCarryFlag();
	tCycles = 4;
	mCycles = 1;
}

void CPU::RLA()
{
	currentInstruction.mnemonic = "RLA";
	bool oldCarry = GetCarryFlag();
	SetFlag(Flag::Zero, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
	AF.GetHighByte() <<= 1 | (u8)oldCarry;
	tCycles = 4;
	mCycles = 1;
}

void CPU::RRCA()
{
	currentInstruction.mnemonic = "RRCA";
	SetFlag(Flag::Zero, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
	AF.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
	tCycles = 4;
	mCycles = 1;
}

void CPU::RRA()
{
	currentInstruction.mnemonic = "RRA";
	bool oldCarry = GetCarryFlag();
	SetFlag(Flag::Zero, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
	(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
	AF.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
	tCycles = 4;
	mCycles = 1;
}

void CPU::CPL()
{
	currentInstruction.mnemonic = "CPL";
	SetFlag(Flag::Subtract, true);
	SetFlag(Flag::HalfCarry, true);
	AF.SetHighByte(~AF.GetHighByte());
	tCycles = 4;
	mCycles = 1;
}

void CPU::CCF()
{
	currentInstruction.mnemonic = "CCF";
	SetFlag(Flag::HalfCarry, false);
	SetFlag(Flag::Subtract, false);
	bool flag = GetCarryFlag();
	flag ? SetFlag(Flag::Carry, false) : SetFlag(Flag::Carry, true);
	tCycles = 4;
	mCycles = 1;
}

void CPU::BIT(RegisterTarget reg, int bit)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, true);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = std::format("BIT {:d} A", bit);
			(AF.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = std::format("BIT {:d} B", bit);
			(BC.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = std::format("BIT {:d} C", bit);
			(BC.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = std::format("BIT {:d} D", bit);
			(DE.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = std::format("BIT {:d} E", bit);
			(DE.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = std::format("BIT {:d} H", bit);
			(HL.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = std::format("BIT {:d} L", bit);
			(HL.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = std::format("BIT {:d} (HL)", bit);
			(memory->Read(HL.GetRegister()) & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid BIT Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RES(RegisterTarget reg, int bit)
{
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = std::format("RES {:d} A", bit);
			AF.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = std::format("RES {:d} B", bit);
			BC.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = std::format("RES {:d} C", bit);
			BC.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = std::format("RES {:d} D", bit);
			DE.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = std::format("RES {:d} E", bit);
			DE.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = std::format("RES {:d} H", bit);
			HL.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = std::format("RES {:d} H", bit);
			HL.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = std::format("RES {:d} (HL)", bit);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister() & ~(1 << bit)));
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RES Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SET(RegisterTarget reg, int bit)
{
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = std::format("SET {:d} A", bit);
			AF.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = std::format("SET {:d} B", bit);
			BC.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = std::format("SET {:d} C", bit);
			BC.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = std::format("SET {:d} D", bit);
			DE.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = std::format("SET {:d} E", bit);
			DE.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = std::format("SET {:d} H", bit);
			HL.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = std::format("SET {:d} L", bit);
			HL.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = std::format("SET {:d} (HL)", bit);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) | (1 << bit));
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid SET Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RLC(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "RLC A";
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "RLC B";
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "RLC C";
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "RLC D";
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "RLC E";
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "RLC H";
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "RLC L";
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "RLC (HL)";
			(memory->Read(HL.GetRegister()) << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) << 1 | (u8)GetCarryFlag());
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RLC Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RL(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	bool oldCarry = GetCarryFlag();
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "RL A";
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "RL B";
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "RL C";
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "RL D";
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "RL E";
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "RL H";
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "RL L";
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "RL (HL)";
			(memory->Read(HL.GetRegister()) << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) << 1 | (u8)oldCarry);
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RL Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RRC(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "RRC A";
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "RRC B";
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "RRC C";
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "RRC D";
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "RRC E";
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "RRC H";
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "RRC L";
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "RRC (HL)";
			(memory->Read(HL.GetRegister()) >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) >> 1 | ((u8)GetCarryFlag() << 7));
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RRC Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::RR(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	bool oldCarry = GetCarryFlag();
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "RR A";
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "RR B";
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "RR C";
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "RR D";
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "RR E";
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "RR H";
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "RR L";
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "RR (HL)";
			(memory->Read(HL.GetRegister()) >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) >> 1 | ((u8)oldCarry << 7));
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid RR Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SLA(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SLA A";
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SLA B";
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SLA C";
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SLA D";
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SLA E";
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SLA H";
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SLA L";
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SLA (HL)";
			(memory->Read(HL.GetRegister()) << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) << 1);
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid SLA Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SRA(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	u8 msb;
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SRA A";
			msb = AF.GetHighByte() & 0x80;
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SRA B";
			msb = BC.GetHighByte() & 0x80;
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SRA C";
			msb = BC.GetLowByte() & 0x80;
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SRA D";
			msb = DE.GetHighByte() & 0x80;
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SRA E";
			msb = DE.GetLowByte() & 0x80;
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SRA H";
			msb = HL.GetHighByte() & 0x80;
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SRA L";
			msb = HL.GetLowByte() & 0x80;
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SRA (HL)";
			msb = memory->Read(HL.GetRegister()) & 0x80;
			(memory->Read(HL.GetRegister()) >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) >> 1 | msb);
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid SRA Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SWAP(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	SetFlag(Flag::Carry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SWAP A";
			((AF.GetHighByte() >> 4) | (AF.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() = (AF.GetHighByte() >> 4) | (AF.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SWAP B";
			((BC.GetHighByte() >> 4) | (BC.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			BC.GetHighByte() = (BC.GetHighByte() >> 4) | (BC.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SWAP C";
			((BC.GetLowByte() >> 4) | (BC.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			BC.GetLowByte() = (BC.GetLowByte() >> 4) | (BC.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SWAP D";
			((DE.GetHighByte() >> 4) | (DE.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			DE.GetHighByte() = (DE.GetHighByte() >> 4) | (DE.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SWAP E";
			((DE.GetLowByte() >> 4) | (DE.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			DE.GetLowByte() = (DE.GetLowByte() >> 4) | (DE.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SWAP H";
			((HL.GetHighByte() >> 4) | (HL.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			HL.GetHighByte() = (HL.GetHighByte() >> 4) | (HL.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SWAP L";
			((HL.GetLowByte() >> 4) | (HL.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			HL.GetLowByte() = (HL.GetLowByte() >> 4) | (HL.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SWAP (HL)";
			((memory->Read(HL.GetRegister()) >> 4) | (memory->Read(HL.GetRegister()) << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			memory->Write(HL.GetRegister(), (memory->Read(HL.GetRegister()) >> 4) | (memory->Read(HL.GetRegister()) << 4));
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid SWAP Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}

void CPU::SRL(RegisterTarget reg)
{
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::HalfCarry, false);
	switch (reg)
	{
		case RegisterTarget::A:
			currentInstruction.mnemonic = "SRL A";
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			currentInstruction.mnemonic = "SRL B";
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			currentInstruction.mnemonic = "SRL C";
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			currentInstruction.mnemonic = "SRL D";
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			currentInstruction.mnemonic = "SRL E";
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			currentInstruction.mnemonic = "SRL H";
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			currentInstruction.mnemonic = "SRL L";
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
			currentInstruction.mnemonic = "SRL (HL)";
			(memory->Read(HL.GetRegister()) >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(memory->Read(HL.GetRegister()) & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			memory->Write(HL.GetRegister(), memory->Read(HL.GetRegister()) >> 1);
			tCycles = 16;
			mCycles = 4;
			break;
		default:
			std::cout << "Unsupported or Invalid SRL Instruction\n";
			std::exit(EXIT_FAILURE);
			break;
	}
}
