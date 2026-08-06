#pragma once 
#include <set>

#include "PenDefine/PengineDefine.h"		//PengineDefine

#include <fstream>

#pragma region Forward declarations
namespace Pengine
{
	class PenColor;
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

		bool serializeScene(const char* filePath);
		void loadScene(const char* filePath);
		
		void							changeBackgroundColor(const PenColor& col);
		_NODISCARD const PenColor&		getBackgroundColor() const;

		void	removeObject(const PenObjectId obj);
		void	addObject(const PenObjectId obj);

		_NODISCARD bool isObjectInScene(const PenObjectId obj);

	private :
		bool serializeObject(std::ostream& out, PenObjectId id);
		void loadObject(std::ifstream& infile);
		void loadComponent(std::ifstream& infile, PenObjectId id);


		std::set<PenObjectId> m_objects;
		PenColor* m_backgroundColor;
	};
}