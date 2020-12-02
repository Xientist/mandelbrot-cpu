#pragma once

#include "Complex.h"

namespace jw {

	class Complexd : public Complex<double>
	{
	public:
		Complexd(double r, double i);
	};

}
