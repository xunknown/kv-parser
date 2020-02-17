/**
 * @author      : alpha (alpha@mascot)
 * @created     : Monday Feb 17, 2020 23:32:17 HKT
 */

#include <string.h>
#include "kv-parser.h"

#define VALID(str)	((str) != NULL && (str)[0] != '\0')

char *kv_trim_token(char *token, const char *delimiter)
{
	if (token != NULL && delimiter != NULL) {
		char *next_token = NULL;
		return strtok_r(token, delimiter, &next_token);
	}

	return token;
}

static void kv_reset(struct kv_pair *kv)
{
	if (kv != NULL) {
		kv->key = NULL;
		kv->value = NULL;
	}
}

static int kv_process(char *key, char *value,
		      const struct kv_delimiter *delimiter,
		      struct kv_pair *kv)
{
	if (kv == NULL) {
		return -1;
	}

	if (delimiter != NULL) {
		kv->key = kv_trim_token(key, delimiter->trim_key);
		kv->value = kv_trim_token(value, delimiter->trim_value);
	} else {
		kv->key = key;
		kv->value = value;
	}

	return VALID(kv->key) ? 1 : 0;
}

int kv_parse_pair(char *buffer, const struct kv_delimiter *delimiter,
		  struct kv_pair *kv)
{
	char *first_token = NULL;
	char *next_token = NULL;
	char *key = NULL;
	char *value = NULL;

	if (buffer == NULL) {
		kv_reset(kv);
		return -1;
	}

	if (delimiter == NULL || delimiter->split_pair == NULL) {
		return kv_process(buffer, NULL, delimiter, kv);
	}

	first_token = strtok_r(buffer, delimiter->split_pair, &next_token);
	if (first_token == buffer) {
		key = first_token;
		value = strtok_r(NULL, delimiter->split_pair, &next_token);
	} else {
		key = NULL;
		value = first_token;
	}

	return kv_process(key, value, delimiter, kv);
}

int kv_parse_list(char *buffer, const struct kv_delimiter *delimiter,
		  char **next, struct kv_pair *kv)
{
	if (delimiter == NULL || delimiter->split_list == NULL) {
		return kv_parse_pair(buffer, delimiter, kv);
	}

	if (next != NULL) {
		char *pair = strtok_r(buffer, delimiter->split_list, next);
		return kv_parse_pair(pair, delimiter, kv);
	}

	return kv_parse_pair(buffer, delimiter, kv);
}
