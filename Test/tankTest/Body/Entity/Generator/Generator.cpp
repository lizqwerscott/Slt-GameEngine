#include "Generator.h"
#include "../../Net/NetEnergy/NetEnergy.h"

Generator::Generator(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp, float generatorSpeed, float energyMax) :
    Entity(name, "Generator", parent, nodePos, hp),
    m_generatorSpeed(generatorSpeed),
    m_generatorEnergyMax(energyMax),
    m_generatorEnergy(0)
{
    this->m_net = new NetEnergy();
    this->m_isDrawUi = false;

    sf::Texture * generatorTexture = ResourceManager::GetTexture(std::string("generator"));
    generatorTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, generatorTexture);
}

void Generator::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Generator]person look Generator\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Generator::UpdateSelf(sf::Time &dt)
{
    if (m_generatorEnergy <= m_generatorEnergyMax) {
	Log::setLevel(LOG_LEVEL_INFO);
	double step = dt.asSeconds() / 1 * m_generatorSpeed;
	m_generatorEnergy += step;
	// Log::printLog("dt: %lf\n", dt.asSeconds());
	// Log::printLog("step: %lf, energy: %f\n", step, m_generatorEnergy);
    }
}

 void Generator::DrawUiSelf()
 {
     if (this->m_isDrawUi) {
	 ImGui::Begin("Generator");
	 if (ImGui::Button("quit")) {
	     this->m_isDrawUi = false;
	 }
	 ImGui::Text("Speed: %f", this->m_generatorSpeed);
	 ImGui::Text("Energy: %f", this->m_generatorEnergy);
	 ImGui::End();
     }
 }

