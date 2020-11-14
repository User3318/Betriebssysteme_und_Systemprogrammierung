#pragma once

#include "Block.h"

class PyramidBlock : public Block {
    friend class Field;
public:
    virtual std::string toString();
    virtual ~PyramidBlock() = default;
private:
    PyramidBlock(int id, int posX, int posY);

};