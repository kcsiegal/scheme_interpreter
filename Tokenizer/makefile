# cs251-f11-swiss
# makefile
# Oct 19. 2011

CC=gcc
CFLAGS=
LDFLAGS=
SOURCES=TokenList.c TokenList.h Main.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tokenizer

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
