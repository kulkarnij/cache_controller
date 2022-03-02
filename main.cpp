#include "global_defines.h"
#include "cache_controller.h"
#include "cache_controller_tb.h"
//cb is located in cache_controller::check() for better signal visibility.
int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1,SC_PS);

	sc_signal <sc_biguint<DM_WIDTH_BITS>> dout;
    sc_signal<bool> data_valid;
    sc_signal <bool> hit;
	sc_signal<sc_biguint<DM_WIDTH_BITS>> din;
    sc_signal<sc_uint<PROC_WIDTH>> proc_address;
	sc_signal<bool> ce,oe,we; // Assumed true polarity for ease of reading. Usuallya ctive low in practice.
	sc_signal<bool> reset_n;
	sc_clock clk("my_clock",10,SC_NS,0.5,0,SC_NS,false); // 10 timeunits, 50% duty, first edge at 5 from false->true;

	

	cache_controller  cc("DUT");
    cc.dout(dout);
    cc.data_valid(data_valid);
    cc.hit(hit);
	cc.din(din);
	cc.proc_address(proc_address);
	cc.ce(ce);
	cc.oe(oe);
	cc.we(we);
	cc.reset_n(reset_n);
	cc.clk(clk);

	cache_controller_tb  cc_tb("TB");
	cc_tb.din(din);
	cc_tb.proc_address(proc_address);
	cc_tb.ce(ce);
	cc_tb.oe(oe);
	cc_tb.we(we);
	cc_tb.reset_n(reset_n);
	cc_tb.clk(clk);

	cc.check();
	cc_tb.evict_once_then_update();
	sc_start(60,SC_NS);
}
