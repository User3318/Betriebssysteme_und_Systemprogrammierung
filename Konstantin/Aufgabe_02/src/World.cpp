#include "World.h"

#include "Field.h"

#include <iostream>

const std::string World::add = "add";
const std::string World::cube = "cube";
const std::string World::pyramid = "pyramid";
const std::string World::move = "move";
const std::string World::exit = "exit";

World::World(int length, int width)
{
    this->length = length;
    this->width = width;
    this->field = new Field(this->length, this->width);
    this->running = true;

    this->inputThread = new std::thread(&World::receiveConsoleInput, this);
}

World::~World()
{
    delete field;
    delete inputThread;
}

void World::executeAdd(const std::string& type, int x, int y){
    if (type == cube) {
        int retId = field->Field::addCubeBlock(x, y);
        if (retId == -1) {
            std::cout << "The cube could not be added!\n" << std::endl;
        } else {
            std::cout << "ID of the added cube: " << std::to_string(retId) << std::endl;
        }
    }else{
        int retId = field->Field::addPyramidBlock(x, y);
        if (retId == -1){
            std::cout << "The pyramid could not be added!\n" << std::endl;
        }else{
            std::cout << "ID of the added pyramid: " << std::to_string(retId) << std::endl;
        }
    }
}

void World::executeMove(int id, int x, int y){
    bool successful = field->Field::moveBlock(id, x, y);
    if (successful){
        std::cout << "Moving was successful!\n" << std::endl;
    }else{
        std::cout << "Moving failed!\n" << std::endl;
    }
}

bool World::onlyDigits(std::string &coordinates){
    return coordinates.find_first_not_of("0123456789") == std::string::npos;
}

int World::receiveConsoleInput()
{
    bool correctCommand = false;
    while (!correctCommand){
        std::string command;
        std::cout << "Input: " << std::endl;
        getline(std::cin, command);
        std::vector<std::string> commandParts = World::split(command);
        if (!commandParts.empty()){
            if (commandParts.at(0) == exit){
                correctCommand = true;
                running = false;
            }else if(commandParts.at(0) == add && commandParts.size() == 4 && ((commandParts.at(1) == cube) || (commandParts.at(1) == pyramid)) && onlyDigits(commandParts.at(2)) && onlyDigits(commandParts.at(3))){
                executeAdd(commandParts.at(1), stoi(commandParts.at(2)), stoi(commandParts.at(3)));
            }else if(commandParts.at(0) == move && commandParts.size() == 4 && onlyDigits(commandParts.at(1)) && onlyDigits(commandParts.at(2)) && onlyDigits(commandParts.at(3))) {
                executeMove(std::stoi(commandParts.at(1)), std::stoi(commandParts.at(2)),std::stoi(commandParts.at(3)));
            }else{
                std::cout << "ERROR: Wrong commands or arguments, make sure to use the commands exactly as given above!\n" << std::endl;
            }
        }else{
            std::cout << "ERROR: Empty Input!\n" << std::endl;
        }
    }
    return 0;
}

bool World::isRunning() const
{
    return running;
}

std::vector<std::string> World::split(std::string in) {
    char separator = ' ';
    int begin = 0;
    std::vector<std::string> result;

    while ((begin = in.find_first_not_of(separator, begin)) != std::string::npos) {
        int end = in.find_first_of(separator, begin);
        result.push_back(in.substr(begin, end - begin));
        begin = end;
    }
    return result;
}
