import threading
import time
import socket
import json

CONST_INT_TO_BYTE_LIST = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
CONST_IP_ADDR = '255.255.255.255'
CONST_PORT_RECV = 20000
CONST_PORT_SEND = 20001


#
# 		单例模式　&& 类
#

class UdpSocketHolder(object):
    _instance_lock = threading.Lock()

    udpSocket = None
    udpListenThread = None
    isLoad = False
    num = 0

    def __init__(self):
        time.sleep(1)

    @classmethod
    def instance(cls, *args, **kwargs):
        if not hasattr(UdpSocketHolder, '_instance'):
            with UdpSocketHolder._instance_lock:
                if not hasattr(UdpSocketHolder, '_instance'):
                    UdpSocketHolder._instance = UdpSocketHolder()
        return UdpSocketHolder._instance


class SocketListenThread(threading.Thread):
    isRunning = True

    def __intToHex(self, intDat):
        if 16 > intDat >= 0:
            return CONST_INT_TO_BYTE_LIST[intDat]
        else:
            return '[Error]'

    def bytesToHexString(self, bytesData):
        resultStr = ''
        for tempByte in bytesData:
            resultStr += self.__intToHex((int)(tempByte / 16))
            resultStr += self.__intToHex((int)(tempByte % 16))
            resultStr += ' '
        return resultStr

    def run(self):
        print('正在监听局域网的地址数据包')
        while (self.isRunning):
            data, addr = UdpSocketHolder.instance().udpSocket.recvfrom(1024)
            # print(addr)
            try:
                # print(data.decode())
                tempJsonObj = json.loads(data.decode())
                if 'timestamp' in tempJsonObj :
                    result = '{"timestamp":'+str(tempJsonObj['timestamp'])+',"ipaddress":"'+str(get_host_ip())+'"}'
                    UdpSocketHolder.instance().udpSocket.sendto(result.encode(encoding='utf-8'),(addr[0],addr[1]))
            except Exception as e :
                print('cache')

    def handleSensorData(self, rawData, addr):
        print('收到数据')


#
#	初始化
#
def killPortProcess(port):
    print('！！！　　杀死对应端口的进程未完成！')


def checkPortUsed(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(('127.0.0.1', port))
        s.shutdown(2)
        return True
    except Exception as e:
        return False


def init():
    if not UdpSocketHolder.instance().isLoad:
        UdpSocketHolder.instance().isLoad = True
        # 　端口占用检查
        if checkPortUsed(CONST_PORT_RECV):
            print('检测到本机局域网接受端口 ( ' + str(CONST_PORT_RECV) + ' ) 已被占用')
            killPortProcess(CONST_PORT_RECV)
            print('杀死对应端口进程 ( ' + str(CONST_PORT_RECV) + ' )')
        else:
            print('端口空闲')
        # 启动局域网监听线程
        UdpSocketHolder.instance().udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        UdpSocketHolder.instance().udpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        try:
            UdpSocketHolder.instance().udpSocket.bind((CONST_IP_ADDR, CONST_PORT_RECV))
            if not UdpSocketHolder.instance().udpListenThread == None:
                UdpSocketHolder.instance().udpListenThread.isRunning = False
                time.sleep(0.05)
            UdpSocketHolder.instance().udpListenThread = SocketListenThread()
            UdpSocketHolder.instance().udpListenThread.start()
        except Exception as e:
            print('初始化监听线程失败，可能已经运行')
        print('初始化')

def get_host_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(('8.8.8.8', 80))
        ip = s.getsockname()[0]
    finally:
        s.close()

    return ip
