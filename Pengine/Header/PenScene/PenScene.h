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
	public:
		PenScene();
		PenScene(const PenScene& other) = default;
		PenScene(PenScene&& other) = default;
		~PenScene();

		PenScene& operator=(const PenScene& rhs) = default;
		PenScene& operator=(PenScene&& rhs) = default;
		
		void							changeBackgroundColor(const PenColor& col);
		_NODISCARD const PenColor&		getBackgroundColor() const;

		void	removeObject(const PenObjectId obj);
		void	addObject(const PenObjectId obj);

		_NODISCARD bool isObjectInScene(const PenObjectId obj);

	private :
		std::set<PenObjectId> m_objects;
		PenColor* m_backgroundColor;
	};
}