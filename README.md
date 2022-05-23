# cache_controller
Cache controller with data-dependent eviction policy

# Introduction

This repo contains a cache controller with eviction policy that depends on data. It is currently configured for a 4-way set associative cache with a total size of 1MByte. The cache line is 256-bit wide. Processor address is assumed to be 32-bit. Therefore the first 14 MSBs are tag, the next 13 are the 8K sets which together store 8K * 4 = 32K cache lines, 32-byte wide.

# Memory Organization

When cache is accessed, each transaction splits into a tag lookup followed by an optional update cycle for write operations. In order to support non-blocking back-back operations, two port memories are assumed. Since this is an architectural model, this simply means that two processes may access the memory at a time, one for lookup and another for write. When a read operation is issued on the same address that is being looked-up in a write operation, snooping is supported in tag and data memories so that one gets fresh data.

A cache lookup operation involves inspection of all "ways" to match the tag. In addition, in this particular case, we also need to inspect the data in each of the ways for determining eviction.  In order to support throughput and avoid cumbersome control logic and state storage that is difficult to pull-through in short duration, the memories are laid out in parallel. Thus there are 4 tag memories that look up each way in a cycle and 4 data memories that can read data in each way. Depending upon the match, logic is present to update only one of the 4 ways. This represents a high performance but high power and area design choice. 

The cache line of 256 bits is quite big. For ease of coding, it is represented by a monolithic memory although the implementation can later be changed to compose it with traditional memory sizes.

# Module organization
cache_controller is the top level module that simply does bit slicing on the address line. tag_memory has most of the intelligence of populating the cache and determing matches and outputs matched way number and various control signals signifying snooping, read/write operations and looup and update cycles. data_memory uses these signals to read data and determine cache way to be evicted. globals include file tries to parametrizet he design for bit widths etc. However this is not supported everywhere at this time, so please do not expect the code to autoconfigure based on thse constants. The EVICTION_POLICY constant however is implemented. Finally, tb files are test benches and cb are checkerboards which at this point simple print output.

## Eviction
Eviction policy is determined by the data_memory module based on the constant EVICTION_POLICY. 0 always evicts way 0. 1 evicts the way with lowest value of the most significant word and 2 evicts the way with least value of one of the 8 nth significat words where n is specified by 3 LSBs of way 0. The logic of this is expcted to result in big comparators and muxes and may be difficult to timeing close during the look-up cycle, when it is needed to be established.

An important point to note is that we do not assume that memories can be initialized at reset. We do not know if any of the cache is filled, so all are asssumed to have valid data. It is expected that the cache will fill itself since the input and the eviction policy is random enough to evict all ways after a few writes.

# Code Status
The code at this point represents 1 day of effort. It compiles using the supplied makefile with systemc complied with C++11 support and generated the output file "out". One test that evicts a way and then populates and reads from it is passing.   Sample output is included in sample_out.txt. There is plenty of room for improvment.

# Future Improvements

- Consider maintaining valid bits so that initial reads are valid.
- Test for conditions such as chip enable controlled operations, constrained random inputs and lot more functional testing.
- Add vcd dump file which was not done due to time constraints.


