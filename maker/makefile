#------------------------------------------------------
# Makefile for C/C++ Program
#------------------------------------------------------

TARGET=maker
#------------------------------------------------------
# Default Parameters
#------------------------------------------------------

CC=mpic++
CPPFLAGS=-O3 
LDFLAGS=

#------------------------------------------------------
# Compile Option
#------------------------------------------------------

-include makefile.opt

#------------------------------------------------------
# Definition
#------------------------------------------------------

.SUFFIXES: .c .cc .h. .o

#---
# Source Files
#---

SRC=$(shell ls *.cc)
HED=$(shell ls *.h)
OBJ=$(SRC:.cc=.o)

#------------------------------------------------------
# rules
#------------------------------------------------------

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

.cc.o:
	$(CC) $(CPPFLAGS) -c $< 

.PHONY: clean dep

dep:
	g++ -MM -MG $(SRC) >makefile.depend

makefile.depend: 
	g++ -MM -MG $(SRC) >makefile.depend

clean:
	rm -f $(TARGET) $(OBJ) gmon.*.out gmon.out

tar:
	tar cvzf $(TARGET).tar.gz $(SRC) $(HED) makefile

#--------------------------------------------------
-include makefile.depend
