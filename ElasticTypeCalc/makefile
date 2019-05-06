CC=g++
CFLAGS=-c -Wall --std=c++11
LDFLAGS=
SOURCES=pch.cpp Calc.cpp ElasticType.cpp TypedNum.cpp CalcNode.cpp CalcFncVarController.cpp ElasticTypeCalc.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ElasticTypeCalc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm $(EXECUTABLE) $(OBJECTS)

run: $(EXECUTABLE)
	cp $(EXECUTABLE) ~/
	chmod +x ~/$(EXECUTABLE)
	~/$(EXECUTABLE)
    
    
    
    