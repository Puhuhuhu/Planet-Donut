# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc geomod.cc gisement.cc robot.cc simulation.cc base.cc message.cc
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

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
projet.o: projet.cc simulation.h
geomod.o: geomod.cc geomod.h
gisement.o: gisement.cc gisement.h message.h geomod.h
robot.o: robot.cc robot.h gisement.h message.h geomod.h
simulation.o: simulation.cc simulation.h base.h gisement.h geomod.h
base.o: base.cc base.h robot.h gisement.h message.h geomod.h
message.o: message.cc message.h
