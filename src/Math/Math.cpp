#include "Math.h"

using namespace slt;

Math *math = nullptr;

void Math::init(sf::Vector2u WindowSize)
{
	if (math == nullptr)
	{
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

void Math::setSlotToMeterUnit(float stmu) {
	math->SLTOMETER_UNIT = stmu;
}

void Math::setSlotToPixelUnit(float stpu) {
	math->SLTTOPIXEL_UNIT = stpu;
}

float Math::getSlotToMeterUnit() {
	return math->SLTOMETER_UNIT;
}

float Math::getSlotToPixelUnit() {
	return math->SLTTOPIXEL_UNIT;
}


//The World CoordinateSystem To Draw CoordiateSystem
const sf::Vector2f 
Math::WorldCoordSToDrawCoordS(b2Vec2 worldPos) {
	return sf::Vector2f((worldPos.x + math->m_windowSize.x / math->SLTTOPIXEL_UNIT / 2) * math->SLTTOPIXEL_UNIT, (-(worldPos.y - math->m_windowSize.y / math->SLTTOPIXEL_UNIT / 2)) * math->SLTTOPIXEL_UNIT);
}

//The Draw CoordiateSystem To World CoordinateSystem
const b2Vec2 
Math::DrawCoordSToWorldCoordS(sf::Vector2f drawPos) {
	return b2Vec2((drawPos.x - math->m_windowSize.x / 2) / math->SLTTOPIXEL_UNIT, (-(drawPos.y - math->m_windowSize.y / 2)) / math->SLTTOPIXEL_UNIT);
}

//The World CoordinateSystem To Physical CoordinateSystem
const b2Vec2 
Math::WorldCoordSToPhysicalCoordS(b2Vec2 worldPos) {
	return b2Vec2(worldPos.x * math->SLTOMETER_UNIT, worldPos.y * math->SLTOMETER_UNIT);
}

//The Physical CoordinateSystem To World CoordinateSystem 
const b2Vec2 
Math::PhysicalCoordSToWorldCoordS(b2Vec2 physicalPos) {
	return b2Vec2(physicalPos.x / math->SLTOMETER_UNIT, physicalPos.y / math->SLTOMETER_UNIT);
}

//The Draw CoordiateSystem To Physical CoordinateSystem
const b2Vec2 
Math::DrawCoordSToPhysicalCoords(sf::Vector2f drawPos) {
	return Math::WorldCoordSToPhysicalCoordS(Math::DrawCoordSToWorldCoordS(drawPos));
}

//The Physical CoordinateSystem To Draw CoordinateSystem 
const sf::Vector2f 
Math::PhysicalCoordSToDrawCoordS(b2Vec2 physicalPos) {
	return Math::WorldCoordSToDrawCoordS(Math::PhysicalCoordSToWorldCoordS(physicalPos));
}

const float 
Math::SLTToPixel(float slt) {
	return slt * math->SLTTOPIXEL_UNIT;
}

const float 
Math::PixelToSLT(float pixel) {
	return pixel / math->SLTTOPIXEL_UNIT;
}

const float 
Math::SLTToMeter(float slt) {
	return slt * math->SLTOMETER_UNIT;
}

const float 
Math::MeterToSLT(float meter) {
	return meter / math->SLTOMETER_UNIT;
}

const float 
Math::MeterToPixel(float meter) {
	return Math::SLTToPixel(Math::MeterToSLT(meter));
}

const float 
Math::PixelToMeter(float pixel) {
	return Math::SLTToMeter(Math::PixelToSLT(pixel));
}
