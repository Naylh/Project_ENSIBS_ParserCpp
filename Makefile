# options de compilation
CC = g++
CCFLAGS = -g -Wall
LIBS = -lm -lstdc++
INCLUDES =
EXEC_NAME = projet 

# fichiers du projet
SRC = main.cpp sources/parsing/Parser.cpp sources/utils/node/Position.cpp sources/utils/node/Node.cpp sources/utils/analyze/Analyzer.cpp test/TestNode.cpp test/TestParser.cpp test/TestDijkstra.cpp
OBJ = $(SRC:.c=.o)
EXEC = ./build/run.out

# règle initiale
all: $(EXEC_NAME)

# règles de compilation
%.o: %.cpp
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

# règles d'édition de liens
$(EXEC_NAME): $(OBJ)
	$(CC) -o $(EXEC_NAME) $(OBJ) $(LIBS)

# règles supplémentaires
.PHONY: clean mrproper

clean:
	rm -f *.o

mproper:
	rm -f $(EXEC) *.o