module CLA_16bit_tb;

    // Inputs
    reg [15:0] a;
    reg [15:0] b;
    reg cin;

    // Outputs
    wire [15:0] sum;
    wire cout;
    wire Pout;
    wire Gout;

    // Instantiate the Unit Under Test (UUT)
    CLA_16bit uut (
        .a(a), 
        .b(b), 
        .cin(cin), 
        .sum(sum), 
        .cout(cout), 
        .Pout(Pout), 
        .Gout(Gout)
    );

    initial begin
        // Initialize Inputs
        $display("Running 16-bit CLA Testbench...");

        // Test Case 1
        a = 16'h0000; b = 16'h0000; cin = 0;
        #10 $display("Test Case 1: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 2
        a = 16'hFFFF; b = 16'h0000; cin = 0;
        #10 $display("Test Case 2: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 3
        a = 16'hFFFF; b = 16'h0001; cin = 0;
        #10 $display("Test Case 3: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 4
        a = 16'h1234; b = 16'h5678; cin = 0;
        #10 $display("Test Case 4: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 5
        a = 16'hAAAA; b = 16'h5555; cin = 1;
        #10 $display("Test Case 5: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 6
        a = 16'h0F0F; b = 16'hF0F0; cin = 1;
        #10 $display("Test Case 6: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        // Test Case 7
        a = 16'h8000; b = 16'h8000; cin = 1;
        #10 $display("Test Case 7: a = %h, b = %h, cin = %b, sum = %h, cout = %b", a, b, cin, sum, cout);

        $finish;
    end
endmodule
