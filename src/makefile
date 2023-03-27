IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

_DEPS = solver.h TTT.h CLIPosition.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = obj
_OBJ = TTT.o CLI.o solver.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
  
$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@$(CC) -o ../$@ $^ $(CFLAGS)

debug: CFLAGS += -g
debug: $(OBJ)
	$(CC) -o ../$@ $^ $(CFLAGS)

clean:
	@rm $(ODIR)/*
