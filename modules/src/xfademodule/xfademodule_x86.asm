section .text

;;  void fade_mmx(uint_32 size, unsigned char* framebuf1,
;; 	     unsigned char* framebuf2, unsigned char* result,
;; 	     int fadeValue)

global fade_mmx
global _fade_mmx

fade_mmx:
_fade_mmx:

        push    ebp
        mov     ebp, esp
        sub     esp, 0x08        ; 8 bytes of local stack space
        pusha   ;push    ebx

.size	equ     8
.fb1	equ     12
.fb2	equ     16
.dst    equ     20
.fade   equ     24

.tmp     equ     -8

        mov     eax, [ebp + .fade]
        mov     word [ebp + .tmp + 0], ax
        mov     word [ebp + .tmp + 2], ax
        mov     word [ebp + .tmp + 4], ax
        mov     word [ebp + .tmp + 6], ax
        
	movq    mm5, [ebp + .tmp]
        
        mov     eax, 255
        sub     eax, [ebp + .fade]
        mov     word [ebp + .tmp + 0], ax
        mov     word [ebp + .tmp + 2], ax
        mov     word [ebp + .tmp + 4], ax
        mov     word [ebp + .tmp + 6], ax
        
	movq    mm4, [ebp + .tmp]

       	pxor    mm6, mm6
        
       	mov     edi, [ebp + .dst]
	mov     esi, [ebp + .fb1]
	mov     ebx, [ebp + .fb2]
	mov     eax, [ebp + .size]
	shr     eax, 1
	cmp     eax, 0
	jz      .end

        align 32
.loop:
                movq    mm0, [esi]
                movq    mm1, [esi]
		  
		punpcklbw mm0, mm6
		punpckhbw mm1, mm6
		  
		movq    mm2, [ebx]
		movq    mm3, [ebx]
		  
		punpcklbw mm2, mm6
		punpckhbw mm3, mm6
		  
		pmullw  mm0, mm4
		pmullw  mm1, mm4
		 
		pmullw  mm2, mm5
		pmullw  mm3, mm5
		  
		paddw   mm0, mm2
		paddw   mm1, mm3
		  
		psrlw   mm0, 8
		psrlw   mm1, 8
		  
		packuswb mm0, mm1
		  
		movq    [edi], mm0
		  
		add     esi, 8
		add     ebx, 8
		add     edi, 8
                dec     eax
	jnz .loop

.end:

        ;; TODO: restpixel bearbeiten
        emms

        popa; pop     ebx
        leave                   ; mov esp,ebp / pop ebp
        ret


;;  void fade_e3dnow(uint_32 size, unsigned char* framebuf1,
;; 	     unsigned char* framebuf2, unsigned char* result,
;; 	     int fadeValue)

global fade_e3dnow
global _fade_e3dnow

fade_e3dnow:
_fade_e3dnow:

        push    ebp
        mov     ebp, esp
        sub     esp, 0x08        ; 8 bytes of local stack space
	pusha                    ;push    ebx

.size	equ     8
.fb1	equ     12
.fb2	equ     16
.dst    equ     20
.fade   equ     24
        
.tmp     equ     -8

        mov     eax, [ebp + .fade]
        mov     word [ebp + .tmp + 0], ax
        mov     word [ebp + .tmp + 2], ax
        mov     word [ebp + .tmp + 4], ax
        mov     word [ebp + .tmp + 6], ax
        
	movq    mm5, [ebp + .tmp]
        
        mov     eax, 255
        sub     eax, [ebp + .fade]
        mov     word [ebp + .tmp + 0], ax
        mov     word [ebp + .tmp + 2], ax
        mov     word [ebp + .tmp + 4], ax
        mov     word [ebp + .tmp + 6], ax
        
	movq    mm4, [ebp + .tmp]

       	pxor    mm6, mm6
        
       	mov     edi, [ebp + .dst]
	mov     esi, [ebp + .fb1]
	mov     ebx, [ebp + .fb2]
	mov     eax, [ebp + .size]
	shr     eax, 1
	cmp     eax, 0
	jz      .end

        align 32
.loop:
                prefetchnta     [esi + 64]
                prefetchnta     [ebx + 64]
        
                movq    mm0, [esi]
                movq    mm1, [esi]
		  
		punpcklbw mm0, mm6
		punpckhbw mm1, mm6
		  
		movq    mm2, [ebx]
		movq    mm3, [ebx]
		  
		punpcklbw mm2, mm6
		punpckhbw mm3, mm6
		  
		pmullw  mm0, mm4
		pmullw  mm1, mm4
		 
		pmullw  mm2, mm5
		pmullw  mm3, mm5
		  
		paddw   mm0, mm2
		paddw   mm1, mm3
		  
		psrlw   mm0, 8
		psrlw   mm1, 8
		  
		packuswb mm0, mm1
		  
		movntq  [edi], mm0
		  
		add     esi, 8
		add     ebx, 8
		add     edi, 8
                dec     eax
	jnz .loop

.end:

        ;; TODO: restpixel bearbeiten
        femms

        popa                    ; pop     ebx
        leave                   ;mov esp,ebp / pop ebp

        ret
