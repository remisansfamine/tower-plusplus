
CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

BIN=tower
CXXFLAGS=-Wall -g -O0 -fPIC -I../externals/include
CPPFLAGS=-MMD

ifeq ($(OS),Windows_NT)
LDFLAGS=-L../externals/$(TARGET)/libs
LDLIBS=-lgpdll -lglfw3dll -lgdi32 -lglu32
else
LD_LIBRARY_PATH=../externals/$(TARGET)/bin
LDFLAGS+=-L../externals/$(TARGET)/bin -Wl,-rpath,$(LD_LIBRARY_PATH)
LDLIBS=-lgp -lglfw
endif

OBJS=src/main.o src/bullet.o src/button_manager.o src/button.o src/collisions.o src/enemy.o src/hud.o src/entity_manager.o src/entity.o src/explosive_bullet.o src/explosive_tower.o src/game.o src/healer_enemy.o src/map.o src/maths.o src/resource_manager.o src/shop_button.o src/slowing_bullet.o src/slowing_tower.o src/standard_bullet.o src/standard_tower.o src/strong_enemy.o src/tower_slot.o src/tower.o src/weak_enemy.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean run

all: $(BIN)

-include $(DEPS)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

run: $(BIN)
	PATH=$$PATH:externals/$(TARGET)/bin ./$<

clean:
	rm -f $(OBJS) $(DEPS) $(BIN)
