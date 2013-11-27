#include <stdio.h>
#include <stdint.h>
#include <json-glib/json-glib.h>
#include "request.h"

static JsonParser *
get_message_parser(const char *msg)
{
    JsonParser *parser;
    size_t size;

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
get_query_result(JsonNode *root, char *expression)
{
    JsonNode *result;
    JsonArray *array;
    unsigned length;

    result = json_path_query(expression, root, NULL);
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
        u_warn("Bad array length: %u\n", length);
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
get_string(JsonParser *parser, char *expr)
{
    JsonNode *root, *node;
    const char *str;

    root = json_parser_get_root(parser);
    if (!root) {
        u_warn("Failed to get parser root!\n");
        return NULL;
    }

    node = get_query_result(root, expr);
    if (!node)
        return NULL;

    str = json_node_get_string(node);
    if (!str) {
        u_warn("Failed to get JSON node's string!\n");
        return NULL;
    }

    return u_strdup(str);
}

static int
get_integer(JsonParser *parser, char *expr)
{
    JsonNode *root, *node;

    root = json_parser_get_root(parser);
    if (!root) {
        u_warn("Failed to get parser root!\n");
        return 0;
    }

    node = get_query_result(root, expr);
    if (!node)
        return 0;

    return (int) json_node_get_int(node);
}

static void
object_foreach_handler(JsonObject *object,
                       const char *member_name,
                       JsonNode *member_node,
                       gpointer user_data)
{
    struct u_dict *dict = user_data;
    char *key, *value;

    key = u_strdup(member_name);
    value = u_strdup(json_node_get_string(member_node));

    u_dict_add(dict, key, value);
}

static struct u_dict *
get_dict(JsonParser *parser, char *expr)
{
    JsonNode *root, *node;
    JsonObject *object;
    struct u_dict *dict;

    root = json_parser_get_root(parser);
    if (!root) {
        u_warn("Failed to get parser root!\n");
        return NULL;
    }

    node = get_query_result(root, expr);
    if (!node)
        return NULL;

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

    req = u_malloc(sizeof(struct request));
    if (!req)
        return NULL;

    if (parse_message(req, msg)) {
        u_free(req);
        return NULL;
    }

    return req;
}
