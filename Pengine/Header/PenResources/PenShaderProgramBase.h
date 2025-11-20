#pragma once
#include "PenResources/PenResourcesManager.h"

#define VECTOR2_CAST
#include <Vector/Vector2/Vector2.h>

#include <Matrix/Mat3.h>
#include <Matrix/Mat4.h>


namespace Pengine::Resources
{
	/// I'll have to handle all the uniform one day 
	class PenShaderProgramBase /*: public PenResoucesBase*/  //in the futur
	{
	public:
		PenShaderProgramBase() = default;

		/*PenShaderProgramBase(const PenResourcesId& id) : PenResoucesBase(id) {}*/		//in the furtur

		virtual ~PenShaderProgramBase() = default;

		virtual bool use() const = 0;

		virtual void unuse() const = 0;

		virtual void destroy() = 0;

		/*bool loadResource(const char* path) override; */		//in the futur 

		virtual bool initShaderProgram() = 0;

		virtual void setUniform(const char* name, bool value) = 0;

		virtual void setUniform(const char* name, int value) = 0;
 
		virtual void setUniform(const char* name, float value) = 0;

		virtual void setUniform(const char* name, const PenMath::Vector2f& value) = 0;

		virtual void setUniform(const char* name, const PenMath::Vector3f& value) = 0;

		virtual void setUniform(const char* name, const PenMath::Vector4f& value) = 0;

		virtual void setUniform(const char* name, const PenMath::Mat3& value) = 0;

		virtual void setUniform(const char* name, const PenMath::Mat4& value) = 0;
	};
}