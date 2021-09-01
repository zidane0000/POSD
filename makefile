.PHONY: dirs clean

SRC = src/compound_shape.h src/ellipse.h src/iterator.h src/null_iterator.h src/rectangle.h \
 			src/shape_iterator.h src/sort.h src/terminal.h src/triangle.h src/two_dimensional_coordinate.h \
			src/utility.h src/area_visitor.h src/info_visitor.h src/visitor.h src/shape_builder.h \
			src/scanner.h src/filter.h src/shape_filter.h src/shape_setter.h

TEST = test/ut_compound_shape.h test/ut_ellipse.h test/ut_iterator.h test/ut_rectangle.h \
 			 test/ut_sort.h test/ut_terminal.h test/ut_triangle.h test/ut_utility.h test/ut_visitor.h \
			 test/ut_shape_builder.h test/ut_scanner.h test/ut_filter.h

OBJ = obj/shape.o

all: dirs ut_main

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(OBJ)
	g++ -std=c++11 -Wfatal-errors test/ut_main.cpp obj/shape.o -o bin/ut_main -lgtest -lpthread
	# g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp $(OBJ) -o bin/ut_main -lgtest -pthread
	# g++ -std=c++17 -std=c++11 src/main.cpp -o bin/geo

obj/shape.o: src/shape.h src/shape.cpp
	g++ -std=c++11 -Wfatal-errors -c src/shape.cpp -o obj/shape.o
	# g++ -std=c++11 -Wfatal-errors -Wall -c src/shape.cpp -o obj/shape.o

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
