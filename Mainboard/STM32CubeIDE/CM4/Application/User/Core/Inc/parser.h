#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include <string.h>
#include <stdint.h>

#define MAX_TOKEN_AMOUT 256 //uint16_t
#define MAX_TOKEN_LENGHT 128

#define is_header(x) (strcmp(getHeader(p->payload, &tokens.tokens[i]), x) == 0)
#define is_data_str(x) (strcmp(getData(p->payload, &tokens.tokens[i]), x) == 0)

#define get_data_str(x) sscanf(getData(p->payload, &tokens.tokens[i]), "%s", x)
#define get_data_int(x) sscanf(getData(p->payload, &tokens.tokens[i]), "%d", &x)
#define get_data_long(x) sscanf(getData(p->payload, &tokens.tokens[i]), "%ld", &x)
#define get_data_short(x) sscanf(getData(p->payload, &tokens.tokens[i]), "%hd", &x)

typedef enum parse_err_e {
	not_found, // no json string found
	format, // format of the string isn't as expected

	done, // all well, parsing successfull

} parse_err_t ;

typedef struct token_s {
	uint16_t head_start, head_end;
	uint16_t data_start, data_end;
} token_t;

typedef struct tokens_s {
	token_t tokens[MAX_TOKEN_AMOUT];
	uint16_t nb;
} tokens_t;

parse_err_t parse(tokens_t* tokens, uint8_t* data, uint16_t len);

char* getHeader(uint8_t buffer[], token_t* token);
char* getData(uint8_t buffer[], token_t* token);

#endif /* INC_PARSER_H_ */
