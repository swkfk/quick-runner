CXX := g++
CXXFLAG := -std=c++17
OUT := runner
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,${SRC})

.PHONY: clean

${OUT}: ${OBJ}
	${CXX} ${CXXFLAG} -o $@ ${OBJ}

%.o: %.cpp
	${CXX} ${CXXFLAG} -c -o $@ $<

clean:
	rm -f *.o *.out ${OUT}

install: ${OUT}
	sudo cp ${OUT} /usr/bin/${OUT}
