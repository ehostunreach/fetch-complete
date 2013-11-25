#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

struct request {
    char *source_code;
    unsigned line, column;
    char *clang_args;
};

static struct request *
get_request_from_json_object(JsonObject *object)
{
    struct request *req;
    unsigned line, column;
    const char *source_code, *clang_args;

    /* extract keys/values from object */
    line = json_object_get_int_member(object, "line");
    column = json_object_get_int_member(object, "column");

    source_code = json_object_get_string_member(object, "source_code");
    clang_args = json_object_get_string_member(object, "clang_args");
    if (!source_code || !clang_args) {
        g_print("Missing keys from JSON data!\n");
        return NULL;
    }

    /* allocate and fill the request */
    req = g_malloc(sizeof(struct request));
    if (!req) {
        g_printerr("Out of memory!\n");
        return NULL;
    }

    req->line = line;
    req->column = column;

    req->source_code = g_strdup(source_code);
    if (!req->source_code) {
        g_printerr("out of memory!\n");

        g_free(req);
        return NULL;
    }

    req->clang_args = g_strdup(clang_args);
    if (!req->clang_args) {
        g_printerr("out of memory!\n");

        g_free(req->source_code);
        g_free(req);
        return NULL;
    }

    return req;
}

static struct request *
get_request_from_message(SoupMessage *msg)
{
    struct request *req;
    JsonParser *parser;
    JsonNode *root;
    JsonObject *object;

    /* create parser */
    parser = json_parser_new();
    if (!parser) {
        g_printerr("Failed to create json parser!\n");
        return NULL;
    }

    /* read json data */
    if (!json_parser_load_from_data(parser, msg->request_body->data,
                                    msg->request_body->length, NULL))
    {
        g_printerr("Failed to parse JSON data!\n");
        g_object_unref(parser);
        return NULL;
    }

    /* get root node */
    root = json_parser_get_root(parser);
    if (!root) {
        g_printerr("Bad JSON root node\n");
        g_object_unref(parser);
        return NULL;
    }

    /* get root object */
    object = json_node_get_object(root);
    if (!object) {
        g_printerr("Bad object in JSON node!\n");
        g_object_unref(parser);
        return NULL;
    }

    req = get_request_from_json_object(object);
    g_object_unref(parser);
    return req;
}

static int
process_message(SoupMessage *msg)
{
    struct request *req;

    req = get_request_from_message(msg);
    if (!req)
        return -1;


    g_free(req->source_code);
    g_free(req->clang_args);
    g_free(req);
    return 0;
}

static void
server_callback(SoupServer *server, SoupMessage *msg,
                const char *path, GHashTable *query,
                SoupClientContext *context, gpointer data)
{
    (void) server;
    (void) path;
    (void) query;
    (void) context;
    (void) data;

    if (msg->method != SOUP_METHOD_POST) {
        soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);
        return;
    }

    if ((msg->request_body->length > 0) && (process_message(msg) == 0))
        soup_message_set_status(msg, SOUP_STATUS_OK);
    else
        soup_message_set_status(msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
}

int main(int argc, char *argv[])
{
    GMainLoop *loop;
    SoupServer *server;
    int port = 13333;

    (void) argc;
    (void) argv;

    server = soup_server_new(SOUP_SERVER_PORT, port,
                             SOUP_SERVER_SERVER_HEADER, "auto-complete",
                             NULL);
    if (!server) {
        g_printerr("Unable to bind to server port %d\n", port);
        exit(1);
    }

    soup_server_add_handler(server, NULL, server_callback, NULL, NULL);
    soup_server_run_async(server);

    g_print("\nWaiting for requests on port %u...\n", port);

    loop = g_main_loop_new(NULL, TRUE);
    g_main_loop_run(loop);

    return 0;
}
