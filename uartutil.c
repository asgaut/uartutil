/*
    Win32 serial port CTS and DSR inputs reporting test program.
*/

#include <windows.h>
#include <stdio.h>

HANDLE hSerialPort;

BOOL GetDSR(void)
{
    DWORD dwModemStatus;

    GetCommModemStatus(hSerialPort, &dwModemStatus);
    return (dwModemStatus & MS_DSR_ON) ? TRUE : FALSE;
}

BOOL GetCTS(void)
{
    DWORD dwModemStatus;

    GetCommModemStatus(hSerialPort, &dwModemStatus);
    return (dwModemStatus & MS_CTS_ON) ? TRUE : FALSE;
}

/*
void SetDTR(BOOL fDTR)
{
    EscapeCommFunction(hSerialPort, fDTR ? SETDTR : CLRDTR);
}

void SetRTS(BOOL fRTS)
{
    EscapeCommFunction(hSerialPort, fRTS ? SETRTS : CLRRTS);
}
*/

BOOL Open(const char* portname)
{
    HANDLE hPort;

    hPort = CreateFile(portname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    if (hPort != INVALID_HANDLE_VALUE) {
        hSerialPort = hPort;
    }
    else return FALSE;
    return TRUE;
}

BOOL Close(void)
{
    return CloseHandle(hSerialPort);
}

int main(int argc, char* argv[])
{
    char* portname;

    if (argc > 1) {
        portname = argv[1];
    }
    else {
        printf("Usage: uartdiag <portname>\n");
        return 1;
    }
    if (!Open(portname)) {
        printf("Failed to open port %s\n", portname);
        return 1;
    }
    BOOL fDSR = GetDSR();
    BOOL fCTS = GetCTS();
    printf("DSR = %d, CTS = %d\n", fDSR, fCTS);
    Close();
    return 0;
}
