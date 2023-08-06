CXX := g++
CXXFLAG := -std=c++17
SRC := $(wildcard *.cpp)

platform_linux := linux
platform_win := win

PLATFORM = linux

ifeq ($(PLATFORM), $(platform_win))
	OUT = runner.exe
	OBJ = $(patsubst %.cpp,%.win,${SRC})
else
	OUT = runner
	OBJ = $(patsubst %.cpp,%.o,${SRC})
endif

.PHONY: clean

${OUT}: ${OBJ}
	${CXX} ${CXXFLAG} -o $@ ${OBJ}

%.o: %.cpp
	${CXX} ${CXXFLAG} -c -o $@ $<

%.win: %.cpp
	${CXX} ${CXXFLAG} -c -o $@ $<

clean:
ifeq ($(PLATFORM), $(platform_win))
	del /F *.win ${OUT}
else
	rm -f *.o ${OUT}
endif

install: ${OUT}
ifeq ($(PLATFORM), $(platform_win))
	@echo Unsupported target on Windows!
else
	sudo cp ${OUT} /usr/bin/${OUT}
endif

