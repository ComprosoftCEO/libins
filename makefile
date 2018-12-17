# Makefile for Insanity Standard Library (libins)
CC=gcc
INCLUDES=-IICC/dev
CFLAGS=-O3 -fPIC $(INCLUDES) -Wall -Wno-unused-function -Wno-unused-result
DEPFLAGS=-MD -MF $(@:$(OBJD)/%=$(DEPD)/%.d) -MT $@ -MP
LIBS=-lpthread


# Library to compile
#	lib<Library>.so   = Production library
#	lib<Library>d.so  = Debug library
LIBRARY=icc


# Directories
#	SRCD = Source directory (where to put the actual code)
#	OBJD = Object directory (where to put all .o and .do files)
#	LIBD = Library directory (where to put .so file)
#	DEPD = Dependency directory (where to put all .d files)
SRCD=src
OBJD=obj
LIBD=lib
DEPD=obj
$(shell mkdir -p $(OBJD) $(LIBD) $(DEPD))




# C sources
CSRC=\
	Insanity-Dev.c \
	\
	args/init_data.c \
	args/Argc.c \
	args/Argv.c \
	args/ArgvReset.c 

# Insanity sources
ISRC=\
	stdio/PrintNumber.ins \



# Computer library name, objects, debug objects, dependency files, etc.
LIB      = $(LIBD)/lib$(LIBRARY).so
DLIB     = $(LIBD)/lib$(LIBRARY)d.so
OBJS     = $(addprefix $(OBJD)/,$(CSRC:%.c=%.o) $(ISRC:%=%.o))
DEB_OBJS = $(OBJS:%.o=%.do)
DEPENDS  = $(addprefix $(DEPD)/,$(OBJS:$(OBJD)/%=%.d) $(DEB_OBJS:$(OBJD)/%=%.d))
ICFILES  = $(ISRC:%=$(SRCD)/%.c)




.PHONY: all
all: $(LIB) $(DLIB)


# Compile the library
$(LIB): $(OBJS)
	$(CC) -shared $^ -o $@ $(LIBS)

# Compile the debug shared library
$(DLIB): $(DEB_OBJS)
	$(CC) -shared $^ -o $@ $(LIBS)



# Bring in the dependency info for *existing* .o files
-include $(DEPENDS)


# Compile C object files
$(OBJD)/%.o: $(SRCD)/%.c
	@mkdir -p $(dir $(@)) $(addprefix $(DEPD)/,$(dir $(@:$(OBJD)/%=%)))
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

# Compile debug C object files
$(OBJD)/%.do: $(SRCD)/%.c
	@mkdir -p $(dir $(@)) $(addprefix $(DEPD)/,$(dir $(@:$(OBJD)/%=%)))
	$(CC) -c -g $(CFLAGS) $(DEPFLAGS) $< -o $@

# "Compile" insanity C source files
.PRECIOUS: %.c
%.ins.c: %.ins
	icc $< $@




# Remove all files
.PHONY: clean
clean:
	rm -f $(LIB) $(DLIB) $(OBJS) $(DEB_OBJS) $(DEPENDS) $(ICFILES)


# Print out a makefile variable
print-%  : ; @echo $* = $($*)
