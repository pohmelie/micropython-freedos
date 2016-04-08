/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// options to control how MicroPython is built

#include <mpconfigport.h>

#undef MICROPY_STREAMS_NON_BLOCK
#define MICROPY_STREAMS_NON_BLOCK (0)

#undef MICROPY_PY_SYS_PLATFORM
#define MICROPY_PY_SYS_PLATFORM "freedos"

// djgpp dirent struct does not have d_ino field
#undef _DIRENT_HAVE_D_INO

// djgpp errno.h have no ENOTSUP
#include <errno.h>
#ifndef ENOTSUP
#define ENOTSUP 88
#endif

extern const struct _mp_obj_module_t mp_module_dos;

#undef MICROPY_PORT_BUILTIN_MODULES

#define MICROPY_PY_DOS_DEF { MP_OBJ_NEW_QSTR(MP_QSTR_dos), (mp_obj_t)&mp_module_dos },

#define MICROPY_PORT_BUILTIN_MODULES \
    MICROPY_PY_FFI_DEF \
    MICROPY_PY_JNI_DEF \
    MICROPY_PY_TIME_DEF \
    MICROPY_PY_SOCKET_DEF \
    { MP_ROM_QSTR(MP_QSTR_umachine), MP_ROM_PTR(&mp_module_machine) }, \
    { MP_ROM_QSTR(MP_QSTR_uos), MP_ROM_PTR(&mp_module_os) }, \
    MICROPY_PY_USELECT_DEF \
    MICROPY_PY_TERMIOS_DEF \
    MICROPY_PY_DOS_DEF
