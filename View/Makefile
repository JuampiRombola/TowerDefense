CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGET := bin/towerdefense
BUILDDIRS := build/Commands build/Towers build/EnviormentUnits build/Map

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/Commands -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/Map -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/Towers -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11 -g -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline
LIB := -pthread -lm
INC := -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC)-o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIRS)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC)-o $@ "; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; 
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
