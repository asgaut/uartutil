# Win32 uartutil

Utility for reporting the status of the DSR and CTS on UARTs on a Windows system.

## Usage

```bat
uartutil.exe <port>
```

## Example

```bat
uartutil.exe COM1
```

## Building

Open a Developer Command Prompt for Visual Studio and run the following command:

```bat
cl uartutil.c
```
