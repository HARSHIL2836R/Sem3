`timescale 1ns/1ps

module tb_rca_32_bit;

parameter N = 32;

// declare your signals as reg or wire
reg [N-1:0] A, B;// inputs to the module
reg cin;
wire [N-1:0] S, cout;//nets
reg [N-1:0] new_A, new_B;//random inputs from stimuli
reg new_cin;
reg [N-1:0] check_S, check_cout;

initial begin	
    repeat(10) begin
    // write the stimuli conditions
    new_A = $random;
    new_B = $random;
    new_cin = $random;

    A = new_A;
    B = new_B;
    cin = new_cin;

    {check_cout, check_S} = A + B + cin;
    $monitor("check_S:%d, S:%d, check_cout:%d, cout:%d",check_S,S,check_cout,cout);
    if (check_S == S) begin
        $display("TEST CASE PASSED");
        $display("A:%d",A);
    end
    #10;
    end
end

rca_Nbit #(.N(N)) dut (.a(A), .b(B), .cin(cin), .S(S), .cout(cout));


initial begin
    $dumpfile("rca_32bit.vcd");
    $dumpvars(0, tb_rca_32_bit);
end

endmodule
