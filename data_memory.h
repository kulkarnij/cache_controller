#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H
#include "global_defines.h"


SC_MODULE (data_memory) {
//Ports
	sc_out <sc_biguint<DM_WIDTH_BITS>> dout;
    sc_out<bool> data_valid;
	sc_out <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The address of the way to be evicted.
    //From cache controller:
	sc_in <sc_biguint<DM_WIDTH_BITS>> din;
    sc_in <sc_uint<TAG_DEPTH>> address; // We will use one mem for each way, that is why this is tag-depth (13) not offset depth (15)
	sc_in <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in <bool> reset_n;


	//From tag_memory
	sc_in <sc_uint<ASSOCIATIVITY>> way_match_rd, way_match_wr; // fully decoded match vector. 4'b0 is no match.
    sc_in <bool> hit;
	sc_in<bool> evict; // Not used here.
	sc_in<bool> lookup_cycle;
	sc_in<bool> update_cycle;
    sc_in<sc_uint<ASSOCIATIVITY>> snoop; // If any way is being updated and being read at the same time.
	sc_in <bool> read_operation, write_operation; // Current state, driven directly by memory controls. No update cycle in read_operation;
	sc_in_clk clk;
//Storage
	//One memory for each way for parallel lookups.
	sc_biguint<DM_WIDTH_BITS> dmem0[1<<TAG_DEPTH];
	sc_biguint<DM_WIDTH_BITS> dmem1[1<<TAG_DEPTH];
	sc_biguint<DM_WIDTH_BITS> dmem2[1<<TAG_DEPTH];
	sc_biguint<DM_WIDTH_BITS> dmem3[1<<TAG_DEPTH];
	sc_signal <sc_biguint<DM_WIDTH_BITS>> data_way0,data_way1,data_way2,data_way3;
//Register signals for the write operation
	sc_signal <sc_biguint<DM_WIDTH_BITS>> din_wr;
    sc_signal <sc_uint<TAG_DEPTH>> address_wr; 

	void read_data();
    void drive_data();
	void write_mem();
    void set_eviction_way();
    void set_update_inputs();

//This method explicitly assumes 4 ways, DEFINE_NOT_HONORED

	sc_uint<2> find_min_way(const sc_biguint<256> d0,const sc_biguint<256> d1,const sc_biguint<256> d2,const sc_biguint<256> d3, const sc_uint<3> index);
	SC_CTOR(data_memory) 
	{
		SC_METHOD(read_data);
		sensitive <<address<<lookup_cycle; 
		SC_METHOD(drive_data);
        sensitive<<clk.pos()<<reset_n.neg();
		SC_METHOD(write_mem);
		sensitive << clk.pos();
		SC_METHOD(set_eviction_way); // Needed to be established in lookup cycle, cannot be clocked.
        sensitive<<data_way0<<data_way1<<data_way2<<data_way3;

        SC_METHOD (set_update_inputs);
		sensitive<<clk.pos()<<reset_n.neg();
	}

};

#endif
