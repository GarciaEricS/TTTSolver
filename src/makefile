IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

_DEPS = solver.h TTT.h CLIPosition.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = obj
_OBJ = TTT.o CLI.o solver.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ODIR_DEBUG = obj-debug
OBJ_DEBUG = $(patsubst %, $(ODIR_DEBUG)/%,$(_OBJ))
  
$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

main: CFLAGS += -Ofast
main: $(OBJ)
	@$(CC) -o ../$@ $^ $(CFLAGS)

clean:
	@rm -f $(ODIR)/*
	@rm -f $(ODIR_DEBUG)/*

$(ODIR_DEBUG)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR_DEBUG)
	@$(CC) -c -o $@ $< $(CFLAGS)

debug: CFLAGS += -g
debug: $(OBJ_DEBUG)
	@$(CC) -o ../$@ $^ $(CFLAGS)
	@gdb --tui ../$@


