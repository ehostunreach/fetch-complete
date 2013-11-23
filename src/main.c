#include <config.h>
#include <stdlib.h>
#include <libsoup/soup.h>

static void
print_message(SoupMessage *msg, const char *path)
{
    SoupMessageHeadersIter iter;
    const char *name, *value;

    g_print("%s %s HTTP 1.%d\n",
            msg->method, path, soup_message_get_http_version(msg));

    soup_message_headers_iter_init(&iter, msg->request_headers);
    while (soup_message_headers_iter_next(&iter, &name, &value))
        g_print("%s: %s\n", name, value);

    if (msg->request_body->length)
        g_print("%s\n", msg->request_body->data);
}

static void
do_get(SoupServer *server, SoupMessage *msg)
{
    (void) server;
    (void) msg;

    g_print("Processing get message\n");
}

static void
do_put(SoupServer *server, SoupMessage *msg)
{
    (void) server;
    (void) msg;

    g_print("Processing put message\n");
}

static void
server_callback(SoupServer *server, SoupMessage *msg,
                const char *path, GHashTable *query,
                SoupClientContext *context, gpointer data)
{
    (void) query;
    (void) context;
    (void) data;

    print_message(msg, path);

    if (msg->method == SOUP_METHOD_GET || msg->method == SOUP_METHOD_HEAD)
        do_get(server, msg);
    else if (msg->method == SOUP_METHOD_PUT)
        do_put(server, msg);
    else
        soup_message_set_status(msg, SOUP_STATUS_NOT_IMPLEMENTED);

    g_print(" -> %d %s\n\n", msg->status_code, msg->reason_phrase);
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
    g_print("\nStarting server on port %d\n", soup_server_get_port(server));

    soup_server_run_async(server);

    g_print("\nWaiting for requests...\n");

    loop = g_main_loop_new(NULL, TRUE);
    g_main_loop_run(loop);

    return 0;
}
