#include "PenLight/PenPointLight.h"

//#include <GLFW/glfw3.h>

using namespace Pengine;

void PenPointLight::setType(const PenLightType type)
{
}

void PenPointLight::useValues(std::shared_ptr<Resources::PenShaderProgramBase> prog)
{
	//CHANGE COLOR AT RUNTIME
 //   PenMath::Vector3f lightColor;
 //   lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
 //   lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
 //   lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
 //   PenMath::Vector3f diffuseColor = lightColor * PenMath::Vector3f(0.5f); // decrease the influence
 //   PenMath::Vector3f ambientColor = diffuseColor * PenMath::Vector3f(0.2f); // low influence

	//prog->setUniform("light.ambient", ambientColor);
	//prog->setUniform("light.diffuse", diffuseColor);

	prog->setUniform("light.ambient", this->m_ambientColor);
	prog->setUniform("light.diffuse", this->m_diffuseColor);
	prog->setUniform("light.specular", this->m_specular);
}
