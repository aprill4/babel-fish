#include "ast.h"
#include "IRBuilder.h"
#include "arm.h"
#include "pass.h"
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

extern int scan_string(const char *str);
extern int yyparse();
extern Root *root;

void print_help(char *program) {
    printf("Usage: %s", program);
    printf(" [ -h | --help ] [ -O2 ] [ -o <output-asm = test.s> ] <input-file = test.c>\n");
}

std::string input_command;

bool match(char *a, const char *b) {
    return strcmp(a, b) == 0;
}

static char *read_entire_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (!fp) {
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    auto length = ftell(fp);
    assert(length != -1);
    rewind(fp);

    char *buffer = (char *)malloc(length+1);

    if (!buffer) {
        return nullptr;
    }

    if (fread(buffer, 1, length, fp) == 0) {
        return nullptr;
    }

    buffer[length] = '\0';

    fclose(fp);

    return buffer;
}

int main(int argc, char** argv) {

    if (argc == 1) {
        print_help(argv[0]);
        return 1;
    }

    const char *source_file = "test.c";
    const char *output_file = "test.s";
    bool enable_optimization = false;

    for (int i = 1; i < argc; ++i) {
        if (match(argv[i], "-h") || match(argv[i], "--help")) {
            print_help(argv[0]);
            return 0;
        } else if (match(argv[i], "-o")) {
            if (i + 1 < argc) {
                output_file = argv[i + 1];
                i += 1;
            } else {
                print_help(argv[0]);
                return 0;
            }
        } else if (match(argv[i], "-O2") || match(argv[i], "-O1") || match(argv[i], "-O")) {
            enable_optimization = true;
        } else if (match(argv[i], "-S")) {
        } else {
            source_file = argv[i];
        }
    }

    cout << source_file << endl;
    auto file_content = read_entire_file(source_file);
    scan_string(file_content);
    yyparse();

    IRBuilder * irBuilder = new IRBuilder();
    root->generate(irBuilder);
    //cout << R"(target triple = "x86_64-pc-linux-gnu")" << endl << endl;

    auto m = irBuilder->getModule();

    //cout << m->print() << endl;

    auto mm = emit_asm(m);

    mm->print(stdout);
    printf("\n\n");

    stack_ra(mm);
    //mm->print(stdout);
    // remove_redundant_load(mm);

    mm->print(stdout);

    FILE *out = fopen(output_file, "w");
    mm->print(out);


    return 0;
}

