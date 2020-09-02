//
// Created by Flo Schmidt on 02.09.20.
//

#ifndef DYNAMICBINARYTRANSLATORRISCV64_X86_64_DISPATCH_H
#define DYNAMICBINARYTRANSLATORRISCV64_X86_64_DISPATCH_H

#include <util/typedefs.h>
#include <gen/translate.h>

void dispatch_instr(const t_risc_instr *instr, const register_info *r_info);

#endif //DYNAMICBINARYTRANSLATORRISCV64_X86_64_DISPATCH_H
