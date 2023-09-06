// # pip install pyserial
// import serial
// import serial.tools.list_ports
// import time

// def findActiveSerialPort():
//     available_ports = list(serial.tools.list_ports.comports())
    
//     for port_info in available_ports:
//         try:
//             # Try to open the port and immediately close it to check if it's available
//             port = serial.Serial(port=port_info.device, timeout=1)
//             port.close()
//             return port_info.device
//         except (serial.SerialException, OSError):
//             pass
    
//     return None  # No active serial port found


enum ifCm{
   rstPkt   = 0x1,
   setMem   = 0x2,
   getMem   = 0x3,
   dbSetReg = 0x11,
   dbGetReg = 0x12,
   dbFlags  = 0x13,
   dbSetPC  = 0x14,
   dbGetPC  = 0x15,
   dbPause  = 0x16,
   dbStep   = 0x17,
   dbGetBP  = 0x18,
   dbTogBP  = 0x19,
   dbTogDB  = 0x1A
}






class PacketField:
    # Supported Types: int, bool List[PacketField]
    # Size in Bytes!
    def __init__(self,data,size:int) -> None:
        self.size = size
        self.data = data

    def encode(self) -> list[int]:
        values = []
        for i in range(0,self.size):
            values[i] = 0

        if(isinstance(self.data,int)) :
            for i in range(self.size):
                values[i] = ((self.data >> 8*i) & 0xff)
        elif(isinstance(self.data,bool)) :
            if(self.data):
                values[0] = 1
        elif(isinstance(self.data, list)):
            values = []
            for f in self.data:
                if(isinstance(f,PacketField)):
                    values.append(f.encode())
                else:
                    TypeError(f'Encode on PacketField does not support lists of ${type(f)}')
        else:
            pass
        return values


class BitFlags(PacketField):
    def __init__(self,BitFields:list[str]) -> None:
        super().__init__(None, 1)
        self.data = {}
        self.orderKey = {}
        cnt = 0
        for i in BitFields:
            self.data[i] = False
            self.orderKey[cnt] = i
            cnt+=1

    def set(self,field):
        self.data[field] = True

    def reset(self,field):
        self.data[field] = False

    def encode(self) -> list[int]:
        flags:int = 0
        for key in self.orderKey:
            field = self.orderKey[key]
            if(self.data[field]):
                flags|= 1<<(8-key)
        return flags
                


class IfPacketHeader(PacketField):
    def __init__(self,cmd:int,dataLen:int) -> None:
        super().__init__(None,4)
        self.fields:list[PacketField] = []
        self.cmd = PacketField(cmd,1)
        self.dataLen = PacketField(dataLen,1)
        self.noop = PacketField(False,1)
        self.flags = BitFlags(['ret','retReq','boop'])

    def encode(self) -> list[int]:
        hdr = PacketField([self.cmd,self.dataLen,self.noop,self.flags],4)
        return hdr.encode()
    
class IfPacket:
    def __init__(self,header:PacketField,body:PacketField) -> None:
        self.header = header
        self.body = body
        pass


class IfPacketSetData(IfPacket):
    def __init__(self,addr,val) -> None:
        header = IfPacketHeader(ifCmd.setMem,8)
        data = PacketField([PacketField(addr,4),PacketField(val,4)],8)
        super().__init__(header,data)
        pass
    pass
    
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



