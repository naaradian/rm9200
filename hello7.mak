###Make File#########################################################
## This file was generated by MetaDeveloper a product of: 
##    ARC International.
##    http://www.ARC.com/
##
##    Copyright (c) ARC International
##    All rights reserved
##
#####################################################################
#####################################################################
CC = C:\ARC\MetaWare\hcarm\bin\hcarm.exe
LD = C:\ARC\MetaWare\hcarm\bin\hcarm.exe
AS = C:\ARC\MetaWare\hcarm\bin\hcarm.exe
VPATH = c:\arc\mqx2.50_atevbrm9200.met\examples\hello7;C:\ARC\rtcs2.95\lib\at91rm9200l.met;C:\ARC\mqx2.50_atevbrm9200.met\lib\atevbrm9200l.met;C:\ARC\mqx2.50_atevbrm9200.met\lib\at91rm9200l.met;C:\ARC\mqx2.50_atevbrm9200.met\lib\atevbrm9200l.met;C:\ARC\MetaWare\hcarm\lib\le\thumb

hello7.elf:  hello7.o asm_test.o work.o at45.o work1.o jump.o EMBISR.o ttl.o hello.o dataflash.o spi_pol.o buk_pum.o rtcs.a atevbrm9200.a mqx.a libc.a met.o
	@echo Linking...  
	@$(LD) -Bgrouplib -Bstatic -Hhostlink -Heos=mqx -Hon=Long_enums -Hnoreent -Hnoswst -Hnosdata -Hoff=Behaved -Hheap=0 -HL -m -o C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.elf @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opl -Hldopt=-q > C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.map
	@echo Build is finished.


-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.d

hello7.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\hello7.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.c

asm_test.o: C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\asm_test.s
	@echo Assembling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\asm_test.s ...  
	@$(AS) -c -Hasopt=-o,asm_test.o @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opa C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\asm_test.s

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\work.d

work.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\work.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\work.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\at45.d

at45.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\at45.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\at45.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\work1.d

work1.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\work1.cpp ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\work1.cpp

jump.o: C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\jump.s
	@echo Assembling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\jump.s ...  
	@$(AS) -c -Hasopt=-o,jump.o @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opa C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\jump.s

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\EMBISR.d

EMBISR.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\EMBISR.cpp ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\EMBISR.cpp

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\ttl.d

ttl.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\ttl.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\ttl.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello.d

hello.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\hello.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\dataflash.d

dataflash.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\dataflash.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\dataflash.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\spi_pol.d

spi_pol.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\spi_pol.c ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\spi_pol.c

-include C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\buk_pum.d

buk_pum.o:
	@echo Compiling C:\\ARC\\mqx2.50_atevbrm9200.met\\examples\\hello7\\buk_pum.cpp ...  
	@$(CC) -Hnocopyr -c -Hasopt=-c @C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\hello7.opc C:\ARC\mqx2.50_atevbrm9200.met\examples\hello7\buk_pum.cpp

rtcs.a:
atevbrm9200.a:
mqx.a:
libc.a:
met.o:
