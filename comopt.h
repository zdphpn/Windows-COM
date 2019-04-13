
#ifndef _COMOPT_H
#define _COMOPT_H


extern "C"
{

    struct COMOPT
    {

        DWORD BaudRate;			/* Baudrate at which running		*/
        DWORD ByteSize;			/* Number of bits/byte, 4-8			*/
        DWORD Parity;			/* 0-4=None,Odd,Even,Mark,Space		*/
        DWORD StopBits;			/* 0,1,2 = 1, 1.5, 2				*/

        DWORD IntervalTimeout;	/* Maximum time between chars		*/
    };

    BOOL			APIENTRY	checkCom(unsigned int cNum);
    HANDLE			APIENTRY	openCom(unsigned int cNum);
    BOOL			APIENTRY	configCom(HANDLE hCom,COMOPT *opt);
    unsigned int	APIENTRY	recvData(HANDLE hCom,unsigned char *buf,unsigned int bufLen);
    unsigned int	APIENTRY	sendData(HANDLE hCom,unsigned char *dat,unsigned int datLen);
    BOOL			APIENTRY	closeCom(HANDLE hCom);

    BOOL			APIENTRY	clearCache(HANDLE hCom);

}




#endif