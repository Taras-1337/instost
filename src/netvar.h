#pragma once

#include "SDK/IBaseClientDLL.h"

struct recv_table **
netvar_get_tables(void);

int
netvar_get_offset(struct recv_table **tables,
                  const char         *table_name,
                  const char         *prop_name);
