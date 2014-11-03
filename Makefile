CC=g++ -g
MCC=$(CC) -c
VPATH=src:headers
SRC=$(wildcard *.cpp ./src/*.cpp)
INCLUDE=-Iheaders
OBJ=$(patsubst %.cpp,%.o,$(notdir $(SRC)))
EXE=main
$(EXE):${OBJ}
	$(CC) $^ -o $(EXE) $(INCLUDE)

%.o:%.cpp
	$(MCC) $< -o $@ $(INCLUDE)

clean:
	rm $(OBJ)

	
