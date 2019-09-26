
CDIALECT = c99

OBJECTS = out/Random.o

OUTPUT = librandom.a

INCLUDES = ./include

TESTS := 

ALL_CFLAGS = $(CFLAGS) $(foreach include,$(INCLUDES),-I$(include)) -fPIC

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(AR) rcs $(OUTPUT) $(OBJECTS)

test: $(TESTS)

out/:
	mkdir out/	

out/%.o: src/%.c | out/
	$(CC) $(ALL_CFLAGS) -c -o $@ $^


test-%: test/%.c $(OBJECTS)
	 $(CC) $(LDFLAGS) -o test/$@ 
	 
clean:
	rm -rf out/ $(OUTPUT)