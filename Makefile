GXX = gcc
CFLAGS = -pedantic -g -Wall -Wvla -Werror -Wno-error=unused-variable -lpthread -pthread
OFILES = gol.o gol_cmd.o gol_io.o gol_sim.o gol_part.o

all: thread

thread: $(OFILES)
	$(GXX) $(CFLAGS) gol.o gol_cmd.o gol_io.o gol_sim.o gol_part.o -o thread

gol.o: gol.c gol_cmd.h gol_io.h gol_sim.h gol_part.h gol_struct.h
	$(GXX) $(CFLAGS) gol.c -c

gol_cmd.o: gol_cmd.c gol_cmd.h
	$(GXX) $(CFLAGS) gol_cmd.c -c

gol_io.o: gol_io.c gol_io.h
	$(GXX) $(CFLAGS) gol_io.c -c

gol_sim.o: gol_sim.c gol_sim.h gol_io.h gol_struct.h
	$(GXX) $(CFLAGS) gol_sim.c -c

gol_part.o: gol_part.c gol_part.h gol_io.h gol_sim.h gol_struct.h
	$(GXX) $(CFLAGS) gol_part.c -c

clean:
	rm thread *.o *~