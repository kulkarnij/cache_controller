#ifndef TAG_MEMORY_H
#define TAG_MEMORY_H
#include "global_defines.h"

//For quick read, associativity is 4, TAG_WIDTH is 16 , 2MSBs are stuffed, TAG_DEPTH is 13, associativity width is 2.
//SET_MEMORY_DEPTH is 2^13
//At this point, a two cycle operation is envisioned: For reading or writing cache line: First operation is always tag_lookup
//This modifies determines the set address bits for the next operation. For reading with a match: There is no tag mem op, only data_mem read.
//For reading without match, there is no "next op. The MMU may decide to read from main mem and write to cache.
//For write with all sets full, set address is determined by the eviction controller.
// For write with vacancy, set address is determined. In both the cases, a modified write address should show in the next cycle.

SC_MODULE (tag_memory) {
//Ports
	sc_out <sc_uint<ASSOCIATIVITY>> set_match; // fully decoded match vector. 4'b0 is no match.
    sc_out <bool> hit;
	sc_in <sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_in <sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_in <bool> ce,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in<sc_uint<ASSOCIATIVITY_WIDTH>> set_we; // Store tag at a particular set.
	sc_in_clk clk;
//Storage
	sc_uint<TAG_WIDTH> smem0[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem1[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem2[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem3[SET_MEMORY_DEPTH];
	void tag_lookup();
	void write_setmemory();
	void common_assignments();
    sc_signal <bool> no_write;
    //assert_zero_one_hot(set_we); // Does not work right now. Check later.
   sc_signal < sc_uint<TAG_WIDTH>> masked_tag_value;

SC_CTOR(tag_memory) 
	{
		SC_METHOD(tag_lookup);
		//sensitive << tag_value << ce << oe << set_we;
		//Make outputs synchronous
		sensitive << clk.pos();
		SC_METHOD(write_setmemory);
		sensitive << masked_tag_value << ce << oe << set_we << no_write;
        SC_METHOD (common_assignments)
        sensitive << tag_value << set_we << set_match;
	}

};

#endif
