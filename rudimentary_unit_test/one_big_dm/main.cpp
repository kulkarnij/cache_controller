#include "global_defines.h"
#include "data_memory.h"
#include "data_memory_tb.h"
#include "data_memory_cb.h"

int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1,SC_PS);
	sc_signal <sc_biguint<DM_WIDTH_BITS>> dout;
	sc_signal <sc_biguint<DM_WIDTH_BITS>> din;
    sc_signal <sc_uint<OFFSET_DEPTH>> address;
	sc_signal <bool> ce,we,oe; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_clock clk("my_clock",10,SC_PS,0.5,0,SC_PS,false); // 10 timeunits, 50% duty, first edge at 5 from false->true;
	sc_signal<int> a,b,sum;

	data_memory  dmem("DUT");
	dmem.din(din);
	dmem.dout(dout);
	dmem.address(address);
	dmem.ce(ce);
	dmem.oe(oe);
	dmem.we(we);
	dmem.clk(clk);

	data_memory_tb  dmem_tb("TB");
	dmem_tb.din(din);
	dmem_tb.address(address);
	dmem_tb.ce(ce);
	dmem_tb.oe(oe);
	dmem_tb.we(we);
	dmem_tb.clk(clk);

	data_memory_cb  dmem_cb("CB");
	dmem_cb.din(din);
	dmem_cb.dout(dout);
	dmem_cb.address(address);
	dmem_cb.ce(ce);
	dmem_cb.oe(oe);
	dmem_cb.we(we);
	dmem_cb.clk(clk);

	dmem_tb.simple_write_read1();
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
