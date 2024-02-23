CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -MMD -MP -I/opt/homebrew/opt/libomp/include -Xpreprocessor -fopenmp
LDFLAGS = -L/opt/homebrew/lib -L/opt/homebrew/opt/libomp/lib 
LDLIBS = -lpng -Xlinker -lomp

SRC = mandelbrot.cpp complex_numbers.cpp color.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

mandelbrot: $(OBJ)
	$(CXX) $(OBJ) -o mandelbrot $(LDFLAGS) $(LDLIBS)
	rm -f $(OBJ) $(DEP)
	
-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) mandelbrot $(DEP)

.PHONY: clean


