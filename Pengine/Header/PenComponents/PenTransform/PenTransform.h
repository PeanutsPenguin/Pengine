#pragma once 

#include "PenComponents/PenComponentsBase.h"

namespace Pengine::Components
{
	class PenTransform : public PenComponentsBase
	{
#pragma region Public
	public:
		PenTransform() = delete;

		PenTransform(PenComponentsId id) : PenComponentsBase(id) {}

		~PenTransform() = default;

		void render() override;
#pragma endregion

		//TO DO : Add a vec3f
	};
}