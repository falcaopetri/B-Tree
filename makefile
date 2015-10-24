# B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
# DC - UFSCar - São Carlos - 2015
# Source: http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
CC := gcc
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/btree

SRCEXT := c
SOURCES:=$(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
FILTERED_OBJECTS := $(filter-out $(BUILDDIR)/main.o, $(OBJECTS))
# Descomente essa linha para ativar o modo DEBUG
CFLAGS := #-g -Wall -DDEBUG=1
LIB :=
INC := -I include

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR)/*"; $(RM) -r $(BUILDDIR) $(BINDIR)/*

# Tests
debug: $(TARGET)
	@echo " Lembre-se de habilitar as flags de debug nas CFLAGS...";
	@echo " $(CC) $(CFLAGS) $(FILTERED_OBJECTS) test/debug.c $(INC) $(LIB) -o bin/debug"; $(CC) $(CFLAGS) $(FILTERED_OBJECTS) test/debug.c $(INC) $(LIB) -o bin/debug

.PHONY: clean
