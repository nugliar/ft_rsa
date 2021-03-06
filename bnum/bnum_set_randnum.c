#include <bnum.h>

void    set_randnum(t_num *num, int bits)
{
  int			fd, i, len;
	uint64_t	min;

	len = (bits-1) / BNUM_DIGIT_BIT + 1;

  if ((len < 0) || (len > BNUM_MAX_DIG))
    BNUM_ERROR("invalid big number size");
	if (len == 0)
	{
		set_num(num, 0);
		return ;
	}

  fd = open("/dev/random", O_RDONLY);
  if (fd < 0)
  	BNUM_ERROR("/dev/random");

  do {
		read(fd, num->val, len * sizeof(uint64_t));
	} while (!(num->val[len-1] & BNUM_MSB_VAL));

	for (i = 0; i < len; i++)
		num->val[i] = num->val[i] & BNUM_MAX_VAL;
  for (; i < BNUM_MAX_DIG; i++)
    num->val[i] = 0;

	if ((min = bits % BNUM_DIGIT_BIT) != 0)
	{
		min = (1ull << (min-1));
		while (!(num->val[len-1] & min))
			read(fd, num->val+len-1, sizeof(uint64_t));
		num->val[len-1] &= (min << 1) - 1ull;
	}
	close(fd);
  num->len = len;
	num->sign = BNUM_POS;
}
