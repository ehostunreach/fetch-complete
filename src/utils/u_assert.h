#ifndef U_ASSERT_H
#define U_ASSERT_H

#if !defined(__INSIDE_UTILS__) && !defined(UTILS_COMPILATION)
#error "Only <utils.h> can be included directly"
#endif

#include <assert.h>

#define u_assert(expr)      assert((expr))

#endif /* U_ASSERT_H */
