#pragma once 

#include "PenSystem/PenSystemBase.h"

#include <unordered_map>

namespace Pengine::System
{
	class PenTransformSystem final : public PenSystemBase
	{
	public:
		PenTransformSystem() = default;
		PenTransformSystem(const PenTransformSystem& other) = default;
		PenTransformSystem(PenTransformSystem&& other) = default;
		~PenTransformSystem() final = default;

		PenTransformSystem& operator=(const PenTransformSystem& rhs) = default;
		PenTransformSystem& operator=(PenTransformSystem&& rhs) = default;

		void update(double dt) final;

		void addRoot(const PengineIds obj);
		void addChild(const PengineIds obj, const PengineIds parent);
		void removeRoot(const PengineIds obj);

		void reparentChild(const PengineIds obj, const PengineIds oldParent, const PengineIds newParent, bool keepPosition = true);

		void onEntityInserted(const PengineIds newObj) final;
		void onEntityDestroyed(const PengineIds obj) final;

	private:
		std::unordered_map<PengineIds, std::set<PengineIds>> m_children;
	};
}