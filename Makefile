CC = gcc
LD = ld
RM = -rm

CFLAGS = -m64

BANNER = @echo -e "\n=== $@\n"

all: asm2c

asm2c: asm2c.o
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: %.c
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

clean:
	$(BANNER)
	$(RM) -f asm2c *.o
