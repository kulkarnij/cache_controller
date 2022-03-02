#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H
#include <systemc.h>
// Everything is byte addressable
#define PROC_WIDTH 32 //32-bit processor.
#define OFFSET_WIDTH  5 // 32bytes in a cache line
#define OFFSET_DEPTH 15 // 1Mbytes/32 32K cache lines
#define SET_WIDTH 13  // Number of lines/associativity
#define TAG_RAW_WIDTH 14  // PROC_ADDR-OFFSET_WIDTH-SET_WIDTH
#define TAG_DEPTH 13  // This should have been 2^13, late to correct at this point.We are using 4 TLB memories of this size.


#define DM_WIDTH  1 << OFFSET_WIDTH  // in bytes
#define DM_WIDTH_BITS  1 << (OFFSET_WIDTH +3) // in bits.
#define DM_DEPTH  1 << OFFSET_DEPTH

// Currently these are hand-calculated due to lack of time but can be calculated similarly. > 64bit memory will need code change
// from sc_int to sc_bigint
#define DM_INSTNCE_WIDTH  4 // 4-byte memory instances.
#define DM_INSTANCE_WIDTH_BITS 32 // use 32-bit memories.  
#define DM_INSTANCE_COUNT 8 // Use 8 32 bit instances. 

// Organize tag memory so that 4 sets can be checked simultaneously. Tag is 14 bit wide, pad it 16 and so final org is 16*4 = 64 bit wide

// These  are handcalulated.
#define TAG_MEMORY_WIDTH  64
#define ASSOCIATIVITY  4 //  4 way associative
#define ASSOCIATIVITY_WIDTH 2  //  2 bits for set number
#define TAG_WIDTH 16 // 2 MSB's are stuffed.
#define SET_MEMORY_DEPTH 1<<TAG_DEPTH
#define TAG_AND_MASK  0X3FFF

#define EVICTION_POLICY 2 // 0 and default: always evict way 0, 1: evict way with lowest valued data,2:lowest nth word.




#endif
