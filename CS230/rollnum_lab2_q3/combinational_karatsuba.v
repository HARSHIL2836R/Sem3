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

module karatsuba_2 (X,Y,Z);
    input [1:0] X,Y;
    output [3:0] Z;

    wire Xn,Xe,Yn,Ye;
    assign {Xn,Xe} = X;
    assign {Yn,Ye} = Y;

    wire [1:0] z0,z1,z2,z3;

    assign z0[0] = Xe & Ye;
    assign z0[1] = 0;
    assign z2[0] = Xn & Yn;
    assign z2[1] = 0;

    wire signX, signY,sub;
    assign sub = 1;
    wire z3_1,z3_2;
    assign signX = ~Xn & Xe;
    assign signY = ~Yn & Ye;
    assign z3_1 = Xn ^ Xe;
    assign z3_2 = Yn ^ Ye;

    wire [1:0] z1_1;
    wire cout_z1_1,add;
    assign add = 0;
    assign z3[0] = z3_1 & z3_2;
    assign z3[1] = 0;
    adder_subtractor_Nbit #(.N(2)) A_1 (.a(z0),.b(z2),.a_or_s(add),.out(z1_1),.cout(cout_z1_1));

    wire sign_z3, cout_z1;
    assign sign_z3 = ~signX ^ ~signY;

    adder_subtractor_Nbit #(.N(2)) A_2 (.a(z1_1),.b(z3),.a_or_s(sign_z3),.out(z1),.cout(cout_z1));

    //Converting z1,z2,z3 to 4 bits

    wire [3:0] big_z0_z2,big_z1;
    wire dummy_cout;
    assign big_z0_z2[1:0] = z0;
    assign big_z0_z2[3:2] = z2;
    assign big_z1[0] = 0;
    assign big_z1[2:1] = z1;
    assign big_z1[3] = 0;

    rca_Nbit #(.N(4)) dut (.a(big_z0_z2), .b(big_z1), .cin(1'b0), .S(Z), .cout(dummy_cout));

endmodule

module karatsuba_4 (X,Y,Z);
    input [3:0] X,Y;
    output [7:0] Z;

    wire [1:0] Xn,Xe,Yn,Ye;
    assign {Xn,Xe} = X;
    assign {Yn,Ye} = Y;

    wire [3:0] z0,z1,z2,z3;

    karatsuba_2 dut1 (.X(Xe),.Y(Ye),.Z(z0));
    karatsuba_2 dut2 (.X(Xn),.Y(Yn),.Z(z2));

    wire signX, signY,sub;
    assign sub = 1;
    wire [1:0] z3_1,z3_2;
    adder_subtractor_Nbit #(.N(2)) S_1 (.a(Xn),.b(Xe),.a_or_s(sub),.out(z3_1),.cout(signX));
    adder_subtractor_Nbit #(.N(2)) S_2 (.a(Yn),.b(Ye),.a_or_s(sub),.out(z3_2),.cout(signY));

    wire [3:0] z1_1;
    wire cout_z1_1,add;
    assign add = 0;
    karatsuba_2 dut3 (.X(z3_1),.Y(z3_2),.Z(z3));
    adder_subtractor_Nbit #(.N(4)) A_1 (.a(z0),.b(z2),.a_or_s(add),.out(z1_1),.cout(cout_z1_1));

    wire sign_z3, cout_z1;
    assign sign_z3 = ~signX ^ ~signY;

    adder_subtractor_Nbit #(.N(4)) A_2 (.a(z1_1),.b(z3),.a_or_s(sign_z3),.out(z1),.cout(cout_z1));

    //Converting z1,z2,z3 to 8 bits

    wire [7:0] big_z0_z2,big_z1;
    wire dummy_cout;
    assign big_z0_z2[3:0] = z0;
    assign big_z0_z2[7:4] = z2;
    assign big_z1[1:0] = 0;
    assign big_z1[5:2] = z1;
    assign big_z1[7:6] = 0;

    rca_Nbit #(.N(8)) dut (.a(big_z0_z2), .b(big_z1), .cin(1'b0), .S(Z), .cout(dummy_cout));

endmodule

module karatsuba_8 (X,Y,Z);
    input [7:0] X,Y;
    output [15:0] Z;

    wire [3:0] Xn,Xe,Yn,Ye;
    assign {Xn,Xe} = X;
    assign {Yn,Ye} = Y;

    wire [7:0] z0,z1,z2,z3;

    karatsuba_4 dut1 (.X(Xe),.Y(Ye),.Z(z0));
    karatsuba_4 dut2 (.X(Xn),.Y(Yn),.Z(z2));

    wire signX, signY,sub;
    assign sub = 1;
    wire [3:0] z3_1,z3_2;
    adder_subtractor_Nbit #(.N(4)) S_1 (.a(Xn),.b(Xe),.a_or_s(sub),.out(z3_1),.cout(signX));
    adder_subtractor_Nbit #(.N(4)) S_2 (.a(Yn),.b(Ye),.a_or_s(sub),.out(z3_2),.cout(signY));

    wire [7:0] z1_1;
    wire cout_z1_1,add;
    assign add = 0;
    karatsuba_4 dut3 (.X(z3_1),.Y(z3_2),.Z(z3));
    adder_subtractor_Nbit #(.N(8)) A_1 (.a(z0),.b(z2),.a_or_s(add),.out(z1_1),.cout(cout_z1_1));

    wire sign_z3, cout_z1;
    assign sign_z3 = ~signX ^ ~signY;

    adder_subtractor_Nbit #(.N(8)) A_2 (.a(z1_1),.b(z3),.a_or_s(sign_z3),.out(z1),.cout(cout_z1));

    //Converting z1,z2,z3 to 16 bits

    wire [15:0] big_z0_z2,big_z1;
    wire dummy_cout;
    assign big_z0_z2[7:0] = z0;
    assign big_z0_z2[15:8] = z2;
    assign big_z1[3:0] = 0;
    assign big_z1[11:4] = z1;
    assign big_z1[15:12] = 0;

    rca_Nbit #(.N(16)) dut (.a(big_z0_z2), .b(big_z1), .cin(1'b0), .S(Z), .cout(dummy_cout));

endmodule

module karatsuba_16 (X, Y, Z);
    input [15:0] X,Y;
    output [31:0] Z;

    wire [7:0] Xn,Xe,Yn,Ye;
    assign {Xn,Xe} = X;
    assign {Yn,Ye} = Y;

    wire [15:0] z0,z1,z2,z3;

    karatsuba_8 dut1 (.X(Xe),.Y(Ye),.Z(z0));
    karatsuba_8 dut2 (.X(Xn),.Y(Yn),.Z(z2));

    wire signX, signY,sub;
    assign sub = 1;
    wire [7:0] z3_1,z3_2;
    adder_subtractor_Nbit #(.N(8)) S_1 (.a(Xn),.b(Xe),.a_or_s(sub),.out(z3_1),.cout(signX));//Working Fine
    adder_subtractor_Nbit #(.N(8)) S_2 (.a(Yn),.b(Ye),.a_or_s(sub),.out(z3_2),.cout(signY));//Working Fine

    wire [15:0] z1_1;
    wire cout_z1_1,add;
    assign add = 0;
    karatsuba_8 dut3 (.X(z3_1),.Y(z3_2),.Z(z3));
    adder_subtractor_Nbit #(.N(16)) A_1 (.a(z0),.b(z2),.a_or_s(add),.out(z1_1),.cout(cout_z1_1));

    wire sign_z3, cout_z1;
    assign sign_z3 = ~signX ^ ~signY;

    adder_subtractor_Nbit #(.N(16)) A_2 (.a(z1_1),.b(z3),.a_or_s(sign_z3),.out(z1),.cout(cout_z1));

    //Converting z1,z2,z3 to 32 bits

    wire [31:0] big_z0_z2,big_z1;
    wire dummy_cout;
    assign big_z0_z2[15:0] = z0;
    assign big_z0_z2[31:16] = z2;
    assign big_z1[7:0] = 0;
    assign big_z1[23:8] = z1;
    assign big_z1[31:24] = 0;

    rca_Nbit #(.N(32)) dut (.a(big_z0_z2), .b(big_z1), .cin(1'b0), .S(Z), .cout(dummy_cout));

endmodule
