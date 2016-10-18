# Makefile Generique

EXT = c
CXX = gcc
EXEC = exe

CXXFLAGS = -Wall -W -Werror
LDFLAGS = 

OBJDIR = obj
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -g -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	$(CXX) -g -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJDIR)/*.o
	rm -f $(EXEC)

install: $(EXEC)
	cp $(EXEC) /usr/bin/
