# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
CXXFILES = projet.cc geomod.cc gisement.cc robot.cc simulation.cc base.cc message.cc gui.cc graphic.cc
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle
	
projet: $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o projet $(LDLIBS)

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h constantes.h gui.h geomod.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
geomod.o: geomod.cc geomod.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
gisement.o: gisement.cc gisement.h geomod.h message.h constantes.h
robot.o: robot.cc robot.h geomod.h gisement.h message.h constantes.h
simulation.o: simulation.cc simulation.h base.h geomod.h robot.h \
 gisement.h constantes.h message.h
base.o: base.cc base.h geomod.h robot.h gisement.h message.h constantes.h
message.o: message.cc message.h
gui.o: gui.cc gui.h simulation.h geomod.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
graphic.o: graphic.cc graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
