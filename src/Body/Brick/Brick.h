//
// Created by lscott on 18-6-4.
//

#ifndef slt_1_BRICK_H
#define slt_1_BRICK_H


#include "../../GameObject.h"
#include <glm/glm.hpp>

class Brick : public GameObject
{
public:
    Brick(std::string name, b2Vec2 position, b2Vec2 size, glm::vec3 color, std::string textureName = "block");
    ~Brick();
};


#endif //slt_1_BRICK_H
