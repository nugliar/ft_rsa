#include <ft_ssl.h>
#include <ssl_asn.h>

t_iasn	*asn_construct_sequence(char *key, char *content)
{
	t_iasn	*item;

	item = asn_item_init();
	item->type = ft_strdup(key);
	return (item);
}
