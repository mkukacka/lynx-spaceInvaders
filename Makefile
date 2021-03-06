
include Makefile_lynxcc65.mk

target = spaceInv.lnx
objects = lynx-160-102-16.o lynx-stdjoy.o \
	sprites.o spaceInv.o

all: $(target)

$(target) : $(objects)
	$(CL) -t $(SYS) -C lynx-coll.cfg -o $@ $(objects) lynx.lib 

clean:
	$(RM) *.tgi
	$(RM) *.s
	$(RM) *.joy
	$(RM) *.o
	$(RM) *.pal
	$(RM) *.spr
	$(RM) *.lnx
