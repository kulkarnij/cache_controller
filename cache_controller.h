#ifndef CACHE_CONTROLLER_H
#define CACHE_CONTROLLER_H
#include "global_defines.h"
#include "tag_memory.h"
#include "data_memory.h"


SC_MODULE (cache_controller) {
//Ports
	sc_out <sc_biguint<DM_WIDTH_BITS>> dout;
    sc_out<bool> data_valid;
    sc_out <bool> hit;
	sc_in <sc_biguint<DM_WIDTH_BITS>> din;
    sc_in <sc_uint<PROC_WIDTH>> proc_address;
	sc_in <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_in <bool> reset_n;
	sc_in_clk clk;
//Storage
	void common_assignments();
	void check();
    data_memory dmem;
    tag_memory tmem;
	uint cycle_count = 0; // Only needed by the cheker check() which is rather conveniently put here instead of the top.

	sc_signal <sc_uint<ASSOCIATIVITY>> way_match_rd, way_match_wr; // fully decoded match vector. 4'b0 is no match.
	sc_signal<bool> evict; // Not used here.
	sc_signal<bool> lookup_cycle;
	sc_signal<bool> update_cycle;
	sc_signal <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The address of the way to be evicted.
    sc_signal<sc_uint<ASSOCIATIVITY>> snoop; // If any way is being updated and being read at the same time.
	sc_signal <bool> read_operation, write_operation; // Current state, driven directly by memory controls. No update cycle in read_operation;

	sc_signal <sc_uint<TAG_WIDTH>> tag_value;
    sc_signal <sc_uint<TAG_DEPTH>> tag_address;

SC_CTOR(cache_controller):
    dmem("dmem"),
		tmem("tmem")
		{

			tmem.way_match_rd(way_match_rd);
			tmem.way_match_wr(way_match_wr);
			tmem.hit(hit);
			tmem.evict(evict);
			tmem.lookup_cycle(lookup_cycle);
			tmem.update_cycle(update_cycle);
			tmem.snoop(snoop);
			tmem.read_operation(read_operation);
			tmem.write_operation(write_operation);
			tmem.evict_way(evict_way);

			tmem.tag_value(tag_value);
			tmem.tag_address(tag_address);
			tmem.ce(ce);
			tmem.oe(oe);
			tmem.we(we);
			tmem.reset_n(reset_n);
			tmem.clk(clk);

			dmem.dout(dout);
			dmem.data_valid(data_valid);
			dmem.din(din);
			dmem.address(tag_address);
			dmem.way_match_rd(way_match_rd);
			dmem.way_match_wr(way_match_wr);
			dmem.hit(hit);
			dmem.evict(evict);
			dmem.lookup_cycle(lookup_cycle);
			dmem.update_cycle(update_cycle);
			dmem.snoop(snoop);
			dmem.read_operation(read_operation);
			dmem.write_operation(write_operation);
			dmem.evict_way(evict_way);
			dmem.ce(ce);
			dmem.oe(oe);
			dmem.we(we);
			dmem.reset_n(reset_n);
			dmem.clk(clk);

			SC_METHOD(common_assignments);
			sensitive << proc_address;
			SC_METHOD( check);
			sensitive<<clk.pos();

		}

};

#endif
