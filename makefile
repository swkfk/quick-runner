CXX := g++
CXXFLAG := -std=c++17
OUT := runner
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,${SRC})

.PHONY: clean

${OUT}: ${OBJ}
	${CXX} ${CXXFLAG} -o $@ ${OBJ}

%.o: %.c
	${CC} ${CFLAG} -c -o $@ $<

clean:
	rm -f *.o ${OUT}

install: ${OUT}
	sudo cp ${OUT} /usr/bin/${OUT}
