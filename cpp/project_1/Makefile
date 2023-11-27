.PHONY: all clean

# Variables
CXX = g++
EXEC = .app
DIR = build
MAKE_DIR = mkdir -p
RM_RF = rm -rf

# Entry point
all: ${DIR} .app

# Utils
clean:
	${RM_RF} ${DIR}

# Directories
${DIR}:
	${MAKE_DIR} ${DIR}

# Executables

$(EXEC): $(DIR)/main.o $(DIR)/Menu.o $(DIR)/MenuContext.o $(DIR)/StorableUnit.o $(DIR)/Utils.o $(DIR)/Match.o $(DIR)/Player.o $(DIR)/PlayerGoal.o $(DIR)/Team.o $(DIR)/TeamPlayer.o $(DIR)/TeamStats.o
	$(CXX) -o $@ $^

$(DIR)/main.o: main.cpp
	$(CXX) -o $@ -c $^

$(DIR)/Menu.o: util/Menu.cpp util/Menu.h
	$(CXX) -o $@ -c $<

$(DIR)/MenuContext.o: util/MenuContext.cpp util/MenuContext.h
	$(CXX) -o $@ -c $<

$(DIR)/StorableUnit.o: util/StorableUnit.cpp util/StorableUnit.h
	$(CXX) -o $@ -c $<

$(DIR)/Utils.o: util/Utils.cpp util/Utils.h
	$(CXX) -o $@ -c $<

$(DIR)/Match.o: Match.cpp Match.h
	$(CXX) -o $@ -c $<

$(DIR)/Player.o: Player.cpp Player.h
	$(CXX) -o $@ -c $<

$(DIR)/PlayerGoal.o: PlayerGoal.cpp PlayerGoal.h
	$(CXX) -o $@ -c $<

$(DIR)/Team.o: Team.cpp Team.h
	$(CXX) -o $@ -c $<

$(DIR)/TeamPlayer.o: TeamPlayer.cpp TeamPlayer.h
	$(CXX) -o $@ -c $<

$(DIR)/TeamStats.o: TeamStats.cpp TeamStats.h
	$(CXX) -o $@ -c $<