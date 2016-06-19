IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g

ODIR= ./obj

LIBS= -g -lncurses
LIBS_T = -lgtest -lpthread -lgtest_main -g -ftest-coverage -fprofile-arcs -lncurses

_DEPS = GraphicalUserInterface.h GrafoOp.h GrafoED.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o GrafoOp.o GrafoED.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) $(CXXFLAGS) -c -o $@ $<  

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o tela TelaInicial.cpp $(OBJ) $(LIBS)

.PHONY: teste

teste: $(OBJ)
	$(CXX) $(LIBS_T) $(CXXFLAGS) -o teste testes.cpp $(OBJ)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
