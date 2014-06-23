#
# ZDS II Make File - ArkanoidZ8, Debug
#

CC = @C:\PROGRA~2\ZiLOG\ZDSII_~1.3\bin\eZ8cc
ASM = @C:\PROGRA~2\ZiLOG\ZDSII_~1.3\bin\eZ8asm
LINK = @C:\PROGRA~2\ZiLOG\ZDSII_~1.3\bin\eZ8link
LIB = @C:\PROGRA~2\ZiLOG\ZDSII_~1.3\bin\eZ8lib

# compiler options
#   -alias -asm -bitfieldsize:32 -charsize:8 -const:RAM -debug
#   -define:_Z8F6403 -define:_Z8ENCORE_640_FAMILY
#   -define:_Z8ENCORE_F640X -define:_MODEL_LARGE -doublesize:32
#   -NOexpmac -floatsize:32 -NOfplib -genprintf -NOglobalcopy
#   -NOglobalcse -NOglobalfold -intrinsic -intsize:16 -intsrc -NOjmpopt
#   -NOkeepasm -NOkeeplst -NOlist -NOlistinc -localcopy -localcse
#   -localfold -longsize:32 -NOloopopt -maxerrs:50 -model:L -NOoptlink
#   -optsize -peephole -NOpromote -quiet -regvar -revaa -NOsdiopt
#   -shortsize:16
#   -stdinc:"C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\Z8Encore_F640X"
#   -strict -NOwatch -cpu:Z8F6403
#   -asmsw:" -cpu:Z8F6403 -define:_Z8F6403=1 -define:_Z8ENCORE_640_FAMILY=1 -define:_Z8ENCORE_F640X=1 -define:_MODEL_LARGE=1 -include:C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\Z8Encore_F640X -revaa"
CFLAGS = -sw:C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8_Debug.ccsw
# assembler options
#   -debug -define:_Z8F6403=1 -define:_Z8ENCORE_640_FAMILY=1
#   -define:_Z8ENCORE_F640X=1 -define:_MODEL_LARGE=1 -genobj -NOigcase
#   -include:"C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog;C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\Z8Encore_F640X"
#   -list -NOlistmac -name -pagelen:56 -pagewidth:80 -quiet -sdiopt
#   -warn -NOzmasm -revaa -cpu:Z8F6403
AFLAGS = -sw:C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8_Debug.asmsw

OUTDIR = C:\Users\s122554\Desktop\ArkanoidZ8\

Debug: ArkanoidZ8

deltarget: 
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8.lod  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8.lod

clean: 
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8.lod  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8.lod
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\ansi.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\ansi.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\main.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\main.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\led.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\led.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\helper.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\helper.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\time.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\time.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.obj
	@if exist C:\Users\s122554\Desktop\ArkanoidZ8\menu.obj  \
            del C:\Users\s122554\Desktop\ArkanoidZ8\menu.obj

rebuildall: clean Debug

relink: deltarget Debug

LIBS = 

OBJS =  \
            C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\ansi.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\main.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\led.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\helper.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\time.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.obj  \
            C:\Users\s122554\Desktop\ArkanoidZ8\menu.obj

ArkanoidZ8: $(OBJS)
	 $(LINK)  @C:\Users\s122554\Desktop\ArkanoidZ8\ArkanoidZ8_Debug.linkcmd

C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.asm  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\ez8dev.inc  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\gpio.inc
	 $(ASM)  $(AFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\zsldevinit.asm

C:\Users\s122554\Desktop\ArkanoidZ8\ansi.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\ansi.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\helper.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\ansi.c

C:\Users\s122554\Desktop\ArkanoidZ8\main.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\main.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\dmadefs.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\ez8.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\gpio.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\MathFix.h  \
            C:\Users\s122554\Desktop\ARKANO~1\ansi.h  \
            C:\Users\s122554\Desktop\ARKANO~1\asciiart.h  \
            C:\Users\s122554\Desktop\ARKANO~1\helper.h  \
            C:\Users\s122554\Desktop\ARKANO~1\led.h  \
            C:\Users\s122554\Desktop\ARKANO~1\menu.h  \
            C:\Users\s122554\Desktop\ARKANO~1\time.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\main.c

C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\MathFix.h  \
            C:\Users\s122554\Desktop\ARKANO~1\sinLUT.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\MathFix.c

C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.c  \
            C:\Users\s122554\Desktop\ARKANO~1\sinLUT.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\sinLUT.c

C:\Users\s122554\Desktop\ArkanoidZ8\led.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\led.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\dmadefs.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\ez8.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\gpio.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\charset.h  \
            C:\Users\s122554\Desktop\ARKANO~1\helper.h  \
            C:\Users\s122554\Desktop\ARKANO~1\led.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\led.c

C:\Users\s122554\Desktop\ArkanoidZ8\helper.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\helper.c  \
            C:\Users\s122554\Desktop\ARKANO~1\helper.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\helper.c

C:\Users\s122554\Desktop\ArkanoidZ8\time.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\time.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\dmadefs.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\ez8.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\gpio.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\time.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\time.c

C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\ansi.h  \
            C:\Users\s122554\Desktop\ARKANO~1\asciiart.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\asciiart.c

C:\Users\s122554\Desktop\ArkanoidZ8\menu.obj :  \
            C:\Users\s122554\Desktop\ArkanoidZ8\menu.c  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\FORMAT.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\std\STDARG.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\defines.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\SIO.H  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uart.h  \
            C:\PROGRA~2\ZiLOG\ZDSII_~1.3\include\zilog\uartdefs.h  \
            C:\Users\s122554\Desktop\ARKANO~1\ansi.h  \
            C:\Users\s122554\Desktop\ARKANO~1\helper.h  \
            C:\Users\s122554\Desktop\ARKANO~1\menu.h
	 $(CC)  $(CFLAGS) C:\Users\s122554\Desktop\ArkanoidZ8\menu.c

