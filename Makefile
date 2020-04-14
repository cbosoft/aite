CXX = g++
CFLAGS = -g -pg -Wall -Wextra -Werror -std=c++17 -O2

RANDOM = \
				 obj/random/random.o

PLANET = \
				 obj/planet/planet.o \
				 obj/planet/describe.o \
				 obj/planet/generate.o

ELEMENT = \
					obj/element/element.o

HDR = $(shell ls src/**/*.hpp)
OBJ = $(PLANET) $(ELEMENT) $(RANDOM)
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
