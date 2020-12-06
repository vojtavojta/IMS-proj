test: src/StatisticsOutput.cpp src/commonSimulationQueue.cpp src/eventClass.cpp src/facilityClass.cpp src/generatedNumbersStatistics.cpp src/identifiable.cpp main.cpp src/numberGenerator.cpp src/priorityQueue.cpp src/resourcePromiseClass.cpp src/simSimulatorClass.cpp src/simulationStatistics.cpp
#	g++ -O3 -Wshadow -pedantic -Wall -Wextra -Wabi -std=c++17 *.cpp -o test
	g++ -O3 -std=c++17 src/StatisticsOutput.cpp src/commonSimulationQueue.cpp src/eventClass.cpp src/facilityClass.cpp src/generatedNumbersStatistics.cpp src/identifiable.cpp main.cpp src/numberGenerator.cpp src/priorityQueue.cpp src/resourcePromiseClass.cpp src/simSimulatorClass.cpp src/simulationStatistics.cpp -o test

run: test
	./test
