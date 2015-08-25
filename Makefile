CC = gcc
LD = ld
RM = -rm

CFLAGS = -m64

BANNER = @echo -e "\n=== $@\n"

all: ppc64asm

ppc64asm: main.o helper.o instructions.o
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: %.c
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

clean:
	$(BANNER)
	$(RM) -f ppc64asm *.o
