module add_sub_tb;

reg a_s;
reg [3:0]A,B;
wire [3:0]sum_diff;
wire carry_borrow;

adder_subtractor_Nbit #(.N(4)) uut(A,B,a_s,sum_diff,carry_brrow);

initial begin 
A = 5; B = 3;
a_s = 0; //Additin
#20
a_s = 1; //Subtraction
#20
A = 3; B = 5;
#20
$finish();
end

initial begin
    $dumpfile("add_sub.vcd");
    $dumpvars(0, add_sub_tb);
end

endmodule