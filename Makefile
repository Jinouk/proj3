all: project3.cpp Shapes.cpp function.cpp matrix.c project3

Sources		 = project3.cpp Shapes.cpp function.cpp matrix.c
Objects		 = $(Sources:.cpp,c=.o)

.cpp.o:
	g++ -c -Wall $< -o $@

project3: project3.o Shapes.o function.o matrix.o
	g++ $(Objects) -o $@

clean: 
	-rm *.o
	-rm project3