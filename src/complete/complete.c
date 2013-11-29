#include <json-glib/json-glib.h>
#include <clang-c/Index.h>
#include <utils/utils.h>
#include "cc_request.h"
#include "complete.h"

static char *
get_json_data(struct cc_request *req)
{
    JsonGenerator *generator;
    JsonBuilder *builder;
    JsonNode *root;
    char *data;

    g_type_init();

    builder = json_builder_new();
    cc_request_json(builder, req);
    root = json_builder_get_root(builder);

    generator = json_generator_new();
    json_generator_set_root(generator, root);
    json_generator_set_pretty(generator, TRUE);
    json_generator_set_indent(generator, 4);

    data = json_generator_to_data(generator, NULL);
    u_assert(data);

    json_node_free(root);
    g_object_unref(generator);
    g_object_unref(builder);

    return data;
}

char *
complete(const char *fname,
         unsigned line, unsigned column,
         const char *clang_args)
{
    struct cc_request *req;
    char *data;

    u_assert(fname && clang_args);

    req = cc_request_init(fname, line, column, clang_args);
    if (!req) {
        u_warn("Request initialization failed!\n");
        return NULL;
    }

    if (cc_request_run(req)) {
        u_warn("Failed to executed completion request!\n");
        cc_request_fini(req);
        return NULL;
    }

    data = get_json_data(req);
    cc_request_fini(req);

    return data;
}
