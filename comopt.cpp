
#include "comopt.h"
#include <stdio.h>

extern "C"
{

    BOOL APIENTRY DllMain(HANDLE hModule,
                          DWORD  ul_reason_for_call,
                          LPVOID lpReserved
                         )
    {
        return TRUE;
    }


    BOOL APIENTRY checkCom(unsigned int cNum)
    {
        HANDLE hCom;
        char file[16] = {0};

        if(cNum > 9)
        {
            sprintf(file, "\\\\.\\COM%d", cNum);
        }
        else
        {
            sprintf(file, "COM%d", cNum);
        }
        hCom = CreateFile(file, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
        if(hCom == INVALID_HANDLE_VALUE)
        {
            return FALSE;
        }
        CloseHandle(hCom);

        return TRUE;
    }

    HANDLE APIENTRY openCom(unsigned int cNum)
    {
        HANDLE hCom;
        char file[16] = {0};

        if(cNum > 9)
        {
            sprintf(file, "\\\\.\\COM%d", cNum);
        }
        else
        {
            sprintf(file, "COM%d", cNum);
        }
        hCom = CreateFile(file, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

        return hCom;
    }
    BOOL APIENTRY configCom(HANDLE hCom, COMOPT *opt)
    {
        int res = 0;

        if(opt->BaudRate == 0)
        {
            opt->BaudRate = 115200;
        }
        if(opt->ByteSize < 4 || opt->ByteSize > 8)
        {
            opt->ByteSize = 8;
        }
        if(opt->StopBits < 0 || opt->StopBits > 3)
        {
            opt->StopBits = 0;
        }
        if(opt->Parity < 0 || opt->Parity > 4)
        {
            opt->Parity = 0;
        }
        if(opt->IntervalTimeout == 0)
        {
            opt->IntervalTimeout = (115200 * 5) / opt->BaudRate;
        }

        res = SetupComm(hCom, 1024, 1024);
        if(!res)
        {
            return FALSE;
        }

        COMMTIMEOUTS timeOuts;
        timeOuts.ReadIntervalTimeout = opt->IntervalTimeout;
        timeOuts.ReadTotalTimeoutConstant = 0;
        timeOuts.ReadTotalTimeoutMultiplier = 0;
        res = SetCommTimeouts(hCom, &timeOuts);
        if(!res)
        {
            return FALSE;
        }

        DCB dcb;
        res = GetCommState(hCom, &dcb);
        if(!res)
        {
            return FALSE;
        }
        dcb.fAbortOnError = FALSE;
        dcb.BaudRate = opt->BaudRate;
        dcb.ByteSize = (unsigned char)opt->ByteSize;
        dcb.Parity = (unsigned char)opt->Parity;
        dcb.StopBits = (unsigned char)opt->StopBits;
        res = SetCommState(hCom, &dcb);
        if(!res)
        {
            return FALSE;
        }

        PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
        ClearCommError(hCom, NULL, NULL);

        return TRUE;
    }
    unsigned int APIENTRY recvData(HANDLE hCom, unsigned char *buf, unsigned int bufLen)
    {
        unsigned long readLen = 0;
        BOOL readState;
        OVERLAPPED overLapped;

        memset(&overLapped, 0, sizeof(OVERLAPPED));
        overLapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        readState = ReadFile(hCom, buf, bufLen, &readLen, &overLapped);
        if(!readState)
        {
            if(GetLastError() == ERROR_IO_PENDING)
            {
                GetOverlappedResult(hCom, &overLapped, &readLen, TRUE);
            }
        }

        return readLen;
    }
    unsigned int APIENTRY sendData(HANDLE hCom, unsigned char *dat, unsigned int datLen)
    {
        unsigned long writeLen = 0;
        BOOL writeState;
        OVERLAPPED overLapped;

        memset(&overLapped, 0, sizeof(OVERLAPPED));
        overLapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        writeState = WriteFile(hCom, dat, datLen, &writeLen, &overLapped);
        if(!writeState)
        {
            if(GetLastError() == ERROR_IO_PENDING)
            {
                GetOverlappedResult(hCom, &overLapped, &writeLen, TRUE);
            }
        }

        return writeLen;
    }
    BOOL APIENTRY closeCom(HANDLE hCom)
    {
        if(hCom == INVALID_HANDLE_VALUE)
        {
            return FALSE;
        }
        CloseHandle(hCom);

        return TRUE;
    }

    BOOL APIENTRY clearCache(HANDLE hCom)
    {
        PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
        ClearCommError(hCom, NULL, NULL);

        return TRUE;
    }

}

