#ifndef CC_REQUEST_H
#define CC_REQUEST_H

struct cc_request {
    int cx_argc;
    char **cx_argv;

    CXIndex cx_idx;
    CXTranslationUnit cx_tu;
    CXCodeCompleteResults *cx_res;

    char *fname;
    unsigned row, col;
    struct u_array *res;
};

struct cc_request *
cc_request_init(const char *fname,
                unsigned line,
                unsigned column,
                const char *clang_args);

void
cc_request_fini(struct cc_request *req);

int
cc_request_run(struct cc_request *req);

void
cc_request_json(JsonBuilder *bld, struct cc_request *req);

#endif /* CC_REQUEST_H */
