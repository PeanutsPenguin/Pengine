#pragma once 

#include "PenSystem/PenSystemBase.h"

#include <unordered_map>

namespace Pengine::System
{
	class PenTransformSystem : public PenSystemBase
	{
	public:
		PenTransformSystem() = default;	

		~PenTransformSystem() override = default;

		void update(double dt) override;

		void addRoot(const PenObjectId obj);

		void removeRoot(const PenObjectId obj);

		void addChild(const PenObjectId obj, const PenObjectId parent);

		void reparentChild(const PenObjectId obj, const PenObjectId oldParent, const PenObjectId newParent, bool keepPosition = true);

		void onEntityInserted(const PenObjectId newObj) override;

		void onEntityDestroyed(const PenObjectId obj) override;

	private:
		std::unordered_map<PenObjectId, std::set<PenObjectId>> m_children;
	};
}