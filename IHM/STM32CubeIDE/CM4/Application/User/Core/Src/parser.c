#include "parser.h"
#include <string.h>
#include <stdint.h>

uint8_t control_chars[] = {'\0','"',',',':','{','}'};

char header_buffer[MAX_TOKEN_LENGHT], data_buffer[MAX_TOKEN_LENGHT]; // having only one buffer seems to cause issues when both getHeader and getData are called inside the same function (printf for example)

static uint8_t _getToNextCtrlChr(uint16_t* cursor, uint8_t data[], uint16_t max_index){
	while(*cursor < max_index){
		for (uint16_t i = 0; i < sizeof(control_chars)/sizeof(control_chars[0]); i ++){
			if(data[*cursor] == control_chars[i]) return control_chars[i];
		}
		(*cursor)++;
	}

	return '\0';
}

#define current_token tokens->tokens[tokens->nb]

parse_err_t parse(tokens_t* tokens, uint8_t data[], uint16_t len){
	uint16_t cursor = 0; // cursor
	tokens->nb = 0;
	uint8_t apostrophe_cnt = 0;

	if(_getToNextCtrlChr(&cursor, data, len) != '{') return not_found;

	while(cursor < len){
		cursor++; // ignore the previous control character (not to find it again 0 chars away)
		switch(_getToNextCtrlChr(&cursor, data, len)){
		case '"' :
			switch (apostrophe_cnt){
				case 0 : current_token.head_start = cursor + 1; break;
				case 1 : current_token.head_end = cursor - 1; break;
				case 2 : current_token.data_start = cursor + 1; break;
				case 3 : current_token.data_end = cursor - 1; break;
				default : return format;
			}
			apostrophe_cnt ++;

			break;
		case ',' :
			if(data[cursor -1] != '"') current_token.data_end = cursor -1;

			tokens->nb++;
			apostrophe_cnt = 0;
			break;
		case ':' :
			if(data[cursor +1] != '"') current_token.data_start = cursor +1;
			break;
		case '{' :
			return format;
		case '}' :
			tokens->nb++; // the last token is not followed by a ',' as the '}' replaces it
			return done;
		default : return format;
		}
	}

	return format; // got to the end of the buffer without finding a '}' to indicate the end of the json string
}

char* getHeader(uint8_t buffer[], token_t* token){
	memcpy(header_buffer, &buffer[token->head_start], token->head_end - token->head_start +1);
	header_buffer[token->head_end - token->head_start +1] = '\0';
	return header_buffer;
}
char* getData(uint8_t buffer[], token_t* token){
	memcpy(data_buffer, &buffer[token->data_start], token->data_end - token->data_start +1);
	data_buffer[token->data_end - token->data_start +1] = '\0';
	return data_buffer;
}
