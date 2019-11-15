


INCLUDES = random/include libconinteract/include

ALL_CFLAGS = $(CFLAGS) $(foreach include,$(INCLUDES),-I$(include)) -fPIC

LIBS = m



ALL_LD_FLAGS := $(LDFLAGS) 

OUTPUT:=ninegaps

OBJECTS = src/main.o 
LIBRARIES = libconinteract/libconinteract.a random/librandom.a

$(OUTPUT): $(OBJECTS) $(LIBRARIES)
	$(CC) $(ALL_LD_FLAGS) -o $@ $^ $(foreach library,$(LIBS),-l$(library))

libconinteract/%:
	$(MAKE) -C libconinteract $*
	
random/%:
	$(MAKE) -C random  $*

clean-recursive:
	$(MAKE) libconinteract/clean
	$(MAKE) random/clean

clean: clean-recursive
	

%.o: %.c
	$(CC) $(ALL_CFLAGS) -o $@ -c $^

dist: clean
	zip -r NineGapsGame.zip src/ libconinteract/ random/ README.md Makefile -x random/.git libconinteract/.git
