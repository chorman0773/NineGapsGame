


INCLUDES = random/include libconinteract/include

ALL_CFLAGS = $(CFLAGS) $(foreach include,$(INCLUDES),-I$(include)) -fPIC

LIBS = m



ALL_LD_FLAGS := $(LDFLAGS) $(foreach library,$(LIBS),-l$(library))

OUTPUT:=ninegaps

OBJECTS = src/main.o libconinteract/libconinteract.a random/librandom.a

$(OUTPUT): $(OBJECTS)
	$(CC) $(ALL_LD_FLAGS) -o $@ $^

libconinteract/libconinteract.a: 
	$(MAKE) -C libconinteract
	
random/librandom.a:
	$(MAKE) -C random 

clean-recursive:
	$(MAKE) -C libconinteract clean
	$(MAKE) -C random clean
	rm -rf $(OUTPUT) out/

clean: clean-recursive


%.o: %.c
	$(CC) $(ALL_CFLAGS) -o $@ -c $^
