module CLA_4bit(a, b, cin, sum, cout);
    input [3:0] a,b;
    input cin;
    output [3:0] sum;
    output cout;    
    
    wire [3:0] carry;
    reg [3:0] G,P;
    
    generate 
    genvar i;
    for (i=0;i<4;i=i+1) begin
        
        assign G[i]=a[i]&b[i];
        assign P[i]=a[i]^b[i];
        if (i ==0) begin
            assign carry[i]=G[i]|P[i]&cin;
            assign sum[i]=a[i]^b[i]^cin;
        end
        else begin
            assign carry[i]=G[i]|P[i]&carry[i-1];
            assign sum[i]=a[i]^b[i]^carry[i-1];
        end
    end
    endgenerate
    assign cout = carry[3];

endmodule


module CLA_4bit_P_G(a, b, cin, sum, P, G);
    input [3:0] a,b;
    output [4:0] sum;
    output P,G;
    
    wire [3:0] carry;
    reg [3:0] Go,Po;

    generate 
    genvar i;
    for (i=0;i<4;i=i+1) begin
        
        assign Go[i]=a[i]&b[i];
        assign Po[i]=a[i]^b[i];
        if (i ==0) begin
            assign carry[i]=Go[i]|Po[i]&cin;
            assign sum[i]=a[i]^b[i]^cin;
        end
        else begin
            assign carry[i]=Go[i]|Po[i]&carry[i-1];
            assign sum[i]=a[i]^b[i]^carry[i-1];
        end
    end
    endgenerate

    assign P = Po[0]&Po[1]&Po[2]&Po[3];
    assign G = Go[3] | Po[3]&Go[2] | Po[3]&Po[2]&Go[1]|Po[3]&Po[2]&Po[1]&Go[0];

endmodule


module lookahead_carry_unit_16_bit(P0, G0, P1, G1, P2, G2, P3, G3, cin, C4, C8, C12, C16, GF, PF);
    input P0,P1,P2,P3,G0,G1,G2,G3,CIN;
    output [3:0] PF,GF;
    output C4,C8,C12,C16;

    assign C4=G0|P0&cin;
    assign C8=G1|P1&C4;
    assign C12=G2|P2&C8;
    assign C16=G3|P3&C12;
endmodule


module CLA_16bit(a, b, cin, sum, cout, Pout, Gout);
    input [15:0] a,b;
    input cin;
    output [15:0] sum;
    output cout, Pout, Gout;
    
    reg C1,C2,C3;
    reg P0,P1,P2,P3,G0,G1,G2,G3;
    CLA_4bit_P_G cla1(a[3:0],b[3:0],sum[3:0], P0,G0);
    CLA_4bit_P_G cla2(a[3:0],b[3:0],sum[3:0],cout[3:0]);
endmodule


module CLA_32bit(a, b, cin, sum, cout, Pout, Gout);

endmodule

module lookahead_carry_unit_32_bit (P0, G0, P1, G1, cin, C16, C32, GF, PF);

endmodule

