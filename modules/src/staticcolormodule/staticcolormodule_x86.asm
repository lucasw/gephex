section .text

;;  static void fill_mmx(uint_32* fb, int size, uint_32 color)

global fill_mmx
global _fill_mmx

fill_mmx:
_fill_mmx:

        push    ebp
        mov     ebp, esp
        pusha; push    ebx

.dst	equ     8
.size	equ     12
.col	equ     16

        mov     edi, [ebp + .dst]
	mov     eax, [ebp + .size]
	shr     eax, 3
	cmp     eax, 0
	jz      .end
        
        mov     ebx, [ebp + .col]
        movd    mm1, ebx
        movd    mm0, ebx
        punpckldq mm0, mm1

        align 32
.loop:
                movq    [edi + 0],  mm0
                movq    [edi + 8],  mm0
                movq    [edi + 16], mm0
                movq    [edi + 24], mm0
                add     edi, 32
                dec     eax
        jnz     .loop

        emms
.end:
        ;; TODO: restpixel bearbeiten

        popa; pop     ebx
        leave                   ; mov esp,ebp / pop ebp
        ret
