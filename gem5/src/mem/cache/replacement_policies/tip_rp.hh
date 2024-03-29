/** Triple Insertion Policy */

#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_TIP_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_TIP_RP_HH__

#include "mem/cache/replacement_policies/lru_rp.hh"
#include "cpu/base.hh"



struct TIPRPParams;

class TIPRP : public LRURP
{
  protected:
     /**
     * Declare Bimodal throtle parameter(=btp).
     * Variable required when using Bimodel Insertion policy.
     * Value in the range [0,100] used to decide
     * if a new entry is inserted at the MRU or LRU position.
     *
     * BaseCPU is pointer to store struct the current cpu.
     */
    const unsigned btp;
    BaseCPU *cpu;
  
  public:
    /** Convenience typedef. */
    typedef TIPRPParams Params;

    /**
     * Construct and initiliaze this replacement policy.
     */
    TIPRP(const Params *p);

    /**
     * Destructor.
     */
    ~TIPRP() {}

    /**
     * Reset replacement data for an entry. Used when an entry is inserted.
     * Choice replacement policy to decide whether use LRU or BIP
     *
     * @param replacement_data Replacement data to be reset.
     */
    void reset(const std::shared_ptr<ReplacementData>& replacement_data) const
                                                                     override;
};

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_TIP_RP_HH__
