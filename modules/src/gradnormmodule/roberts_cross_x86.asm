
;;  void roberts_cross_x86_e3dnow(uint_32 xsize, uint_32 ysize,
;;                   const uint_32* src,
;;      	     uint_32* dst,
;;                   float scale)

global _roberts_cross_e3dnow

section .text

_roberts_cross_e3dnow: 
        
        push    ebp 
        mov     ebp, esp 
        sub     esp, 0x40        ; 64 bytes of local stack space

xsize	equ     8
ysize	equ     12
src	equ     16
dst     equ     20
scale	equ	24

yi      equ     -16


        femms
                        
        mov     esi, [ebp + src]
        mov     edi, [ebp + dst]

        prefetch [esi+4]
        
        mov     eax, [ebp + xsize]
        shl     eax, 2
        add     eax, 4
        add     esi, eax        ; esi = src + xsize + 1
        add     edi, eax        ; edi = dst + xsize + 1

        prefetchw [edi]
        prefetch [esi]


        mov     ecx, [ebp + ysize] ; init of yloop
        sub     ecx, 2
        mov     [ebp + yi], ecx

        mov     ebx, [ebp + xsize]
        shl     ebx, 2
        neg     ebx             ; ebx = -4*xsize


        pxor    mm3, mm3                
        pxor    mm4, mm4
        pxor    mm5, mm5
        pxor    mm6, mm6

roberts_cross_e3dnow_yloop:
        cmp     DWORD [ebp + yi],  0
        je       roberts_cross_e3dnow_yloop_done

        mov     ecx, [ebp + xsize] ; init of xloop
        sub     ecx, 2

        align 32
roberts_cross_e3dnow_xloop:
        cmp     ecx, 0
        je      roberts_cross_e3dnow_xloop_done

        prefetchw [edi+64]
        prefetch [esi+64]
        
        movd    mm3, [esi]
        movd    mm5, [esi + ebx - 4]
        psadbw  mm3, mm5    
        movd    mm4, [esi - 4]
        movd    mm6, [esi + ebx]

        psadbw  mm4, mm6

        paddw   mm3, mm4
        packuswb mm3, mm3

        movd    eax, mm3
        
        xor     edx, edx
        and     eax, 0xff
                
        or      edx, eax
        shl     edx, 8

        or      edx, eax
        shl     edx, 8

        or      edx, eax

        mov     [edi], edx

        dec     ecx             ; end of xloop        
        add     esi, 4
        add     edi, 4
        jmp     roberts_cross_e3dnow_xloop

roberts_cross_e3dnow_xloop_done:

        dec     DWORD [ebp + yi]       ; end of yloop        
        add     esi, 8
        add     edi, 8
        jmp     roberts_cross_e3dnow_yloop

roberts_cross_e3dnow_yloop_done:
        
        femms

        leave                   ; mov esp,ebp / pop ebp 
        ret

