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

void
request_destroy(struct request *req);

#endif /* REQUEST_H */
