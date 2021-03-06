# FreeDOS ad-hoc module for [micropython](https://github.com/micropython/micropython)

Fun time of python on embedded FreeDOS boards is come!

This is only «some» files of build (see building part at [micropython wiki](https://github.com/micropython/micropython/wiki/Building-micropython-for-FreeDOS)).

Binary releases available at https://github.com/pohmelie/micropython-freedos/releases

## Building
1. Follow the [freedos build guide](https://github.com/micropython/micropython/wiki/Building-micropython-for-FreeDOS).
2. Before building micropython copy this repo files to `micropython/unix` directory overwriting.

## `dos` module
Micropython extended with `dos` module, which have some classic DOS functions:
* `inportb`, `inportw`, `outportb`, `outportw` for port io.
* `mem_get_byte`, `mem_set_byte` for **slow** far pointers.
* `fmemcpy(address, bytes)` for **fast** far memory copy.
* `enable`, `disable` interrupts.
* `bios_timeofday`, `gettime`, `settime`, `getdate`, `setdate` for some datetime manipulation.

## Next extending
Dos module (or another) one can be simply extended. Here is some pattern, cause right now there is no developer api explanation on micropython wiki/docs.

1. `#include "py/runtime.h"`, which contains all(?) macros you need for developing.
2. Define your function in format like

    `static mp_obj_t mod_modulename_funcname(mp_obj_t arg1, mp_obj_t arg2, mp_obj_t arg3)`

    If your function have more than 3 arguments, then use

    `static mp_obj_t mod_modulename_funcname(size_t n, const mp_obj_t *args)`

3. «Fill» function body.

    To unpack arguments you should use `mp_obj_get_` macros(?) family or similar, I have no experience with data structures as arguments right now, but I think they use something similar.

4. Return result of your function.

    If it is `None`, then `mp_const_none`, else you need to build proper micropython object with `mp_obj_new_` macros family or similar.

5. Add «magic» macros.

    If argument count is in [0..3] the use

    `MP_DEFINE_CONST_FUN_OBJ_x(mod_modulename_funcname_obj, mod_modulename_funcname);`

    where «x» is in [0..3] and for variable arguments count:

    `MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mod_modulename_funcname_obj, min_args_count, max_args_count, mod_modulename_funcname);`

6. Declare your module «names» structure.

    ```
    static const mp_rom_map_elem_t mp_module_modulename_globals_table[] = {
        {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_modulename)},

        {MP_ROM_QSTR(MP_QSTR_funcname), MP_ROM_PTR(&mod_modulename_funcname_obj)},
    };
    ```

7. Declare final part of module.

    ```
    STATIC MP_DEFINE_CONST_DICT(mp_module_modulename_globals, mp_module_modulename_globals_table);

    const mp_obj_module_t mp_module_modulename = {
        .base = { &mp_type_module },
        .globals = (mp_obj_dict_t*)&mp_module_modulename_globals,
    };
    ```
8. Add your module to `Makefile`.

    ```
    SRC_MOD += modulename.c
    ```

9. Add your module to `mpconfigport_freedos.h`, so it will be builtin.

    ```
    extern const struct _mp_obj_module_t mp_module_modulename;
    #define MICROPY_PY_MODULENAME_DEF { MP_ROM_QSTR(MP_QSTR_modulename), MP_ROM_PTR(&mp_module_modulename) },

    #undef MICROPY_PORT_BUILTIN_MODULES
    #define MICROPY_PORT_BUILTIN_MODULES \
        ... \
        MICROPY_PY_MODULENAME_DEF
    ```
