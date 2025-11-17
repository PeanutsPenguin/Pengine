#pragma once 
#include <set>

#include "PengineDefine.h"

#pragma region Forward declarations
namespace Pengine
{
	class PenColor;
	class PenObject;
}
#pragma endregion

namespace Pengine
{
	class PenScene
	{
#pragma region Public
	public:
		PenScene();

		~PenScene();
		
		void changeBackgroundColor(const PenColor& col);

		const PenColor& getBackgroundColor() const;

		void removeObject(const PenObjectId obj);

		void addObject(const PenObjectId obj);

		_NODISCARD bool isObjectInScene(const PenObjectId obj);
#pragma endregion

#pragma region Private
	private :
		PenColor* m_backgroundColor;
		std::set<PenObjectId> m_objects;
#pragma endregion
	};
}