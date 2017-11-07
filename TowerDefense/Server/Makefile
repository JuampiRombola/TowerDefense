CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGET := bin/towerdefenseserver
BUILDDIRS := build/GameModel/Commands build/GameModel/Towers build/GameModel/EnviormentUnits 
BUILDDIRS += build/GameModel/GameNotifications
BUILDDIRS += build/GameModel/Map build/Lobbies build/Notifications
#BUILDDIRS := build/Lobbies
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/GameModel/Commands -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/GameModel/Map -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/GameModel/Towers -type f -name *.$(SRCEXT))
SOURCES += $(shell find src/GameModel/GameNotifications -type f -name *.$(SRCEXT))
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
