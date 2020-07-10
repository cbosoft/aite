CXX ?= g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2

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
				 obj/system/system.o \
				 obj/system/id.o \
				 obj/system/generate.o

OBJECT = \
				 obj/object/object.o \
				 obj/object/describe.o \
				 obj/object/planet.o \
				 obj/object/star.o \
				 obj/object/earthlike_planet.o \
				 obj/object/generate.o

COLONY = \
				 obj/colony/colony.o \
				 obj/colony/discover.o \
				 obj/colony/bootstrap.o \
				 obj/colony/update.o \
				 obj/colony/serial.o \
				 obj/colony/exploration.o \
				 obj/colony/describe.o

RESOURCES = \
						obj/resources/resource.o \
						obj/resources/resources.o \
						obj/resources/resource_pool.o \
						obj/resources/processed_resources.o \
						obj/resources/pooled_resource.o

CHEMISTRY = \
					obj/chemistry/element.o \
					obj/chemistry/electrons.o \
					obj/chemistry/chemical_component.o \
					obj/chemistry/table.o

EVENT = \
				obj/event/from_string.o \
				obj/event/new_colony_event.o

FEATURE = \
					obj/feature/feature.o \
					obj/feature/load.o \
					obj/feature/generate.o

ITEM = \
			 obj/item/item.o

HISTORY = \
					obj/history/history.o \
					obj/history/load.o \
					obj/history/generate.o

UTIL = \
			 obj/util/equation.o \
			 obj/util/random.o \
			 obj/util/time.o \
			 obj/util/sqlite.o \
			 obj/util/alphabet.o \
			 obj/util/format.o \
			 obj/util/thesaurus.o \
			 obj/util/path.o \
			 obj/util/file.o \
			 obj/util/socket.o \
			 obj/util/vec.o

CLIENT = \
				 obj/client/main.o \
				 obj/client/args.o \
				 obj/client/help.o \
				 obj/client/reply.o \
				 obj/client/welcome.o \
				 obj/client/client.o

SERVER = \
				 obj/server/server.o \
				 obj/server/main.o \
				 obj/server/listen.o \
				 obj/server/client.o \
				 obj/server/args.o

RESOURCE_EDITOR = \
									obj/devtools/resource_editor/main.o \
									obj/util/sqlite.o

HDR = $(shell ls src/**/*.hpp)
OBJ = $(UNIVERSE) $(GALAXY) $(SYSTEM) $(OBJECT) $(COLONY) $(RESOURCES) $(CHEMISTRY) $(EVENT) $(FEATURE) $(HISTORY) $(UTIL) $(ITEM)
LINK = -lpthread -lsqlite3
DEFS =

## Colours
COL_OBJ = $(shell tput setaf 3)
COL_EXE = $(shell tput setaf 4)
COL_RST = $(shell tput sgr0)
COL_BLD = $(shell tput bold)

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


.PHONY: all options

all: options aite_client aite_server

options:
	@printf "Compiler: $(COL_BLD)$(CXX)$(COL_RST)\n"

aite_client: $(CLIENT) $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(DEFS) $(CLIENT) $(OBJ) -o $@ $(LINK)

aite_server: $(SERVER) $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(DEFS) $(SERVER) $(OBJ) -o $@ $(LINK)

test: obj/main.o $(OBJ) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(DEFS) obj/main.o $(OBJ) -o $@ $(LINK)

resed: $(RESOURCE_EDITOR) $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(DEFS) $(RESOURCE_EDITOR) -o $@ $(LINK)




prof_pdf:
	gprof aite gmon.out > analysis.txt
	gprof2dot -o d.dot analysis.txt
	dot -Tpdf d.dot > prof.pdf


clean:
	rm -rf obj aite_client aite_server
