#include <go32.h>
#include <sys/farptr.h>
#include <dos.h>
#include <bios.h>
#include <conio.h>

#include "py/runtime.h"


static mp_obj_t mod_dos_inportb(mp_obj_t address) {

    return mp_obj_new_int(inportb(mp_obj_get_int(address)));

}
static MP_DEFINE_CONST_FUN_OBJ_1(mod_dos_inportb_obj, mod_dos_inportb);


static mp_obj_t mod_dos_inportw(mp_obj_t address) {

    return mp_obj_new_int(inportw(mp_obj_get_int(address)));

}
static MP_DEFINE_CONST_FUN_OBJ_1(mod_dos_inportw_obj, mod_dos_inportw);


static mp_obj_t mod_dos_outportb(mp_obj_t address, mp_obj_t value) {

    outportb(mp_obj_get_int(address), mp_obj_get_int(value));
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_2(mod_dos_outportb_obj, mod_dos_outportb);


static mp_obj_t mod_dos_outportw(mp_obj_t address, mp_obj_t value) {

    outportw(mp_obj_get_int(address), mp_obj_get_int(value));
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_2(mod_dos_outportw_obj, mod_dos_outportw);


static mp_obj_t mod_dos_mem_get_byte(mp_obj_t address) {

    return mp_obj_new_int(_farpeekb(_dos_ds, mp_obj_get_int(address)));

}
static MP_DEFINE_CONST_FUN_OBJ_1(mod_dos_mem_get_byte_obj, mod_dos_mem_get_byte);


static mp_obj_t mod_dos_mem_set_byte(mp_obj_t address, mp_obj_t value) {

    _farpokeb(_dos_ds, mp_obj_get_int(address), mp_obj_get_int(value));
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_2(mod_dos_mem_set_byte_obj, mod_dos_mem_set_byte);


static mp_obj_t mod_dos_bios_timeofday() {

    unsigned long time;
    _bios_timeofday(_TIME_GETCLOCK, &time);
    return mp_obj_new_int(time);

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_bios_timeofday_obj, mod_dos_bios_timeofday);


static mp_obj_t mod_dos_enable() {

    enable();
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_enable_obj, mod_dos_enable);


static mp_obj_t mod_dos_disable() {

    disable();
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_disable_obj, mod_dos_disable);


static mp_obj_t mod_dos_kbhit() {

    return mp_obj_new_int(kbhit());

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_kbhit_obj, mod_dos_kbhit);


static mp_obj_t mod_dos_getch() {

    return mp_obj_new_int(getch());

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_getch_obj, mod_dos_getch);


static mp_obj_t mod_dos_getdate() {

    mp_obj_t date_array[3];
    struct date d;

    getdate(&d);
    date_array[0] = mp_obj_new_int(d.da_year);
    date_array[1] = mp_obj_new_int(d.da_mon);
    date_array[2] = mp_obj_new_int(d.da_day);

    return mp_obj_new_tuple(3, date_array);

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_getdate_obj, mod_dos_getdate);


static mp_obj_t mod_dos_setdate(mp_obj_t year, mp_obj_t month, mp_obj_t day) {

    struct date d;

    d.da_year = mp_obj_get_int(year);
    d.da_mon = mp_obj_get_int(month);
    d.da_day = mp_obj_get_int(day);
    setdate(&d);

    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_3(mod_dos_setdate_obj, mod_dos_setdate);


static mp_obj_t mod_dos_gettime() {

    mp_obj_t time_array[4];
    struct time t;

    gettime(&t);
    time_array[0] = mp_obj_new_int(t.ti_hour);
    time_array[1] = mp_obj_new_int(t.ti_min);
    time_array[2] = mp_obj_new_int(t.ti_sec);
    time_array[3] = mp_obj_new_int(t.ti_hund);

    return mp_obj_new_tuple(4, time_array);

}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_dos_gettime_obj, mod_dos_gettime);


static mp_obj_t mod_dos_settime(mp_uint_t n, const mp_obj_t *args) {

    struct time t;

    t.ti_hour = mp_obj_get_int(args[0]);
    t.ti_min = mp_obj_get_int(args[1]);
    t.ti_sec = mp_obj_get_int(args[2]);
    t.ti_hund = mp_obj_get_int(args[3]);
    settime(&t);

    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mod_dos_settime_obj, 4, 4, mod_dos_settime);


static mp_obj_t mod_dos_delay(mp_obj_t ms) {

    delay(mp_obj_get_int(ms));
    return mp_const_none;

}
static MP_DEFINE_CONST_FUN_OBJ_1(mod_dos_delay_obj, mod_dos_delay);


static const mp_map_elem_t mp_module_dos_globals_table[] = {
    {MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_dos)},

    {MP_OBJ_NEW_QSTR(MP_QSTR_inportb), (mp_obj_t)&mod_dos_inportb_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_inportw), (mp_obj_t)&mod_dos_inportw_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_outportb), (mp_obj_t)&mod_dos_outportb_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_outportw), (mp_obj_t)&mod_dos_outportw_obj},

    {MP_OBJ_NEW_QSTR(MP_QSTR_mem_get_byte), (mp_obj_t)&mod_dos_mem_get_byte_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_mem_set_byte), (mp_obj_t)&mod_dos_mem_set_byte_obj},

    {MP_OBJ_NEW_QSTR(MP_QSTR_enable), (mp_obj_t)&mod_dos_enable_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_disable), (mp_obj_t)&mod_dos_disable_obj},

    {MP_OBJ_NEW_QSTR(MP_QSTR_bios_timeofday), (mp_obj_t)&mod_dos_bios_timeofday_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_kbhit), (mp_obj_t)&mod_dos_kbhit_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_getch), (mp_obj_t)&mod_dos_getch_obj},

    {MP_OBJ_NEW_QSTR(MP_QSTR_getdate), (mp_obj_t)&mod_dos_getdate_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_setdate), (mp_obj_t)&mod_dos_setdate_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_gettime), (mp_obj_t)&mod_dos_gettime_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_settime), (mp_obj_t)&mod_dos_settime_obj},

    {MP_OBJ_NEW_QSTR(MP_QSTR_delay), (mp_obj_t)&mod_dos_delay_obj},
};

STATIC MP_DEFINE_CONST_DICT(mp_module_dos_globals, mp_module_dos_globals_table);

const mp_obj_module_t mp_module_dos = {
    .base = { &mp_type_module },
    .name = MP_QSTR_dos,
    .globals = (mp_obj_dict_t*)&mp_module_dos_globals,
};
