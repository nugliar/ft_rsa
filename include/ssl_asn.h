#ifndef ASN_SPECIFIC_H
# define ASN_SPECIFIC_H

// ASN.1 - Abstract Syntax Notation One
// Refer to X.208, X.209, X.608

// IDENTIFIER OCTET

// Bits 8 and 7 represent tag class
# define ASN_TAG_UNIVERSAL    0x0
# define ASN_TAG_APPLICATION  0x40
# define ASN_TAG_CONTEXT      0x80
# define ASN_TAG_PRIVATE      0xC0

// Bit 6 represent encoding complexity
# define ASN_ENCODE_PRIMITIVE 0x0
# define ASN_ENCODE_CONSTRUCT 0x20

// Bits 5 to 1 represent tag number
// If tag number <= 30, tag is simple
# define ASN_TAG_SIMPLE       0x0

// If tag number > 30, tag is complex
// bits 5 to 1 are set to '1'
# define ASN_TAG_COMPLEX      0x1F

# define ASN_TAG_BOOLEAN      0x1
# define ASN_TAG_INT          0x2
# define ASN_TAG_BIT_STRING   0x3
# define ASN_TAG_OCTET_STRING 0x4
# define ASN_TAG_NULL         0x5
# define ASN_TAG_OBJECT_ID    0x6
# define ASN_TAG_OBJECT_DESCR 0x7
# define ASN_TAG_SEQUENCE     0x10

// If tag is complex, 2 or more octets are used.
// Each subsequent octet's 8th bit is set to '1',
// except the last one.
// Bits 7 to 1 of each subsequent octet is used to
// store tag number represented as unsigned integer,
// with bit 7 of first subsequent octet representing
// most significant bit of integer
# define ASN_TAG_SUBSEQ       0x80
# define ASN_TAG_SUBSEQ_LAST  0x0

// LENGTH OCTET

// If number of content octets is <= 127,
// short form of length octet is used.
// Short form consist of only one octet, where
// bit 8 is set to '0', and bits 7 to 1
// represent number of content octets
# define ASN_LEN_SHORT        0x0

// If number of content octets is > 127,
// long form shall be used.
// Long form consist of 2 or more octets, and
// bit 8 of first length octet is set to '1'.
// Bits 7 to 1 of first length octet are used to
// store number of following length octets.
// Bits 8 to 1 of each following length octet are
// used to store unsigned integer, representing
// number of content octets, with bit 8 of first consequent
// length octet as most significant bit of integer
# define ASN_LEN_LONG         0x80

typedef struct  s_iasn
{
  void          *content;
  char          *type;
  size_t        size;
}               t_iasn;

struct s_der;
struct s_node;

struct s_node	*asn_tree(char *);
void			asn_tree_del(struct s_node *);
void			*asn_tree_fetch(t_node *, const char *);
t_htbl			*asn_tree_items(struct s_node *);
void			asn_tree_items_del(t_htbl *);
int				asn_tree_der_encode(struct s_node *, struct s_der **);
int				asn_tree_der_decode(
					struct s_der *, const char *, struct s_node **);
t_iasn			*asn_item_init(void);
void			asn_item_del(t_iasn *);
void			*asn_item_content(t_iasn *);
size_t			asn_item_size(t_iasn *);
char			*asn_item_type(t_iasn *);
t_iasn			*asn_primitive_bool(char *, char *);
t_iasn			*asn_primitive_int(char *, char *);
t_iasn			*asn_primitive_ostring(char *, char *);
t_iasn			*asn_primitive_bitstring(char *, char *);
t_iasn			*asn_primitive_oid(char *, char *);
t_iasn			*asn_primitive_null(char *, char *);
t_iasn			*asn_construct_sequence(char *, char *);
void			asn_print(struct s_node *);
int				asn_transform(struct s_node *, struct s_node *);
char			*asn_oid_tree_get_name(const char *);
char			*asn_oid_tree_get_oid(const char *);

#endif
