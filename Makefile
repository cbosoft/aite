CXX = g++
CFLAGS = -g -pg -Wall -Wextra -Werror -std=c++17 -O2

UNIVERSE = \
					 obj/universe/universe.o \
					 obj/universe/galaxy.o \
					 obj/universe/run.o \
					 obj/universe/event.o \
					 obj/universe/colony.o

GALAXY = \
				 obj/galaxy/galaxy.o \
				 obj/galaxy/system.o

SYSTEM = \
				 obj/system/system.o

PLANET = \
				 obj/planet/planet.o \
				 obj/planet/describe.o \
				 obj/planet/generate.o

COLONY = \
				 obj/colony/colony.o \
				 obj/colony/discover.o \
				 obj/colony/bootstrap.o \
				 obj/colony/update.o \
				 obj/colony/describe.o

CHEMISTRY = \
					obj/chemistry/element.o \
					obj/chemistry/distribute.o \
					obj/chemistry/electrons.o \
					obj/chemistry/table.o

EVENT = \
				obj/event/event.o \
				obj/event/from_string.o \
				obj/event/new_colony_event.o

FEATURE = \
					obj/feature/feature.o \
					obj/feature/generate.o

UTIL = \
			 obj/util/random.o \
			 obj/util/time.o \
			 obj/util/alphabet.o \
			 obj/util/thesaurus.o \
			 obj/util/vec.o

CLIENT = \
				 obj/client/main.o \
				 obj/client/args.o \
				 obj/client/connect.o

SERVER = \
				 obj/server/server.o \
				 obj/server/main.o \
				 obj/server/listen.o \
				 obj/server/client.o \
				 obj/server/args.o

HDR = $(shell ls src/**/*.hpp)
OBJ = $(UNIVERSE) $(GALAXY) $(SYSTEM) $(PLANET) $(COLONY) $(CHEMISTRY) $(EVENT) $(FEATURE) $(UTIL)
LINK = -lpthread
DEFS =

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@echo -e "\u001b[33mASSEMBLING OBJECT $@\u001b[0m"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


.PHONY: all

all: aite_client aite_server

aite_client: $(CLIENT) $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) $(CLIENT) $(OBJ) -o $@ $(LINK)

aite_server: $(SERVER) $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) $(SERVER) $(OBJ) -o $@ $(LINK)

test: obj/main.o $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) obj/main.o $(OBJ) -o $@ $(LINK)




prof_pdf:
	gprof aite gmon.out > analysis.txt
	gprof2dot -o d.dot analysis.txt
	dot -Tpdf d.dot > prof.pdf


clean:
	rm -rf obj aite_client aite_server
