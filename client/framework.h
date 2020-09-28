#pragma once
/* (c) 2020 by dbj@dbj.org -- LICENSE_DBJ -- https://dbj.org/license_dbj/ */

// also since this is windows app there is no std streams 
// thus there is no point of printf-ing from here
#include "../dbj--simplelog/dbj_simple_log.h"


#include "../shared_items/windows_includer.h" // DBJ_VERIFYX , DBJ_ASSERT
#include "../shared_items/hresult_verify.h"
#include "../shared_items/dbj_start_stop.h"

#define APP_NAME "dbjlogsvr_cpp_client"
#define APP_VERSION "0.2.0"

#include "win_dump_generator.h"


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>


