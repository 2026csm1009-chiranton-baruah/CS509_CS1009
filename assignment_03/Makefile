CXX = g++

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

SRC_DIR = src
INC_DIR = include
DRIVER_DIR = driver

TARGET = $(DRIVER_DIR)/driver

SOURCES = \
	$(SRC_DIR)/mst.cpp \
	$(DRIVER_DIR)/driver.cpp

HEADERS = \
	$(INC_DIR)/csr_graph.hpp \
	$(INC_DIR)/mst.hpp

REPORT = report.txt

TESTS = \
	tests/mst_10.txt \
	tests/mst_100.txt \
	tests/mst_10000.txt \
	tests/mst_50000.txt \
	tests/mst_100000.txt

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) tests/mst_10.txt

report: $(TARGET)
	@echo "CS509 Assignment 3 - MST Report" > $(REPORT)
	@echo "================================" >> $(REPORT)
	@echo "" >> $(REPORT)
	@for test in $(TESTS); do \
		echo "========================================" >> $(REPORT); \
		echo "Test: $$test" >> $(REPORT); \
		echo "========================================" >> $(REPORT); \
		./$(TARGET) $$test >> $(REPORT); \
		echo "" >> $(REPORT); \
	done
	@echo "Report generated: $(REPORT)"

