#include "CPU.h"
#include "Memory.h"

void CPU::Step()
{

}

int CPU::Decode()
{
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
			}
			break;
		case RegisterTarget::MemC:
			switch (from)
			{
				case RegisterTarget::A:
					memory->Write(0xFF00 + BC.GetLowByte(), AF.GetHighByte());
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
			}
			break;
		default:

	}
}
