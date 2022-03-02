#ifndef TAGMEMORY_TB_H
#define  TAGMEMORY_TB_H
#include "global_defines.h"

SC_MODULE (tag_memory_tb){
	sc_out <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The set-address of the way to be evicted.
	sc_out <sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_out <sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_out <bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_out <bool> reset_n;
	sc_in_clk clk;



	
	void evict_once_then_update();
	int cycle_count = 0;
	SC_CTOR(tag_memory_tb) {
        SC_METHOD(evict_once_then_update);
		sensitive<<clk.neg();
	}
		
};
#endif
