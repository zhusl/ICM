#ifndef _ICM_BASIC_H_
#define _ICM_BASIC_H_
// Includes
//  default
#include <string>
#include <cctype>
#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <functional>
#include <algorithm>
#include <initializer_list>
#include <cassert>
//  common
#include "file.h"
#include "prints.h"
#include "memory.h"
#include "charptr.h"
#include "range.h"
#include "lightlist.h"
#include "bijectionmap.h"

// Declares

// Using
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::shared_ptr;
using std::unique_ptr;
using std::list;
using std::to_string;
using namespace Common;

template <typename T> constexpr T MaxValue() { return std::numeric_limits<T>::max(); }

namespace ICM
{
	std::string to_string();
}

namespace ICM
{
	// Output
	template <typename T>
	inline void print(const T &obj)
	{
		using ICM::to_string;
		using Convert::to_string;
		using std::to_string;

		Common::Output::print(to_string(obj));
	}
	template <>
	inline void print(const std::string &obj)
	{
		Common::Output::print(obj);
	}
	inline void print(const char *obj)
	{
		Common::Output::print(obj);
	}
	inline void println()
	{
		Common::Output::println();
	}
	template <typename T>
	inline void println(const T &obj)
	{
		print(obj);
		println();
	}
	template <typename First, typename... Rest>
	inline void print(const First& first, const Rest&... rest)
	{
		print(first);
		print(rest...);
	}
	template <typename First, typename... Rest>
	inline void println(const First& first, const Rest&... rest)
	{
		print(first);
		println(rest...);
	}
}

#endif
