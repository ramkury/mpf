IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g

ODIR= ./obj

LIBS= -lncurses -lgtest -lpthread -lgtest_main
LIBS_C = -ftest-coverage -fprofile-arcs

_DEPS = GraphicalUserInterface.h GrafoOp.h GrafoED.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o GrafoOp.o GrafoED.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o Gerenciador TelaInicial.cpp $(OBJ) $(LIBS)

.PHONY: teste

teste: $(OBJ)
	$(CXX) -o teste testes.cpp $(OBJ) $(CXXFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
