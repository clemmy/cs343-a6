CXX = u++
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}

OBJECTS = RNG.o Bank.o BottlingPlant.o config.o Groupoff.o NameServer.o Parent.o Printer.o Student.o Truck.o VendingMachine.o Watcard.o WatcardOffice.o Soda.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = soda

.PHONY : all clean

all : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean :
	rm -f *.d *.o ${EXEC01} ${EXECS} ImplKind ImplType
