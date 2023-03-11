IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

_DEPS = solver.h TTT.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = obj
_OBJ = TTT.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
  
$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	@$(CC) -o ../$@ $^ $(CFLAGS)
