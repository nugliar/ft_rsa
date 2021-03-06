#include <ft_ssl.h>
#include <ssl_asn.h>
#include <ssl_der.h>

static const struct {
  char	*type;
  int	(*f_enc)(struct s_der *, void *, size_t);
} T[] = {
	{	"sequence",		der_append_sequence		},
	{	"bool",			der_append_bool			},
	{	"int",			der_append_int			},
	{	"ostring",		der_append_ostring		},
	{	"bitstring",	der_append_bitstring	},
	{	"objectId",		der_append_oid			},
	{	"null",			der_append_null			}
};

static t_htbl	*__init_func_htable(void)
{
	t_htbl	*htbl;

	if (NULL == (htbl = ft_htbl_init(sizeof(T)/sizeof(*T))))
		return (NULL);

	for (int idx = 0; idx < sizeof(T)/sizeof(*T); idx++)
		ft_htbl_add(htbl, T[idx].type, T[idx].f_enc);

	return (htbl);
}

static int	__encode_recur(t_node *node, t_der *der, t_htbl *func_htable)
{
	int		(*f_enc)(t_der *, void *, int);
	t_der	*child_der;
	t_iasn	*item;
	int		ret;

	if (NULL == node)
		return (SSL_OK);

	ret = SSL_OK;
	item = node->content;

	if (NULL == item)
		return (SSL_ERROR("invalid asn item"));

	if (NULL == (f_enc = ft_htbl_get(func_htable, item->type)))
		return (SSL_ERROR("invalid asn type"));

	if (ft_node_is_parent(node))
	{
		child_der = der_init();

		if (SSL_OK != __encode_recur(node->nodes, child_der, func_htable))
			ret = SSL_ERR;
		else if (SSL_OK != f_enc(der, child_der->content, child_der->size))
			ret = SSL_ERR;

		der_del(child_der);

		if (SSL_OK != ret)
			return (SSL_ERR);
	}
	else
	{
		if (SSL_OK != f_enc(der, item->content, item->size))
			return (SSL_ERR);
	}
	return (__encode_recur(node->next, der, func_htable));
}

int	asn_tree_der_encode(t_node *tree, t_der **der)
{
	t_htbl	*func_htable;
	int		ret;

	SSL_CHECK(NULL != tree);
	SSL_CHECK(NULL != der);

	ret = SSL_OK;

	*der = der_init();
	func_htable = __init_func_htable();

	if (SSL_OK != (ret = __encode_recur(tree, *der, func_htable)))
	{
		der_del(*der);
		*der = NULL;
	}
	ft_htbl_del(func_htable);

	return (ret);
}
