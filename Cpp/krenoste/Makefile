CXX=g++
CXXFLAGS=-Wall -pedantic -g
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lxml2 -I/usr/include/libxml2
HEAD=$(wildcard src/*.h src/*.hpp)
SRCS=$(wildcard src/*.cpp)
OBJC=$(SRCS:src/%.cpp=build/%.o)

all: compile doc

run-new: compile
	./krenoste examples/newConfig.json

run-load: compile
	./krenoste examples/saveConfig.json

compile: krenoste

krenoste: build/main
	cp $< $@

build/main: $(OBJC)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(LIBS)

doc: Doxyfile $(HEAD)
	doxygen Doxyfile

clean:
	rm -rf krenoste build/ doc/ 2>/dev/null

.PHONY: clean all run