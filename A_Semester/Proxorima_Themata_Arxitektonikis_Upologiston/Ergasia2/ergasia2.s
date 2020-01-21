.data
X: .double 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48
Z: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24
Y: .double 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.text
MAIN: daddi R1,R0,24
daddi R2,R0,X
daddi R3,R0,Z
daddi R4,R0,Y
loop: 
l.d F1,0(R2)
l.d F2,0(R3)
mul.d F3,F1,F1
div.d F4,F1,F2
add.d F5,F3,F4
s.d F5,0(R4)
daddi R2,R2,8
daddi R3,R3,8
daddi R4,R4,8
l.d F6,-8(R2)
l.d F7,-8(R3)
mul.d F8,F6,F6
div.d F9,F6,F7
add.d F10,F8,F9
s.d F10,-8(R4)
daddi R2,R2,8
daddi R3,R3,8
daddi R4,R4,8
l.d F11,-16(R2)
l.d F12,-16(R3)
mul.d F13,F11,F11
div.d F14,F11,F12
add.d F15,F13,F14
s.d F5,-16(R4)
daddi R2,R2,8
daddi R3,R3,8
daddi R4,R4,8
l.d F16,-32(R2)
l.d F17,-32(R3)
mul.d F18,F16,F16
div.d F19,F16,F17
add.d F20,F18,F19
s.d F5,-32(R4)
daddi R2,R2,8
daddi R3,R3,8
daddi R4,R4,8
daddi R1,R1,-4
bnez R1,loop

halt