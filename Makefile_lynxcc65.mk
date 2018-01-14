
CC65=D:\workspace-lynx\CC65
CC65_BIN=$(CC65)\bin
CC65_INC=$(CC65)\include
CC65_ASMINC=$(CC65)\asminc
CC65_TOOLS=$(CC65)\wbin

CP=$(CC65_TOOLS)\cp
RM=$(CC65_TOOLS)\rm -f
CO=$(CC65_BIN)\co65
CC=$(CC65_BIN)\cc65
AS=$(CC65_BIN)\ca65
CL=$(CC65_BIN)\cl65
LD=$(CC65_BIN)\ld65
SP=$(CC65_BIN)\sp65
SPRPCK=$(CC65_BIN)\sprpck
ECHO=$(CC65_TOOLS)\echo
TOUCH=$(CC65_TOOLS)\touch

.SUFFIXES : .c .s .o .asm .bmp .pal .spr

SYS=lynx

CODE_SEGMENT=CODE
DATA_SEGMENT=DATA
RODATA_SEGMENT=RODATA
BSS_SEGMENT=BSS

SEGMENTS=--code-name $(CODE_SEGMENT) \
				--rodata-name $(RODATA_SEGMENT) \
				--bss-name $(BSS_SEGMENT) \
				--data-name $(DATA_SEGMENT)

# The flag for adding stuff to a library
ARFLAGS=a

# The flags for compiling C-code
CFLAGS=-I . -t $(SYS) --add-source -O -Or -Cl -Os

# Rule for making a *.o file out of a *.s file
# TODO: Find out if this works {}.s{$(ODIR)}.o:
.s.o:
	$(AS) -t $(SYS) -I $(CC65_ASMINC) -o $@ $(AFLAGS) $<

# Rule for making a *.o file out of a *.c file
.c.o:
	$(CC) $(SEGMENTS) $(CFLAGS) $<
	$(AS) -o $@ $(AFLAGS) $(*).s
#	$(RM) $*.s

lynx-stdjoy.o:
	$(CP) $(CC65_INC)\..\joy\$*.joy .
	$(CO) --code-label _lynxjoy $*.joy
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
	$(RM) $*.joy
	$(RM) $*.s

lynx-160-102-16.o:
	$(CP) $(CC65_INC)\..\tgi\lynx-160-102-16.tgi . 
	$(CO) --code-label _lynxtgi lynx-160-102-16.tgi 
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
	$(RM) $*.tgi
	$(RM) $*.s

# Rule for making a *.o file out of a *.bmp file
.bmp.o:
	$(SPRPCK) -t6 -p2 $<
	$(ECHO) .global _$(*B) > $*.s
	$(ECHO) .segment "$(RODATA_SEGMENT)" >> $*.s
	$(ECHO) _$(*B): .incbin "$*.spr" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
	$(RM) $*.s
	$(RM) $*.pal
	$(RM) $*.spr

# Rule for making an *.c file out of a *.pcx file, SHAPED mode
# for transparent mode, use: $(SP) -r $< -c lynx-sprite,mode=transparent
# few examples of other uses:
#  sp65 -r robot1.pcx -c lynx-sprite,mode=packed,ax=0,ay=0 -w robot1.c,ident=robot1
#  sp65 -r robot1.pcx -c lynx-sprite,mode=shaped,ax=0,ay=0,edge=0 -w robot1.c,ident=robot1
#  sp65 -r robot1.pcx -c lynx-sprite,mode=literal,ax=0,ay=0,edge=0 -w robot1.c,ident=robot1
#  sp65 -r robot1.pcx -c lynx-sprite,mode=shaped,ax=0,ay=0,edge=0 -w robot1.s
# Obsolete but still valuable documentation: https://cc65.github.io/doc/sp65.html
.pcx.o:
	$(SP) -r $< -c lynx-sprite,mode=shaped,ax=0,ay=0,edge=0 -w $*.s,ident=$*
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s
	
