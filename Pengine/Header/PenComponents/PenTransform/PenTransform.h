#pragma once 

#include "PenComponents/PenComponentsBase.h"

namespace Pengine::Components
{
	class PenTransform : public PenComponentsBase
	{
	public:
		PenTransform() = delete;

		PenTransform(PenComponentsId id) : PenComponentsBase(id) {}

		~PenTransform() = default;

		void render() override;
	};
}