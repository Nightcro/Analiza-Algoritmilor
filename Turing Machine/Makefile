CC = gcc
CFLAG = -Wall -Wextra -g
EXE = task1
OBJ = turing_req.o turing_machine.o
DEPS = turing_req.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

build: $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./$(EXE)

.PHONY : clean

clean:
	rm -f *.o $(EXE)

.PHONY: leak

leak:
	valgrind --leak-check=full --track-origins=yes ./$(EXE)