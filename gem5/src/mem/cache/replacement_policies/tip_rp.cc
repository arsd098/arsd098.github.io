/** Triple Insertion Policy */

#include "mem/cache/replacement_policies/tip_rp.hh"

#include <memory>

#include "base/random.hh"
#include "params/TIPRP.hh"

// Added Header File
#include "cpu/o3/probe/elastic_trace.hh"

// Declare Global varialbe
int PSEL1=0;
int numLIP=0;
int numLRU=0;
int numBIP=0;

TIPRP::TIPRP(const Params *p)
    : LRURP(p), btp(p->btp), cpu(p->cpu)
{
}

// Activation Function
int active ( int LIP, int LRU, int BIP ) {
    if (LIP<LRU && LIP<BIP) { 
	PSEL1 = 2; }
    else if (LRU<LIP && LRU<BIP) {
	PSEL1 = 0; }
    else {
	PSEL1 = 1; }

    return PSEL1;
}

// Triple Insertion Policy
void
TIPRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::shared_ptr<LRUReplData> casted_replacement_data =
        std::static_pointer_cast<LRUReplData>(replacement_data);
    
    if (cpu == NULL)
	return;

    // Run LRU insertion and Count the LRU miss
    if(cpu->totalInsts()%1024 > 0 && cpu->totalInsts()%1024 < 12 ) {
	casted_replacement_data->lastTouchTick = curTick(); 
	numLRU++; }

    // Run BIP insertion and Count the LRU miss
    else if(cpu->totalInsts()%1024 > 11 && cpu->totalInsts()%1024 < 23) {
	if (random_mt.random<unsigned>(1, 100) <= btp) {
		casted_replacement_data->lastTouchTick = curTick(); } 
	else {
        	casted_replacement_data->lastTouchTick = 1; }
	numBIP++;} 

    // Run LIP insertion and Count the LIU miss
    else if(cpu->totalInsts()%1024 > 23 && cpu->totalInsts()%1024 < 35) {
	if (random_mt.random<unsigned>(1, 100) <= 0) {
		casted_replacement_data->lastTouchTick = curTick(); } 
	else {
        	casted_replacement_data->lastTouchTick = 1; }
	numLIP++;}
 

    else {

        active(numLIP, numLRU, numBIP);

    	// When PSEL1 == 0, Use LRU policy
    	if(PSEL1 == 0 ) {
		casted_replacement_data->lastTouchTick = curTick(); }
    	// When PSEL1 == 1, Use BIP policy
    	else if (PSEL1 == 1)
    	{
    		if (random_mt.random<unsigned>(1, 100) <= btp) {
		// Entries are inserted as MRU if lower than btp      	
			casted_replacement_data->lastTouchTick = curTick(); } 
		else {
        	// Entries are inserted as LRU if bigger than btp
        		casted_replacement_data->lastTouchTick = 1; }
    	}
	// When PSEL1 == 2, Use BIP policy
        else if (PSEL1 == 2)
	{
    		if (random_mt.random<unsigned>(1, 100) <= 0) {
		// Entries are inserted as MRU if lower than 0      	
			casted_replacement_data->lastTouchTick = curTick(); } 
		else {
        	// Entries are inserted as LRU if bigger than 0
        		casted_replacement_data->lastTouchTick = 1; }
    	}
    }
}

TIPRP*
TIPRPParams::create()
{
    return new TIPRP(this);
}
