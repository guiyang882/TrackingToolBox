//
//  wisard.cpp
//
//
//  Created by Maurizio Giordano on 18/01/13.
//
// the WISARD implementation for background extraction
//

#include "wnet_lib.hpp"
#include "wisard.hpp"
#include <iostream>
#include <string>
using namespace std;

u64int_t mypowers[64] = {
    1UL, 2UL, 4UL, 8UL, 16UL, 32UL, 64UL, 128UL, 256UL, 512UL, 1024UL, 2048UL, 4096UL, 8192UL, 16384UL, 32768UL, 65536UL, 131072UL , 262144UL, 524288UL,
    1048576UL, 2097152UL, 4194304UL, 8388608UL, 16777216UL, 33554432UL, 67108864UL, 134217728UL, 268435456UL, 536870912UL, 1073741824UL, 2147483648UL,
    4294967296UL, 8589934592UL, 17179869184UL, 34359738368UL, 68719476736UL, 137438953472UL, 274877906944UL, 549755813888UL, 1099511627776UL, 2199023255552UL, 4398046511104UL, 8796093022208UL, 17592186044416UL, 35184372088832UL, 70368744177664UL, 140737488355328UL, 281474976710656UL, 562949953421312UL, 1125899906842624UL, 2251799813685248UL, 4503599627370496UL, 9007199254740992UL, 18014398509481984UL, 36028797018963968UL, 72057594037927936UL, 144115188075855872UL, 288230376151711744UL, 576460752303423488UL, 1152921504606846976UL, 2305843009213693952UL, 4611686018427387904UL, 9223372036854775808UL
};

extern int status;

cache_entry_t *cacheinit(int nram, int cachesize) {
    cache_entry_t *top, *newp;
    // create first element;
    newp = (cache_entry_t *)malloc(sizeof(cache_entry_t));
    newp->cr = -1;
    newp->cg = -1;
    newp->cb = -1;
    newp->tuple = (int *)malloc(nram * sizeof(int));
    newp->next = newp;
    newp->prev = newp;
    top = newp;
    
    // add other element;
    for (int i=1; i <= cachesize; i++) {
        newp = (cache_entry_t *)malloc(sizeof(cache_entry_t));
        newp->cr = -1;
        newp->cg = -1;
        newp->cb = -1;
        newp->tuple = (int *)malloc(nram * sizeof(int));
        newp->next = top;
        newp->prev = top->prev;
        (top->prev)->next = newp;
        top->prev = newp;
    }
    return top;
}

void printCache(cache_entry_t *cache) {
    cache_entry_t *p;
    if (cache == (cache_entry_t *)NULL) {
        printf("Cache empyty\n");
        return;
    }
    printf("{");
    for (p=cache;p->next != cache; p=p->next ) {
        printf("[%d,%d,%d] ", p->cr, p->cg, p->cb);
    }
    printf("}\n");
}

// net structure (+utilities)
wisard_t *net_create(int n_bit, int im_width, int im_height, string colormode, int nt, int cachesize) {
    register int i, j;
    int npixels;
    int nloc= mypowers[n_bit];
    
    wisard_t *n;
    n=(wisard_t *)malloc(sizeof(wisard_t));
    n->n_bit = n_bit;
    
    // mode delta (differenze)
    if (colormode == "RGB") {
        n->nt = nt;
        // compute number of rams
        if ((n->nt * 3) % n_bit == 0)
            n->n_ram = (int)((n->nt * 3) / n_bit);
        else
            n->n_ram = (int)((n->nt * 3) / n_bit) + 1;
        // compute neighbour mapping
        n->neigh_map = neigh_mapping(n->n_ram, n->n_bit, n->nt, 3, n->neigh_map_raw);
        n->neigh_w = 3;
        n->neigh_h = nt;
    } else if (colormode == "HSV") {
        n->nt = nt;
        // compute number of rams
        if ((n->nt * 2) % n_bit == 0)
            n->n_ram = (int)((n->nt * 2) / n_bit);
        else
            n->n_ram = (int)((n->nt * 2) / n_bit) + 1;
        // compute neighbour mapping
        n->neigh_map = neigh_mapping(n->n_ram, n->n_bit, n->nt, 2, n->neigh_map_raw);
        n->neigh_w = 2;
        n->neigh_h = nt;
    } else {
        cout << "Error: color " << colormode << " mode not supported!" << endl;
    }
    // creates the neural network list.
    // each neuron is a hash-table, and a
    // discriminator is a list of neurons
    npixels = im_width * im_height;
    wentry_t ***net;
    net = (wentry_t ***)malloc(npixels * sizeof(wentry_t **));
    // alloc tuple cache
    cache_entry_t **cache;
    cache = (cache_entry_t **)malloc(npixels * sizeof(cache_entry_t *));
    for (i = 0; i < npixels; i++) {
        net[i] = (wentry_t**)malloc(n->n_ram * sizeof(wentry_t*));
        cache[i] = (cache_entry_t *)cacheinit(n->n_ram,cachesize);
        for (j=0; j < n->n_ram; j++) {
            net[i][j] = wram_create();
        }
    }

    n->net = net;
    n->cachearray = cache;

    return n;
}

// returns a random element of a sequence,
// consuming it. Heavily optimized version
pix_t select(std::pair < int, int> *seq, int *dim) {
    int pos;
    pix_t elem;
    if (*dim == 1) {
        //printf("LAST ");
        *dim = *dim - 1;
        return seq[*dim];
    } else if (*dim > 1) {
        pos = rand() % (*dim-1);
        //printf("POS %d ",pos);
        elem = seq[pos];
        seq[pos] = seq[*dim-1];
        seq[*dim-1] = elem;
        *dim = *dim - 1;
        //free(seq[*dim-1]);
    } else {
        elem = make_pair(-1,0);
    }
    return elem;
}

// random neighbor_mapping creation:
pix_t **neigh_mapping(int n_ram, int n_bit, int w, int h, std::pair <int, int>* raw_map) {
    register int i,j;
    pix_t *pixels, *tmp, **input_map;
    std::pair <int, int> *pixels_raw, *tmp_raw, **input_map_raw;
    int npixels;
    
    // init source pixels (ram_index, bit_index)
    npixels = n_ram * n_bit;
    pixels = (pix_t*)malloc(npixels * sizeof(pix_t));
    pixels_raw = (std::pair <int, int> *)malloc(npixels * sizeof(std::pair <int, int>));
    for (i = 0; i < n_ram; i++)
        for (j=0; j < n_bit; j++) {
            pixels[i * n_bit + j] = make_pair(i,mypowers[j]);
            pixels_raw[i * n_bit + j] = make_pair(i,j);
    }
    // create as many full neuron mappings as
    // possible with the existing pixels
    input_map = (pix_t**)malloc(h * sizeof(pix_t*));
    raw_map = (std::pair <int, int> *)malloc(w * h * sizeof(std::pair <int, int>));
    for (i=0; i<h;i++) {
        tmp = (pix_t*)malloc(w * sizeof(pix_t));
        for (j=0;j<w;j++) {
            //tmp[j] = make_pair(i,mypowers[j]); OLD
            raw_map[i * w + j] = select(pixels_raw,&npixels);
            tmp[j] = make_pair(raw_map[i * w + j].first,mypowers[raw_map[i * w + j].second]);
        }
        input_map[i] = tmp;
    }
    return input_map;
}


// create a dynamic array of int (ram entries)
int *wnet_create(int size) {
    int i;
    int *m;
    m=(int *)malloc(size * sizeof(int));
    return m;
}

// discriminator print utility functions
void wnet_print(int *m, int size) {
    int i;
    
    printf("{");
    for (i=0;i<size;i++) {
        if (m[i]>0) {
            printf("%d:%d", i, m[i]);
            if (i!=size-1) printf(" ");
        }
    }
    printf("}");
}

void wnet_print2(int *m, int size) {
    int i;
    
    printf("{");
    for (i=0;i<size;i++) {
        printf("%d:%d", i, m[i]);
        if (i!=size-1) printf(" ");
    }
    printf("}");
}

// wisard print function
void print_net(int ***net, int dim, int n_ram, int n_loc) {
    int x,y;
    printf("[");
    for (x = 0; x < dim; x++) {
        if (x!=0) printf(" ");
        printf("<");
        for (y = 0; y < n_ram; y++)
            wnet_print(net[x][y], n_loc);
        printf(">");
        if (x!=dim -1) printf(",\n");
    }
    printf("]");

}

// count non-zero ram entries
int wnet_len(int *m, int size) {
    int i,cnt=0;
    
    for (i=0;i<size;i++) {
        if (m[i]>0) cnt++;
    }
    return cnt;
}

void net_free(int ***net, int dim, int n_ram) {
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j=0; j < n_ram; j++) {
            free(net[i][j]);
            net[i][j] = NULL;
        }
        free(net[i]);
    }
    free(net);
}

