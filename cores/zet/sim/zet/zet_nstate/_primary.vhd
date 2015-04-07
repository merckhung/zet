library verilog;
use verilog.vl_types.all;
entity zet_nstate is
    generic(
        opcod_st        : vl_logic_vector(0 to 2) := (Hi0, Hi0, Hi0);
        modrm_st        : vl_logic_vector(0 to 2) := (Hi0, Hi0, Hi1);
        offse_st        : vl_logic_vector(0 to 2) := (Hi0, Hi1, Hi0);
        immed_st        : vl_logic_vector(0 to 2) := (Hi0, Hi1, Hi1);
        execu_st        : vl_logic_vector(0 to 2) := (Hi1, Hi0, Hi0)
    );
    port(
        state           : in     vl_logic_vector(2 downto 0);
        prefix          : in     vl_logic;
        need_modrm      : in     vl_logic;
        need_off        : in     vl_logic;
        need_imm        : in     vl_logic;
        end_seq         : in     vl_logic;
        ftype           : in     vl_logic_vector(5 downto 0);
        \of\            : in     vl_logic;
        next_in_opco    : in     vl_logic;
        next_in_exec    : in     vl_logic;
        \block\         : in     vl_logic;
        div_exc         : in     vl_logic;
        tflm            : in     vl_logic;
        intr            : in     vl_logic;
        iflm            : in     vl_logic;
        nmir            : in     vl_logic;
        iflss           : in     vl_logic;
        next_state      : out    vl_logic_vector(2 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of opcod_st : constant is 1;
    attribute mti_svvh_generic_type of modrm_st : constant is 1;
    attribute mti_svvh_generic_type of offse_st : constant is 1;
    attribute mti_svvh_generic_type of immed_st : constant is 1;
    attribute mti_svvh_generic_type of execu_st : constant is 1;
end zet_nstate;
