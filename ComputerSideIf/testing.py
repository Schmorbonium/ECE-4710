# pip install pyserial
import serial
import time



def getHeader(addr:list[int],ttl:int,data_len:int,id:int) -> int:
    hdr:int = 0

    attn:int = 0
    for i in addr:
        attn |= 1 << i
    hdr |= (attn & 0xF) << 12

    hdr |= (ttl & 0x3) << 8

    hdr |= (data_len & 0x7) << 5 

    hdr |= (id & 0xF)

    return hdr

def toggleBMsg(addr:list[int]) -> list[int]:
    hdr:int = getHeader(addr,3,0,2)
    return [hdr]

def toggleOMsg(addr:list[int]) -> list[int]:
    hdr:int = getHeader(addr,3,0,3)
    return [hdr]

def toggleRMsg(addr:list[int]) -> list[int]:
    hdr:int = getHeader(addr,3,0,1)
    return [hdr]

def toggleGMsg(addr:list[int]) -> list[int]:
    hdr:int = getHeader(addr,3,0,4)
    return [hdr]


with serial.Serial('', 115200, timeout=1) as ser:
    while True:
        msg:list[int] = toggleBMsg([1])
        ser.write(msg)
        time.sleep(1)
        msg:list[int] = toggleGMsg([2])
        ser.write(msg)
        time.sleep(1)
        msg:list[int] = toggleOMsg([1,2])
        ser.write(msg)
        time.sleep(1)
        msg:list[int] = toggleRMsg([2])
        ser.write(msg)
        time.sleep(1)



