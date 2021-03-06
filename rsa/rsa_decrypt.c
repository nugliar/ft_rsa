#include <ft_ssl.h>
#include <ssl_asn.h>
#include <ssl_rsa.h>
#include <ssl_rand.h>
#include <bnum.h>

static t_rsa	*__items;

// EME PKCS1 v1.5 decoding
// Split PS ostring, message cstring and three intermediate octets
static int	__eme_pkcs1_v1_5_split(uint8_t **octets, int *osize)
{
	uint8_t	*optr;
	uint8_t	*mes;
	size_t	messize;
	int		check;
	int		ix;

	optr = *octets;
	ix = 0;

	if ((optr[ix++] != 0x00) || (optr[ix++] != 0x02))
	{
		return (SSL_ERROR("bad padding"));
	}
	check = 0;

	while (ix < *osize)
	{
		if (optr[ix++] == 0x00)
		{
			check = 1;
			break ;
		}
	}
	if (check != 1)
	{
		return (SSL_ERROR("bad padding"));
	}
	messize = *osize - ix;

	if (messize == 0)
	{
		*octets = (uint8_t *)ft_strdup("");
		*osize = 0;
	}
	else
	{
		SSL_ALLOC(mes, messize);
		ft_memcpy(mes, optr + ix, messize);
		*octets = mes;
		*osize = messize;
	}
	SSL_FREE(optr);

	return (SSL_OK);
}

// RSA decryption primitive (... refer to RFC 3447)
//
// If the first form (n, d) of K is used, let m = c^d mod n.
//
// If the second form (p, q, dP, dQ, qInv) of K is used,
// proceed as follows:
//
// 1.	Let m_1 = c^dP mod p and m_2 = c^dQ mod q.
//
// 2.	Let h = (m_1 - m_2) * qInv mod p.
//
// 3.	Let m = m_2 + q * h.
//
static int	__decrypt_prim(t_num *ciph_rep, t_num *mes_rep)
{
	t_num	m1;
	t_num	m2;
	t_num	h;

	if (compare_num_u(ciph_rep, __items->modulus) >= 0)
	{
		return (SSL_ERROR("ciphertext represantative out of range"));
	}
	// first form
	m_powmod_num(ciph_rep, __items->privexp, __items->modulus, mes_rep);

	// // second form
	// init_num(&m1);
	// init_num(&m2);
	// init_num(&h);
	//
	// m_powmod_num(ciph_rep, __items->exponent1, __items->prime1, &m1);
	// m_powmod_num(ciph_rep, __items->exponent2, __items->prime2, &m2);
	// sub_num(&m1, &m2, &h);
	// mul_num(&h, __items->coeff, &h);
	// divmod_num(&h, __items->prime1, NULL, &h);
	// mul_num(__items->prime2, &h, mes_rep);
	// add_num(mes_rep, &m2, mes_rep);

	return (SSL_OK);
}

// RSA decryption scheme
static int	__decrypt(
	const char *ciph, size_t ciphsize, char **mes, size_t *messize)
{
	uint8_t	*octets;
	int		osize;
	int		modsize;
	t_num	mes_rep;
	t_num	ciph_rep;

	modsize = CEIL(__items->keysize, 8) / 8;

	if ((ciphsize > modsize) || (ciphsize < 11))
	{
		return (SSL_ERROR("invalid rsa cipher"));
	}
	if (SSL_OK != rsa_os2i(&ciph_rep, (uint8_t *)ciph, ciphsize))
	{
		return (SSL_ERR);
	}
	if (SSL_OK != __decrypt_prim(&ciph_rep, &mes_rep))
	{
		return (SSL_ERR);
	}
	if (SSL_OK != rsa_i2os(&mes_rep, &octets, modsize))
	{
		return (SSL_ERR);
	}
	osize = modsize;

	if (SSL_OK != __eme_pkcs1_v1_5_split(&octets, &osize))
	{
		SSL_FREE(octets);
		return (SSL_ERR);
	}
	*mes = (char *)octets;
	*messize = osize;

	return (SSL_OK);
}

int rsa_decrypt(t_ostring *ciph, t_ostring *mes, t_node *asn_key)
{
	int	keysize;

	if ((NULL == ciph) || (NULL == ciph->content)
		|| (NULL == mes) || (NULL == asn_key))
	{
		return (SSL_ERROR("invalid input"));
	}
	mes->content = NULL;

	if (ft_strcmp(asn_key->key, "RSA_PRIVATE_KEY"))
	{
		return (SSL_ERROR("expected rsa private key"));
	}
	if (SSL_OK != rsa_key_items(asn_key, &__items))
	{
		return (SSL_ERROR("bad rsa key"));
	}
	if (SSL_OK != __decrypt(
		ciph->content, ciph->size, &(mes->content), &(mes->size)))
	{
		return (SSL_ERROR("rsa decrypt error"));
	}
	return (SSL_OK);
}
