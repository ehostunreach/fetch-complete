fetch-complete
==============

fech-complete offers auto-completion results for C/C++ remotely. It listens
for JSON POST requests on a specific port and replies with a response which
contains the available results for auto-completion in JSON format.

The following example demonstrates the JSON format of each request & response:

```bash
curl \
    -X POST \
    -H "Content-Type: application/json" \
    -d '{
        "file_name": "main.c",
        "clang_args": "-Wall -Wextra -g -O0 -c main.c",
        "line": 8,
        "column": 8,
        "file_list": { "main.c": "#include <stdio.h>

        int main(int argc, char *argv[])
        {
                                                          
                                                              
                                                                    
                                                                 
                                                                                                                                                          
                                                                                                                                                          
                                                                                                                                                          
                                                                                                                                                          
                                                                                                                                                          
                    return 0;
                }" }
        }' \
        http://localhost:13333/
```

Output:
```bash

{
    "results" : [
        {
            "typed" : {
                "kind" : "ParmDecl",
                "text" : "argc"
            },
            "chunks" : [
                {
                    "kind" : "ResultType",
                    "text" : "int"
                },
                {
                    "kind" : "TypedText",
                    "text" : "argc"
                }
            ]
        },
        {
            "typed" : {
                "kind" : "ParmDecl",
                "text" : "argv"
            },
            "chunks" : [
                {
                    "kind" : "ResultType",
                    "text" : "char **"
                },
                {
                    "kind" : "TypedText",
                    "text" : "argv"
                }
            ]
        },
        {
            "typed" : {
                "kind" : "FunctionDecl",
                "text" : "fwrite_unlocked"
            },
            "chunks" : [
                {
                    "kind" : "ResultType",
                    "text" : "int"
                },
                {
                    "kind" : "TypedText",
                    "text" : "fwrite_unlocked"
                },
                {
                    "kind" : "LeftParen",
                    "text" : "("
                },
                {
                    "kind" : "Placeholder",
                    "text" : "const void *restrict __ptr"
                },
                {
                    "kind" : "Comma",
                    "text" : ", "
                },
                {
                    "kind" : "Placeholder",
                    "text" : "int __size"
                },
                {
                    "kind" : "Comma",
                    "text" : ", "
                },
                {
                    "kind" : "Placeholder",
                    "text" : "int __n"
                },
                {
                    "kind" : "Comma",
                    "text" : ", "
                },
                {
                    "kind" : "Placeholder",
                    "text" : "FILE *restrict __stream"
                },
                {
                    "kind" : "RightParen",
                    "text" : ")"
                }
            ]
        },

    ...
    ...
    ...
```

### To build:

```
git clone https://github.com/ehostunreach/fetch-complete.git
cd fetch-complete
./autogen.sh
./configure --prefix=<path> --with-llvm-prefix=<llvm-inst-dir>
make && make install
```
