#include "global_defines.h"
#include "tag_memory.h"
#include "tag_memory_tb.h"
#include "tag_memory_cb.h"

int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1,SC_PS);
	sc_signal <sc_uint<ASSOCIATIVITY>> set_match_rd,set_match_wr; // fully decoded match vector. 4'b0 is no match.
    sc_signal <bool> hit;
	sc_signal<bool> evict;
	sc_signal<bool> lookup_cycle;
	sc_signal<bool> update_cycle;
    sc_signal<sc_uint<ASSOCIATIVITY>> snoop; // If any way is being updated and being read at the same time.
	sc_signal <bool> read_operation, write_operation; // Current state, driven directly by memory controls. No update cycle in read_operation;

	sc_signal <sc_uint<ASSOCIATIVITY_WIDTH>> evict_way; // The set-address of the way to be evicted.
	sc_signal<sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_signal<sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_signal<bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_signal<bool> reset_n;
	sc_clock clk("my_clock",10,SC_NS,0.5,0,SC_NS,false); // 10 timeunits, 50% duty, first edge at 5 from false->true;

	tag_memory  tmem("DUT");
	tmem.set_match_rd(set_match_rd);
	tmem.set_match_wr(set_match_wr);
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

	tag_memory_tb  tmem_tb("TB");
	tmem_tb.evict_way(evict_way);
	tmem_tb.tag_value(tag_value);
	tmem_tb.tag_address(tag_address);
	tmem_tb.ce(ce);
	tmem_tb.oe(oe);
	tmem_tb.we(we);
	tmem_tb.reset_n(reset_n);
	tmem_tb.clk(clk);

	tag_memory_cb  tmem_cb("CB");
	tmem_cb.set_match_rd(set_match_rd);
	tmem_cb.set_match_wr(set_match_wr);
	tmem_cb.hit(hit);
	tmem_cb.evict(evict);
	tmem_cb.lookup_cycle(lookup_cycle);
	tmem_cb.update_cycle(update_cycle);
	tmem_cb.snoop(snoop);
	tmem_cb.read_operation(read_operation);
	tmem_cb.write_operation(write_operation);
	tmem_cb.evict_way(evict_way);

	tmem_cb.tag_value(tag_value);
	tmem_cb.tag_address(tag_address);
	tmem_cb.ce(ce);
	tmem_cb.oe(oe);
	tmem_cb.we(we);
	tmem_cb.reset_n(reset_n);
	tmem_cb.clk(clk);

	tmem_tb.evict_once_then_update();
	sc_start(60,SC_NS);
}
