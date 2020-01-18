.data
X: .double 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48
Z: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24
Y: .double 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.text
MAIN: daddi R1,R0,24
daddi R2,R0,X
daddi R3,R0,Z
daddi R4,R0,Y
loop: l.d F1,0(R2)
l.d F2,0(R3)
mul.d F3,F1,F1
div.d F4,F1,F2
add.d F5,F3,F4
s.d F5,0(R4)
daddi R2,R2,8
daddi R3,R3,8
daddi R4,R4,8
daddi R1,R1,-1
bnez R1,loop
halt