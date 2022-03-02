#include "global_defines.h"
#include "memory_instance.h"
#include "memory_instance_tb.h"
#include "memory_instance_cb.h"

int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1,SC_PS);
	sc_signal <sc_uint<DM_INSTANCE_WIDTH_BITS>> dout;
	sc_signal <sc_uint<DM_INSTANCE_WIDTH_BITS>> din;
    sc_signal <sc_uint<OFFSET_DEPTH>> address;
	sc_signal <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_clock clk("my_clock",10,SC_PS,0.5,0,SC_PS,false); // 10 timeunits, 50% duty, first edge at 5 from false->true;
	sc_signal<int> a,b,sum;

	memory_instance  mem("DUT");
	mem.din(din);
	mem.dout(dout);
	mem.address(address);
	mem.ce(ce);
	mem.oe(oe);
	mem.we(we);
	mem.clk(clk);

	memory_instance_tb  mem_tb("TB");
	mem_tb.din(din);
	mem_tb.address(address);
	mem_tb.ce(ce);
	mem_tb.oe(oe);
	mem_tb.we(we);
	mem_tb.clk(clk);

	memory_instance_cb  mem_cb("CB");
	mem_cb.din(din);
	mem_cb.dout(dout);
	mem_cb.address(address);
	mem_cb.ce(ce);
	mem_cb.oe(oe);
	mem_cb.we(we);
	mem_cb.clk(clk);

	mem_tb.simple_write_read1();
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
