#include "./includes/leak_finder.h"

#define BUF_SIZE (100)

void *my_malloc(size_t size, const char *file, const char *function, int line)
{
	int i, num_of_addrs;
	void *buff[BUF_SIZE];
	char **symbol_str;
	FILE *logs_file;

	logs_file = fopen("./leaks_locater/allocation_log", "a");
	if(logs_file == NULL)
		exit(0);
	num_of_addrs = backtrace(buff, BUF_SIZE);
	symbol_str = backtrace_symbols(buff, num_of_addrs);

	fprintf(logs_file, "+-----------------------------------------------------------"
			"-------------------+---------------------- ALLOCATED:---"
			"---------------------------------------+");
	if (symbol_str == NULL)
		fprintf(logs_file, "backtrace_symbols returned NULL");
	for (i = (num_of_addrs - 1); i >= 0; i--)
		fprintf(logs_file, "%s", symbol_str[i]);
	fprintf(logs_file, "+");
	free(symbol_str);
	void *p = malloc(size);
	fprintf(logs_file, "------------------------------------------------------"
			"------------------------+- ADDRESS: '%p'+- FILE: '%s'+- FUNCTION: '%s'+"
			"- LINE: '%d'+---------------------------------------------------------"
			"----------------\n", p, file, function, line);
	fclose(logs_file);
	return (p);
}