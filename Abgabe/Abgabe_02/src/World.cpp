#include "World.h"

#include "Field.h"

#include <iostream>

const std::string World::add = "add";
const std::string World::cube = "cube";
const std::string World::pyramid = "pyramid";
const std::string World::move = "move";
const std::string World::exit = "exit";

World::World(int length, int width) {
    this->length = length;
    this->width = width;
    this->field = new Field(this->length, this->width);
    this->running = true;

    this->inputThread = new std::thread(&World::receiveConsoleInput, this);
}

World::~World() {
    delete field;
    delete inputThread;
}

int World::receiveConsoleInput() {
    std::string input;
    std::string output;
    std::vector<std::string> splittedInput;

    while (isRunning()) {
        getline(std::cin, input);
        splittedInput = split(input);
        output = "";

        //exit
        if (splittedInput.size() == 1) {
            if (splittedInput[0] == exit) {
                running = false;
                output = "Exiting...";
            }
        }
        //add  or move
        else if (splittedInput.size() == 4) {
            if (splittedInput[0] == add) {
                addBlockToWorld(splittedInput, &output);
            } else if (splittedInput[0] == move) {
                moveBlockInWorld(splittedInput, &output);
            }
        }
        //general error output
        if (output.empty()) {
            output = "Wrong input format!";
        }
        std::cout << output << std::endl;
    }
    inputThread->detach();
    return 0;
}

void World::addBlockToWorld(const std::vector<std::string> &splittedString, std::string *output) {
    int x, y;
    //convert numbers
    try {
        x = std::stoi(splittedString[2]);
        y = std::stoi(splittedString[3]);
    } catch (const std::exception &exception) {
        *output = "Failed to add Block, could not convert string to numbers!";
        return;
    }
    //test out of range
    if(x >= length || y >= width) {
        *output = "Coordinates out of range!";
        return;
    }
    //try to add blocks
    int blockId = -1;
    if (splittedString[1] == cube) {
        blockId = field->addCubeBlock(x, y);
    } else if (splittedString[1] == pyramid) {
        blockId = field->addPyramidBlock(x, y);
    }
    if (blockId != -1) {
        *output = splittedString[1] + " added with Id " + std::to_string(blockId);
    } else {
        *output = "Failed to add " + splittedString[1] + " to the world!";
    }
}

void World::moveBlockInWorld(const std::vector<std::string> &splittedString, std::string *output) {
    int id, x, y;
    //convert numbers
    try {
        id = std::stoi(splittedString[1]);
        x = std::stoi(splittedString[2]);
        y = std::stoi(splittedString[3]);
    } catch (const std::exception &exception) {
        *output = "Failed to move Block, could not convert string to numbers!";
        return;
    }
    //test out of range
    if(x >= length || y >= width) {
        *output = "Coordinates out of range!";
        return;
    }
    //move block
    if (field->moveBlock(id, x, y)) {
        *output = "Moved block " + std::to_string(id) + " to position " + std::to_string(x) + "|" + std::to_string(y);
    } else {
        *output = "Failed to move block " + std::to_string(id) + " to position " + std::to_string(x) + "|" + std::to_string(y);
    }
}

bool World::isRunning() const {
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
