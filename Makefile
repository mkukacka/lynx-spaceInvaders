
include Makefile_lynxcc65.mk

target = spaceInv.lnx
objects = lynx-160-102-16.o lynx-stdjoy.o \
	spaceInv.o

# robot.o: robot.bmp
# 	$(SPRPCK) -t6 -p2 -a004003 robot.bmp
# 	$(ECHO) .global _robot > $*.s
# 	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
# 	$(ECHO) _robot: .incbin \"robot.spr\" >> $*.s
# 	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

# robot1.o: robot1.pcx
# 	$(SP) -r $< -c lynx-sprite,mode=literal,ax=0,ay=0,edge=0 -w $*.c,ident=$*
# 	$(CC) $(SEGMENTS) $(CFLAGS) $*.c
# 	$(AS) -o $@ $(AFLAGS) $(*).s
# 	$(RM) $*.c

# robot1.o: robot1.bmp
# 	$(SPRPCK) -t6 -p2 -a004003 $<
# 	$(ECHO) .global _robot1 > $*.s
# 	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
# 	$(ECHO) _robot1: .incbin \"robot1.spr\" >> $*.s
# 	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

# robot1.o: robot1.pcx
# 	$(SPRPCK) -t3 -p2 -a004003 $<
# 	$(ECHO) .global _$* > $*.s
# 	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
# 	$(ECHO) _$*: .incbin \"$*.spr\" >> $*.s
# 	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

# $(SP) -r $< --slice 16,0,8,8 -c lynx-sprite,mode=literal,ax=0,ay=0 -w $*.c,ident=$*

# oddSize.o: oddSize.pcx
# 	$(SP) -r $< -c lynx-sprite,mode=literal,ax=0,ay=0 -w $*.c,ident=$* 
# 	$(CC) $(SEGMENTS) $(CFLAGS) -o $*.s $*.c 
# 	$(AS) -o $@ $(AFLAGS) $(*).s 
# #	$(RM) $*.c 

all: $(target)

$(target) : $(objects)
	$(CL) -t $(SYS) -o $@ $(objects) lynx.lib 

clean:
	$(RM) *.tgi
	$(RM) *.s
	$(RM) *.joy
	$(RM) *.o
	$(RM) *.pal
	$(RM) *.spr
	$(RM) *.lnx
