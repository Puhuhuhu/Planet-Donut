# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc geomod.cc message_geomod.cc
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
projet.o: projet.cc geomod.h message_geomod.h
geomod.o: geomod.cc geomod.h
message_geomod.o: message_geomod.cc message_geomod.h
