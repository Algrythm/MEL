@echo off
cd /d %~dp0
cls
echo Welcome to the MEL installer.
echo This will move the MEL file into Program Files.
echo Add the directory C:\Program Files\MEL to your PATH in environment variables to access MEL by console.
pause
cls
mkdir "C:\Program Files\MEL"
move "mel.exe" "C:\Program Files\MEL"
echo Complete!
pause