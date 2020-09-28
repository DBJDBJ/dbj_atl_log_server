#pragma once
/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */

// DBJ FW requirement
extern "C" {
     static const char* DBJ_APP_NAME = "DBJ COM Client" ;
     static const char* DBJ_APP_VERSION = "1.0.0";
}


// remember to link in the library "dbj_simplelog.lib"
// easy way: #pragma comment(lib, "dbj_simplelog.lib")
// where the lib has to be on the path
#include "../dbj--simplelog/dbj_simple_log.h"

#include "../shared_items/windows_includer.h"
#include "../shared_items/win_dump_generator.h"

#ifndef _KERNEL_MODE
#include "../shared_items/dbj_start_stop.h"
#endif

#include "../shared_items/hresult_verify.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


