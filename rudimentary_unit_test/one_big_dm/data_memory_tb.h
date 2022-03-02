#ifndef DATAMEMORY_TB_H
#define  DATAMEMORY_TB_H
#include "global_defines.h"

SC_MODULE (data_memory_tb){
	sc_out <sc_biguint<DM_WIDTH_BITS>> din;
    sc_out <sc_uint<OFFSET_DEPTH>> address;
	sc_out <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_in_clk clk;
	void simple_write_read1();
	int cycle_count = 0;
	SC_CTOR(data_memory_tb) {
        SC_METHOD(simple_write_read1);
		sensitive<<clk.pos();
	}
		
};
#endif
