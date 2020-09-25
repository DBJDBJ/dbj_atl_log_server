#pragma once
/*
(c) 2020 by dbj@dbj.org -- LICENSE_DBJ

https://stackoverflow.com/a/64065120/10870835

*/

#include <guiddef.h>

namespace dbj {
	namespace win {
		constexpr inline bool
			equal_guids (const GUID& rguid1, const GUID& rguid2)
			noexcept
		{
			return
				rguid1.Data1 == rguid2.Data1 &&
				rguid1.Data2 == rguid2.Data2 &&
				rguid1.Data3 == rguid2.Data3 &&
				rguid1.Data4[0] == rguid2.Data4[0] &&
				rguid1.Data4[1] == rguid2.Data4[1] &&
				rguid1.Data4[2] == rguid2.Data4[2] &&
				rguid1.Data4[3] == rguid2.Data4[3] &&
				rguid1.Data4[4] == rguid2.Data4[4] &&
				rguid1.Data4[5] == rguid2.Data4[5] &&
				rguid1.Data4[6] == rguid2.Data4[6] &&
				rguid1.Data4[7] == rguid2.Data4[7];
		}

		constexpr inline bool operator == (const GUID & guidOne, const GUID & guidOther)
		{
			return equal_guids(guidOne, guidOther);
		}
	} // namespace win 
} // namespace dbj 
