#include "turing_req.h"

// Program realizat de Mindru Alexandru-Ionut
// Grupa 321CB

int main(void)
{
	FILE *in = fopen("task1.in", "rt");

	if (in == NULL)
	{
		fprintf(stderr, "Eroare deschidere fisier de input!\n");
		return 1;
	}

	FILE *out = fopen("task1.out", "wt");
	TuringMachine* machine = read(in);

	if (machine == NULL)
	{
		fclose(in);
		fclose(out);
		return 0;
	}

	//print_turing(out, machine);
	work_machine(out, &machine);

	free_machine(&machine);
	fclose(in);
	fclose(out);
	return 0;
}