# Source: http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
# TODO tester

CC := gcc
SRCDIR := src
BUILDDIR := build
TARGET := bin/btree

SRCEXT := c
SOURCES:=$(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -DDEBUG=1
LIB :=
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	# $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
