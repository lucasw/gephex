section .text

;   void cvt_rgb32_to_i420_mmx(uint8_t* dst, const uint32_t* src,
;                              size_t width, size_t height,
;                              int* pitches, int* offsets)
global cvt_rgb32_to_i420_mmx
cvt_rgb32_to_i420_mmx:
	push	ebp 
	mov	ebp, esp 
	sub	esp, 36        ; local stack space
	pusha

.dst 	equ	8
.src	equ	12
.width	equ	16
.height	equ	20
.pitches equ    24
.offsets equ    28
        
.y	   equ	-4
.x         equ  -8
.pitch_y   equ  -12
.pitch_uv  equ  -16
.pad_y	   equ	-20
.pad_uv    equ  -24
.w2        equ  -28
.h2        equ  -32
.pitch_src equ  -36
            
        mov     eax, 0x00190019
        movd    mm7, eax
        movd    mm4, eax
        punpckldq mm7, mm4

        mov     eax, 0x00810081
        movd    mm6, eax
        movd    mm4, eax
        punpckldq mm6, mm4
                
        mov     eax, 0x00420042
        movd    mm5, eax
        movd    mm4, eax
        punpckldq mm5, mm4
        
        pxor    mm4, mm4
        
        mov     esi, [ebp + .src]
        mov     edi, [ebp + .dst]

        mov     eax, [ebp + .offsets]
        add     edi, [eax]         ; edi = plane_y + offsets[0]

        mov     eax, [ebp + .pitches]
        mov     ebx, [eax]
        mov     [ebp + .pitch_y], ebx

        mov     ebx, [eax + 4]
        mov     [ebp + .pitch_uv], ebx

        mov     eax, [ebp + .pitch_y]
        shl     eax, 1
        sub     eax, [ebp + .width] 
        mov     [ebp + .pad_y], eax  ; pad_y = 2*pitch_y - width

        mov     eax, [ebp + .width]
        shr     eax, 1
        mov     [ebp + .w2], eax

        mov     eax, [ebp + .height]
        shr     eax, 1
        mov     [ebp + .h2], eax
        mov     [ebp + .y], eax ;  y = height / 2
        
        mov     eax, [ebp + .pitch_uv]
        sub     eax, [ebp + .w2]
        mov     [ebp + .pad_uv], eax ; pad_uv = pitch_uv - width/2

        mov     eax, [ebp + .width]
        shl     eax, 2
        mov     [ebp + .pitch_src], eax ; pitch_src = 4*width

	cmp	dword [ebp + .h2], 0
	jz	NEAR .end

       	cmp	dword [ebp + .w2], 0
	jz	NEAR .end

	align 16
	.yloop:
                mov       ecx, [ebp + .w2]
                jmp       .xloop
                align 32
                .xloop:
                        mov        edx, [ebp + .pitch_src]
        
                        ;; shuffle all b values to mm0, all g values to mm1,
                        ;; and all r values to mm2
                        mov        al, [esi + edx + 4]
                        shl        eax, 8
                        mov        al, [esi + edx]
                        shl        eax, 8
                        mov        al, [esi + 4]
                        shl        eax, 8
                        mov        al, [esi]
                        movd       mm0, eax
                        punpcklbw  mm0, mm4

                        mov        al, [esi + edx + 5]
                        shl        eax, 8
                        mov        al, [esi + edx + 1]
                        shl        eax, 8
                        mov        al, [esi + 5]
                        shl        eax, 8
                        mov        al, [esi + 1]
                        movd       mm1, eax
                        punpcklbw  mm1, mm4

                        mov        al, [esi + edx + 6]
                        shl        eax, 8
                        mov        al, [esi + edx + 2]
                        shl        eax, 8
                        mov        al, [esi + 6]
                        shl        eax, 8
                        mov        al, [esi + 2]
                        movd       mm2, eax
                        punpcklbw  mm2, mm4
        
                        pmullw     mm0, mm7
                        pmullw     mm1, mm6
                        pmullw     mm2, mm5

                        paddusw    mm0, mm1
                        paddusw    mm0, mm2

                        psrlw      mm0, 8
        
                        packuswb   mm0, mm0 ; mm0 contains y4y3y2y1y4y3y2y1
        
                        movd       eax, mm0

                        mov        edx, [ebp + .pitch_y]
                        mov        [edi], ax
                        shr        eax, 16
                        mov        [edi + edx], ax

        		add	   esi, 8
        		add        edi, 2
                        dec        ecx
                jnz     .xloop

                add     esi, [ebp + .pitch_src]
                add     edi, [ebp + .pad_y]

                dec     dword [ebp + .y]
	jnz .yloop

.end:
	emms

	popa
	leave			; mov esp,ebp / pop ebp 
	ret
