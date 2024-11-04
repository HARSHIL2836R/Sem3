`timescale 1ns/1ps

module testbench_rca_Nbit;

    // Parameters
    parameter N = 32;

    // Inputs
    reg [N-1:0] a;
    reg [N-1:0] b;
    reg [N-1:0] cin;

    // Outputs
    wire [N-1:0] S;
    wire cout;

    // Instantiate the Unit Under Test (UUT)
    rca_Nbit #(N) uut (
        .a(a),
        .b(b),
        .cin(cin),
        .S(S),
        .cout(cout)
    );

    // Test vectors
    initial begin
        // Test 1: Add two small numbers without carry-in
        a = 32'h0000000F;   // 15 in hexadecimal
        b = 32'h00000001;   // 1 in hexadecimal
        cin = 0;
        #10; // Wait 10 time units
        $display("Test 1: a = %h, b = %h, cin = %b, S = %h, cout = %b", a, b, cin, S, cout);

        // Test 2: Add two larger numbers without carry-in
        a = 32'h0000FFFF;   // 65535 in hexadecimal
        b = 32'h00010000;   // 65536 in hexadecimal
        cin = 0;
        #10;
        $display("Test 2: a = %h, b = %h, cin = %b, S = %h, cout = %b", a, b, cin, S, cout);

        // Test 3: Add with carry-in
        a = 32'hFFFFFFFF;   // All bits set to 1 (max 32-bit unsigned value)
        b = 32'h00000001;   // 1 in hexadecimal
        cin = 1;
        #10;
        $display("Test 3: a = %h, b = %h, cin = %b, S = %h, cout = %b", a, b, cin, S, cout);

        // Test 4: Random large numbers with carry-in
        a = 32'hF0F0F0F0;
        b = 32'h0F0F0F0F;
        cin = 1;
        #10;
        $display("Test 4: a = %h, b = %h, cin = %b, S = %h, cout = %b", a, b, cin, S, cout);

        // Finish simulation
        $finish;
    end

endmodule
