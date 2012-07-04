#Student ID s3258798
#Student Name Brad Mccormack
#Subject COSC2140OUA Programming using C++
#Period SP3 2011
CXX = g++
CXXFLAGS = -ansi -Wall -pedantic -gstabs
CXXLDFLAGS =

GTEST_DIR=gtest-1.6.0
GTEST_CXXFLAGS = -I $(GTEST_DIR)/include -I $(GTEST_DIR)
GTEST_CXXLDFLAGS = 

OBJECTS = \
	book.o \
	controller.o\
	item.o\
	model.o\
	music.o\
	shop.o\
	shoppingcart.o\
	utility1.o\
	view.o\


wimmera: wimmera.o deps
	$(CXX) wimmera.o $(OBJECTS)  -o wimmera

wimmera.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o wimmera.o

deps: $(OBJECTS)

book.o: src/book.cpp
	$(CXX) $(CXXFLAGS) -c src/book.cpp


controller.o: src/controller.cpp
	$(CXX) $(CXXFLAGS) -c src/controller.cpp

item.o: src/item.cpp
	$(CXX) $(CXXFLAGS) -c src/item.cpp

model.o: src/model.cpp
	$(CXX) $(CXXFLAGS) -c src/model.cpp

music.o: src/music.cpp
	$(CXX) $(CXXFLAGS) -c src/music.cpp

shop.o: src/shop.cpp
	$(CXX) $(CXXFLAGS) -c src/shop.cpp

shoppingcart.o: src/shoppingcart.cpp
	$(CXX) $(CXXFLAGS) -c src/shoppingcart.cpp

utility1.o: src/utility1.cpp
	$(CXX) $(CXXFLAGS) -c src/utility1.cpp

view.o: src/view.cpp
	$(CXX) $(CXXFLAGS) -c src/view.cpp

clean:
	rm *.o ./wimmera
