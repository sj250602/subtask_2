CXX=g++
RM=rm -f

compile:subtask_2.cpp
	$(CXX) subtask_2.cpp -o output -std=c++11 `pkg-config --cflags --libs opencv`
run:subtask_2.cpp
	./output
clear:
	$(RM) output
clear_data:
	$(RM) graph_coor.csv
