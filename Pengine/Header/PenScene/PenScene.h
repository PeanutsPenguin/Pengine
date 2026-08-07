#pragma once 
#include <set>

#include "PenDefine/PengineDefine.h"		//PengineDefine
#include "PenColor/PenColor.h"

#include <fstream>
#include <string>

namespace Pengine
{
	class PenScene
	{
		friend class PenSceneManager;

	public:
		PenScene();
		PenScene(const std::string& path);
		PenScene(const PenScene& other) = default;
		PenScene(PenScene&& other) = default;
		~PenScene() = default;

		PenScene& operator=(const PenScene& rhs) = default;
		PenScene& operator=(PenScene&& rhs) = default;

		bool serializeScene();
		void loadScene(const std::string& filePath);
		
		void							changeBackgroundColor(const PenColor& col);
		_NODISCARD const PenColor&		getBackgroundColor() const;

		void	removeObject(const PenObjectId obj);
		void	addObject(const PenObjectId obj);

		_NODISCARD bool isObjectInScene(const PenObjectId obj);

		const std::string& getSceneName();

	private :
		bool serializeObject(std::ostream& out, PenObjectId id);
		void loadObject(std::ifstream& infile);
		void loadComponent(std::ifstream& infile, PenObjectId id);

		std::set<PenObjectId> m_objects;
		PenColor m_backgroundColor;
		std::string m_scenePath;
	};
}