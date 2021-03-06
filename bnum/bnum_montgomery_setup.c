#include <bnum.h>

void	montgomery_setup(const t_num *num, uint64_t *rho)
{
	uint64_t	b, x;

	/* fast inversion mod 2^k, see LibTomMath */
	b = num->val[0];

	if (!(b & 1u))
		BNUM_ERROR("Montogemy reduction requires odd modulo");

	x = (((b + 2u) & 4u) << 1) + b; // x*a == 1 mod 2^4
	x *= 2u - b * x; // .. 2^8
	x *= 2u - b * x; // .. 2^16
	x *= 2u - b * x; // .. 2^32
	x *= 2u - b * x; // .. 2^64

	/* rho = -1/num mod b */
	*rho = ((t_uint128)BNUM_BASE - x) & BNUM_MAX_VAL;
}
