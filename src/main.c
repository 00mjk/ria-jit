//
// Created by flo on 24.04.20.
//

#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "cache.h"
#include "translate.hpp"
#include "parser.h"
#include "loadElf.h"
#include <getopt.h>

//just temporary - we need some way to control transcoding globally?
bool finalize = false;

//prototypes
int transcode_loop();

t_risc_addr init_entry_pc();

t_risc_addr execute_cached(t_cache_loc loc);

t_cache_loc translate_block(t_risc_addr risc_addr);

int main(int argc, char *argv[]) {
    int opt_index = 0;
    char *file_path = NULL;

    //read command line options (ex. -f for executable file, -v for verbose logging, etc.)
    while ((opt_index = getopt(argc, argv, ":f:vh")) != -1) {
        switch (opt_index) {
            case 'v':
                verbose = true;
                break;
            case 'f':
                file_path = optarg;
                break;
            case ':':
            case 'h':
            default:
                fprintf(stderr, "Usage: dynamic-translate -f <filename> [-v][…]\n");
                return 1;
        }
    }

    printf("Verbose: %d\n", verbose);
    printf("File path: %s\n", file_path);

    if (file_path == NULL) {
        fprintf(stderr, "Bad. Invalid file path.\n");
        return 2;
    }

    printf("Hello World!\n");
    test_parsing();
    transcode_loop(file_path);
    return 0;
}

int transcode_loop(char *file_path) {
    t_risc_elf_map_result result = mapIntoMemory(file_path);
    t_risc_addr pc = result.entry;

    init_hash_table();

    while (!finalize) {
        //check our previously translated code
        t_cache_loc cache_loc = lookup_cache_entry(pc);

        //we have not seen this block before
        if (cache_loc == UNSEEN_CODE) {
            cache_loc = translate_block(pc);
        }

        //execute the cached (or now newly generated code) and update the program counter
        pc = execute_cached(cache_loc);

        //tmp - programm should exit on syscall
        finalize = true;
    }

    return 0;
}

/**
 * Translate the basic block at the passed RISC-V pc address.
 * @param risc_addr the RISC-V address of the basic block in question
 * @return cache location of the translated code
 */
t_cache_loc translate_block(t_risc_addr risc_addr) {
    not_yet_implemented("Translate Block");
    return 0;
}

/**
 * Execute cached translated code at the passed location.
 * @param loc the cache address of that code
 * @return the program counter value after execution of the translated basic block
 */
t_risc_addr execute_cached(t_cache_loc loc) {
    // execute the function at loc
    // check pc = pc[register]
    not_yet_implemented("Execute Cached");
    return 0;
}

t_risc_instr *decode_next() {
    not_yet_implemented("Decode next");
    return NULL;
}

/**
 * Initialize the program counter to the program entry point address.
 * @return initial RISC-V program counter value
 */
t_risc_addr init_entry_pc() {
    not_yet_implemented("Init entry pc");
    return 0;
}
