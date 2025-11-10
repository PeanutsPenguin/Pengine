#pragma once
#include "PenResources/PenResourcesManager.h"

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
	};
}