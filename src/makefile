IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR)

ODIR= ./obj

LIBS= -lgtest -lpthread -lgtest_main -g -ftest-coverage -fprofile-arcs

_DEPS = grafo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = grafo.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) $(CXXFLAGS) -c -o $@ $<  

main: $(OBJ)
	$(CXX) $(LIBS) $(CXXFLAGS) -o gerenciador main.cpp $(OBJ) 

.PHONY: teste

teste: $(OBJ)
	$(CXX) $(LIBS) $(CXXFLAGS) -o teste testes.cpp $(OBJ)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
