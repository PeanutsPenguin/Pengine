#pragma once
#include "PenResources/PenResourcesManager.h"

#include "PenResources/PenShaderBase.h"

#define VECTOR2_CAST
#include <Vector/Vector2/Vector2.h>
#include <Matrix/Mat3.h>
#include <Matrix/Mat4.h>


namespace Pengine::Resources
{
	class PenShaderProgramBase : public PenResourcesBase
	{
	public:
		PenShaderProgramBase() = default;
		PenShaderProgramBase(const PenResourcesId& id) : PenResourcesBase(id) {}
		virtual ~PenShaderProgramBase() = default;

		virtual bool loadResource(const char* path) = 0;

		virtual bool createResource(const char* PenfilePath, const char* sourcePath) = 0;

		virtual bool createResource(const char* PenfilePath, const char* sourcePath, 
									std::shared_ptr<PenShaderBase> vertexShader, 
									std::shared_ptr<PenShaderBase> fragmentShader) = 0;

		virtual bool use() const = 0;

		virtual void unuse() const = 0;

		virtual void destroy() = 0;

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