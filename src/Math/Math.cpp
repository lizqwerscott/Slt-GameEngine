#include "Math.h"

using namespace slt;

Math *math = nullptr;

void Math::init(sf::Vector2u WindowSize)
{
    if (math == nullptr) {
        math = new Math(WindowSize);
    }
}

Math *
Math::getInstance()
{
    return math;
}

void Math::Destory()
{
    delete math;
    math = nullptr;
}

Math::Math(sf::Vector2u WindowSize) : m_windowSize(WindowSize) {}
Math::~Math() {}

void Math::setWindowSize(sf::Vector2u windowSize)
{
    math->m_windowSize = windowSize;
}

void Math::setSlotToMeterUnit(float stmu)
{
    math->SLTOMETER_UNIT = stmu;
}

void Math::setSlotToPixelUnit(float stpu)
{
    math->SLTTOPIXEL_UNIT = stpu;
}

float Math::getSlotToMeterUnit()
{
    return math->SLTOMETER_UNIT;
}

float Math::getSlotToPixelUnit()
{
    return math->SLTTOPIXEL_UNIT;
}


//The World CoordinateSystem To Draw CoordiateSystem
const sf::Vector2f
Math::WorldCoordSToDrawCoordS(b2Vec2 worldPos)
{
    return sf::Vector2f((worldPos.x + math->m_windowSize.x / math->SLTTOPIXEL_UNIT / 2) * math->SLTTOPIXEL_UNIT, (-(worldPos.y - math->m_windowSize.y / math->SLTTOPIXEL_UNIT / 2)) * math->SLTTOPIXEL_UNIT);
}

//The Draw CoordiateSystem To World CoordinateSystem
const b2Vec2
Math::DrawCoordSToWorldCoordS(sf::Vector2f drawPos)
{
    return b2Vec2((drawPos.x - math->m_windowSize.x / 2) / math->SLTTOPIXEL_UNIT, (-(drawPos.y - math->m_windowSize.y / 2)) / math->SLTTOPIXEL_UNIT);
}

//The World CoordinateSystem To Physical CoordinateSystem
const b2Vec2
Math::WorldCoordSToPhysicalCoordS(b2Vec2 worldPos)
{
    return b2Vec2(worldPos.x * math->SLTOMETER_UNIT, worldPos.y * math->SLTOMETER_UNIT);
}

//The Physical CoordinateSystem To World CoordinateSystem
const b2Vec2
Math::PhysicalCoordSToWorldCoordS(b2Vec2 physicalPos)
{
    return b2Vec2(physicalPos.x / math->SLTOMETER_UNIT, physicalPos.y / math->SLTOMETER_UNIT);
}

//The Draw CoordiateSystem To Physical CoordinateSystem
const b2Vec2
Math::DrawCoordSToPhysicalCoords(sf::Vector2f drawPos)
{
    return Math::WorldCoordSToPhysicalCoordS(Math::DrawCoordSToWorldCoordS(drawPos));
}

//The Physical CoordinateSystem To Draw CoordinateSystem
const sf::Vector2f
Math::PhysicalCoordSToDrawCoordS(b2Vec2 physicalPos)
{
    return Math::WorldCoordSToDrawCoordS(Math::PhysicalCoordSToWorldCoordS(physicalPos));
}

const float
Math::SLTToPixel(float slt)
{
    return slt * math->SLTTOPIXEL_UNIT;
}

const sf::Vector2f
Math::SLTToPixel(b2Vec2 pos)
{
    return sf::Vector2f(Math::SLTToPixel(pos.x), Math::SLTToPixel(pos.y));
}

const float
Math::PixelToSLT(float pixel)
{
    return pixel / math->SLTTOPIXEL_UNIT;
}

const float
Math::SLTToMeter(float slt)
{
    return slt * math->SLTOMETER_UNIT;
}

const float
Math::MeterToSLT(float meter)
{
    return meter / math->SLTOMETER_UNIT;
}

const float
Math::MeterToPixel(float meter)
{
    return Math::SLTToPixel(Math::MeterToSLT(meter));
}

const float
Math::PixelToMeter(float pixel)
{
    return Math::SLTToMeter(Math::PixelToSLT(pixel));
}

const b2Vec2
Math::UnitVector(b2Vec2 vector)
{
    return b2Vec2(vector.x / vector.Length(), vector.y / vector.Length());
}

const b2Vec2
Math::InverseVector(b2Vec2 vector)
{
    return b2Vec2(-vector.x, -vector.y);
}

const b2Vec2
Math::NumberProduct(b2Vec2 vector, double t)
{
    return b2Vec2(vector.x * t, vector.y * t);
}

const b2Vec2
Math::NumberProduct(b2Vec2 vector, float t)
{
    return b2Vec2(vector.x * t, vector.y * t);
}

const b2Vec2
Math::NumberProduct(b2Vec2 vector, int t)
{
    return b2Vec2(vector.x * t, vector.y * t);
}

const unsigned int
Math::bkdrHash(std::string str)
{
    return Math::bkdrHash((char *)str.c_str());
}

const unsigned int
Math::bkdrHash(char * str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

void Math::vectorToCharList(std::vector<std::string> vector, const char ** result)
{
    for (int i = 0; i < static_cast<int>(vector.size()); i++) {
        result[i] = const_cast<char *>(vector[i].c_str());
    }
}

const float
Math::degreeToRad(float degree) {
    return (PI / 180) * degree * -1.0f;
}

const float
Math::radToDegree(float rad) {
    return (180 / PI) * rad * -1.0f;
}
