LIBRARY_ARCH_FOLDER := x86_64-w64-mingw32

INCLUDE_DIRS := -I$(dirs $(wildcard src/**/)) \
				-Isrc/ \
				-Idep/SDL2/$(LIBRARY_ARCH_FOLDER)/include \
				-Idep/SDL2/$(LIBRARY_ARCH_FOLDER)/include/SDL2 \
				-Idep/SDL2_image/$(LIBRARY_ARCH_FOLDER)/include \
				-Idep/SDL2_ttf/$(LIBRARY_ARCH_FOLDER)/include \
				-Idep/SDL2_mixer/$(LIBRARY_ARCH_FOLDER)/include \

LIBRARY_DIRS := -Ldep/SDL2/$(LIBRARY_ARCH_FOLDER)/lib \
				-Ldep/SDL2_image/$(LIBRARY_ARCH_FOLDER)/lib \
				-Ldep/SDL2_ttf/$(LIBRARY_ARCH_FOLDER)/lib \
				-Ldep/SDL2_mixer/$(LIBRARY_ARCH_FOLDER)/lib 

LIBRARY_FILES := -lmingw32 \
				 -lSDL2main \
				 -lSDL2 \
				 -lSDL2_image \
				 -lSDL2_ttf \
				 -lSDL2_mixer

CXX := c++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -O2 \
$(INCLUDE_DIRS) $(LIBRARY_DIRS) $(LIBRARY_FILES)

SOURCE_FILES := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
HEADER_FILES := $(wildcard src/*.cpp) $(wildcard src/**/*.h)
OBJECT_FILES := $(addprefix obj/, $(notdir $(SOURCE_FILES:.cpp=.o)))

all: $(OBJECT_FILES) main.exe

main.exe: $(OBJ_FILES) $(SOURCE_FILES) $(H_FILES) 
	$(CXX) $^ $(CXXFLAGS) -o $(addprefix bin/, $@) 

$(OBJECT_FILES): $(SOURCE_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm bin/main.exe
