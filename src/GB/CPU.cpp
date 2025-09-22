#include "CPU.h"
#include "Memory.h"
#include <iostream>

CPU::CPU(Memory* memory)
	: memory(memory), PC(0x00), SP(0x00), IME(false), zero(false), subtract(false), halfCarry(false), carry(false),
	AF(0x0), BC(0x0), DE(0x0), HL(0x0), OP(0x0)
{
}

CPU::~CPU()
{
}

void CPU::Step()
{

}

void CPU::Decode()
{
	OP = FetchByte();
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
		DEC(RegisterTarget::C);
		break;
	case 0x06:
		LD(RegisterTarget::B, RegisterTarget::Byte);
		break;
	case 0x07:
		
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

		break;
	case 0x10:
		
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

		break;
	case 0xC8:

		break;
	case 0xC9:

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

		break;
	case 0xD0:

		break;
	case 0xD1:
		POP(RegisterTarget::DE);
		break;
	case 0xD2:
		JP(Condition::NotCarry);
		break;
	case 0xD3:

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

		break;
	case 0xD8:

		break;
	case 0xD9:

		break;
	case 0xDA:
		JP(Condition::Carry);
		break;
	case 0xDB:

		break;
	case 0xDC:
		CALL(Condition::Carry);
		break;
	case 0xDD:

		break;
	case 0xDE:
		SBC(RegisterTarget::Byte);
		break;
	case 0xDF:

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

		break;
	case 0xE4:

		break;
	case 0xE5:
		PUSH(RegisterTarget::HL);
		break;
	case 0xE6:
		AND(RegisterTarget::Byte);
		break;
	case 0xE7:

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

		break;
	case 0xEC:

		break;
	case 0xED:

		break;
	case 0xEE:
		XOR(RegisterTarget::Byte);
		break;
	case 0xEF:

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

		break;
	case 0xF4:

		break;
	case 0xF5:
		PUSH(RegisterTarget::AF);
		break;
	case 0xF6:
		OR(RegisterTarget::Byte);
		break;
	case 0xF7:

		break;
	case 0xF8:
		// LD(RegisterTarget::HL, )
		break;
	case 0xF9:
		LD(RegisterTarget::SP, RegisterTarget::HL);
		break;
	case 0xFA:
		LD(RegisterTarget::A, RegisterTarget::Word);
		break;
	case 0xFB:

		break;
	case 0xFC:

		break;
	case 0xFD:

		break;
	case 0xFE:
		CP(RegisterTarget::Byte);
		break;
	case 0xFF:

		break;
	default:
		std::cout << std::hex << "Unsupported instruction " << OP << " at " << PC << '\n';
		std::exit(EXIT_FAILURE);
		break;
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
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					AF.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					AF.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					AF.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					AF.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					AF.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					AF.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					AF.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemBC:
					AF.SetHighByte(memory->Read(BC.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemDE:
					AF.SetHighByte(memory->Read(DE.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHLDec:
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					HL--;
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHLInc:
					AF.SetHighByte(memory->Read(HL.GetRegister()));
					HL++;
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::OffsetC:
					AF.SetHighByte(memory->Read(0xFF00 + BC.GetLowByte()));
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::Offset:
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
					BC.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					BC.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					BC.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					BC.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					BC.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					BC.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					BC.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					BC.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					BC.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					BC.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					BC.SetLowByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					BC.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					BC.SetLowByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					BC.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					DE.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					DE.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					DE.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					DE.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					DE.SetHighByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					DE.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					DE.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					DE.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					DE.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					DE.SetLowByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					DE.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					DE.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					DE.SetLowByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					DE.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					HL.SetHighByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					HL.SetHighByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					HL.SetHighByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					HL.SetHighByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					HL.SetHighByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					HL.SetHighByte(HL.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					HL.SetHighByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					HL.SetLowByte(AF.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					HL.SetLowByte(BC.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					HL.SetLowByte(BC.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					HL.SetLowByte(DE.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					HL.SetLowByte(DE.GetLowByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					HL.SetLowByte(HL.GetHighByte());
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::Byte:
					HL.SetLowByte(FetchByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::MemHL:
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
					SP = FetchWord();
					tCycles = 12;
					mCycles = 3;
					break;
				case RegisterTarget::HL:
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
					memory->Write(FetchWord(), AF.GetHighByte());
					tCycles = 16;
					mCycles = 4;
					break;
				case RegisterTarget::SP:
				{
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
					memory->Write(HL.GetRegister(), AF.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::B:
					memory->Write(HL.GetRegister(), BC.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::C:
					memory->Write(HL.GetRegister(), BC.GetLowByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::D:
					memory->Write(HL.GetRegister(), DE.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::E:
					memory->Write(HL.GetRegister(), DE.GetLowByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::H:
					memory->Write(HL.GetRegister(), HL.GetHighByte());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::L:
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
			SetFlag(Flag::Subtract, false);
			((AF.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			AF.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			SetFlag(Flag::Subtract, false);
			((BC.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			SetFlag(Flag::Subtract, false);
			((BC.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::BC:
			BC++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			SetFlag(Flag::Subtract, false);
			((DE.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((DE.GetHighByte() & 0x0F) + 1 & 0x0F) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			SetFlag(Flag::Subtract, false);
			((DE.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::DE:
			DE++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			SetFlag(Flag::Subtract, false);
			((HL.GetHighByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetHighByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetHighByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			SetFlag(Flag::Subtract, false);
			((HL.GetLowByte() + 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetLowByte() & 0x0F) + 1 > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetLowByte()++;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::HL:
			HL++;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
		case RegisterTarget::A:
			SetFlag(Flag::Subtract, true);
			((AF.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			AF.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			SetFlag(Flag::Subtract, true);
			((BC.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			SetFlag(Flag::Subtract, true);
			((BC.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((BC.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			BC.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::BC:
			BC--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			SetFlag(Flag::Subtract, true);
			((DE.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			SetFlag(Flag::Subtract, true);
			((DE.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((DE.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			DE.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::DE:
			DE--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			SetFlag(Flag::Subtract, true);
			((HL.GetHighByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetHighByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetHighByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			SetFlag(Flag::Subtract, true);
			((HL.GetLowByte() - 1) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((HL.GetLowByte() & 0x0F) == 0x0) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			HL.GetLowByte()--;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::HL:
			HL--;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			PC = address;
			tCycles = 16;
			mCycles = 4;
			break;
		case Condition::Zero:
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
	u8 offset = FetchByte();
	switch (condition)
	{
		case Condition::None:
		{
			PC += offset;
			tCycles = 12;
			mCycles = 3;
			break;
		}
		case Condition::Zero:
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
		case Condition::Carry:
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
		case Condition::NotCarry:
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
					((AF.GetHighByte() + AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (AF.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + AF.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += AF.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::B:
					((AF.GetHighByte() + BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (BC.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + BC.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += BC.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::C:
					((AF.GetHighByte() + BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (BC.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + BC.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += BC.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::D:
					((AF.GetHighByte() + DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (DE.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + DE.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += DE.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::E:
					((AF.GetHighByte() + DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (DE.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + DE.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += DE.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::H:
					((AF.GetHighByte() + HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (HL.GetHighByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + HL.GetHighByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += HL.GetHighByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::L:
					((AF.GetHighByte() + HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (HL.GetLowByte() & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + HL.GetLowByte()) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += HL.GetLowByte();
					tCycles = 4;
					mCycles = 1;
					break;
				case RegisterTarget::MemHL:
					((AF.GetHighByte() + memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
					(((AF.GetHighByte() & 0x0F) + (memory->Read(HL.GetRegister()) & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((AF.GetHighByte() + memory->Read(HL.GetRegister())) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					AF.GetHighByte() += memory->Read(HL.GetRegister());
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::Byte:
				{
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
					(((HL.GetRegister() & 0x0FFF) + (BC.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + BC.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += BC.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::DE:
					(((HL.GetRegister() & 0x0FFF) + (DE.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + DE.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += DE.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::HL:
					(((HL.GetRegister() & 0x0FFF) + (HL.GetRegister() & 0x0FFF)) > 0x0FFF) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((HL.GetRegister() + HL.GetRegister()) > 0xFFFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					HL.GetRegister() += HL.GetRegister();
					tCycles = 8;
					mCycles = 2;
					break;
				case RegisterTarget::SP:
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
					s8 offset = FetchByte();
					SetFlag(Flag::Zero, false);
					((SP & 0x0F) + (offset & 0x0F) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
					((SP & 0xFF) + (offset & 0xFF) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
					SP += offset;
					tCycles = 16;
					mCycles = 4;
				}
				default:
					std::cout << "Unsupported or Invalid Add Instruction\n";
					std::exit(EXIT_FAILURE);
					break;
			}
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
			((AF.GetHighByte() + AF.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (AF.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + AF.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += AF.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			((AF.GetHighByte() + BC.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (BC.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + BC.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += BC.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			((AF.GetHighByte() + BC.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (BC.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + BC.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += BC.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			((AF.GetHighByte() + DE.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (DE.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + DE.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			((AF.GetHighByte() + DE.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (DE.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + DE.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			((AF.GetHighByte() + HL.GetHighByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (HL.GetHighByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + HL.GetHighByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += HL.GetHighByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			((AF.GetHighByte() + HL.GetLowByte() + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (HL.GetLowByte() & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + HL.GetLowByte() + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += HL.GetLowByte() + (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			((AF.GetHighByte() + memory->Read(HL.GetRegister()) + (u8)temp) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(((AF.GetHighByte() & 0x0F) + (memory->Read(HL.GetRegister()) & 0x0F) + (u8)temp) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			((AF.GetHighByte() + memory->Read(HL.GetRegister()) + (u8)temp) > 0xFF) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += memory->Read(HL.GetRegister()) + (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
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
			((AF.GetHighByte() - AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (AF.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < AF.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			((AF.GetHighByte() - BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			((AF.GetHighByte() - BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			((AF.GetHighByte() - DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() += DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			((AF.GetHighByte() - DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			((AF.GetHighByte() - HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			((AF.GetHighByte() - HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			((AF.GetHighByte() - memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (memory->Read(HL.GetRegister()) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < memory->Read(HL.GetRegister())) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= memory->Read(HL.GetRegister());
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
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
			((AF.GetHighByte() - (AF.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((AF.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (AF.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= AF.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			((AF.GetHighByte() - (BC.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((BC.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (BC.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			((AF.GetHighByte() - (BC.GetLowByte() + (u8)temp))) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((BC.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (BC.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			((AF.GetHighByte() - (DE.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((DE.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (DE.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			((AF.GetHighByte() - (DE.GetLowByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((DE.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (DE.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= DE.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			((AF.GetHighByte() - (HL.GetHighByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((HL.GetHighByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (HL.GetHighByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetHighByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			((AF.GetHighByte() - (HL.GetLowByte() + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((HL.GetLowByte() & 0x0F) + (u8)temp)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (HL.GetLowByte() + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= HL.GetLowByte() - (u8)temp;
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			((AF.GetHighByte() - (memory->Read(HL.GetRegister()) + (u8)temp)) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < ((memory->Read(HL.GetRegister() + (u8)temp)) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < (memory->Read(HL.GetRegister()) + (u8)temp)) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= memory->Read(HL.GetRegister()) - (u8)temp;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
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
			(AF.GetHighByte() & AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			(AF.GetHighByte() & BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			(AF.GetHighByte() & BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			(AF.GetHighByte() & DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			(AF.GetHighByte() & DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			(AF.GetHighByte() & HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			(AF.GetHighByte() & HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			(AF.GetHighByte() & memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() &= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
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
			(AF.GetHighByte() ^ AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			(AF.GetHighByte() ^ BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			(AF.GetHighByte() ^ BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			(AF.GetHighByte() ^ DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			(AF.GetHighByte() ^ DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			(AF.GetHighByte() ^ HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			(AF.GetHighByte() ^ HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			(AF.GetHighByte() ^ memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() ^= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
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
			(AF.GetHighByte() | AF.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= AF.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			(AF.GetHighByte() | BC.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= BC.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			(AF.GetHighByte() | BC.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			(AF.GetHighByte() | DE.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= DE.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			(AF.GetHighByte() | DE.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= DE.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			(AF.GetHighByte() | HL.GetHighByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= HL.GetHighByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			(AF.GetHighByte() | HL.GetLowByte()) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= HL.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			(AF.GetHighByte() | memory->Read(HL.GetRegister())) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() |= memory->Read(HL.GetRegister());
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::Byte:
		{
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
			((AF.GetHighByte() - AF.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (AF.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < AF.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::B:
			((AF.GetHighByte() - BC.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::C:
			((AF.GetHighByte() - BC.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (BC.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < BC.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() -= BC.GetLowByte();
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::D:
			((AF.GetHighByte() - DE.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::E:
			((AF.GetHighByte() - DE.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (DE.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < DE.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::H:
			((AF.GetHighByte() - HL.GetHighByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetHighByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetHighByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::L:
			((AF.GetHighByte() - HL.GetLowByte()) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (HL.GetLowByte() & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < HL.GetLowByte()) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 4;
			mCycles = 1;
			break;
		case RegisterTarget::MemHL:
			((AF.GetHighByte() - memory->Read(HL.GetRegister())) == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			((AF.GetHighByte() & 0x0F) < (memory->Read(HL.GetRegister()) & 0x0F)) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
			(AF.GetHighByte() < memory->Read(HL.GetRegister())) ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::Byte:
		{
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
			memory->Write(--SP, PC >> 8);
			memory->Write(--SP, PC & 0xFF);
			PC = address;
			tCycles = 24;
			mCycles = 6;
			break;
		case Condition::Zero:
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
			BC.SetLowByte(memory->Read(SP++));
			BC.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::DE:
			DE.SetLowByte(memory->Read(SP++));
			DE.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::HL:
			HL.SetLowByte(memory->Read(SP++));
			HL.SetHighByte(memory->Read(SP++));
			break;
		case RegisterTarget::AF:
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
			memory->Write(--SP, BC.GetHighByte());
			memory->Write(--SP, BC.GetLowByte());
			break;
		case RegisterTarget::DE:
			memory->Write(--SP, DE.GetHighByte());
			memory->Write(--SP, DE.GetLowByte());
			break;
		case RegisterTarget::HL:
			memory->Write(--SP, HL.GetHighByte());
			memory->Write(--SP, HL.GetLowByte());
			break;
		case RegisterTarget::AF:
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
		u8 low = memory->Read(SP++);
		u8 high = memory->Read(SP++);
		PC = (high << 8) | low;
		tCycles = 16;
		mCycles = 4;
		break;
	case Condition::Zero:
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
		u8 low = memory->Read(SP++);
		u8 high = memory->Read(SP++);
		PC = (high << 8) | low;
		tCycles = 16;
		mCycles = 4;
		break;
	}
}

void CPU::SCF()
{
	SetFlag(Flag::HalfCarry, false);
	SetFlag(Flag::Subtract, false);
	SetFlag(Flag::Carry, true);
	tCycles = 4;
	mCycles = 1;
}

void CPU::RLCA()
{
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
	SetFlag(Flag::Subtract, true);
	SetFlag(Flag::HalfCarry, true);
	AF.SetHighByte(~AF.GetHighByte());
	tCycles = 4;
	mCycles = 1;
}

void CPU::CCF()
{
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
			(AF.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() & (1 << bit)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			AF.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			BC.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			BC.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			DE.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			DE.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			HL.GetHighByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			HL.GetLowByte() &= ~(1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			AF.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			BC.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			BC.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			DE.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			DE.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			HL.GetHighByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			HL.GetLowByte() |= (1 << bit);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1 | (u8)GetCarryFlag();
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1 | (u8)oldCarry;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | ((u8)GetCarryFlag() << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | ((u8)oldCarry << 7);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() << 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() >> 7) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() <<= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			msb = AF.GetHighByte() & 0x80;
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			msb = BC.GetHighByte() & 0x80;
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			msb = BC.GetLowByte() & 0x80;
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			msb = DE.GetHighByte() & 0x80;
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			msb = DE.GetLowByte() & 0x80;
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			msb = HL.GetHighByte() & 0x80;
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			msb = HL.GetLowByte() & 0x80;
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1 | msb;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			((AF.GetHighByte() >> 4) | (AF.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			AF.GetHighByte() = (AF.GetHighByte() >> 4) | (AF.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			((BC.GetHighByte() >> 4) | (BC.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			BC.GetHighByte() = (BC.GetHighByte() >> 4) | (BC.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			((BC.GetLowByte() >> 4) | (BC.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			BC.GetLowByte() = (BC.GetLowByte() >> 4) | (BC.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			((DE.GetHighByte() >> 4) | (DE.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			DE.GetHighByte() = (DE.GetHighByte() >> 4) | (DE.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			((DE.GetLowByte() >> 4) | (DE.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			DE.GetLowByte() = (DE.GetLowByte() >> 4) | (DE.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			((HL.GetHighByte() >> 4) | (HL.GetHighByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			HL.GetHighByte() = (HL.GetHighByte() >> 4) | (HL.GetHighByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			((HL.GetLowByte() >> 4) | (HL.GetLowByte() << 4)) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			HL.GetLowByte() = (HL.GetLowByte() >> 4) | (HL.GetLowByte() << 4);
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
			(AF.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(AF.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			AF.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::B:
			(BC.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::C:
			(BC.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(BC.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			BC.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::D:
			(DE.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::E:
			(DE.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(DE.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			DE.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::H:
			(HL.GetHighByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetHighByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetHighByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::L:
			(HL.GetLowByte() >> 1) == 0 ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
			(HL.GetLowByte() & 0x01) == 1 ? SetFlag(Flag::Carry, true) : SetFlag(Flag::Carry, false);
			HL.GetLowByte() >>= 1;
			tCycles = 8;
			mCycles = 2;
			break;
		case RegisterTarget::MemHL:
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
