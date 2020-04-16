CXX = g++
CFLAGS = -g -pg -Wall -Wextra -Werror -std=c++17 -O2

UNIVERSE = \
					 obj/universe/universe.o \
					 obj/universe/galaxy.o \
					 obj/universe/colony.o

GALAXY = \
				 obj/galaxy/galaxy.o \
				 obj/galaxy/introduce.o

SYSTEM = \
				 obj/system/system.o \
				 obj/system/introduce.o

PLANET = \
				 obj/planet/planet.o \
				 obj/planet/describe.o \
				 obj/planet/generate.o

COLONY = \
				 obj/colony/colony.o \
				 obj/colony/discover.o \
				 obj/colony/describe.o

ELEMENT = \
					obj/element/element.o \
					obj/element/distribute.o \
					obj/element/table.o

UTIL = \
			 obj/util/random.o \
			 obj/util/vec.o

HDR = $(shell ls src/**/*.hpp)
OBJ = $(UNIVERSE) $(GALAXY) $(SYSTEM) $(PLANET) $(COLONY) $(ELEMENT) $(UTIL)
LINK =
DEFS =

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@echo -e "\u001b[33mASSEMBLING OBJECT $@\u001b[0m"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


obj/test/%.o: src/test/%.cpp $(HDR)
	@echo -e "\u001b[33mASSEMBLING OBJECT $@\u001b[0m"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


aite: obj/main.o $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) obj/main.o $(OBJ) -o aite $(LINK)


tests: src/test/main.cpp $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) src/test/main.cpp $(OBJ) -o $@ $(LINK)


prof_pdf:
	gprof aite gmon.out > analysis.txt
	gprof2dot -o d.dot analysis.txt
	dot -Tpdf d.dot > prof.pdf


clean:
	rm -rf obj aite tests
