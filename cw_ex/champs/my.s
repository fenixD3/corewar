.name	"My!"
.comment "Alors la, si ca marche, trop content !  :)"


		live %5
		sti     r1,%:label00,%1
        ld %12,r2
        fork  %:label00
        sti     r1,%:label00,%1



label00: ld    %400,r3
     live  %0
     ld    %0,r2
     ld    %0,r4
