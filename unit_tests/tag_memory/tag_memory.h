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
	sc_out <sc_uint<ASSOCIATIVITY>> set_match_rd, set_match_wr; // fully decoded match vector. 4'b0 is no match.
    sc_out <bool> hit;
	sc_out<bool> evict;
	sc_out<bool> lookup_cycle;
	sc_out<bool> update_cycle;
    sc_out<sc_uint<ASSOCIATIVITY>> snoop; // If any way is being updated and being read at the same time.
	sc_out <bool> read_operation, write_operation; // Current state, driven directly by memory controls. No update cycle in read_operation;

	sc_in <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The set-address of the way to be evicted.

	sc_in <sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_in <sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_in <bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in <bool> reset_n;
	sc_in_clk clk;
//Storage
	sc_uint<TAG_WIDTH> smem0[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem1[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem2[SET_MEMORY_DEPTH];
	sc_uint<TAG_WIDTH> smem3[SET_MEMORY_DEPTH];
	void tag_lookup();
	void write_setmemory();
	void common_assignments();
    void set_update_inputs();
    //assert_zero_one_hot(set_we); // Does not work right now. Check later.
	sc_signal < sc_uint<TAG_WIDTH>> masked_tag_value;
	sc_signal <sc_uint<ASSOCIATIVITY_WIDTH>> current_way; // Used to by set_we
	sc_signal <sc_uint<ASSOCIATIVITY>> current_way_decoded; // Used to by set_we
	sc_signal <sc_uint<TAG_WIDTH>> tag_value_wr; // We are looking for these address bits.
    sc_signal <sc_uint<TAG_DEPTH>> tag_address_wr; // Tag can be stored at this addres in any of the 4 set memories.

	SC_CTOR(tag_memory) 
	{
		SC_METHOD(tag_lookup); // Needed in the same cycle as lookup so that update can proceed next.
		sensitive << tag_value << read_operation<<update_cycle<<lookup_cycle<<tag_address<<tag_address_wr<<set_match_wr;

		SC_METHOD(write_setmemory);
		sensitive << update_cycle << set_match_wr<<tag_address_wr<<tag_value_wr;

        SC_METHOD (common_assignments);
		sensitive <<tag_value<<ce<<we<<oe;  
        SC_METHOD (set_update_inputs);
		sensitive<<clk.pos()<<reset_n.neg();
	}

};

#endif
