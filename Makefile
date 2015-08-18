CC = gcc
LD = ld
RM = -rm

CFLAGS = -m64

BANNER = @echo -e "\n=== $@\n"

all: pwrasm

pwrasm: main.o helper.o instructions.o
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: %.c
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

clean:
	$(BANNER)
	$(RM) -f pwrasm *.o
