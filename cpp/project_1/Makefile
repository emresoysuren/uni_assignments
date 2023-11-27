.PHONY: all clean

# Variables
CXX = g++
EXEC = .app

# Entry point
all: .app

# Utils
clean:
	rm *.o

# Executables

$(EXEC): main.o Menu.o MenuContext.o StorableUnit.o Utils.o Match.o Player.o PlayerGoal.o Team.o TeamPlayer.o TeamStats.o
	$(CXX) -o $@ $^
	make clean

main.o: main.cpp
	$(CXX) -c $^

Menu.o: util/Menu.cpp util/Menu.h
	$(CXX) -c $<

MenuContext.o: util/MenuContext.cpp util/MenuContext.h
	$(CXX) -c $<

StorableUnit.o: util/StorableUnit.cpp util/StorableUnit.h
	$(CXX) -c $<

Utils.o: util/Utils.cpp util/Utils.h
	$(CXX) -c $<

Match.o: Match.cpp Match.h
	$(CXX) -c $<

Player.o: Player.cpp Player.h
	$(CXX) -c $<

PlayerGoal.o: PlayerGoal.cpp PlayerGoal.h
	$(CXX) -c $<

Team.o: Team.cpp Team.h
	$(CXX) -c $<

TeamPlayer.o: TeamPlayer.cpp TeamPlayer.h
	$(CXX) -c $<

TeamStats.o: TeamStats.cpp TeamStats.h
	$(CXX) -c $<