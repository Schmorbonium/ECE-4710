# pip install pyserial
import serial
import time



def getHeader(addr:list[int],ttl:int,data_len:int,id:int) -> list[int]:
    hdr1:int = 0

    attn:int = 0
    for i in addr:
        attn |= 1 << i

    hdr1 |= (attn & 0xF) << 4
    hdr1 |= (ttl & 0x3)

    hdr2:int = 0
    hdr2 |= (data_len & 0x7) << 5 
    hdr2 |= (id & 0xF)

    return [hdr1,hdr2]

def toggleBMsg(addr:list[int]) -> list[int]:
    hdr:list[int] = getHeader(addr,3,0,2)
    return hdr

def toggleOMsg(addr:list[int]) -> list[int]:
    hdr:list[int] = getHeader(addr,3,0,3)
    return hdr

def toggleRMsg(addr:list[int]) -> list[int]:
    hdr:list[int] = getHeader(addr,3,0,1)
    return hdr

def toggleGMsg(addr:list[int]) -> list[int]:
    hdr:list[int] = getHeader(addr,3,0,4)
    return hdr

def sendMsg(msg:list[int],ser:serial.SerialBase):
    for i in msg :
        ser.write(i & 0xff)

with serial.Serial('', 115200, timeout=1) as ser:
    while True:
        msg:list[int] = toggleBMsg([1])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleGMsg([2])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleOMsg([1,2])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleRMsg([2])
        sendMsg(msg,ser)
        time.sleep(1)



