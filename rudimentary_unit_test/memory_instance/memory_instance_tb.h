#ifndef MEMORY_INSTANCE_TB_H
#define  MEMORY_INSTANCE_TB_H
#include "global_defines.h"

SC_MODULE (memory_instance_tb){
	sc_out <sc_uint<DM_INSTANCE_WIDTH_BITS>> din;
    sc_out <sc_uint<OFFSET_DEPTH>> address;
	sc_out <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_in_clk clk;
	void simple_write_read1();
	int cycle_count = 0;
	SC_CTOR(memory_instance_tb) {
        SC_METHOD(simple_write_read1);
		sensitive<<clk.pos();
	}
		
};
#endif
