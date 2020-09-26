#pragma once
/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */

#include "../shared_items/windows_includer.h" // DBJ_VERIFY , DBJ_ASSERT

#include <crtdbg.h> // DBJ added
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include "../shared_items/hresult_verify.h"
#include "../shared_items/win_guid_compare.h"

#define APP_NAME "bteclog_cpp_client"
#define APP_VERSION "0.0.1"

#include "win_dump_generator.h"
#include "dbj_com_autoinit.h"