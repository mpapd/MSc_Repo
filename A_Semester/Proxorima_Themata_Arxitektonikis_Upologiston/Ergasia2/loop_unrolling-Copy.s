.data
X: .double 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42,44, 46, 48
Z: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
Y: .double 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.text
MAIN:	
		daddi R1,R0,24
		daddi R2,R0,X
		daddi R3,R0,Z
		daddi R4,R0,Y
loop:	
		l.d F1,0(R2)
		l.d F2,0(R3)
		l.d F15,8(R2)
		l.d F16,8(R3)
		l.d F17,24(R2)
		l.d F18,24(R3)
		l.d F19,32(R2)
		l.d F20,32(R3)
		
		mul.d F3,F1,F1
		div.d F4,F1,F2
		add.d F5,F3,F4
		
		mul.d F6,F15,F15
		div.d F7,F15,F16
		add.d F8,F6,F7
		
		mul.d F9,F17,F17
		div.d F10,F17,F18
		add.d F11,F9,F10
		
		mul.d F12,F19,F19
		div.d F13,F19,F20
		add.d F14,F12,F13
		
		s.d F5,0(R4)
		s.d F8,8(R4)
		s.d F11,16(R4)
		s.d F14,24(R4)

		daddi R2,R2,32
		daddi R3,R3,32
		daddi R4,R4,32
		
		daddi R1,R1,-4
		bnez R1, loop
		halt
		