/* 32-bit simple karatsuba multiplier */

/*32-bit Karatsuba multipliction using a single 16-bit module*/

module iterative_karatsuba_32_16(clk, rst, enable, A, B, C);
    input clk;
    input rst;
    input [31:0] A;
    input [31:0] B;
    output [63:0] C;
    
    input enable;
    
    
    wire [1:0] sel_x;
    wire [1:0] sel_y;
    
    wire [1:0] sel_z;
    wire [1:0] sel_T;
    
    
    wire done;
    wire en_z;
    wire en_T;
    
    
    wire [32:0] h1;
    wire [32:0] h2;
    wire [63:0] g1;
    wire [63:0] g2;
    
    assign C = g2;
    reg_with_enable #(.N(63)) Z(.clk(clk), .rst(rst), .en(en_z), .X(g1), .O(g2) );  // Fill in the proper size of the register
    reg_with_enable #(.N(32)) T(.clk(clk), .rst(rst), .en(en_T), .X(h1), .O(h2) );  // Fill in the proper size of the register
    
    iterative_karatsuba_datapath dp(.clk(clk), .rst(rst), .X(A), .Y(B), .Z(g2), .T(h2), .sel_x(sel_x), .sel_y(sel_y), .sel_z(sel_z), .sel_T(sel_T), .en_z(en_z), .en_T(en_T), .done(done), .W1(g1), .W2(h1));
    iterative_karatsuba_control control(.clk(clk),.rst(rst), .enable(enable), .sel_x(sel_x), .sel_y(sel_y), .sel_z(sel_z), .sel_T(sel_T), .en_z(en_z), .en_T(en_T), .done(done));
    
endmodule

module iterative_karatsuba_datapath(clk, rst, X, Y, T, Z, sel_x, sel_y, en_z, sel_z, en_T, sel_T, done, W1, W2);
    input clk;
    input rst;
    input [31:0] X;    // input X
    input [31:0] Y;    // Input Y
    input [32:0] T;    // input which sums X_h*Y_h and X_l*Y_l (its also a feedback through the register)
    input [63:0] Z;    // input which calculates the final outcome (its also a feedback through the register)
    output reg [63:0] W1;  // Signals going to the registers as input
    output reg [32:0] W2;  // signals hoing to the registers as input
    

    input [1:0] sel_x;  // control signal 
    input [1:0] sel_y;  // control signal 
    
    input en_z;         // control signal 
    input [1:0] sel_z;  // control signal 
    input en_T;         // control signal 
    input [1:0] sel_T;  // control signal 
    
    input done;         // Final done signal
    
    
    
    
    //-------------------------------------------------------------------------------------------------
    
    // Write your datapath here
    //Input to and output for 16 bit multiplier module
    reg [15:0] mult_in_1,mult_in_2;
    wire [31:0] mult_out;
    mult_16 U0 (
        .X(mult_in_1),.Y(mult_in_2),.Z(mult_out)
    );

    reg [15:0] sub_in_1, sub_in_2;
    wire [15:0] sub_out;
    wire sub_cout, ov;
    subtract_Nbit #(.N(16)) U1 (
        .a(sub_in_1), .b(sub_in_2), .cin(1'b0), .S(sub_out), .ov(ov), .cout_sub(sub_cout)
    );

    wire [15:0] sub_out_comp;
    wire cout_comp;
    Complement2_Nbit #(.N(16)) U2 (
        .a(sub_out), .c(sub_out_comp), .cout_comp(cout_comp)
    );

    wire sign;
    assign sign = T[32] ^ sub_cout;

    reg [31:0] add_in_1, add_in_2;
    wire [31:0] add_out;
    wire add_cout;
    adder_Nbit #(.N(32)) U3 (
        .a(add_in_1), .b(add_in_2), .cin(1'b0), .S(add_out), .cout(add_cout)
    );
    wire [31:0] T_comp;
    Complement2_Nbit #(.N(32)) U4 (
        .a(T[31:0]), .c(T_comp), .cout_comp(cout_comp)
    );

    reg [31:0] add_sub_in_1, add_sub_in_2;
    wire [31:0] add_sub_out;
    reg add_sub_cin;
    wire add_sub_cout;
    adder_Nbit #(.N(32)) U5 (
        .a(add_sub_in_1), .b(add_sub_in_2), .cin(add_sub_cin), .S(add_sub_out), .cout(add_sub_cout)
    );

    reg [63:0] big_add_in_1, big_add_in_2;
    wire [63:0] big_add_out;
    wire big_add_cout;
    adder_Nbit #(.N(64)) U6 (
        .a(big_add_in_1), .b(big_add_in_2), .cin(1'b0), .S(big_add_out), .cout(big_add_cout)
    );

    always @ * begin
        case(sel_y)
            2'b01: begin  // xl * yl -> W1l
                mult_in_1 <= X[15:0];
                mult_in_2 <= Y[15:0];
                W1 <= {32'b0 , mult_out[31:0]};
            end
            2'b10: begin 
                mult_in_1 <= X[31:16];
                mult_in_2 <= Y[31:16];
                W1 <= {mult_out[31:0], Z[31:0]};
            end
            2'b11: begin
                mult_in_1 <= T[15:0];
                W2 <= {sign,mult_out[31:0]};
                case(sub_cout)
                        1'b0: begin
                            mult_in_2 <= sub_out;
                        end
                        1'b1: begin
                            mult_in_2 <= sub_out_comp;
                        end
                endcase
            end
            default: begin
                mult_in_1 <= {16'b0};
                mult_in_2 <= {16'b0};
            end
        endcase

        case(sel_T)
            2'b00: begin
                sub_in_1 <= X[31:16];
                sub_in_2 <= X[15:0];
                case (sub_cout)
                    1'b0: begin
                    W2 <= {sub_cout, 16'b0, sub_out};    
                    end
                    1'b1: begin
                    W2 <= {sub_cout, 16'b0, sub_out_comp};    
                    end
                endcase
            end
            2'b01: begin
                sub_in_1 <= Y[31:16];
                sub_in_2 <= Y[15:0];
                // Output of this subtractor goes to multiplier
            end
            2'b10: begin
                add_in_1 <= Z[63:32];
                add_in_2 <= Z[31:0];
                add_sub_cin <= T[32];
                case(T[32]) 
                    1'b0: begin
                        add_sub_in_1 <= T[31:0];
                        add_sub_in_2 <= add_out[31:0];
                        W2 <= {add_sub_cout,add_sub_out};
                    end
                    1'b1: begin
                        add_sub_in_1 <= T_comp[31:0];
                        add_sub_in_2 <= add_out[31:0];
                        W2 <= {add_sub_cout,add_sub_out};
                    end
                endcase
            end
            2'b11: begin
                big_add_in_1 <= Z[63:0];
                big_add_in_2 <= {16'b0,T[31:0],16'b0};
                W1 <= big_add_out;
            end
            default: begin
                big_add_in_1 <= 64'b0;
                big_add_in_2 <= 64'b0;
                sub_in_1 <= 16'b0;
                sub_in_2 <= 16'b0;
                add_in_1 <= 32'b0;
                add_in_2 <= 32'b0;
            end
        endcase
    end
    //--------------------------------------------------------

endmodule


module iterative_karatsuba_control(clk,rst, enable, sel_x, sel_y, sel_z, sel_T, en_z, en_T, done);
    input clk;
    input rst;
    input enable;
    
    output reg [1:0] sel_x;
    output reg [1:0] sel_y;
    
    output reg [1:0] sel_z;
    output reg [1:0] sel_T;    
    
    output reg en_z;
    output reg en_T;
    
    
    output reg done;
    
    reg [5:0] state, nxt_state;
    parameter S = 6'b000000; //dummy start state
    parameter S0 = 6'b000001;   // xl * yl -> W1l
    parameter S1 = 6'b000010;   // xh * yh -> W1h
    parameter S2 = 6'b000100;   // xh - xl -> W2 [15:0], W2[32] = sub_cout
    parameter S3 = 6'b001000;   // T * (yh - yl) -> W2 
    parameter S4 = 6'b010000;   // T + (Zh + Zl) -> W2
    parameter S5 = 6'b100000;   // Z + (T << 16) -> W1
    parameter S6 = 6'b111111;   // done

    always @(posedge clk) begin
        if (rst) begin
            state <= S;
        end
        else if (enable) begin
            state <= nxt_state;
        end
    end
    

    always@(*) begin
        case(state)
            S: begin
                sel_x <= 2'b00;
                sel_y <= 2'b00;
                en_z <= 1'b1;
                en_T <= 1'b0;
                sel_z <= 2'b00;
                sel_T <= 2'b00;
                done <= 1'b0;

                nxt_state <= S0;
            end
            S0: 
                begin
                    done <= 1'b0;
                    if (enable) begin 
                        sel_x <= 2'b01;
                        sel_y <= 2'b01;
                        en_z <= 1'b1;
                        en_T <= 1'b0;
                        sel_z <= 2'b00;
                        sel_T <= 2'b00;
                        
                        nxt_state <= S1;
                    end
                end
            S1: 
                begin
                    sel_x <= 2'b10;
                    sel_y <= 2'b10;
                    en_z <= 1'b1;
                    en_T <= 1'b0;
                    sel_z <= 2'b00;
                    sel_T <= 2'b00;
                    
					nxt_state <= S2;
                end
            S2: 
                begin
                    sel_x <= 2'b11;
                    sel_y <= 2'b00;
                    en_z <= 1'b0;
                    en_T <= 1'b1;
                    sel_z <= 2'b00;
                    sel_T <= 2'b00;
                    
					nxt_state <= S3;
                end
            S3: 
                begin
                    sel_x <= 2'b00;
                    sel_y <= 2'b11;
                    en_z <= 1'b0;
                    en_T <= 1'b1;
                    sel_z <= 2'b00;
                    sel_T <= 2'b01;
                    
					nxt_state <= S4;
                end
            S4: 
                begin
                    sel_x <= 2'b00;
                    sel_y <= 2'b00;
                    en_z <= 1'b0;
                    en_T <= 1'b1;
                    sel_z <= 2'b00;
                    sel_T <= 2'b10;
                    
					nxt_state <= S5;
                end
            S5: 
                begin
                    sel_x <= 2'b00;
                    sel_y <= 2'b00;
                    en_z <= 1'b1;
                    en_T <= 1'b0;
                    sel_z <= 2'b00;
                    sel_T <= 2'b11;
                    
					nxt_state <= S6;
                end
            S6:
                begin
                    en_z <= 1'b0;
                    en_T <= 1'b0;
                    done <= 1'b1;
                end
            default:
                begin
                    sel_x <= 2'b00;
                    sel_y <= 2'b00;
                    en_z <= 1'b0;
                    en_T <= 1'b0;
                    sel_z <= 2'b00;
                    sel_T <= 2'b00;
                    done <= 1'b0;
                end
        endcase
        
    end

endmodule


module reg_with_enable #(parameter N = 32) (clk, rst, en, X, O );
    input [N:0] X;
    input clk;
    input rst;
    input en;
    output [N:0] O;
    
    reg [N:0] R;
    
    always@(posedge clk) begin
        if (rst) begin
            R <= {N{1'b0}};
        end
        if (en) begin
            R <= X;
        end
    end
    assign O = R;
endmodule







/*-------------------Supporting Modules--------------------*/
/*------------- Iterative Karatsuba: 32-bit Karatsuba using a single 16-bit Module*/

module mult_16(X, Y, Z);
input [15:0] X;
input [15:0] Y;
output [31:0] Z;

assign Z = X*Y;

endmodule


module mult_17(X, Y, Z);
input [16:0] X;
input [16:0] Y;
output [33:0] Z;

assign Z = X*Y;

endmodule

module full_adder(a, b, cin, S, cout);
input a;
input b;
input cin;
output S;
output cout;

assign S = a ^ b ^ cin;
assign cout = (a&b) ^ (b&cin) ^ (a&cin);

endmodule


module check_subtract (A, B, C);
 input [7:0] A;
 input [7:0] B;
 output [8:0] C;
 
 assign C = A - B; 
endmodule



/* N-bit RCA adder (Unsigned) */
module adder_Nbit #(parameter N = 32) (a, b, cin, S, cout);
input [N-1:0] a;
input [N-1:0] b;
input cin;
output [N-1:0] S;
output cout;

wire [N:0] cr;  

assign cr[0] = cin;


generate
    genvar i;
    for (i = 0; i < N; i = i + 1) begin
        full_adder addi (.a(a[i]), .b(b[i]), .cin(cr[i]), .S(S[i]), .cout(cr[i+1]));
    end
endgenerate    


assign cout = cr[N];

endmodule


module Not_Nbit #(parameter N = 32) (a,c);
input [N-1:0] a;
output [N-1:0] c;

generate
genvar i;
for (i = 0; i < N; i = i+1) begin
    assign c[i] = ~a[i];
end
endgenerate 

endmodule


/* 2's Complement (N-bit) */
module Complement2_Nbit #(parameter N = 32) (a, c, cout_comp);

input [N-1:0] a;
output [N-1:0] c;
output cout_comp;

wire [N-1:0] b;
wire ccomp;

Not_Nbit #(.N(N)) compl(.a(a),.c(b));
adder_Nbit #(.N(N)) addc(.a(b), .b({ {N-1{1'b0}} ,1'b1 }), .cin(1'b0), .S(c), .cout(ccomp));

assign cout_comp = ccomp;

endmodule


/* N-bit Subtract (Unsigned) */
module subtract_Nbit #(parameter N = 32) (a, b, cin, S, ov, cout_sub);
//Gives A-B if A>=B or 2's complement of B-A is A<B

input [N-1:0] a;
input [N-1:0] b;
input cin;//Previous borrow, added to b during subtraction
output [N-1:0] S;
output ov;
output cout_sub;

wire [N-1:0] minusb;
wire cout;
wire ccomp;

Complement2_Nbit #(.N(N)) compl(.a(b),.c(minusb), .cout_comp(ccomp));//ccomp = 1 shows b is zero
adder_Nbit #(.N(N)) addc(.a(a), .b(minusb), .cin(1'b0), .S(S), .cout(cout));//

assign ov = (~(a[N-1] ^ minusb[N-1])) & (a[N-1] ^ S[N-1]);//?
assign cout_sub = cout | ccomp;//If zero, output is negative, otherwise positive

endmodule



/* n-bit Left-shift */

module Left_barrel_Nbit #(parameter N = 32)(a, n, c);

input [N-1:0] a;
input [$clog2(N)-1:0] n;
output [N-1:0] c;


generate
genvar i;
for (i = 0; i < $clog2(N); i = i + 1 ) begin: stage
    localparam integer t = 2**i;
    wire [N-1:0] si;
    if (i == 0) 
    begin 
        assign si = n[i]? {a[N-t:0], {t{1'b0}}} : a;
    end    
    else begin 
        assign si = n[i]? {stage[i-1].si[N-t:0], {t{1'b0}}} : stage[i-1].si;
    end
end
endgenerate

assign c = stage[$clog2(N)-1].si;

endmodule



