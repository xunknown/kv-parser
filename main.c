/**
 * @author      : alpha (alpha@mascot)
 * @created     : Monday Feb 17, 2020 23:32:03 HKT
 */

#include <stdio.h>
#include "kv-parser.h"

int main(int argc, char *argv[])
{
	char buffer[] = "a=1, b =2, c= 3, d=4 , e = 5 ,f=, g, =7,=,,,x y = 8 9";
	struct kv_delimiter delimiter = {
		.split_list = ",",
		.split_pair = "=",
		.trim_key = " ",
		.trim_value = " ",
	};
	struct kv_pair kv;
	char *next;
	int ret;

	printf("parse:'%s'\n", buffer);
	ret = kv_parse_list(buffer, &delimiter, &next, &kv);
	while (ret >= 0) {
		if ( ret == 1) {
			printf("%d:key='%s', value='%s'\n", ret, kv.key, kv.value);
		}
		ret = kv_parse_list(NULL, &delimiter, &next, &kv);
	}

	delimiter.split_list = ",;\n";
	for (int i = 1; i < argc; i++) {
		printf("parse:'%s'\n", argv[i]);
		ret = kv_parse_list(argv[i], &delimiter, &next, &kv);
		while (ret >= 0) {
			printf("%d:key='%s', value='%s'\n", ret, kv.key, kv.value);
			ret = kv_parse_list(NULL, &delimiter, &next, &kv);
		}
	}

	return 0;
}
