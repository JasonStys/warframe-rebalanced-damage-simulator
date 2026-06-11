CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = warframe_damage_simulator
SOURCES = Main.cpp DamageCalculator.cpp Weapon.cpp Enemy.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
