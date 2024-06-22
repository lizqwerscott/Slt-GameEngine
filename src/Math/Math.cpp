#include "slt/Math/Math.h"

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

const double
Math::PointProduct(b2Vec2 v1, b2Vec2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
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
Math::degreeToRad(float degree)
{
    return (PI / 180) * degree;
}

const float
Math::radToDegree(float rad)
{
    return (180 / PI) * rad;
}

bool Math::PointInLine(b2Vec2 point, b2Vec2 start, b2Vec2 end)
{
    b2Vec2 v1 = point - start;
    b2Vec2 v2 = point - end;
    bool InStraightLineP = b2Cross(v1, v2) == 0;
    bool InXP = point.x >= fmin(start.x, end.x) && point.x <= fmax(start.x, end.x) && point.y >= fmin(start.y, end.y) && point.y <= fmax(start.y, end.y);
    return InStraightLineP && InXP;
}

bool Math::LinesIntersectionP(b2Vec2 p1, b2Vec2 p2, b2Vec2 q1, b2Vec2 q2)
{
    b2Vec2 v1 = p2 - p1;
    b2Vec2 v2 = q2 - q1;
    bool intersectionP = b2Cross(v1, v2) != 0;
    bool k1P = (b2Cross(p1 - q1, q2 - q1) * b2Cross(q2 - q1, p2 - q1)) >= 0;
    bool k2P = (b2Cross(q1 - p1, p2 - p1) * b2Cross(p2 - p1, q2 - p1)) >= 0;
    return intersectionP && k1P && k2P;
}

const b2Vec2
Math::LinesIntersection(b2Vec2 p1, b2Vec2 p2, b2Vec2 q1, b2Vec2 q2)
{
    float a1 = (p1.y - p2.y) / (p1.x - p2.x);
    float b1 = p1.y - a1 * p1.x;

    float a2 = (q1.y - q2.y) / (q1.x - q2.x);
    float b2 = q1.y - a2 * q1.x;

    b2Vec2 result;
    result.x = (b1 - b2) / (a2 - a1);
    result.y = a1 * result.x + b1;

    return result;
}

const b2Vec2 Math::rotatingVector(b2Vec2 p, float angle, b2Vec2 originCoordinates)
{
    b2Mat22 rotationMatrix;
    rotationMatrix.Set(b2Vec2(cos(angle), sin(angle)), b2Vec2(-sin(angle), cos(angle)));
    b2Vec2 relativePos = p - originCoordinates;
    return rotationMatrix.Solve(relativePos) + originCoordinates;
}
