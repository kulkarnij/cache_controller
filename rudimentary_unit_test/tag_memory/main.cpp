#include "global_defines.h"
#include "tag_memory.h"
#include "tag_memory_tb.h"
#include "tag_memory_cb.h"

int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1,SC_PS);
	sc_signal <sc_uint<ASSOCIATIVITY>> set_match; // fully decoded match vector. 4'b0 is no match.
    sc_signal <bool> hit;
	sc_signal<sc_uint<TAG_WIDTH>> tag_value; // We are looking for these address bits.
    sc_signal<sc_uint<TAG_DEPTH>> tag_address; // Tag can be stored at this addres in any of the 4 set memories.
	sc_signal<bool> ce,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
    sc_signal <sc_uint<ASSOCIATIVITY_WIDTH>> set_we; // Store tag at a particular set.
	sc_clock clk("my_clock",10,SC_PS,0.5,0,SC_PS,false); // 10 timeunits, 50% duty, first edge at 5 from false->true;

	tag_memory  tmem("DUT");
	tmem.set_match(set_match);
	tmem.hit(hit);
	tmem.tag_value(tag_value);
	tmem.tag_address(tag_address);
	tmem.ce(ce);
	tmem.oe(oe);
	tmem.set_we(set_we);
	tmem.clk(clk);

	tag_memory_tb  tmem_tb("TB");
	tmem_tb.tag_value(tag_value);
	tmem_tb.tag_address(tag_address);
	tmem_tb.ce(ce);
	tmem_tb.oe(oe);
	tmem_tb.set_we(set_we);
	tmem_tb.clk(clk);

	tag_memory_cb  tmem_cb("CB");
	tmem_cb.set_match(set_match);
	tmem_cb.hit(hit);
	tmem_cb.tag_value(tag_value);
	tmem_cb.tag_address(tag_address);
	tmem_cb.ce(ce);
	tmem_cb.oe(oe);
	tmem_cb.set_we(set_we);
	tmem_cb.clk(clk);

	tmem_tb.simple_write_read1();
	sc_start(60,SC_PS);

/*
	adder_simple_tb tb("TB");
	tb.a(a);
	tb.b(b);
	tb.sum(sum);
	tb.clock(clock);
	adder_simple_cb cb("CB");
	cb.a(a);
	cb.b(b);
	cb.sum(sum);
	cb.clock(clock);
    //tb.generate();
	sc_start(60,SC_PS);
*/

}
