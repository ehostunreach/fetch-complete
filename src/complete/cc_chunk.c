#include <json-glib/json-glib.h>
#include <utils/utils.h>
#include "cc_chunk.h"

struct cc_chunk *
cc_chunk_init(const char *kind, const char *text)
{
    struct cc_chunk *chunk;

    u_assert(kind && text);

    chunk = u_malloc(sizeof(struct cc_chunk));

    chunk->kind = u_strdup(kind);
    chunk->text = u_strdup(text);

    return chunk;
}

void
cc_chunk_fini(struct cc_chunk *chunk)
{
    u_assert(chunk && chunk->kind && chunk->text);

    if (chunk->kind)
        u_free(chunk->kind);
    if (chunk->text)
        u_free(chunk->text);
    if (chunk)
        u_free(chunk);
}

void
cc_chunk_json(JsonBuilder *builder, struct cc_chunk *chunk)
{
    u_assert(builder && chunk);

    json_builder_begin_object(builder);

        json_builder_set_member_name(builder, "kind");
        json_builder_add_string_value(builder, chunk->kind);

        json_builder_set_member_name(builder, "text");
        json_builder_add_string_value(builder, chunk->text);

    json_builder_end_object(builder);
}
