@echo off

@echo Compilation : 

gcc src/*.c -o binaries/letx.exe

IF %errorlevel% EQU 0 (
    @echo OK
    rem D:/Tenegan/Documents/Some_Bytes/projet_explorateur-fichier/binaries/letx.exe
)

PAUSE