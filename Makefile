.PHONY: clean

FLAGS = -Wall -pedantic-errors -std=c++23
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

SOURCEDIR = src
BUILDDIR = build

EXECUTABLE = tictactoe
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

all: dir $(BUILDDIR)/$(EXECUTABLE)

debug: FLAGS += -DDEBUG -g
debug: clean all

dir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LIBS) $(FLAGS) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*o $(BUILDDIR)/$(EXECUTABLE)