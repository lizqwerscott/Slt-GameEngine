#ifndef MATH_H
#define MATH_H
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

//The Const var
//MWT: the world unit
//Meter: the physical unit
//pixel: the Draw unit

#define PI 3.1415926

//MWT to meter
namespace slt
{
class Math
{
public:
    static void init(sf::Vector2u WindowSize);
    static Math * getInstance();
    static void Destory();
private:
    Math(sf::Vector2u WindowSize);
    ~Math();
public:
    static void setWindowSize(sf::Vector2u windowSize);

    static void setSlotToMeterUnit(float stmu);
    static void setSlotToPixelUnit(float stpu);
    static float getSlotToMeterUnit();
    static float getSlotToPixelUnit();

    //The World CoordinateSystem To Draw CoordiateSystem
    static const sf::Vector2f WorldCoordSToDrawCoordS(b2Vec2 worldPos);

    //The Draw CoordiateSystem To World CoordinateSystem
    static const b2Vec2 DrawCoordSToWorldCoordS(sf::Vector2f drawPos);

    //The World CoordinateSystem To Physical CoordinateSystem
    static const b2Vec2 WorldCoordSToPhysicalCoordS(b2Vec2 worldPos);

    //The Physical CoordinateSystem To World CoordinateSystem
    static const b2Vec2 PhysicalCoordSToWorldCoordS(b2Vec2 physicalPos);

    //The Draw CoordiateSystem To Physical CoordinateSystem
    static const b2Vec2 DrawCoordSToPhysicalCoords(sf::Vector2f drawPos);

    //The Physical CoordinateSystem To Draw CoordinateSystem
    static const sf::Vector2f PhysicalCoordSToDrawCoordS(b2Vec2 physicalPos);

    static const float SLTToPixel(float slt);
    static const sf::Vector2f SLTToPixel(b2Vec2 pos);
    static const float PixelToSLT(float pixel);
    static const float SLTToMeter(float slt);
    static const float MeterToSLT(float meter);
    static const float MeterToPixel(float meter);
    static const float PixelToMeter(float pixel);

    static const b2Vec2 UnitVector(b2Vec2 vector);
    static const b2Vec2 InverseVector(b2Vec2 vector);
    static const b2Vec2 NumberProduct(b2Vec2 vector, int t);
    static const b2Vec2 NumberProduct(b2Vec2 vector, float t);
    static const b2Vec2 NumberProduct(b2Vec2 vector, double t);
    static const double PointProduct(b2Vec2 v1, b2Vec2 v2);

    static void vectorToCharList(std::vector<std::string> vector, const char ** result);
public:
    static const float degreeToRad(float degree);
    static const float radToDegree(float rad);
public:
    // Use BKDR Hash Function
    static const unsigned int bkdrHash(std::string str);
    static const unsigned int bkdrHash(char * str);
public:
    static bool PointInLine(b2Vec2 point, b2Vec2 start, b2Vec2 end);
    static bool LinesIntersectionP(b2Vec2 p1, b2Vec2 p2, b2Vec2 q1, b2Vec2 q2);
    static const b2Vec2 LinesIntersection(b2Vec2 p1, b2Vec2 p2, b2Vec2 q1, b2Vec2 q2);
    static const b2Vec2 rotatingVector(b2Vec2 p, float angle, b2Vec2 originCoordinates = b2Vec2(0, 0));
    private:
    float SLTOMETER_UNIT = 1;
    float SLTTOPIXEL_UNIT = 10;
    sf::Vector2u m_windowSize;
};
}

#endif
