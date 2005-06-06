typedef union
{
  struct slist_s_t* list;
  struct expression_s_t* expr;
  char*        text;
  double       num;
} YYSTYPE;
#define	NUMBER	257
#define	HOCH	258
#define	TIMES	259
#define	MODULO	260
#define	DIV	261
#define	PLUS	262
#define	MINUS	263
#define	EOL	264
#define	SEMICOLON	265
#define	KLAUF	266
#define	KLZU	267
#define	ID	268
#define	KOMMA	269
#define	PIPE	270
#define	NEGATION	271

