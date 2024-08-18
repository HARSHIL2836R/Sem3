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

assign input_b = a_or_s ^ b;

rca_Nbit #(.N(N)) dut (.a(a), .b(input_b), .cin(a_or_s), .S(out), .cout(cout));

endmodule

module karatsuba_8 (X,Y,Z);
input [7:0] X,Y;
output [15:0] Z;

generate
    genvar j;
    genvar i;
    for (i=0;i<7;i=i+1) begin
        for (j=0;i<7;i=i+1) begin
            wire xj_yi;
            assign xj_yi = X[i] & Y[j];//assign and gates to all combinations
            if (i == 0)begin
                if (j ==0) begin
                    assign Z[0] = X[0] & Y[0];//save the first digit of output
                end
            end
            else if (i == 1)begin
                wire cout_ij;
                if (j == 0) begin
                    half_adder ha_ij (x1_y0,xj_yi,Z[1],cout_ij);//first half adder
                end
                else if (j == 7) begin
                    wire hao_ij;
                    half_adder ha_ij (x7_y1,cout_16,hao_ij,cout_ij);//last half adder
                end
                else begin
                    genvar a,b,c;
                    assign a = i-1;
                    assign b = j+1;
                    assign c = j-1;
                    wire fao_ij;
                    full_adder fa_ij (xa_yb,xi_yj,cout_ic,fao_ij,cout_ij);
                end
            end

        end 
    end
endgenerate

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
assign sub =1;
wire [7:0] z3_1,z3_2;
adder_subtractor_Nbit #(.N(8)) S_1 (.a(Xn),.b(Xe),.a_or_s(sub),.out(z3_1),.cout(signX));
adder_subtractor_Nbit #(.N(8)) S_2 (.a(Yn),.b(Ye),.a_or_s(sub),.out(z3_2),.cout(signY));

wire [15:0] z1_1;
wire cout_z1_1,add;
assign add = 0;
karatsuba_8 dut3 (.X(z3_1),.Y(z3_2),.Z(z3));
adder_subtractor_Nbit #(.N(16)) A_1 (.a(z0),.b(z2),.a_or_s(add),.out(z1_1),.cout(cout_z1_1));

wire sign_z3, cout_z1;
assign sign_z3 = signX ^ signY;

adder_subtractor_Nbit #(.N(16)) A_2 (.a(z1_1),.b(z3),.a_or_s(sign_z3),.out(z1),.cout(cout_z1));

endmodule
