how to compile and run:

g++ -o Main *.cpp -std=c++11
./Main input1.txt input2.txt output.txt

input1.txt: First line decides how big the nxn grid is, each line after that has 3 numbers separated with a space. First number means the value of the balloon, second and third are the coordinates.

input2.txt: First line decides how big the nxn grid is, then the next n lines gives the grid. Other lines gives the coordinates for the bomb.

Part1: using the input1.txt program places balloons to the grid. if 3 ballons of the same value touches each other, all 3 disappears and a balloon of +1 values put in the last placed balloon.

Part2: a bomb splashes all the ballons with the same value its put in, in the same horizontal, vertical and diagonal planes.
