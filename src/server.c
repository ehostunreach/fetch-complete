#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsoup/soup.h>
#include "request.h"

static int
process_message(SoupMessage *msg)
{
    struct request *req;
    char *data;

    req = request_new(msg->request_body->data);
    if (!req)
        return 1;

    data = request_response(req);
    if (!data)
        return 1;

    request_destroy(req);

    soup_message_set_response(msg, "application/json",
                              SOUP_MEMORY_TAKE, data, strlen(data));
    soup_message_set_status(msg, SOUP_STATUS_OK);
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
        return;
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
