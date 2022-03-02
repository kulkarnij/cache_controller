#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H
#include "global_defines.h"


SC_MODULE (data_memory) {
//Ports
	sc_out <sc_biguint<DM_WIDTH_BITS>> dout;
	sc_in <sc_biguint<DM_WIDTH_BITS>> din;
    sc_in <sc_uint<OFFSET_DEPTH>> address;
	sc_in <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_in_clk clk;
//Storage
	sc_biguint<DM_WIDTH_BITS> dmem[DM_DEPTH];
	void read_mem();
	void write_mem();

	SC_CTOR(data_memory) 
	{
		SC_METHOD(read_mem);
		sensitive << clk.pos();
		SC_METHOD(write_mem);
		sensitive << clk.pos();
	}

};

#endif
