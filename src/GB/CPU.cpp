#include "CPU.h"
#include "Memory.h"
#include <iostream>

CPU::CPU(Memory* memory)
	: memory(memory), PC(0x00), SP(0x00), IME(false), zero(false), subtract(false), halfCarry(false), carry(false),
	AF(0x0), BC(0x0), DE(0x0), HL(0x0)
{
}

CPU::~CPU()
{
}

void CPU::Step()
{

}

int CPU::Decode()
{
	return 1;
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
				case RegisterTarget::MemC:
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
		case RegisterTarget::MemC:
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
			((DE.GetHighByte() & 0x0F) + 1 & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
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
			((memory->Read(HL.GetRegister()) & 0x0F) + 1 & 0x0F)) > 0x0F) ? SetFlag(Flag::HalfCarry, true) : SetFlag(Flag::HalfCarry, false);
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

void CPU::ADD(RegisterTarget to, RegisterTarget from)
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
				case RegisterTarget::Byte:
				{
					u8 byte = FetchByte();
					((AF.GetHighByte() + byte == 0) ? SetFlag(Flag::Zero, true) : SetFlag(Flag::Zero, false);
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
