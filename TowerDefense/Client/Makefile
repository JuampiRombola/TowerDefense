CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGET := bin/towerdefenseclient
BUILDDIRS := build/GUINotifications build/Lobbies build/NetCommands


SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/NetCommands -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/GUINotifications -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/Lobbies -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11 -g -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline
LIB := -pthread -lm -lyaml-cpp
INC := -L/usr/local/lib -Iinclude

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
