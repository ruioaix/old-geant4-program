
INC += -I /usr/include/Geant4 -I include/
LIBS += -l CLHEP
LIBS += -l G4global -l G4tracking -l G4run -l G4materials -l G4geometry -l G4particles -l G4processes -l G4event -l G4RayTracer -l G4digits_hits
LIBS += -l G4interfaces -l G4intercoms -l G4graphics_reps -l G4vis_management 
LIBS += -l G4OpenGL -l G4modeling -l G4Tree -l G4FR -l G4VRML -l G4visHepRep -l G4GMocren

src := $(wildcard src/*.cc)

interim := $(subst .cc,.o,${src})
CPPFLAGS += -O3 -Wall -Wextra -Wno-long-long -pedantic -ggdb -DG4VIS_USE_OPENGLQT -DG4VIS_USE

all: prog

src/%.o: src/%.cc include/%.hh
	g++ ${CPPFLAGS} ${INC} $< -c -o $@

prog: main.cc ${interim}
	g++ ${CPPFLAGS} ${INC} ${LIBS} $^ -o $@

clean:
	rm -f prog src/*.o


.PHONY: all clean
