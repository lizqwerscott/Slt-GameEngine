//
// Created by lscott on 18-6-5.
//

#ifndef slt_1_BLOCK_H
#define slt_1_BLOCK_H


#include "../../GameObject.h"

class Block : public GameObject
{
public:
    Block(std::string name, b2Vec2 position, std::string textureName = "paddle");
};


#endif //slt_1_BLOCK_H
