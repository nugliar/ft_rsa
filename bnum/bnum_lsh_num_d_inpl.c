#include <bnum.h>

void	lsh_num_d_inpl(t_num *num, int shifts)
{
	int		i;

	if (shifts <= 0)
  {
    return ;
  }
	num->len = BNUM_MIN(BNUM_MAX_DIG, num->len + shifts);
	for (i = num->len-1; i >= shifts; i--)
  {
    num->val[i] = num->val[i - shifts];
  }
	while (i >= 0)
  {
    num->val[i--] = 0;
  }
	skip_zeros(num);
}
