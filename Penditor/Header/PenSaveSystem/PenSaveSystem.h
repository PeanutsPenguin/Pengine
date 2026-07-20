#pragma once

namespace Penditor
{
	class PenSavior
	{
	public:
		PenSavior() = default;
		PenSavior(const PenSavior& other) = default;
		PenSavior(PenSavior&& other) = default;
		~PenSavior() = default;

		PenSavior& operator=(const PenSavior& rhs) = default;
		PenSavior& operator=(PenSavior&& rhs) = default;

		void checkSaveInputs();

		void saveAll();
	};
}