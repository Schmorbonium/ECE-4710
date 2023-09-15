#include "comIfPkts.hpp"
#include "charBuffer.hpp"

// -------------------PacketField -----------------------------
PacketField::PacketField(uint8_t data) : data(data) {}
PacketField::PacketField(CharBuffer *que) { parseFromQue(que); }
void PacketField::parseFromQue(CharBuffer *que) { data = que->pop(); }
void PacketField::appendToQue(CharBuffer *que) { que->append(data); }
void PacketField::setByte(uint8_t flags) { data = flags; }
uint8_t PacketField::getByte() { return data; }

// -------------------FlagField -----------------------------
FlagField::FlagField(uint8_t flags) : PacketField(data) {}
FlagField::FlagField(CharBuffer *que) { parseFromQue(que); }
void FlagField::setFlag(uint8_t index) { data |= (1 << index); }
void FlagField::resetFlag(uint8_t index) { data &= ~(1 << index); }
bool FlagField::getFlag(uint8_t index) { return data & (1 << index); }

// -------------------UnusedField -----------------------------
UnusedField::UnusedField(CharBuffer *que) { parseFromQue(que); }
void UnusedField::parseFromQue(CharBuffer *que) { que->pop(); }
void UnusedField::appendToQue(CharBuffer *que) { que->append(0); }

Header::Header(cmdID cmd, uint8_t dataSize, uint8_t flags) : cmd(PacketField(cmd)), dataLen(PacketField(cmd)), flags(FlagField(flags)) {}
Header::Header(CharBuffer *que) : Header() { parseFromQue(que); }

bool Header::isAResponse()
{
    return this->flags.getFlag(0);
}

bool Header::responseRequested()
{
    return this->flags.getFlag(1);
}

void Header::setIsAResponse(bool value)
{
    this->flags.setFlag(0);
}

void Header::setResponseRequested(bool value)
{
    this->flags.setFlag(1);
}

void Header::parseFromQue(CharBuffer *que)
{
    cmd = PacketField(que);
    dataLen = PacketField(que);
    unused = UnusedField(que);
    flags = FlagField(que);
}

void Header::appendToQue(CharBuffer *que)
{
    cmd.appendToQue(que);
    dataLen.appendToQue(que);
    unused.appendToQue(que);
    flags.appendToQue(que);
}