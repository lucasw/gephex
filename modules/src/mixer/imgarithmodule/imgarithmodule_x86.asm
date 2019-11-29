section .text

;;  void mul_x86_mmx(uint_32 size,
;;		     const unsigned char* framebuf1,
;;		     const unsigned char* framebuf2,
;;		     unsigned char* result,  int amount)
global	mul_mmx
global	_mul_mmx 
mul_mmx: 
_mul_mmx: 
	push	ebp 
	mov	ebp,esp 
	sub	esp,0x08	; 8 bytes of local stack space
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.fb2	equ	16
.dst	equ	20
.amount	equ	24

.tmp	equ	-8

	mov	eax, [ebp + .amount]

	mov	[ebp + .tmp + 0], ax
	mov	[ebp + .tmp + 2], ax
	mov	[ebp + .tmp + 4], ax
	mov	[ebp + .tmp + 6], ax

	movq	mm4, [ebp + .tmp]
	
	mov	eax, 255
	sub	eax, [ebp + .amount]
	
	mov	[ebp + .tmp + 0], ax
	mov	[ebp + .tmp + 2], ax
	mov	[ebp + .tmp + 4], ax
	mov	[ebp + .tmp + 6], ax

	movq	 mm6, [ebp + .tmp]

	pxor	mm5, mm5
	
	mov	esi, [ebp + .fb1]
	mov	ebx, [ebp + .fb2]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 1
	cmp	eax, 0
	jz	NEAR .end

	align 32
	.loop:
		movq	  mm0, [esi]
		punpcklbw mm0, mm5	; mm0 = x1 

		movq	  mm7, mm0	; mm7 = x1 
	
		movq	  mm1, [ebx]	
		punpcklbw mm1, mm5	; mm1 = y1 
		
		pmullw	  mm0, mm1	; mm0 = x1*y1
		psrlw	  mm0, 8
		
		movq	  mm2, [esi]
		punpckhbw mm2, mm5

		movq	  mm3, [ebx]
		punpckhbw mm3, mm5

		pmullw	  mm2, mm3	; mm2 = x2*y2
		psrlw	  mm2, 8
			
		movq	  mm3, [esi]	
		movq	  mm1, mm7	; mm1 = x1
		punpckhbw mm3, mm5	; mm3 = x2 

		pmullw	  mm1, mm6	; mm1 =	 x1 * (1-f)
		pmullw	  mm3, mm6	; mm3 =	 x2 * (1-f)
		pmullw	  mm0, mm4	; mm0 =	 (x1*y1) * f
		pmullw	  mm2, mm4	; mm2 =	 (x2*y2) * f
			
		paddw	  mm1, mm0	; mm1 = x1*(1-f) + (x1*y1)*f
		paddw	  mm2, mm3	; mm2 = x2*(1-f) + (x2*y2)*f

		psrlw	  mm1, 8
		psrlw	  mm2, 8

		packuswb  mm1, mm2	; mm1 = x*(1-f) + (x*y)*f 

		movq	  [edi], mm1			

		add	  esi, 8
		add	  ebx, 8
		add	  edi, 8
		dec	  eax
	jnz .loop
.end:
	emms

	mov	ecx, [ebp + .size]
	and	ecx, 0x01	; TOCHECK
	cmp	ecx, 0
	jz	.quit

	;; TODO: process last pixel manually

.quit:
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret



;; static void invert_mmx( uint_32 size, 
;;	      	           const unsigned char* src,
;;			   const unsigned char* dummy,
;;			   unsigned char* dst, int amount ) 
global	invert_mmx
global	_invert_mmx 
invert_mmx: 
_invert_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.dst	equ	20

	mov	esi, [ebp + .fb1]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]
	shr	eax, 3
	cmp	eax, 0
	jz	.end

	mov	ebx, 0x00ffffff
	movd	mm0, ebx
	movd	mm4, ebx
	punpckldq mm4, mm0

	align 32
	.loop:
		movq	mm0, [esi]
		movq	mm1, [esi+8]
		movq	mm2, [esi+16]
		movq	mm3, [esi+24]
		pxor	mm0, mm4
		pxor	mm1, mm4
		pxor	mm2, mm4
		pxor	mm3, mm4
		movq	[edi],	  mm0
		movq	[edi+8],  mm1
		movq	[edi+16], mm2
		movq	[edi+24], mm3
		add	esi, 32
		add	edi, 32
		dec	eax
	jnz .loop
	emms
.end:

	;; TODO: process last pixels manually
	
	popa ;pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret


;; static void mulc_mmx(uint_32 size,
;;			const unsigned char* framebuf1,
;;			const unsigned char* framebuf2,
;;			unsigned char* result, int amount)

global	mulc_mmx
global	_mulc_mmx 
mulc_mmx: 
_mulc_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.dst	equ	20
.amount equ	24
	
	mov	esi, [ebp + .fb1]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 1
	cmp	eax, 0
	jz	.end

	mov	ebx, [ebp + .amount]
	mov	ecx, ebx
	shl	ebx, 16
	or	ebx, ecx
	
	movd	mm4, ebx
	movd	mm0, ecx
	punpckldq mm4, mm0
	
	pxor	mm5, mm5

	align 32
	.loop:
		movq	  mm0, [esi]
		movq	  mm1, mm0

		punpcklbw mm0, mm5	; mm0 = x1 
		punpckhbw mm1, mm5	; mm1 = x2

		pmullw	  mm0, mm4
		psrlw	  mm0, 6	; mm0 = 4*c*x1

		pmullw	  mm1, mm4
		psrlw	  mm1, 6	; mm0 = 4*c*x2

		packuswb  mm0, mm1	; mm0 = 4*c*x

		movq	[edi], mm0
			
		add	esi, 8
		add	edi, 8
		dec	eax
	jnz .loop
	emms
.end:

	;; TODO: process last pixel manually
	
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret

	
;; static void subc_mmx(uint_32 size,
;;			const unsigned char* framebuf1,
;;			const unsigned char* framebuf2,
;;			unsigned char* result, int amount)

global	subc_mmx
global	_subc_mmx 
subc_mmx: 
_subc_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.dst	equ	20
.amount equ	24
	
	mov	esi, [ebp + .fb1]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 2
	cmp	eax, 0
	jz	.end

	mov	ebx, [ebp + .amount]
	mov	bh, bl
	shl	ebx, 8
	mov	bl, bh
	
	movd	mm4, ebx
	movd	mm0, ebx
	punpckldq mm4, mm0
	
	align 32
	.loop:
		movq	mm0, [esi]
		movq	mm1, [esi+8]			
		psubusb mm0, mm4 
		psubusb mm1, mm4
		movq	[edi],	 mm0
		movq	[edi+8], mm1
		add	esi, 16			
		add	edi, 16
		dec	eax
	jnz .loop
	
	emms	    
.end:
	;; TODO: process last pixel manually
	
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret

;; static void addc_mmx(uint_32 size,
;;			const unsigned char* framebuf1,
;;			const unsigned char* framebuf2,
;;			unsigned char* result, int amount)

global	addc_mmx
global	_addc_mmx 
addc_mmx: 
_addc_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.dst	equ	20
.amount equ	24
	
	mov	esi, [ebp + .fb1]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 2
	cmp	eax, 0
	jz	.end

	mov	ebx, [ebp + .amount]
	mov	bh, bl
	shl	ebx, 8
	mov	bl, bh
	
	movd	mm4, ebx
	movd	mm0, ebx
	punpckldq mm4, mm0
	
	align 32
	.loop:
		movq	mm0, [esi]
		movq	mm1, [esi+8]			
		paddusb mm0, mm4 
		paddusb mm1, mm4
		movq	[edi],	 mm0
		movq	[edi+8], mm1
		add	esi, 16			
		add	edi, 16
		dec	eax
	jnz .loop
	
	emms	    
.end:
	;; TODO: process last pixel manually
	
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret

;; static void add_mmx(uint_32 size,
;;		       const unsigned char* framebuf1,
;;		       const unsigned char* framebuf2,
;;		       unsigned char* result, int amount)

global	add_mmx
global	_add_mmx 
add_mmx: 
_add_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.fb2	equ	16
.dst	equ	20
.amount equ	24
	
	mov	esi, [ebp + .fb1]
	mov	ebx, [ebp + .fb2]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 2
	cmp	eax, 0
	jz	.end

	mov	ecx, 255
	sub	ecx, [ebp + .amount]
	mov	ch, cl
	shl	ecx, 8
	mov	cl, ch
	
	movd	mm4, ecx
	movd	mm0, ecx
	punpckldq mm4, mm0
	
	align 32
	.loop:
		movq	mm0, [esi]
		movq	mm1, [esi+8]
		movq	mm2, [ebx]
		movq	mm3, [ebx+8]
		psubusb mm2, mm4
		psubusb mm3, mm4 
		paddusb mm0, mm2 
		paddusb mm1, mm3
		movq	[edi], mm0
		movq	[edi+8], mm1
		add	esi, 16
		add	ebx, 16
		add	edi, 16
		dec	eax
	jnz .loop
	
	emms	    
.end:
	;; TODO: process last pixel manually
	
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret

;; static void sub_mmx(uint_32 size,
;;		       const unsigned char* framebuf1,
;;		       const unsigned char* framebuf2,
;;		       unsigned char* result, int amount)

global	sub_mmx
global	_sub_mmx 
sub_mmx: 
_sub_mmx: 
	push	ebp 
	mov	ebp,esp 
	pusha; push	ebx

.size	equ	8
.fb1	equ	12
.fb2	equ	16
.dst	equ	20
.amount equ	24
	
	mov	esi, [ebp + .fb1]
	mov	ebx, [ebp + .fb2]
	mov	edi, [ebp + .dst]
	mov	eax, [ebp + .size]

	shr	eax, 2
	cmp	eax, 0
	jz	.end

	mov	ecx, 255
	sub	ecx, [ebp + .amount]
	mov	ch, cl
	shl	ecx, 8
	mov	cl, ch
	
	movd	mm4, ecx
	movd	mm0, ecx
	punpckldq mm4, mm0
	
	align 32
	.loop:
		movq	mm0, [esi]
		movq	mm1, [esi+8]
		movq	mm2, [ebx]
		movq	mm3, [ebx+8]
		psubusb mm2, mm4
		psubusb mm3, mm4 
		psubusb mm0, mm2 
		psubusb mm1, mm3
		movq	[edi], mm0
		movq	[edi+8], mm1
		add	esi, 16
		add	ebx, 16
		add	edi, 16
		dec	eax
	jnz .loop
	
	emms	    
.end:
	;; TODO: process last pixel manually
	
	popa; pop	ebx
	leave			; mov esp,ebp / pop ebp 
	ret
