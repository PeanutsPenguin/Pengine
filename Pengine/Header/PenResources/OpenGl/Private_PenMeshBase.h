#pragma once 

#include "PenResources/PenResourcesBase.h"

namespace Pengine::Resources
{
	/// <summary>
	/// Base class for a mesh because i think i'll try to render with multiple graphic API
	/// </summary>
	class PenMeshBase
	{
	public:
		PenMeshBase() = default;

		virtual ~PenMeshBase() = default;
	};
}