.name "Meh"
.comment "just say a Meh"

			sti r1, %:liveloop, %1	#25 25
liveloop:	live %0					#10 35
        	zjmp %:liveloop			#20 55

#say meh
			ld %77, r2				#5 60 r2 == M
			aff r2					#2 62 say M
			ld %101, r2				#5 67 r2 == e
			aff r2					#2 69 say e
			ld %104, r2				#5 74 r4 == h
			aff r2					#2 76 say h
			ld %0, r2				#5 81 r5 == 0, carry == 1

#make livers
			fork %:liveloop			#800 881
			fork %:liveloop			#800 1681

			sti r1, %:liveloop2, %1	#25 1706
liveloop2:	live %0					#10 1731
			fork %:liveloop			#800 2531
			fork %:liveloop			#800 3331
			zjmp %:liveloop
