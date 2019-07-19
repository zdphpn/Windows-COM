# Windows-COM
Windows下读写串口(异步)，可同时读写，但读写各自阻塞线程

### 函数列表
* **BOOL** APIENTRY	**checkCom**(unsigned int cNum);
* **HANDLE** APIENTRY	**openCom**(unsigned int cNum);
* **BOOL** APIENTRY	**configCom**(HANDLE hCom,COMOPT* opt);
* **UINT** APIENTRY	**recvData**(HANDLE hCom,unsigned char* buf,unsigned int bufLen);
* **UINT** APIENTRY	**sendData**(HANDLE hCom,unsigned char* dat,unsigned int datLen);
* **BOOL** APIENTRY	**closeCom**(HANDLE hCom);
*  
* **BOOL** APIENTRY	**clearCache**(HANDLE hCom);
