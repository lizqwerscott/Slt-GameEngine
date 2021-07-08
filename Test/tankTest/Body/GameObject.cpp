#include "GameObject.h"

GameObject::GameObject(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    SNode(name, parent)
{
    parent->AddChild(this);
    this->SetPosition(nodePos);
    if (hp <= 0) {
        printf("[ERROR][%s]:this hp must be greater than 0\n", this->GetName().c_str());
    } else {
        m_hp = hp;
    }
    this->SetPosition(nodePos);


    this->pushUpdateCallBack([](SNode * node) -> void {
        auto gameObject = static_cast<GameObject *>(node);
        if (gameObject->m_hp <= 0)
        {
            printf("[Dead]:%s hp is zero", gameObject->GetName().c_str());
            gameObject->GetParent()->DeleteChild(gameObject->GetName());
        }
    });
}

GameObject::~GameObject()
{
    printf("[Dead]:%s is dead\n", GetName().c_str());
}
