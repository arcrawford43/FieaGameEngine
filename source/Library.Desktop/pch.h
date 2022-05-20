#pragma once

//Standard Libraries
#include <stdexcept>
#include <cstddef>
#include <assert.h>
#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>

inline std::size_t operator "" _z(unsigned long long int x)
{
	return static_cast<size_t>(x);
}