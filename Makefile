CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = main.o controller.o academic.o block.o board.o collect.o coop.o dctims.o goose.o gotims.o gym.o needles.o player.o residence.o slc.o tuition.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = bb7k

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
