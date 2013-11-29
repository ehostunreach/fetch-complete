#include <json-glib/json-glib.h>
#include <utils/utils.h>
#include <complete/complete.h>
#include "request.h"

static JsonParser *
get_message_parser(const char *msg)
{
    JsonParser *parser;
    size_t size;

    u_assert(msg);

    parser = json_parser_new();
    if (!parser) {
        u_warn("Failed to create JSON parser!\n");
        return NULL;
    }

    size = u_strlen(msg);
    if (!json_parser_load_from_data(parser, msg, size, NULL)) {
        u_warn("Failed to load JSON data to parser!\n");

        g_object_unref(parser);
        return NULL;
    }

    return parser;
}

static JsonNode *
query_parser(JsonParser *parser, const char *expr)
{
    JsonNode *root, *result;
    JsonArray *array;
    unsigned length;

    root = json_parser_get_root(parser);
    if (!root) {
        u_warn("Parser's root node is NULL!\n");
        return NULL;
    }

    result = json_path_query(expr, root, NULL);
    if (!result) {
        u_warn("JSON path query failed!\n");
        return NULL;
    }

    array = json_node_get_array(result);
    if (!array) {
        u_warn("NULL array in JSON query result!\n");
        json_node_free(result);
        return NULL;
    }

    length = json_array_get_length(array);
    if (length != 1) {
        u_warn("The JSON path didn't match any elements.\n", length);
        json_node_free(result);
        return NULL;
    }

    result = json_array_get_element(array, 0);
    if (!result) {
        u_warn("Bad array element!\n");
        json_node_free(result);
        return NULL;
    }

    return result;
}

static char *
get_string(JsonParser *parser, const char *expr)
{
    JsonNode *node;
    const char *str;

    u_assert(parser && expr);

    node = query_parser(parser, expr);
    if (!node)
        return NULL;

    if (!JSON_NODE_HOLDS_VALUE(node)) {
        u_warn("JSON node doesn't contain a valid value!\n");
        return NULL;
    }

    str = json_node_get_string(node);
    if (!str) {
        u_warn("JSON node has a NULL string!\n");
        return NULL;
    }

    return u_strdup(str);
}

static int
get_integer(JsonParser *parser, const char *expr)
{
    JsonNode *node;

    u_assert(parser && expr);

    node = query_parser(parser, expr);
    if (!node)
        return 0;

    if (!JSON_NODE_HOLDS_VALUE(node)) {
        u_warn("JSON node doesn't contain a valid value!\n");
        return 0;
    }

    return (int) json_node_get_int(node);
}

static void
object_foreach_handler(JsonObject *object,
                       const char *member_name,
                       JsonNode *member_node,
                       gpointer user_data)
{
    struct u_dict *dict;
    char *key, *value;
    const char *node_string;

    (void) object;

    if (!member_name || !member_node || !user_data) {
        u_warn("Bad dictionary values!\n");
        return;
    }

    node_string = json_node_get_string(member_node);
    if (!node_string) {
        u_warn("JSON node has a NULL string!\n");
        return;
    }

    key = u_strdup(member_name);
    value = u_strdup(node_string);

    dict = user_data;
    u_dict_add(dict, (void *) key, (void *) value);
}

static struct u_dict *
get_dict(JsonParser *parser, const char *expr)
{
    JsonNode *node;
    JsonObject *object;
    struct u_dict *dict;

    node = query_parser(parser, expr);
    if (!node)
        return NULL;

    if (!JSON_NODE_HOLDS_OBJECT(node)) {
        u_warn("JSON node doesn't contain a valid object!\n");
        return 0;
    }

    object = json_node_get_object(node);
    if (!object) {
        u_warn("Failed to get JSON object from node!\n");
        return NULL;
    }

    dict = u_dict_init();
    if (!dict)
        return NULL;

    json_object_foreach_member(object, object_foreach_handler, dict);

    return dict;
}

int
dump_file(void *key, void *value)
{
    char *filename, *contents;

    filename = key;
    contents = value;

    if (u_dump_string_to_file(filename, contents))
        return 1;

    return 0;
}

static int
parse_message(struct request *req, const char *msg)
{
    JsonParser *parser;

    parser = get_message_parser(msg);
    if (!parser)
        goto ERR_RET;

    req->file_name = get_string(parser, "$.file_name");
    if (!req->file_name)
        goto ERR_FILE_NAME;

    req->clang_args = get_string(parser, "$.clang_args");
    if (!req->clang_args)
        goto ERR_CLANG_ARGS;

    req->line = get_integer(parser, "$.line");
    req->column = get_integer(parser, "$.column");

    req->files = get_dict(parser, "$.file_list");
    if (u_dict_iter(req->files, dump_file))
        u_warn("Failed to create request files!\n");

    g_object_unref(parser);
    return 0;

ERR_CLANG_ARGS:
    u_free(req->file_name);
ERR_FILE_NAME:
    g_object_unref(parser);
ERR_RET:
    return 1;
}

struct request *
request_new(const char *msg)
{
    struct request *req;

    req = u_calloc(1, sizeof(struct request));

    if (parse_message(req, msg)) {
        u_free(req);
        return NULL;
    }

    return req;
}

char *
request_response(struct request *req)
{
    char *data;

    u_assert(req);

    data = complete(req->file_name, req->line, req->column, req->clang_args);
    if (!data) {
        u_warn("Failed to get a valid JSON reponse!\n");
        return NULL;
    }

    return data;
}
