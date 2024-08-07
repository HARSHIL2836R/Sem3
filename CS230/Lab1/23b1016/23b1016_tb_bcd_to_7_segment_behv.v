module tb ();

wire A,B,C,D,E,F,G;
reg x1,x2,x3,x4;

bc_7 circuit (x1,x2,x3,x4,A,B,C,D,E,F,G);

initial begin
    x1 = 0;x2 = 0;x3=0;x4=1;
    $monitor("x1=%d,x2=%d,x3=%d,x4=%d,A=%d,B=%d,C=%d,D=%d,E=%d,F=%d,G=%d",x1,x2,x3,x4,A,B,C,D,E,F,G);

    $display("Harshil Solanki 23B1016");
    #2 x4=0;x3=1;
    #3 x4=1;
    #4 x2=1;x3=0;x4=0;
    #5 x4=1;
    #6 x3=1;x4=0;
    #7 x4=1;
    #8 x1=1;x2=0;x3=0;x4=0;
    #9 x4=1;
    #10 x1=0;x4=0;
    $finish;

end

initial begin
    $dumpfile("mydesign_tb.vcd");
    $dumpvars(0,circuit);
end

endmodule

