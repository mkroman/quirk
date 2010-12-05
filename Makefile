CXX = g++
CXXFLAGS = -Wall -g -I/usr/local/include -I/usr/include
LDFLAGS = -L/usr/local/lib -L/usr/lib -lcurl -lcurlpp
SOURCES = src/Quirk.cpp src/Grooveshark/Connection.cpp src/Grooveshark/Client.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = bin/quirk

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS) -o $@
