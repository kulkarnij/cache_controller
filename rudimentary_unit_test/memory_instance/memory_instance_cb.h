#ifndef MEMORYINSTANCE_CB_H
#define MEMORYINSTANCE_CB_H
#include "global_defines.h"
SC_MODULE(memory_instance_cb) {
	sc_in <sc_uint<DM_INSTANCE_WIDTH_BITS>> din,dout;
    sc_in <sc_uint<OFFSET_DEPTH>> address;
	sc_in <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_in_clk clk;

    sc_uint<OFFSET_DEPTH> address_d_1;
	void check();
	void delay();
	SC_CTOR(memory_instance_cb) {
		SC_METHOD(delay);
		sensitive<<clk.pos();
		SC_METHOD(check);
		sensitive<<clk.pos();
	}
	
};
#endif
