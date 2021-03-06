#include <bnum.h>

void	decrem_num_u(t_num *num)
{
	uint64_t	borrow;

	if (BNUM_ZERO(num))
	{
		for (int i = 0; i < BNUM_MAX_DIG; i++)
    {
      num->val[i] = BNUM_MAX_VAL;
    }
		return ;
	}
	borrow = 1;
	for (int i = 0; borrow && i < num->len; i++)
	{
		num->val[i] -= borrow;
		borrow = num->val[i] >> (BNUM_DIGIT_BIT-1);
		num->val[i] &= BNUM_MAX_VAL;
	}
}
