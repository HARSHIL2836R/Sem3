module half_adder(a, b, S, cout);
    input a;
    input b;
    output S;
    output cout;

    assign S = a ^ b;
    assign cout = a & b;
endmodule


module full_adder(a, b, cin, S, cout);
    input a, b, cin;
    output S, cout;

    wire h_1_out;//register to store a^b
    wire c_1;//register to store ab
    half_adder h_a_b(a, b, h_1_out, c_1);

    wire c_2;//register to store cin(a^b)
    half_adder h_final(h_1_out,cin,S,c_2);

    assign cout = c_1 | c_2;
endmodule

module rca_Nbit #(parameter N = 32) (a, b, cin, S, cout);
    input [N-1:0] a;
    input [N-1:0] b;
    input cin;
    output [N-1:0] S;
    output cout;

    wire [N-1:0] carin;

    full_adder fa0(a[0],b[0],cin,S[0],carin[0]);

    generate
        genvar i;
        for (i=1;i<N;i=i+1) begin
            full_adder fai(a[i],b[i],carin[i-1],S[i],carin[i]);
        end

    endgenerate
    assign cout = carin[N-1];
        
endmodule

module adder_subtractor_Nbit #(parameter N = 8) (a,b,a_or_s,out,cout);

    input [N-1:0] a,b;//Calculate A-B or A+B
    input a_or_s;//if 1: do subtraction, if 0: do addition
    output [N-1:0] out;//The Result A-B or A+B
    output cout;//Detects overflow, during subtraction, if overflow/borrow is 1, the difference is negative

    wire [N-1:0] input_b;
    wire [N-1:0] t_out;//Temporary output

    assign input_b = {N{a_or_s}} ^ b;

    rca_Nbit #(.N(N)) dut (.a(a), .b(input_b), .cin(a_or_s), .S(t_out), .cout(cout));
    
    //If the Subtraction is negative, we still have to produce positive output with sign only in cout

    wire diff_is_negative;
    assign diff_is_negative = a_or_s & ~cout;
    
    wire [N-1:0] p_out;
    assign p_out = t_out & ~{N{diff_is_negative}};

    wire [N-1:0] negated_out,add_1,inverted_out,n_out;
    wire dummy_cout;
    assign inverted_out = ~t_out;
    assign add_1[N-1:1] = 0;
    assign add_1[0] = 1;
    rca_Nbit #(.N(N)) dut1 (.a(inverted_out), .b(add_1), .cin(add_1[N-1]), .S(negated_out), .cout(dummy_cout));

    assign n_out = negated_out & {N{diff_is_negative}};

    assign out = p_out | n_out;

endmodule


