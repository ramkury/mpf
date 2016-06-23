IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g

ODIR= ./obj

LIBS= -lncurses
LIBS_T = -lgtest -lpthread -lgtest_main
LIBS_C = -ftest-coverage -fprofile-arcs

_DEPS = GraphicalUserInterface.h GrafoOp.h GrafoED.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o GrafoOp.o GrafoED.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS) $(LIBS_T)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o tela TelaInicial.cpp $(OBJ) $(LIBS)

.PHONY: teste

teste: $(OBJ)
	$(CXX) -o teste testes.cpp $(OBJ) $(CXXFLAGS) $(LIBS) $(LIBS_T) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
