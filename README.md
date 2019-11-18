# Windows-COM
Windows下读写串口(异步)，可同时读写，但读写各自阻塞线程

### 串口参数
struct **COMOPT**  
{  
&nbsp;&nbsp;&nbsp;&nbsp;**DWORD** BaudRate;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//Baudrate at which running  
&nbsp;&nbsp;&nbsp;&nbsp;**DWORD** ByteSize;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//Number of bits/byte, 4-8  
&nbsp;&nbsp;&nbsp;&nbsp;**DWORD** Parity;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//0-4=None,Odd,Even,Mark,Space  
&nbsp;&nbsp;&nbsp;&nbsp;**DWORD** StopBits;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//0,1,2 = 1, 1.5, 2  
 
&nbsp;&nbsp;&nbsp;&nbsp;**DWORD** IntervalTimeout;&nbsp;&nbsp;&nbsp;&nbsp;//Maximum time between chars  
};  

### 函数列表
* **BOOL** APIENTRY	**checkCom**(unsigned int cNum);
* **HANDLE** APIENTRY	**openCom**(unsigned int cNum);
* **BOOL** APIENTRY	**configCom**(HANDLE hCom,**COMOPT*** opt);
* **UINT** APIENTRY	**recvData**(HANDLE hCom,unsigned char* buf,unsigned int bufLen);
* **UINT** APIENTRY	**sendData**(HANDLE hCom,unsigned char* dat,unsigned int datLen);
* **BOOL** APIENTRY	**closeCom**(HANDLE hCom);
*  
* **BOOL** APIENTRY	**clearCache**(HANDLE hCom);
