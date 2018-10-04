//
// Created by lscott on 18-6-4.
//

#ifndef slt_1_BALL_H
#define slt_1_BALL_H

#include "../../GameObject.h"

class Ball : public GameObject
{
public:
    Ball(std::string name, b2Vec2 position, std::string textureName = "ball");
    ~Ball();
};


#endif //slt_1_BALL_H
