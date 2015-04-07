library verilog;
use verilog.vl_types.all;
entity zet_div_uu is
    generic(
        z_width         : integer := 16;
        d_width         : vl_notype
    );
    port(
        clk             : in     vl_logic;
        ena             : in     vl_logic;
        z               : in     vl_logic_vector;
        d               : in     vl_logic_vector;
        q               : out    vl_logic_vector;
        s               : out    vl_logic_vector;
        div0            : out    vl_logic;
        ovf             : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of z_width : constant is 1;
    attribute mti_svvh_generic_type of d_width : constant is 3;
end zet_div_uu;
