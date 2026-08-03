CXX = g++
CXXFLAGS = -std=c++17 -O2

TARGET = assignment1

SRC = ~/CS509_CS1009/assignment_01/src/gemm_simple.cpp \
      ~/CS509_CS1009/assignment_01/src/gemm_blocking.cpp \
      ~/CS509_CS1009/assignment_01/src/csr.cpp \
      ~/CS509_CS1009/assignment_01/src/graph_reader.cpp \
      ~/CS509_CS1009/assignment_01/driver/driver.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
