//
//  wnet_lib.hpp
//
//
//  Created by Maurizio Giordano on 18/01/13.
//
//


#ifndef wnet_LIB_H
#define wnet_LIB_H

#include <utility>
#include <stdlib.h>
#include <stdio.h>

extern long int wcounter;

typedef unsigned long int u64int_t;

typedef struct wentry wentry_t;
typedef u64int_t wkey_t;
typedef double wvalue_t;
typedef std::pair < wkey_t, wvalue_t > keyval_t;


struct wentry {
    wkey_t key;
    wvalue_t value;
    wentry_t *next;
    wentry_t *prev;
};

typedef std::pair <int, u64int_t> pix_t;

wentry_t *wram_create();
void wram_set(wentry_t *m, wkey_t key, wvalue_t value);
void wram_set_or_incr(wentry_t *m, wkey_t key, wvalue_t value, wvalue_t incr);
void wram_del(wentry_t *m, wkey_t key);
wvalue_t wram_get(wentry_t *m, wkey_t key);
void wram_incr(wentry_t *m, wkey_t key, wvalue_t incr);
void wram_incr_top(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t top);
void wram_decr(wentry_t *m, wkey_t key);
void wram_decr_or_del(wentry_t *m,wkey_t key,wvalue_t decr);
void wram_decr_all_but_key(wentry_t *m, wkey_t key,wvalue_t incr,wvalue_t decr);
keyval_t wram_up_key_down_rest(wentry_t *m, wkey_t key,wvalue_t incr,wvalue_t decr,wvalue_t top);
keyval_t wram_up_key(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t top);
void wram_decr_all_but_key_top(wentry_t *m, wkey_t key,wvalue_t incr,wvalue_t decr,wvalue_t top);
unsigned long wram_len(wentry_t *m);
void wram_print(wentry_t *m);
void printDiscr(wentry_t **d, int size);
void wram_free(wentry_t *m);
void intuple_print(wkey_t *vector, long size);
wentry_t *wram_copy(wentry_t *m);
void wram_sink(wentry_t *m);
#endif
