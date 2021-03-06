#include <bnum.h>

void	add_num_u(const t_num *a, const t_num *b, t_num *res)
{
	int 	slen, i;

	slen = BNUM_MAX(a->len, b->len)+1;

	if (slen > BNUM_MAX_DIG)
		BNUM_ERROR("big number size limit exceeded");

	{
		const uint64_t	*aptr, *bptr;
		uint64_t		carry, *rptr;

		aptr = a->val;
		bptr = b->val;
		rptr = res->val;
		carry = 0;
		for (i = 0; i < slen-1; i++)
		{
			*rptr = *aptr++ + *bptr++ + carry;
			carry = *rptr >> BNUM_DIGIT_BIT;
			*rptr++ &= BNUM_MAX_VAL;
		}
		*rptr = carry;
	}
	
	for (i = slen; i < BNUM_MAX_DIG; i++)
  {
    res->val[i] = 0;
  }
	res->len = slen;
	skip_zeros(res);
}
