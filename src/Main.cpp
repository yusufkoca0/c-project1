#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void part1(std::vector<std::string> p1, const std::string& output);
void part2(std::vector<std::string> p2, const std::string& output);

int main(int argc, const char * argv[]) {
    std::string output = argv[3];
    std::string str;
    std::vector<std::string> part1Info;
    std::vector<std::string> part2Info;

    //reading input1
    std::ifstream in1(argv[1]);
    while (std::getline(in1, str))
    {
        if(!str.empty()) {
            part1Info.push_back(str);
        }
    }
    in1.close();

    //reading input2
    std::ifstream in2(argv[2]);
    while (std::getline(in2, str))
    {
        if(!str.empty()) {
            part2Info.push_back(str);
        }
    }
    in2.close();

    //clearing output file
    std::ofstream ofs;
    ofs.open(argv[3], std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    part1(part1Info, output);
    part2(part2Info, output);
}

//part1 start
//prints the part1 result
void print1(std::vector<std::vector<int>>& grid, const std::string& output){

    std::ofstream ofs;
    ofs.open(output, std::fstream::app);
    ofs << "PART 1:\n";
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid.size()-1; ++j) {
            ofs << grid.at(i).at(j) << " ";
        }
        ofs << grid.at(i).at(grid.size()-1) << "\n";
    }
    ofs << "\n";
    ofs.close();
}

// check functions to creat links
bool checkUp(std::vector<std::vector<int>>& grid, int x, int y, int v){
    if(x != 0){
        return grid.at(x-1).at(y) == v;

    } else {return false;}
}
bool checkDown(std::vector<std::vector<int>>& grid, int x, int y, int v){
    if(x != grid.size()-1){
        return grid.at(x+1).at(y) == v;

    } else {return false;}
}
bool checkRight(std::vector<std::vector<int>>& grid, int x, int y, int v){
    if(y != grid.size()-1){
        return grid.at(x).at(y+1) == v;

    } else {return false;}
}
bool checkLeft(std::vector<std::vector<int>>& grid, int x, int y, int v){
    if(y != 0){
        return grid.at(x).at(y-1) == v;

    } else {return false;}
}

//function that pushes a balloon to the grid, if it constructs a link with 3 or more balloons it also handles that situation
void pushBalloon(std::vector<std::vector<int>>& grid, std::vector<int>& balloon){
    std::vector<std::vector<int>> link(9, std::vector<int>(2));
    int counter = 0;

    //checks if there is a link and increases the counter if there is a link
    if (checkUp(grid, balloon.at(1), balloon.at(2), balloon.at(0))){
        link.at(counter).at(0) = balloon.at(1)-1;
        link.at(counter).at(1) = balloon.at(2);

        counter++;
        if (checkUp(grid, balloon.at(1)-1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-2;
            link.at(counter).at(1) = balloon.at(2);
            counter++;
        }
        if (checkRight(grid, balloon.at(1)-1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-1;
            link.at(counter).at(1) = balloon.at(2)+1;
            counter++;
        }
        if (checkLeft(grid, balloon.at(1)-1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-1;
            link.at(counter).at(1) = balloon.at(2)-1;
            counter++;
        }
    }
    if (checkDown(grid, balloon.at(1), balloon.at(2), balloon.at(0))){
        link.at(counter).at(0) = balloon.at(1)+1;
        link.at(counter).at(1) = balloon.at(2);
        counter++;
        if (checkDown(grid, balloon.at(1)+1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)+2;
            link.at(counter).at(1) = balloon.at(2);
            counter++;

        }
        if (checkRight(grid, balloon.at(1)+1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)+1;
            link.at(counter).at(1) = balloon.at(2)+1;
            counter++;

        }
        if (checkLeft(grid, balloon.at(1)+1, balloon.at(2), balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-1;
            link.at(counter).at(1) = balloon.at(2)-1;
            counter++;

        }
    }
    if (checkRight(grid, balloon.at(1), balloon.at(2), balloon.at(0))){
        link.at(counter).at(0) = balloon.at(1);
        link.at(counter).at(1) = balloon.at(2)+1;

        counter++;
        if (checkUp(grid, balloon.at(1), balloon.at(2)+1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-1;
            link.at(counter).at(1) = balloon.at(2)+1;
            counter++;

        }
        if (checkRight(grid, balloon.at(1), balloon.at(2)+1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1);
            link.at(counter).at(1) = balloon.at(2)+2;
            counter++;

        }
        if (checkDown(grid, balloon.at(1), balloon.at(2)+1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)+1;
            link.at(counter).at(1) = balloon.at(2)+1;
            counter++;

        }
    }
    if (checkLeft(grid, balloon.at(1), balloon.at(2), balloon.at(0))){
        link.at(counter).at(0) = balloon.at(1);
        link.at(counter).at(1) = balloon.at(2)-1;
        counter++;
        if (checkUp(grid, balloon.at(1), balloon.at(2)-1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)-1;
            link.at(counter).at(1) = balloon.at(2)-1;
            counter++;

        }
        if (checkDown(grid, balloon.at(1), balloon.at(2)-1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1)+1;
            link.at(counter).at(1) = balloon.at(2)-1;
            counter++;

        }
        if (checkLeft(grid, balloon.at(1), balloon.at(2)-1, balloon.at(0))){
            link.at(counter).at(0) = balloon.at(1);
            link.at(counter).at(1) = balloon.at(2)-2;
            counter++;

        }
    }

    //if counter is greater than 2 it means we need to combine balloons, this part handles combining part
    if (counter >= 2){
        for (int i = 0; i < counter; ++i) {
            grid.at(link.at(i).at(0)).at(link.at(i).at(1)) = 0;
        }
        link.clear();
        balloon.at(0)++;
        //after combining it calls itself with a baloon one value higher
        pushBalloon(grid, balloon);
    }
    // if link is less than 3 balloons it places the balloon
    else{
        grid.at(balloon.at(1)).at(balloon.at(2)) = balloon.at(0);
        link.clear();
    }

}

//function tht handles the part1
void part1(std::vector<std::string> p1, const std::string& output){

    //creating grid start
    std::vector<std::vector<int>> grid1(std::stoi(p1.at(0)), std::vector<int>(std::stoi(p1.at(0))));
    for (int i = 0; i < std::stoi(p1.at(0)); ++i) {
        for (int j = 0; j < std::stoi(p1.at(0)); ++j) {
            grid1.at(i).at(j) = 0;
        }
    }
    //creating grid end

    //creating balloons start
    std::vector<std::string> balloonstr;
    std::vector<int> balloon;

    for (int i = 1; i < p1.size(); ++i) {
        std::istringstream iss(p1.at(i));

        while (iss){
            std::string subs;
            iss >> subs;
            balloonstr.push_back(subs);
        }

        balloon.push_back(std::stoi(balloonstr.at(0)));
        balloon.push_back(std::stoi(balloonstr.at(1)));
        balloon.push_back(std::stoi(balloonstr.at(2)));
        //crating balloons end

        pushBalloon(grid1, balloon);
        balloonstr.clear();
        balloon.clear();
    }
    print1(grid1, output);
}
//part1 ends

//part2 start
//prints the part2 result
void print2(std::vector<std::vector<int>>& grid, const std::string& output, int score){
    std::ofstream ofs;
    ofs.open(output, std::fstream::app);
    ofs << "PART 2:\n";
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid.size()-1; ++j) {
            ofs << grid.at(i).at(j) << " ";
        }
        ofs << grid.at(i).at(grid.size()-1) << "\n";
    }
    ofs << "Final Point: " << score << "p";
    ofs.close();
}

//function that pops the balloons and returns the score for each pop operation
int popBalloon(std::vector<std::vector<int>>& grid, std::vector<int>& bomb){

    int value = grid.at(bomb.at(0)).at(bomb.at(1));
    int score = 0;

    for (int i = 0; i < grid.size(); ++i) {

        //pops horizontal
        if (grid.at(i).at(bomb.at(1)) == value){
            grid.at(i).at(bomb.at(1)) = 0;
            score += value;
        }

        for (int j = 0; j < grid.size(); ++j) {

            //pops vertical
            if (grid.at(bomb.at(0)).at(j) == value){
                grid.at(bomb.at(0)).at(j) = 0;
                score += value;
            }

            //pops diagonal
            if ((i-bomb.at(0) == j-bomb.at(1) || i-bomb.at(0) == -(j-bomb.at(1))) && grid.at(i).at(j) == value){
                grid.at(i).at(j) = 0;
                score += value;
            }
        }
    }
    return score;
}

//function tht handles the part2
void part2(std::vector<std::string> p2, const std::string& output){
    int score = 0;

    //creating grid start
    std::vector<std::vector<int>> grid2(std::stoi(p2.at(0)), std::vector<int>(std::stoi(p2.at(0))));
    std::vector<std::string> valuestr;

    for (int i = 1; i < std::stoi(p2.at(0))+1; ++i) {
        std::istringstream iss(p2.at(i));
        while (iss) {
            std::string subs;
            iss >> subs;
            valuestr.push_back(subs);
        }
        for (int j = 0; j < grid2.size(); ++j) {
            grid2.at(i-1).at(j) = std::stoi(valuestr.at(j));
        }
        valuestr.clear();
    }
    //creating grid end


    //creating bombs start
    std::vector<std::string> bombstr;
    std::vector<int> bomb;

    for (int i = std::stoi(p2.at(0))+1; i < p2.size(); ++i) {
        std::istringstream iss(p2.at(i));

        while (iss) {
            std::string subs;
            iss >> subs;
            bombstr.push_back(subs);
        }
        bomb.push_back(std::stoi(bombstr.at(0)));
        bomb.push_back(std::stoi(bombstr.at(1)));
        //crating bombs end

        score += popBalloon(grid2, bomb);
        bombstr.clear();
        bomb.clear();
    }
    print2(grid2,output, score);
}
//part2 end



