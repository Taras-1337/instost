#include "netvar.h"
#include "SDK/IBaseClientDLL.h"
#include "interfaces.h"

#include <strings.h>

#include "c-vector/vec.h"

struct recv_table *
get_table(struct recv_table **tables, const char *table_name);

int
get_prop(struct recv_table **tables, struct recv_table *recv_table, const char *prop_name, struct recv_prop **prop);

struct recv_table **
netvar_get_tables(void)
{
    struct client_class *client_class = get_all_classes(client);

    if (!client_class) {
        return nullptr;
    }

    struct recv_table **tables = vector_create();
    // TODO: vector_reserve(tables, 16);

    while (client_class) {
        vector_add(&tables, client_class->m_pRecvTable);
        client_class = client_class->m_pNext;
    }

    return tables;
}

int
netvar_get_offset(struct recv_table **tables, const char *table_name, const char *prop_name)
{
    struct recv_table *recv_table = get_table(tables, table_name);

    if (!recv_table) {
        return 0;
    }

    return get_prop(tables, recv_table, prop_name, NULL);
}

struct recv_table *
get_table(struct recv_table **tables, const char *table_name)
{
    for (size_t i = 0; i < vector_size(tables); ++i) {
        if (!tables[i]) {
            continue;
        }

        if (strcasecmp(tables[i]->m_pNetTableName, table_name) == 0) {
            return tables[i];
        }
    }

   return nullptr;
}

int
get_prop(struct recv_table **tables, struct recv_table *recv_table, const char *prop_name, struct recv_prop **prop)
{
    int offset = 0;

    for (int i = 0; i < recv_table->m_nProps; ++i) {
        struct recv_prop *recv_prop = &recv_table->m_pProps[i];
        struct recv_table *child = recv_prop->m_pDataTable;

        if (child && (child->m_nProps > 0)) {
            int tmp = get_prop(tables, child, prop_name, prop);
            if (tmp) {
                offset += (recv_prop->m_Offset + tmp);
            }
        }

        if (strcasecmp(recv_prop->m_pVarName, prop_name)) {
            continue;
        }

        if (prop) {
            *prop = recv_prop;
        }

        return (recv_prop->m_Offset + offset);
    }

    return offset;
}
