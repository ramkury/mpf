IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR)

ODIR= ./obj

LIBS= -g -lncurses
LIBS_T = -lgtest -lpthread -lgtest_main -g -ftest-coverage -fprofile-arcs -lncurses

_DEPS = GrafoED.h GrafoOp.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GrafoED.o GrafoOp.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) $(CXXFLAGS) -c -o $@ $<  

main: $(OBJ)
	$(CXX) $(LIBS) $(CXXFLAGS) -o gerenciador main.cpp $(OBJ) 

.PHONY: teste

teste: $(OBJ)
	$(CXX) $(LIBS_T) $(CXXFLAGS) -o teste testes.cpp $(OBJ)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
