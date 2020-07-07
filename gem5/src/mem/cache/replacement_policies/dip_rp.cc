/** Dynamic Insertion Policy */

#include "mem/cache/replacement_policies/dip_rp.hh"

#include <memory>

#include "base/random.hh"
#include "params/DIPRP.hh"

// Added Header File
#include "cpu/o3/probe/elastic_trace.hh"

// Declare Global varialbe
int PSEL=0;
int MISS=0;

DIPRP::DIPRP(const Params *p)
    : LRURP(p), btp(p->btp), cpu(p->cpu)
{
}

// Activation Function
int active ( int miss ) {
    if (miss<0) { 
	PSEL = 0; }
    else {
	PSEL = 1; }
    return PSEL;
}

// Dynamic Insertion Policy
void
DIPRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::shared_ptr<LRUReplData> casted_replacement_data =
        std::static_pointer_cast<LRUReplData>(replacement_data);
    
    if (cpu == NULL)
	return;

    // Run LRU insertion and Count the LRU miss
    if(cpu->totalInsts()%1024 > 0 && cpu->totalInsts()%1024 < 16 ) {
	casted_replacement_data->lastTouchTick = curTick(); 
	MISS++; }

    // Run BIP insertion and Count the LRU miss
    else if(cpu->totalInsts()%1024 > 15 && cpu->totalInsts()%1024 < 32) {
	if (random_mt.random<unsigned>(1, 100) <= btp) {
		casted_replacement_data->lastTouchTick = curTick(); } 
	else {
        	casted_replacement_data->lastTouchTick = 1; }
	MISS--;	} 

    else {

        active(MISS);

    	// When PSEL == 0, Use LRU policy
    	if(PSEL == 0 ) {
		casted_replacement_data->lastTouchTick = curTick(); }
    	// When PSEL == 1, Use BIP policy
    	else if (PSEL == 1)
    	{
    		if (random_mt.random<unsigned>(1, 100) <= btp) {
		// Entries are inserted as MRU if lower than btp      	
			casted_replacement_data->lastTouchTick = curTick(); } 
		else {
        	// Entries are inserted as LRU if bigger than btp
        		casted_replacement_data->lastTouchTick = 1; }
    	}
    }
}

DIPRP*
DIPRPParams::create()
{
    return new DIPRP(this);
}
