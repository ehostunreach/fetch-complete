#ifndef REQUEST_H
#define REQUEST_H

struct request {
    char *file_name;
    unsigned line, column;
    char *clang_args;

    struct u_dict *files;
};

struct request *
request_new(const char *msg);

char *
request_response(struct request *req);

void
request_destroy(struct request *req);

#endif /* REQUEST_H */
