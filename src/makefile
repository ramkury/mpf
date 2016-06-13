IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR)

ODIR= ./obj

LIBS= -lncurses

_DEPS = GraphicalUserInterface.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) $(CXXFLAGS) -c -o $@ $<  

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o tela TelaInicial.cpp $(OBJ) $(LIBS)

.PHONY: teste

teste: $(OBJ)
	$(CXX) $(CXXFLAGS) -o teste testes.cpp $(OBJ) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
