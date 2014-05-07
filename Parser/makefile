# cs251-f11-swiss
# makefile
# Oct 19. 2011

CC=gcc
CFLAGS=
LDFLAGS=
SOURCES=TokenList.c Parser.c Main.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parser

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
