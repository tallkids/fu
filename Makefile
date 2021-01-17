#
#	Makefile for File Management Utility
#
default:
	@echo "Specify one of the following"
	@echo "  make clean               for clean up your directory"
	@echo "  make hpux                for HPUX"
	@echo "  make hpux-x              for HPUX (xfu)"
	@echo "  make h2050               for Hitachi 2050"
	@echo "  make h2050-x             for Hitachi 2050 (xfu)"
	@echo "  make i386bsd             for 386BSD"
	@echo "  make i386bsd-x           for 386BSD (xfu)"
	@echo "  make panix               for PANIX"
	@echo "  make panix-x             for PANIX (xfu)"
	@echo "  make linux               for Linux"
	@echo "  make linux-x             for Linux (xfu)"
	@echo "  make cygwin              for Cygwin"
	@echo "  make bsdi                for BSDI"
	@echo "  make bsdi-x              for BSDI (xfu)"
	@echo "  make minix               for MINIX 1.5 ACK compiler"
	@echo "  make minix-bcc           for MINIX 1.5 BCC compiler"
	@echo "  make sunos               for SunOS"
	@echo "  make sunos-x             for SunOS (xfu)"
	@echo "  make news3400            for Sony NEWS3400"
	@echo "  make news3400-x          for Sony NEWS3400 (xfu)"
	@echo "  make beos                for BeOS Rel.4 Intel"
	@echo "  make mac                 for MacOS"
#
.SUFFIXES:
.SUFFIXES: .c .o
#
.c.o:
	$(CC) -c $(INCDIR) $(XINCDIR) $(CFLAGS) $<
#
targets: $(TARGET)
#
clean:
	-rm -f *.o *~
#
OBJFU	=	fu.o
OBJSUB	=	setup.o getstr.o command.o tree.o archiver.o \
		copyfile.o typefile.o delfile.o findfile.o \
		pushdir.o curjump.o kfunc.o
OBJCOM	=	text.o key.o $(XOBJ)
THEADER	=	futable.h
HEADER	=	fu.h key.h
OPTFLAGS=	-O
CFLAGS	=	$(OPTFLAGS) $(MCFLAGS)
LDFLAGS =	$(LIB)
#
hpux:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DHP9000=1" \
	"LIB=-lcurses"
#
hpux-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DHP9000=1 -DXWINDOW=1 -I /usr/include/X11R4" \
	"LIB=-L /usr/lib/X11R4 -lcurses -lX11 -lV3"
#
h2050:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DH2050=1" \
	"LIB=-lcurses"
#
h2050-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DH2050=1 -DXWINDOW=1" \
	"LIB=-lcurses -lX11 -lnet"
#
i386bsd:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DI386BSD=1" \
	"LIB=-lcurses -ltermcap"
#
i386bsd-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DI386BSD=1 -DXWINDOW=1" \
	"LIB=-lcurses -ltermcap -lX11"
#
mac:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-g -w -Wno-return-type -DMACOS=1 -DI386BSD=1" \
	"LIB=-lcurses"
#
mac-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-g -w -Wno-return-type -DMACOS=1 -DI386BSD=1 -DXWINDOW=1" \
	"LIB=-lcurses -lX11"
#
panix:
	make targets \
	"CC=gcc" "LD=gcc" \
	"TARGET=fu" \
	"MCFLAGS=-DPANIX=1 -DSUNSPARC=1 -traditional -I/usr/ucbinclude"  \
	"LIB=-lcurses -ltermcap"
#
panix-x:
	make targets \
	"CC=gcc" "LD=gcc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DPANIX=1 -DSUNSPARC=1 -DXWINDOW=1 -traditional -I/usr/ucbinclude"  \
	"LIB=-lcurses -ltermcap -lX11 -lm -lnsl -lsocket -dy -Bdynamic"
#
linux:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DLINUX=1 -DHP9000=1" \
	"LIB=-ltermcap"
#
linux-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DLINUX=1 -DHP9000=1 -DXWINDOW=1 -I /usr/include/X11" \
	"LIB=-L/usr/X11R6/lib -ltermcap -lX11"
#
cygwin:
	make targets \
	"CC=gcc" "LD=gcc" \
	"TARGET=fu" \
	"MCFLAGS=-DLINUX=1 -DHP9000=1" \
	"LIB=-lcurses"
#
bsdi:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DI386BSD=1" \
	"LIB=-lcurses -ltermcap"
#
bsdi-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DI386BSD=1 -DXWINDOW=1 -I /usr/include/X11R4" \
	"LIB=-L /usr/lib/X11R4 -lcurses -ltermcap -lX11 -lV3"#
#
minix:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DMINIX=1 -i" \
	"LIB=-i"
#
minix-bcc:
	make targets \
	"CC=bcc" "LD=bcc" \
	"TARGET=fu" \
	"MCFLAGS=-DMINIX=1 -i -0 -I/usr/local/include" \
	"LIB=-i -0"
#
sunos:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DSUNSPARC=1" \
	"LIB=-lcurses -ltermcap"
#
sunos-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DSUNSPARC=1 -DXWINDOW=1 -I/usr/openwin/include" \
	"LIB=-L/usr/openwin/lib -lcurses -ltermcap -lX11"
#
news3400:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DNEWS3400=1 -DSUNSPARC=1" \
	"LIB=-lcurses -ltermcap"
#
news3400-x:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=xfu" \
	"XOBJ=xtext.o xkey.o" \
	"MCFLAGS=-DNEWS3400=1 -DSUNSPARC=1 -DXWINDOW=1 -I/usr/openwin/include" \
	"LIB=-L/usr/openwin/lib -lcurses -ltermcap -lX11"
#
beos:
	make targets \
	"CC=cc" "LD=cc" \
	"TARGET=fu" \
	"MCFLAGS=-DBEOS=1 -DHP9000=1" \
	"LIB=-ltermcap"
#
#	*********** Linkage ***********
#
$(TARGET):	${OBJFU} ${OBJSUB} ${OBJCOM}
	$(LD) ${OBJFU} ${OBJSUB} ${OBJCOM} -o $@ $(LDFLAGS)
#
#	*********** Compile ***********
#
${OBJFU}:	${THEADER} ${HEADER}
${OBJSUB}:	${HEADER}
${OBJCOM}:
