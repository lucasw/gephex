

section .text

;;  void chroma_key_mmx(uint_8 rr, uint_8 gg, uint_8 bb, uint_8 tt,
;;                      uint_32* dst, const uint_32* fg, const uint_32* bg,
;;                      int size)

global chroma_key_mmx
global _chroma_key_mmx

chroma_key_mmx:
_chroma_key_mmx:

        push    ebp
        mov     ebp, esp
        sub     esp, 0x10        ; 16 bytes of local stack space
        pusha; push    ebx

.rr	equ     8
.gg	equ     12
.bb	equ     16
.tt     equ     20
.dst    equ     24
.fg	equ     28
.bg	equ     32
.size	equ	36

.tol    equ     -16
.match  equ     -8

        mov     eax, [ebp + .tt]
        mov     word [ebp + .tol + 0], ax
        mov     word [ebp + .tol + 2], ax
        mov     word [ebp + .tol + 4], ax
        mov     word [ebp + .tol + 6], 0xff
        mov     eax, [ebp + .tol]


        mov     eax, [ebp + .bb]
        mov     byte [ebp + .match + 0], al
        mov     eax, [ebp + .gg]
        mov     byte [ebp + .match + 1], al
        mov     eax, [ebp + .rr]
        mov     byte [ebp + .match + 2], al
        mov     byte [ebp + .match + 3], 127
        mov     eax, [ebp + .match]
        mov     [ebp + .match + 4], eax

	movq    mm5, [ebp + .tol]         ; mm5 = tol
        movq    mm6, [ebp + .match]       ; mm6 = match
	pxor    mm7, mm7                  ; mm7 = 0

	mov     ecx, [ebp + .size]
	mov     esi, [ebp + .fg]
	mov     edx, [ebp + .bg]
	mov     edi, [ebp + .dst]
	shr     ecx, 1
	cmp     ecx, 0
	jz      .end

        align 32
.loop:                           
		movq       mm0, [esi]      ; read foreground
		movq       mm4, mm0        ; store foreground in mm4

		movq       mm1, mm6        ; mm1 = match
		movq       mm2, mm4        ; mm2 = fg

		psubusb    mm0, mm6        ; mm0 = max(fg - match, 0)
		psubusb    mm1, mm4        ; mm1 = max(match - fg, 0)

		por        mm1, mm0        ; mm1 = abs(fg-match)

		movq       mm0, mm1        ; process first pixel in mm0
		movq       mm2, mm1        ; and sexond pixel in mm2

		punpcklbw  mm0, mm7
		pcmpgtw    mm0, mm5        ; mm0 = abs(fg_1 - match) > tt
		psrlw      mm0, 8          ; convert unsigned words
                                           ; to unsigned bytes
		punpckhbw  mm2, mm7
		pcmpgtw    mm2, mm5        ; mm2 = abs(fg_2 - match) > tt
		psrlw      mm2, 8          ; convert unsigned words
                                           ; to unsigned bytes

		packuswb   mm0, mm2        ; mm0 now contains two dwords
                                           ; mm0 = b2 | b1, which determ.
                                           ; wether the first and second
                                           ; pixel come from the fg or bg


                movd       eax, mm0        ; first pixel
                movd       ebx, mm4
        
                cmp        eax, 0

                cmovnz     eax, ebx    
                jz         .first_bg
                jmp        .first_skip 
        .first_bg:                          
                mov        eax, [edx]
        .first_skip:                         

                mov        [edi], eax

                psrlq      mm4, 32         ; second pixel
                psrlq      mm0, 32
                movd       eax, mm0
                movd       ebx, mm4
                
                cmp        eax, 0

                cmovnz     eax, ebx
                jz         .second_bg
                jmp        .second_skip
        .second_bg:
                mov        eax, [edx + 4]
        .second_skip:

                mov        [edi + 4], eax

                add  esi, 8
                add  edx, 8
                add  edi, 8
                dec  ecx
	jnz .loop
.end:
	emms

        popa; pop     ebx
        leave                   ; mov esp,ebp / pop ebp
        ret


;;  void chroma_key_e3dnow(uint_8 rr, uint_8 gg, uint_8 bb, uint_8 tt,
;;                         uint_32* dst, const uint_32* fg, const uint_32* bg,
;;                         int size)

global chroma_key_e3dnow
global _chroma_key_e3dnow

chroma_key_e3dnow:
_chroma_key_e3dnow:

        push    ebp
        mov     ebp, esp
        sub     esp, 0x10        ; 64 bytes of local stack space
        pusha ;push    ebx

.rr	equ     8
.gg	equ     12
.bb	equ     16
.tt      equ     20
.dst     equ     24
.fg	equ     28
.bg	equ     32
.size	equ	36

.tol     equ     -16
.match   equ     -8

        mov     eax, [ebp + .tt]
        mov     word [ebp + .tol + 0], ax
        mov     word [ebp + .tol + 2], ax
        mov     word [ebp + .tol + 4], ax
        mov     word [ebp + .tol + 6], 0xff
        mov     eax, [ebp + .tol]


        mov     eax, [ebp + .bb]
        mov     byte [ebp + .match + 0], al
        mov     eax, [ebp + .gg]
        mov     byte [ebp + .match + 1], al
        mov     eax, [ebp + .rr]
        mov     byte [ebp + .match + 2], al
        mov     byte [ebp + .match + 3], 127
        mov     eax, [ebp + .match]
        mov     [ebp + .match + 4], eax

	movq    mm5, [ebp + .tol]          ; mm5 = tol
        movq    mm6, [ebp + .match]        ; mm6 = match
	pxor    mm7, mm7                  ; mm7 = 0

	mov     ecx, [ebp + .size]
	mov     esi, [ebp + .fg]
	mov     edx, [ebp + .bg]
	mov     edi, [ebp + .dst]
	shr     ecx, 1
	cmp     ecx, 0
	jz      .end

        align 32
.loop:                           
                prefetchnta [esi + 512]
		prefetchnta [edx + 512]

		movq       mm0, [esi]      ; read foreground
		movq       mm4, mm0        ; store foreground in mm4  

		movq       mm1, mm6        ; mm1 = match
		movq       mm2, mm4        ; mm2 = fg

		psubusb    mm0, mm6        ; mm0 = max(fg - match, 0)
		psubusb    mm1, mm4        ; mm1 = max(match - fg, 0)

		por        mm1, mm0        ; mm1 = abs(fg-match)

		movq       mm0, mm1        ; process first pixel in mm0
		movq       mm2, mm1        ; and sexond pixel in mm2

		punpcklbw  mm0, mm7
		pcmpgtw    mm0, mm5        ; mm0 = abs(fg_1 - match) > tt
		psrlw      mm0, 8          ; convert unsigned words
                                           ; to unsigned bytes
		punpckhbw  mm2, mm7
		pcmpgtw    mm2, mm5        ; mm2 = abs(fg_2 - match) > tt
		psrlw      mm2, 8          ; convert unsigned words
                                           ; to unsigned bytes

		packuswb   mm0, mm2        ; mm0 now contains two dwords
                                           ; mm0 = b2 | b1, which determ.
                                           ; wether the first and second
                                           ; pixel come from the fg or bg

		movd       eax, mm0
		cmp        eax, 0

		movd       ebx, mm4
		cmove      ebx, [edx]
		movd       mm3, ebx

		pswapd     mm4, mm4
		pswapd     mm0, mm0

		movd       eax, mm0
		cmp        eax, 0
		movd       ebx, mm4
		cmove      ebx, [edx + 4]
		movd       mm4, ebx

		punpckldq  mm3, mm4

		movntq     [edi], mm3

		add  esi, 8
		add  edx, 8
		add  edi, 8
		dec  ecx
	jnz .loop
.end:    
	femms

        popa ; pop ebx
        leave                   ; mov esp,ebp / pop ebp
        ret

