#ifndef CC_RESULT_H
#define CC_RESULT_H

struct cc_result {
    struct cc_chunk *typed_chunk;
    struct u_array *chunks;
};

struct cc_result *
cc_result_init(void);

void
cc_result_fini(struct cc_result *res);

void
cc_result_fill(struct cc_result *res, CXCompletionResult *cx_res);

void
cc_result_json(JsonBuilder *builder, struct cc_result *res);

#endif /* CC_RESULT_H */
