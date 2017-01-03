//
//  wnet_lib.cpp
//
//
//  Created by Maurizio Giordano on 02/02/13.
//
// a library for ram creation, initialization and print
// rams are circular lists of pairs key value
//

#include <string>
#include "wnet_lib.hpp"

using namespace std;

// create (and init) a ram
wentry_t *wram_create() {
    wentry_t *m;
    wcounter++;
    m = (wentry_t *)malloc(sizeof(wentry_t));
    m->key = -1;
    m->value = -1;
    m->next = m;
    m->prev = m;
    return m;
}
    
// set ram entry to "value"
// if ram is empty, initalize it
void wram_set(wentry_t *m, wkey_t key,wvalue_t value) {
        wentry_t *p, *newp;
    
        // circulate in list for insertion
        p = m;
        for (;;) {
            p = p->next;
            if (p ==m || key <= p->key) break;
        }
        // the key already exists (update)
        if (key == p->key) {
            // delete item if value is null
            if (value==0) {
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                free(p);
            } else {
                p->value = value;
            }
        // the key does not exist (insertion)
        } else {
            wcounter++;
            newp = (wentry_t *)malloc(sizeof(wentry_t));            
            newp->key = key;
            newp->value = value;
            newp->next = p;
            newp->prev = p->prev;
            (p->prev)->next = newp;
            p->prev = newp;
        }
        return;
}

// put ram entry to zero
void wram_del(wentry_t *m, wkey_t key) {
    wentry_t *p;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (key == p->key) {
            (p->prev)->next = p->next;
            (p->next)->prev = p->prev;
            free(p);
            break;
        }
        if (p ==m) break;
    }
}

// get ram entry
wvalue_t wram_get(wentry_t *m, wkey_t key) {
    wentry_t *p;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (key == p->key) return p->value;
        if (p ==m) return (wvalue_t)0;
    }
}

// if ram entry exists increment its value by "incr"
// otherwise ram entry is inserted and set to "value"
void wram_set_or_incr(wentry_t *m, wkey_t key, wvalue_t value, wvalue_t incr) {
    wentry_t *p, *newp;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m || key <= p->key) break;
        //if (key >= p->key) break;
    }
    // the key already exists (update)
    if (key == p->key) {
        p->value += incr;
        // the key does not exist (insertion)
    } else {
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        newp->value = value;
        newp->next = p;
        newp->prev = p->prev;
        (p->prev)->next = newp;
        p->prev = newp;
    }
    return;
}

// if ram entry exists increment its value by "incr"
// otherwise ram entry is inserted and set to "value"
void wram_incr(wentry_t *m, wkey_t key,  wvalue_t incr) {
    wentry_t *p, *newp;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m || key <= p->key) break;
        //if (key >= p->key) break;
    }
    // the key already exists (update)
    if (key == p->key) {
        p->value += incr;
        // the key does not exist (insertion)
    } else {
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        newp->value = incr;
        newp->next = p;
        newp->prev = p->prev;
        (p->prev)->next = newp;
        p->prev = newp;
    }
    return;
}

// if ram entry exists increment its value by "incr"
// otherwise ram entry is inserted and set to "value"
void wram_incr_top(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t top) {
    wentry_t *p, *newp;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m || key <= p->key) break;
        //if (key >= p->key) break;
    }
    // the key already exists (update)
    if (key == p->key) {
        if ((p->value + incr) < top) p->value += incr;
        // the key does not exist (insertion)
    } else {
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        newp->value = incr;
        newp->next = p;
        newp->prev = p->prev;
        (p->prev)->next = newp;
        p->prev = newp;
    }
    return;
}


void wram_decr(wentry_t *m,wkey_t key) {
    wentry_t *p;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        if (key == p->key) {
            if ((p->value - (wvalue_t)1) <= 0) {
                // remove entry
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                free(p);
            } else {
                // decrease the entry
                p->value -= (wvalue_t)1;
            }
            break;
        }
    }
    return;
}

void wram_decr_all_but_key(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t decr) {
    wentry_t *p, *rp, *newp;
    bool notfound = true;
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        if (key == p->key) {  // the key exists (increase it!)
            notfound = false;
            p->value += incr;
        } else {              // the key does not match (decrease it!)
            if ((p->value - decr) < 1) {
                // remove entry
                rp = p;
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                p = p->next;
                free(rp);
                wcounter--;
            } else {
                // decrease the entry
                p->value -= decr;
            }
        }
    }
    if (notfound) {            // the key does not exists (insert it!)
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        newp->value = incr;
        newp->next = m;
        newp->prev = m->prev;
        (m->prev)->next = newp;
        m->prev = newp;
    }
    return;
}

keyval_t wram_up_key_down_rest(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t decr, wvalue_t top) {
    wentry_t *p, *rp, *newp;
    bool notfound = true;
    wkey_t maxk = (wkey_t)0;
    wvalue_t maxv = (wvalue_t)0;
    // circulate in list for decrement
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        if (key == p->key) {  // the key exists (do nothing!)
            ;
        } else {              // the key does not match (decrease it!)
            if ((p->value - decr) < 1) {
                // remove entry
                rp = p;
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                p = p->prev;
                free(rp);
                wcounter--;
            } else {
                // decrease the entry
                p->value -= decr;
                if (maxv < p->value) { maxk = p->key; maxv = p->value; }
            }
        }
    }
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m || key <= p->key) break;
    }
    // the key already exists (update)
    if (key == p->key) {
        if ((p->value + incr) < top) p->value += incr;
        else p->value = top;
        if (maxv < p->value) { maxk = key; maxv = p->value; }
        // the key does not exist (insertion)
    } else {
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        if (incr < top) newp->value = incr;
        else newp->value = top;
        newp->next = p;
        newp->prev = p->prev;
        (p->prev)->next = newp;
        p->prev = newp;
        if (maxv < newp->value) { maxk = key; maxv = newp->value; }
    }
    return make_pair(maxk, maxv);
}

keyval_t wram_up_key(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t top) {
    wentry_t *p, *rp, *newp;
    bool notfound = true;

    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m || key <= p->key) break;
    }
    // the key already exists (update)
    if (key == p->key) {
        if ((p->value + incr) < top) p->value += incr;
        else p->value = top;
        return make_pair(p->key, p->value);
        // the key does not exist (insertion)
    } else {
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        if (incr < top) newp->value = incr;
        else newp->value = top;
        newp->next = p;
        newp->prev = p->prev;
        (p->prev)->next = newp;
        p->prev = newp;
        return make_pair(newp->key, newp->value);
    }
}


void wram_decr_all_but_key_top(wentry_t *m, wkey_t key, wvalue_t incr, wvalue_t decr, wvalue_t top) {
    wentry_t *p, *rp, *newp;
    bool notfound = true;
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        if (key == p->key) {  // the key exists (increase it!)
            notfound = false;
            if ((p->value + incr) < top) p->value += incr;
        } else {              // the key does not match (decrease it!)
            if ((p->value - decr) < 1) {
                // remove entry
                rp = p;
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                p = p->next;
                free(rp);
                wcounter--;
            } else {
                // decrease the entry
                p->value -= decr;
            }
        }
    }
    if (notfound) {            // the key does not exists (insert it!)
        wcounter++;
        newp = (wentry_t *)malloc(sizeof(wentry_t));
        newp->key = key;
        newp->value = incr;
        newp->next = m;
        newp->prev = m->prev;
        (m->prev)->next = newp;
        m->prev = newp;
    }
    return;
}

void wram_decr_or_del(wentry_t *m,wkey_t key,wvalue_t decr) {
    wentry_t *p;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        if (key == p->key) {
            if ((p->value - decr) <= 0) {
                // remove entry
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                free(p);
            } else {
                // decrease the entry
                p->value -= decr;
            }
            break;
        }
    }
    return;
}

// count non-zero ram entries
unsigned long wram_len(wentry_t *m) {
    wentry_t *p;
    int cnt=0;
    
    // circulate in list for insertion
    p = m;
    for (;;) {
        p = p->next;
        if (p ==m) break;
        else cnt++;
    }
    return cnt;
}

wentry_t *wram_copy(wentry_t *m) {
    wentry_t *p, *cp;
    
    cp = wram_create();
    for(p=m;;p=p->next) {
        if (p->next==m) break;
        wram_set(cp, p->next->key, p->next->value);
    }
    return cp;
}

// decrease all ram entries at once
void wram_sink(wentry_t *m) {
    wentry_t *p;
    
    p = m;
    for (;;) {
        if (p->next==m) break;
        p = p->next;
        if (p->value > 1) p->value -= 1;
        else {
            (p->prev)->next = p->next;
            (p->next)->prev = p->prev;
            free(p);
        }
    }
}

// discriminator print utility functions
void wram_print(wentry_t *m) {
    wentry_t *p;
    
    fprintf(stdout,"{");
    for(p=m;;p=p->next) {
        if (p->next==m) break;
        if (p->next->next==m) fprintf(stdout,"%lu:%f", p->next->key, p->next->value);
        else fprintf(stdout,"%lu:%1.0f,", p->next->key, p->next->value);
    }
    fprintf(stdout,"}");
}

void printDiscr(wentry_t **d, int nram) {
    wentry_t *p;
    
    fprintf(stdout,"[");
    for (int neuron=0; neuron<nram; neuron++) {
        fprintf(stdout,"{");
        for(p=d[neuron];;p=p->next) {
            if (p->next==d[neuron]) break;
            if (p->next->next==d[neuron]) fprintf(stdout,"%lu:%1.0f", p->next->key, p->next->value);
            else fprintf(stdout,"%lu:%1.0f,", p->next->key, p->next->value);
        }
        fprintf(stdout,"}");
    }
    fprintf(stdout,"]\n");
}

// free ram
void wram_free(wentry_t *m) {
    free(m);
    m=(wentry_t *)NULL;
}

void intuple_print(wkey_t *vector, long size) {
    long i;
    fprintf(stdout,"[");
    for (i = 0; i < size; i++) {
        if (vector[i]) fprintf(stdout,"%li", vector[i]);
        if (i != size -1) fprintf(stdout,".");
    }
    fprintf(stdout,"]\n");
}


