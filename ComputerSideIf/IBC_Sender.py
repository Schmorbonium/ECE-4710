# pip install pyserial
import serial
import serial.tools.list_ports
import time

def findActiveSerialPort():
    available_ports = list(serial.tools.list_ports.comports())
    
    for port_info in available_ports:
        try:
            # Try to open the port and immediately close it to check if it's available
            port = serial.Serial(port=port_info.device, timeout=1)
            port.close()
            return port_info.device
        except (serial.SerialException, OSError):
            pass
    
    return None  # No active serial port found


def getHeader(addr:list[int],ttl:int,data_len:int,id:int) -> list[int]:
    hdr1:int = 0

    attn:int = 0
    for i in addr:
        attn |= 1 << i

    hdr1 |= (attn & 0xF) << 4
    hdr1 |= (ttl & 0x3)

    hdr2:int = 0
    hdr2 |= (data_len & 0x7) << 5 
    hdr2 |= (id & 0x1F)

    return [hdr1,hdr2,0x0A]

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
    raw = bytes(msg)
    ser.write(raw)
    print(F"sending:0x{raw.hex()}")


activePort = findActiveSerialPort()
with serial.Serial(activePort, 115200, timeout=1) as ser:
    while True:
        msg:list[int] = toggleBMsg([0,1,2,3])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleGMsg([0,1])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleOMsg([0,1])
        sendMsg(msg,ser)
        time.sleep(1)
        msg:list[int] = toggleRMsg([0,1])
        sendMsg(msg,ser)
        time.sleep(1)


