CC = g++
LFLAG = -lwiringPi -lpthread
BLDDIR = .
INCDIR = $(BLDDIR)/inc
SRCDIR = $(BLDDIR)/src
OBJDIR = $(BLDDIR)/obj
BINDIR = $(BLDDIR)/bin
CFLAGS = -Wno-psabi -c -Wall -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
EXE = bin/bin

all: clean $(EXE) 
    
$(EXE): $(OBJ) 
	$(CC) $(OBJDIR)/*.o -o $@ $(LFLAG)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ $(LFLAG)

clean:
	-rm -f $(OBJDIR)/*.o $(EXE)

run-terreo: 
	./$(BINDIR)/bin configuracao_andar_terreo.json

run: 
	./$(BINDIR)/bin $(FILENAME)

