#include "cpuinfo.h"

#include "basic_types.h"
#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

int cpuinfo_has_cpuid()
{
  //TODO: might not work on cyrix or old p5
  // (see: http://www.sandpile.org/ia32/cpuid.htm)
  int_32 t = 0;

#if !defined(CPU_I386)
  return 0;
#elif defined(COMP_VC) 
  _asm
    {
      pushfd				// Save EFLAGS to stack
	pop eax				// Store EFLAGS in EAX
	mov ebx, eax		// Save in EBX for testing later
	xor eax, 00200000h	// Switch bit 21
	push eax			// Copy changed value to stack
	popfd				// Save changed EAX to EFLAGS
	pushfd				// Push EFLAGS to top of stack
	pop eax				// Store EFLAGS in EAX
	cmp eax, ebx		// See if bit 21 has changed
	jz END				// Quit if no CPUID found
        mov eax, 1			// Else set t to 1
        mov t, eax
        END:
    }
#elif defined(COMP_GCC) 
  __asm__ __volatile__
    (
     "pushfl                           \n\t"
     "popl %%eax                       \n\t"
     "movl %%eax, %%ebx                \n\t"
     "xorl $0x00200000, %%eax          \n\t"
     "pushl %%eax                      \n\t"
     "popfl                            \n\t"
     "pushfl                           \n\t"
     "popl %%eax                       \n\t"
     "cmpl %%ebx, %%eax                \n\t"
     "jz 0f                            \n\t"
     "movl $1, %%eax                   \n\t"
     "0:                               \n\t"
     : "=a"(t)
     :
     : "ebx"
     );
#endif

  return t;
}

/**
 * Returns the result that cpuid stores in edx when called with
 * eax == eax_in.
 */
static int_32 cpuid_simple(int_32 eax_in)
{
  int_32 result;

#if !defined(CPU_I386)
  return 0;
#elif defined(COMP_VC) 
  _asm
    {
      mov eax, eax_in
        CPUID
        mov result, edx
	}
#elif defined(COMP_GCC) 
  __asm__ __volatile__
    (
     "cpuid               \n\t"
     :	"=d" (result)
     :	"a" (eax_in)
     : "ebx", "ecx"
     );
#endif
  
  return result;
}

/**
 * Returns all values of cpuid
 */
static void cpuid_extended(uint_32 eax_in,
			   uint_32* eax_out,
			   uint_32* ebx_out,
			   uint_32* ecx_out,
			   uint_32* edx_out)
{

#if !defined(CPU_I386)
  return;
#elif defined(COMP_VC) 
  _asm{
      mov eax, eax_in
      CPUID
	  push edi
	  mov edi, eax_out
      mov [edi], eax
	  mov edi, ebx_out
	  mov [edi], ebx
	  mov edi, ecx_out
	  mov [edi], ecx
	  mov edi, edx_out
	  mov [edi], edx
	  pop edi
	}
#elif defined(COMP_GCC) 
  __asm__ __volatile__
    (
     "cpuid               \n\t"
     :	"=a"(*eax_out), "=b"(*ebx_out), "=c"(*ecx_out), "=d"(*edx_out)
     :	"a"(eax_in)
     );
#endif
  
}

int cpuinfo_has_mmx() {
  return (cpuid_simple(1) & 0x00800000);
}

// fix this! wrong results in intel pIII
// removed from public access
/*int cpuinfo_has_mmxp(){
    return (cpuid_simple(0x80000001) & 0x1000000);
	}*/


int cpuinfo_has_3dnow() {
  return (cpuid_simple(0x80000001) & 0x80000000);
}

int cpuinfo_has_e3dnow() {
  return (cpuid_simple(0x80000001) & 0x40000000);
}


int cpuinfo_has_sse() {
  return (cpuid_simple(1) & 0x02000000);
}


int cpuinfo_has_sse2() {
  return (cpuid_simple(1) & 0x04000000);
}


void cpuinfo_get_vendor(char vendor[13])
{
  uint_32 dummy;
  uint_32* shadow = (uint_32*) vendor;

  vendor[12] = 0;

  cpuid_extended(0,&dummy,shadow+0,shadow+2, shadow+1);
}

void cpuinfo_get_cpu_name(char name[49])
{
  uint_32* shadow = (uint_32*) name;

  name[48] = 0;

  cpuid_extended(0x80000002,shadow+0,shadow+1,shadow+2,shadow+3);
  cpuid_extended(0x80000003,shadow+4,shadow+5,shadow+6,shadow+7);
  cpuid_extended(0x80000004,shadow+8,shadow+9,shadow+10,shadow+11);
}
