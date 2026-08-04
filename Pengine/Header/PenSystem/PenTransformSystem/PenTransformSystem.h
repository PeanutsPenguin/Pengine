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

		void addRoot(const PenObjectId obj);
		void addChild(const PenObjectId obj, const PenObjectId parent);
		void removeRoot(const PenObjectId obj);

		void reparentChild(const PenObjectId obj, const PenObjectId oldParent, const PenObjectId newParent, bool keepPosition = true);

		void onEntityInserted(const PenObjectId newObj) final;
		void onEntityDestroyed(const PenObjectId obj) final;

	private:
		std::unordered_map<PenObjectId, std::set<PenObjectId>> m_children;
	};
}