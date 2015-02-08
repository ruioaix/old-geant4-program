
INC += -I /usr/include/geant4 -I include/
LIBS += -l CLHEP
LIBS += -l G4global -l G4tracking -l G4run -l G4materials -l G4geometry -l G4particles -l G4processes -l G4event -l G4RayTracer -l G4digits_hits
LIBS += -l G4interfaces -l G4intercoms -l G4graphics_reps -l G4vis_management -l G4OpenGL
#LIBS += $(shell geant4-config --libs-without-gui)
#LIBS += -lG4interfaces -lG4persistency -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global
#LIBS += -lG4digits_hits -lG4error_propagation -lG4event -lG4FR -lG4geometry -lG4gl2ps -lG4global -lG4GMocren -lG4graphics_reps -lG4intercoms -lG4interfaces -lG4materials -lG4modeling -lG4OpenGL -lG4parmodels -lG4particles -lG4persistency -lG4physicslists -lG4processes -lG4RayTracer -lG4readout -lG4run -lG4tracking -lG4track -lG4Tree -lG4visHepRep -lG4vis_management -lG4visXXX -lG4VRML

src := src/NXChamberParameterisation.cc src/NXEventAction.cc src/NXHit.cc src/NXMagneticField.cc src/NXPhysicsList.cc src/NXPrimaryGeneratorAction.cc src/NXRunAction.cc src/NXSensitiveDetector.cc src/NXSteppingAction.cc src/NXSteppingVerbose.cc src/NXUIMessenger.cc src/NXUserDetectorConstruction.cc
inc := include/NXChamberParameterisation.hh include/NXEventAction.hh include/NXHit.hh include/NXMagneticField.hh include/NXPhysicsList.hh include/NXPrimaryGeneratorAction.hh include/NXRunAction.hh include/NXSensitiveDetector.hh include/NXSteppingAction.hh include/NXSteppingVerbose.hh include/NXUIMessenger.hh include/NXUserDetectorConstruction.hh

interim := $(subst .cc,.o,${src})
#CPPFLAGS += -Wall -Wextra -pedantic

all: nipXray

src/%.o: src/%.cc include/%.hh
	g++ ${CPPFLAGS} ${INC} $< -c -o $@

nipXray: nipXray.cc ${interim}
	g++ ${CPPFLAGS} ${INC} ${LIBS} $^ -o $@

clean:
	rm nipXray src/*.o

#nipXray: nipXray.cc ${src} ${inc}
#	g++ ${libs} -I /usr/include/geant4 -I include/ nipXray.cc ${src}

.PHONY: all clean