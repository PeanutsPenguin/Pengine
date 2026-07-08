#pragma once 

#include "PenDefine/PengineDefine.h"
#include "PenColor/PenColor.h"

#include "Vector/Vector2/Vector2.h"
#include "Matrix/Mat4.h"

#include <memory>

namespace Pengine
{
	namespace System
	{
		class PenRendererSystem;
	}

	namespace Resources
	{
		class PenGLShaderProgram;
	}
}

namespace Penditor
{
	class PickingHandler
	{
	public: 
		PickingHandler() = default;
		PickingHandler(const PickingHandler& other) = default;
		PickingHandler(PickingHandler&& other) = default;
		~PickingHandler() = default;

		PickingHandler& operator=(const PickingHandler& rhs) = default;
		PickingHandler& operator=(PickingHandler&& rhs) = default;

		Pengine::PenObjectId getSelectedObject();

		void update(std::shared_ptr<Pengine::System::PenRendererSystem> renderer);

	private:
		void updateSelectedObject(const PenMath::Vector2& mousPos, std::shared_ptr<Pengine::System::PenRendererSystem> renderer);

		void renderPicking(std::shared_ptr<Pengine::System::PenRendererSystem> renderer);

		void renderObject(const Pengine::PenObjectId obj, std::shared_ptr<Pengine::System::PenRendererSystem> renderer, const PenMath::Mat4& viewProj);

		const Pengine::PenColor& getPickingColor(const Pengine::PenObjectId obj);

		std::shared_ptr<Pengine::Resources::PenGLShaderProgram> m_pickingShader;
		Pengine::PenObjectId m_selectedObject;
	};
}