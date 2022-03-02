#ifndef TAGMEMORY_CB_H
#define TAGMEMORY_CB_H
#include "global_defines.h"
SC_MODULE(tag_memory_cb) {
//DUT outputs
	sc_in <sc_uint<ASSOCIATIVITY>> way_match_rd, way_match_wr; // fully decoded match vector. 4'b0 is no match.
    sc_in <bool> hit;
	sc_in<bool> evict;
	sc_in<bool> lookup_cycle;
	sc_in<bool> update_cycle;
    sc_in<sc_uint<ASSOCIATIVITY>> snoop; // If any way is being updated and being read at the same time.
	sc_in <bool> read_operation, write_operation; // Current state, driven directly by memory controls. No update cycle in read_operation;

	sc_in <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The set-address of the way to be evicted.

	//DUT inputs

	sc_in <sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_in <sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_in <bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in <bool> reset_n;
	sc_in_clk clk;
    uint cycle_count = 1;

	void check();

	SC_CTOR(tag_memory_cb) {
		SC_METHOD(check);
		sensitive<<clk.pos();
	}
	
};
#endif
