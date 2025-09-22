#include "Memory.h"
#include "Cartridge.h"

#include <fstream>

Memory::Memory()
    : bootROM(0x100, 0), VRAM(0x2000, 0), WRAM0(0x1000, 0), WRAM1(0x1000, 0), ERAM(0x2000, 0),
    OAM(0xA0, 0), ioRegisters(0x80, 0), HRAM(0x80, 0), interruptRegister(0), bootRomEnabled(true)
{
}

Memory::~Memory()
{
}

u8 Memory::Read(u16 address)
{
    if (address < 0x4000)
    {
        if (bootRomEnabled && address < 0xFF)
        {
            return bootROM[address];
        }
        else
        {
            // TODO Cartridge memory reading ROM Bank 0
        }
    }
    else if (address >= 0x4000 && address < 0x8000)
    {
        // TODO Cartridge memory reading ROM Bank N (Switchable with some cart types)
    }
    else if (address >= 0x8000 && address < 0xA000)
    {
        return VRAM[address - 0x8000];
    }
    else if (address >= 0xA000 && address < 0xC000)
    {
        // TODO Cartridge RAM reading (Switchable with some cart types)
    }
    else if (address >= 0xC000 && address < 0xD000)
    {
        return WRAM0[address - 0xA000];
    }
    else if (address >= 0xD000 && address < 0xE000)
    {
        // TODO CGB Mode switchable bank
        return WRAM1[address - 0xB000];
    }
    else if (address >= 0xE000 && address < 0xFE00)
    {
        // TODO possible SRAM interference in flash carts
        address -= 0x1E00;
        if (address >= 0xC000 && address < 0xD000)
        {
            return WRAM0[address - 0xA000];
        }
        if (address >= 0xD000 && address < 0xEE00)
        {
            return WRAM1[address - 0xAE00];
        }
    }
    else if (address >= 0xFE00 && address < 0xFEA0)
    {
        // TODO add in OAM Block when PPU work starts
        return OAM[address - 0xFF00];
    }
    else if (address >= 0xFEA0 && address < 0xFF00)
    {
        // TODO return values depend on GameBoy type
        // DMG, MGB, SGB and SGB2 return 0xFF if OAM blocked causing OAM Corruption otherwise returns 0x00;
        // CBG rev 0-D unique RAM area
        // CGB rev E, AGB, AGS and GBP return high nibble of lower address byte twice
        return 0xFF;
    }
    else if (address >= 0xFF00 && address < 0xFF80)
    {
        // $FF00 Joypad Input
        // $FF01 - $FF02 Serial Transfer
        // $FF04 - $FF07 Timer and divider
        // $FF0F Interrupts ( BIT 0 - VBLANK ) ( BIT 1 - LCD ) ( BIT 2 - Timer ) ( BIT 3 - Serial ) ( BIT 4 - Joypad )
        // $FF10 - $FF26 Audio
        // $FF30 - $FF3F Wave pattern
        // $FF40 - $FF4B LCD Control, Status, Position, Scrolling and Palletes
        // $FF4C - $FF4D KEY0 and KEY1 (CGB)
        // $FF4F VRAM Bank Selected (CBG)
        // $FF50 Boot ROM mapping control
        // $FF51 - $FF55 VRAM DMA (CGB)
        // $FF56 IR port (CGB)
        // $FF68 - $FF6B BG / OBJ Palettes (CGB)
        // $FF6C Object Priority mode (CGB)
        // $FF70 WRAM Bank Select (CGB)
        return ioRegisters[address - 0xFEA0];
    }
    else if (address >= 0xFF80 && address < 0xFFFF)
    {
        return HRAM[address - 0xFF00];
    }
    else if (address == 0xFFFF)
    {
        // BIT 0 - VBLANK
        // BIT 1 - LCD
        // BIT 2 - Timer
        // BIT 3 - Serial
        // BIT 4 - Joypad
        return interruptRegister;
    }
    return 0xFF;
}

void Memory::Write(u16 address, const u8 value)
{
    if (address < 0x4000)
    {
        // TODO Cartidge stuff here (MBC switching stuff??)
    }
    else if (address >= 0x4000 && address < 0x8000)
    {
        // TODO Cartidge stuff here (MBC switching stuff??)
    }
    else if (address >= 0x8000 && address < 0xA000)
    {
        VRAM[address - 0x8000] = value;
    }
    else if (address >= 0xA000 && address < 0xC000)
    {
        // TODO Cartridge RAM writing
    }
    else if (address >= 0xC000 && address < 0xD000)
    {
        WRAM0[address - 0xA000] = value;
    }
    else if (address >= 0xD000 && address < 0xE000)
    {
        // TODO CGB Mode switchable bank
        WRAM1[address - 0xB000] = value;
    }
    else if (address >= 0xE000 && address < 0xFE00)
    {
        // TODO possible SRAM interference in flash carts
        address -= 0x1E00;
        if (address >= 0xC000 && address < 0xD000)
        {
            WRAM0[address - 0xA000] = value;
        }
        if (address >= 0xD000 && address < 0xEE00)
        {
            WRAM1[address - 0xAE00] = value;
        }
    }
    else if (address >= 0xFE00 && address < 0xFEA0)
    {
        // TODO add in OAM Block when PPU work starts
        OAM[address - 0xFF00] = value;
    }
    else if (address >= 0xFEA0 && address < 0xFF00)
    {
        // TODO return values depend on GameBoy type
        // DMG, MGB, SGB and SGB2 return 0xFF if OAM blocked causing OAM Corruption otherwise returns 0x00;
        // CBG rev 0-D unique RAM area
        // CGB rev E, AGB, AGS and GBP return high nibble of lower address byte twice
    }
    else if (address >= 0xFF00 && address < 0xFF80)
    {
        // $FF00 Joypad Input
        // $FF01 - $FF02 Serial Transfer
        // $FF04 - $FF07 Timer and divider
        // $FF0F Interrupts ( BIT 0 - VBLANK ) ( BIT 1 - LCD ) ( BIT 2 - Timer ) ( BIT 3 - Serial ) ( BIT 4 - Joypad )
        // $FF10 - $FF26 Audio
        // $FF30 - $FF3F Wave pattern
        // $FF40 - $FF4B LCD Control, Status, Position, Scrolling and Palletes
        // $FF4C - $FF4D KEY0 and KEY1 (CGB)
        // $FF4F VRAM Bank Selected (CBG)
        // $FF50 Boot ROM mapping control
        // $FF51 - $FF55 VRAM DMA (CGB)
        // $FF56 IR port (CGB)
        // $FF68 - $FF6B BG / OBJ Palettes (CGB)
        // $FF6C Object Priority mode (CGB)
        // $FF70 WRAM Bank Select (CGB)
        ioRegisters[address - 0xFEA0] = value;
    }
    else if (address >= 0xFF80 && address < 0xFFFF)
    {
        HRAM[address - 0xFF00] = value;
    }
    else if (address == 0xFFFF)
    {
        // BIT 0 - VBLANK
        // BIT 1 - LCD
        // BIT 2 - Timer
        // BIT 3 - Serial
        // BIT 4 - Joypad
        interruptRegister = value;
    }
}

bool Memory::LoadBootROM()
{
    std::ifstream file(bootROMPath, std::ios::binary | std::ios::ate);
    if (!file) return false;

    size_t size = file.tellg();
    bootROM.assign(size, 0);
    file.seekg(0);

    file.read(reinterpret_cast<char*>(bootROM.data()), size);

    return true;
}

void Memory::SetBootROMPath(const std::string& path)
{
    bootROMPath = path;
}

void Memory::Reset()
{
    VRAM.clear();
    ERAM.clear();
    WRAM0.clear();
    WRAM1.clear();
    OAM.clear();
    ioRegisters.clear();
    HRAM.clear();
    interruptRegister = 0;
}
