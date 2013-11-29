#ifndef CC_CHUNK_H
#define CC_CHUNK_H

struct cc_chunk {
    char *kind;
    char *text;
};

struct cc_chunk *
cc_chunk_init(const char *kind, const char *text);

void
cc_chunk_fini(struct cc_chunk *chunk);

void
cc_chunk_json(JsonBuilder *builder, struct cc_chunk *chunk);

#endif /* CC_CHUNK_H */
