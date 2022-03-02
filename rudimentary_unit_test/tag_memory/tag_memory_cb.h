#ifndef TAGMEMORY_CB_H
#define TAGMEMORY_CB_H
#include "global_defines.h"
SC_MODULE(tag_memory_cb) {
	sc_in <sc_uint<ASSOCIATIVITY>> set_match; // fully decoded match vector. 4'b0 is no match.
    sc_in <bool> hit;
	sc_in <sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_in <sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_in <bool> ce,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in<sc_uint<ASSOCIATIVITY_WIDTH>> set_we; // Store tag at a particular set.
	sc_in_clk clk;
	void check();
	void delay();
	sc_signal <sc_uint<TAG_WIDTH>> tag_value_d_1; // We are looking for these address bits.
    sc_signal <sc_uint<TAG_DEPTH>> tag_address_d_1; // Tag can be stored at this addres in any of the 4 set memories.
	SC_CTOR(tag_memory_cb) {
		SC_METHOD(delay);
		sensitive<<clk.pos();
		SC_METHOD(check);
		sensitive<<tag_address<<tag_value<<set_match<<set_we;
	}
	
};
#endif
