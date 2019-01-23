@echo off
:loop
	F:\CodeBlocks\Code\rand\bin\Debug\rand.exe %random% > in.txt
	F:\CodeBlocks\Code\yuan\bin\Debug\yuan.exe < in.txt > stdout.txt
	F:\CodeBlocks\Code\zhi\bin\Debug\zhi.exe < in.txt > myout.txt
	fc stdout.txt myout.txt 
if not errorlevel 1 goto loop
pause
goto loop
