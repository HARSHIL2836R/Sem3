`timescale 1ns/1ps

module tb_combinational_karatsuba;

parameter N = 16;

// declare your signals as reg or wire
reg [15:0] X,Y,new_X,new_Y;
wire [31:0] Z;
reg [31:0] check_Z;

initial begin

// write the stimuli conditions
repeat(10) begin
    // write the stimuli conditions
    new_X = $random;
    new_Y = $random;

    X = new_X;
    Y = new_Y;

    check_Z = new_X * new_Y;
    $monitor("check_Z:%d, Z:%d",check_Z,Z);
    if (check_Z == Z) begin
        $display("TEST CASE PASSED");
        $display("X:%d",X);
    end
    #10;
    end
end

karatsuba_16 dut (.X(X), .Y(Y), .Z(Z));

initial begin
    $dumpfile("combinational_karatsuba.vcd");
    $dumpvars(0, tb_combinational_karatsuba);
end

endmodule
