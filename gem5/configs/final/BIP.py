import m5
from m5.objects import *
from new_cache import *
#from optparse import OptionParser

#parser = OptionParser()
#parser.add_option('-l1_policy', type = "string", default = "LRU" )
#parser.add_option('-l2_policy', type = "string", default = "LRU" )
#(options, args) = parser.parse_args()

root = Root()
root.full_system = False
root.system = System()

#root = Root( full_system = False, system = System() )
root.system.clk_domain = SrcClockDomain()
root.system.clk_domain.clock = '2GHz'
root.system.clk_domain.voltage_domain = VoltageDomain()
root.system.mem_mode = 'timing'
root.system.mem_ranges = [AddrRange ('2048MB')]
root.system.mem_ctrl = DDR3_1600_8x8()
root.system.mem_ctrl.range = root.system.mem_ranges[0]
root.system.cpu = TimingSimpleCPU()

root.system.cpu.icache = L1ICache()
root.system.cpu.dcache = L1DCache()
root.system.l2cache = L2Cache()

# Connect Port
root.system.membus = SystemXBar()

root.system.cpu.icache.cpu_side = root.system.cpu.icache_port
root.system.cpu.dcache.cpu_side = root.system.cpu.dcache_port

root.system.l2bus = L2XBar()
root.system.cpu.icache.mem_side = root.system.l2bus.slave
root.system.cpu.dcache.mem_side = root.system.l2bus.slave

root.system.l2cache.cpu_side = root.system.l2bus.master
root.system.l2cache.mem_side = root.system.membus.slave

root.system.mem_ctrl.port = root.system.membus.master

root.system.cpu.createInterruptController()
root.system.system_port = root.system.membus.slave

# Repalcement Polic
root.system.cpu.icache.replacement_policy = LRURP();
root.system.cpu.dcache.replacement_policy = LRURP();
root.system.l2cache.replacement_policy = BIPRP();

# root.system.cpu.interrupt[0].pio = root.system.membus.master
# root.system.cpu.interrupt[0].int_master = root.system.membus.slave
# root.system.cpu.interrupt[0].int_slave = root.system.membus.master

# Maximum instruction
root.system.cpu.max_insts_any_thread = 1000000000

process = Process()
process.cmd = ['test_bench/mcf/mcf_base.amd64-m64-gcc42-nn','test_bench/mcf/inp.in']
root.system.cpu.workload = process
root.system.cpu.createThreads()
m5.instantiate()
exit_event = m5.simulate()
print('Existing @ tick', 'because', exit_event.getCause())
