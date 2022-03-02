#ifndef CACHECONTROLLER_TB_H
#define CACHECONTROLLER_TB_H
#include "global_defines.h"

SC_MODULE (cache_controller_tb){
	sc_out <sc_biguint<DM_WIDTH_BITS>> din;
    sc_out <sc_uint<PROC_WIDTH>> proc_address;
	sc_out <bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_out <bool> reset_n;
	sc_in_clk clk;



	
	void evict_once_then_update();
	int cycle_count = 0;
	SC_CTOR(cache_controller_tb) {
        SC_METHOD(evict_once_then_update);
		sensitive<<clk.neg();
	}
		
};
#endif
