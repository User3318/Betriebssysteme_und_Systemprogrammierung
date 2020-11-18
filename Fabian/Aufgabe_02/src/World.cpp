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
    // TODO implement me
}

int World::receiveConsoleInput() {
    std::string input;
    std::string output;
    std::vector<std::string> splitted_input;

    while (isRunning()) {
        getline(std::cin, input);
        splitted_input = split(input);
        output = "";

        //exit
        if (splitted_input.size() == 1) {
            if (splitted_input[0] == exit) {
                running = false;
                output = "Exiting...";
            }
        }
            //add  or move
        else if (splitted_input.size() == 4) {
            if (splitted_input[0] == add) {
                addBlock(splitted_input, &output);
            } else if (splitted_input[0] == move) {
                moveBlock(splitted_input, &output);
            }
        }
        if (output.empty()) {
            output = "Wrong input format!";
        }
        std::cout << output << std::endl;
    }
    return 0;
}

void World::addBlock(const std::vector<std::string> &splitted_string, std::string *output) {
    int x, y;
    try {
        x = std::stoi(splitted_string[2]);
        y = std::stoi(splitted_string[3]);
    } catch (const std::exception &exception) {
        *output = "Failed to add Block, could not convert string to numbers!";
        return;
    }
    int blockId = -1;
    if (splitted_string[1] == cube) {
        blockId = field->addCubeBlock(x,y);
    } else if (splitted_string[1] == pyramid) {
        blockId = field->addPyramidBlock(x,y);
    }
    if(blockId != -1) {
        *output = splitted_string[1] + " added with Id " + std::to_string(blockId);
    } else {
        *output = "Failed to add " + splitted_string[1] + " to the world!";
    }
}

void World::moveBlock(const std::vector<std::string> &splitted_string, std::string *output) {
    int id, x, y;
    try {
        id = std::stoi(splitted_string[1]);
        x = std::stoi(splitted_string[2]);
        y = std::stoi(splitted_string[3]);
    } catch (const std::exception &exception) {
        *output = "Failed to add Block, could not convert string to numbers!";
        return;
    }
    if(field->moveBlock(id,x,y)) {
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
