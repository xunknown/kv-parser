/**
 * @author      : alpha (alpha@mascot)
 * @created     : Monday Feb 17, 2020 23:32:13 HKT
 */

#ifndef KV_PARSER_H
#define KV_PARSER_H

/* the key and value pointer to the parsed buffer */
struct kv_pair {
	char *key;
	char *value;
};

struct kv_delimiter {
	/*
	 * Split the key-value list with this delimiter
	 * to get each key-value pair.
	 * e.g.
	 * Set split_list="," to split
	 * "k1=v1, k2=v2, k3=v3" with "," into
	 * "k1=v1", " k2=v2,", " k3=v3" pairs.
	 */
	const char *split_list;
	/*
	 * Split the key-value pair with this delimiter
	 * to get the key and value token.
	 * e.g.
	 * Set split_pair="=" to split "k1=v1" with "=" into
	 * "k1" and "v1" tokens, the first token "k1" is key token
	 * and the other is value token.
	 */
	const char *split_pair;
	/*
	 * Trim the delimiter in the key and value token.
	 * e.g.
	 * Set trim_key=" " to trim the space
	 * in the token " k2". Note that only the first token saved.
	 */
	const char *trim_key;
	const char *trim_value;
};

/*
 * Trim the delimiter byte in the token through passed both arguments
 * to strtok_r function and return the first token or NULL.
 */
char *kv_trim_token(char *token, const char *delimiter);

/*
 * Split the key-value pair buffer into key and value token
 * through passed the buffer and delimiter->split_pair
 * to strtok_r function, and then trim the key token with
 * delimiter->trim_key and trim the value token with
 * delimiter->trim_value, the key and value saved in kv argument.
 * Return value:
 * 1 if key is nonemtpy, but value maybe nonempty, empty or NULL.
 * 0 if key is empty or NULL, but value maybe nonempty, empty or NULL.
 * -1 if buffer or kv is NULL, key and value set to NULL if kv not NULL.
 */
int kv_parse_pair(char *buffer, const struct kv_delimiter *delimiter,
		  struct kv_pair *kv);

/*
 * Split the key-value list buffer into key-value pair(s) through passed
 * delimiter->split_list and next argument to strtok_r function, and then
 * split the first key-value pair with kv_parse_pair. To parse remain key-value
 * pair in subsequent calls, buffer should be NULL, and next should be unchanged
 * since the previous call. The key and value saved in kv argument.
 * Return value:
 * 1 if key is nonemtpy, but value maybe nonempty, empty or NULL.
 * 0 if key is empty or NULL, but value maybe nonempty, empty or NULL.
 * -1 if buffer or kv is NULL, key and value set to NULL if kv not NULL, and
 * subsequent calls are infructuous.
 */
int kv_parse_list(char *buffer, const struct kv_delimiter *delimiter,
		  char **next, struct kv_pair *kv);

#endif /* end of include guard KV_PARSER_H */
