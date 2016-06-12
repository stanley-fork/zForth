#ifndef zforth_h
#define zforth_h

#include <stdint.h>

/* ==================== Configurable options =================== */


/* Set to 1 to add tracing support for debugging and inspection. Requires the
 * zf_host_trace() function to be implemented. Adds about one kB to .text and
 * .rodata, dramatically reduces speed, but is very useful. Make sure to enable
 * tracing at run time when calling zf_init() or by setting the 'trace' user
 * variable to 1 */

#define ZF_ENABLE_TRACE 1


/* Set to 1 to add boundary checks to stack operations. Increases .text size
 * by approx 100 bytes */

#define ZF_ENABLE_BOUNDARY_CHECKS 1


/* Set to 1 to enable bootstrapping of the forth dictionary by adding the
 * primitives and user veriables. On small embedded systems you may choose to
 * leave this out and start by loading a cross-compiled dictionary instead.
 * Enabling adds a few hundred bytes to the .text and .rodata segments */
 
#define ZF_ENABLE_BOOTSTRAP 1


/* Type to use for the basic cell, data stack and return stack. Choose a signed
 * integer type that suits your needs, or 'float' or 'double' if you need
 * floating point numbers */

typedef float zf_cell;
#define ZF_CELL_FMT "%.14g"


/* The type to use for pointers and adresses. 'unsigned int' is usually a good
 * choice for best performance and smallest code size */

typedef unsigned int zf_addr;
#define ZF_ADDR_FMT "%04x"


/* Number of cells in memory regions: dictionary size is given in bytes, stack
 * sizes are number of elements */

#define ZF_DICT_SIZE 2048
#define ZF_DSTACK_SIZE 32
#define ZF_RSTACK_SIZE 32


/* =================== End of configuration =================== */

/* Abort reasons */

typedef enum {
	ZF_OK,
	ZF_INPUT_WORD,
	ZF_INPUT_CHAR,
	ZF_ABORT_INTERNAL_ERROR,
	ZF_ABORT_OUTSIDE_MEM,
	ZF_ABORT_DSTACK_UNDERRUN,
	ZF_ABORT_DSTACK_OVERRUN,
	ZF_ABORT_RSTACK_UNDERRUN,
	ZF_ABORT_RSTACK_OVERRUN,
	ZF_ABORT_NOT_A_WORD,
	ZF_ABORT_COMPILE_ONLY_WORD,
} zf_result;

typedef enum {
	ZF_SYSCALL_EMIT,
	ZF_SYSCALL_PRINT,
	ZF_SYSCALL_TELL,
	ZF_SYSCALL_USER = 128
} zf_syscall_id;


/* ZForth API functions */


void zf_init(int trace);
void zf_bootstrap(void);
void *zf_dump(size_t *len);
zf_result zf_eval(const char *buf);

void zf_push(zf_cell v);
zf_cell zf_pop(void);
zf_cell zf_pick(zf_addr n);

/* Host provides these functions */

zf_result zf_host_sys(zf_syscall_id id, const char *last_word);
void zf_host_trace(const char *fmt, va_list va);


#endif
