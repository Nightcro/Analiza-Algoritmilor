#include "turing_req.h"

// Program realizat de Mindru Alexandru-Ionut
// Grupa 321CB

char get_word(FILE *in, char **cuv)
{	// functie creata pentru a citi cuvant cu cuvant
	unsigned int size = initial_size, pass;
	(*cuv) = (char*)malloc(size * sizeof(char));

	if (*cuv == NULL)
	{
		return -1;
	}

	char aux;

	for (pass = 0; ((aux = getc(in)) != '\n') && (aux != EOF) && (aux != ' '); )
	{
		(*cuv)[pass++] = aux;

		if (size == (pass + 1))
		{	// daca a fost atinsa dimensiunea alocata, realocam
			size *= 2;
			(*cuv) = (char*)realloc(*cuv, size * sizeof(char));

			if (*cuv == NULL)
			{
				return -1;
			}
		}
	}

	(*cuv)[pass] = '\0';
	return 0;
}

TuringMachine* initialise_turing_machine()
{	// functie de initializare a unei structuri de tipul TuringMachine
	TuringMachine* machine = (TuringMachine*)malloc(sizeof(TuringMachine));

	if (machine == NULL)
	{
		return NULL;
	}

	machine->initial_state = NULL;
	machine->final_state = NULL;
	machine->vector_state = NULL;
	machine->band1 = NULL;
	machine->band2 = NULL;
	machine->nr_state = 0;
	machine->nr_final_state = 0;
	machine->nr_all_trans = 0;
	return machine;
}

TuringMachine* read(FILE *in)
{	// functie de citire a input-ului
	TuringMachine* machine = initialise_turing_machine();

	if (machine == NULL)
	{
		alocation_error(&machine);
		return NULL;
	}

	unsigned int n, i;
	char error;
	fscanf(in, "%u\n", &n);
	machine->nr_state = n;
	machine->vector_state = (State*)malloc(n * sizeof(State));
	// ^^ starea din care se porneste
	if (machine->vector_state == NULL)
	{
		alocation_error(&machine);
		return NULL;
	}

	for (i = 0; i < n; i++)
	{	// se citesc starile
		error = get_word(in, &machine->vector_state[i].current_state);
		machine->vector_state[i].trans = NULL;
		machine->vector_state[i].nr_trans = 0;
		machine->vector_state[i].alloc_trans = initial_size;

		if (error == -1)
		{
			alocation_error(&machine);
			return NULL;
		}
	}

	fscanf(in, "%u\n", &n);
	machine->nr_final_state = n;
	machine->final_state = (char**)malloc(n * sizeof(char*));

	if (machine->final_state == NULL)
	{
		alocation_error(&machine);
		return NULL;
	}

	for (i = 0; i < n; i++)
	{	// se citesc starile finale
		error = get_word(in, &machine->final_state[i]);

		if (error == -1)
		{
			alocation_error(&machine);
			return NULL;
		}
	}

	error = get_word(in, &machine->initial_state);

	if (error == -1)
	{
		alocation_error(&machine);
		return NULL;
	}

	error = read_trans(in, &machine);
	// ^^ functie de citit tranzitiile
	if (error == -1)
	{
		alocation_error(&machine);
		return NULL;
	}

	error = get_word(in, &machine->band1);

	if (error == -1)
	{
		alocation_error(&machine);
		return NULL;
	}

	error = get_word(in, &machine->band2);

	if (error == -1)
	{
		alocation_error(&machine);
		return NULL;
	}

	return machine;
}

char read_trans(FILE *in, TuringMachine **machine)
{	// functie de citire a tranzitiilor
	unsigned int n, i, j, k;
	char error, *cuv;
	fscanf(in, "%u\n", &n);
	(*machine)->nr_all_trans = n;

	for (i = 0; i < n; i++)
	{
		error = get_word(in, &cuv);

		if (error == -1)
		{
			alocation_error(machine);
			return -1;
		}

		Transition **aux;
		unsigned int *aux_nr_trans, *aux_alloc_trans;

		for (j = 0; j < (*machine)->nr_state; j++)
		{	// caut starea pentru tranzitia respectiva
			if (strcmp((*machine)->vector_state[j].current_state, cuv) == 0)
			{
				break;
			}
		}

		aux = &(*machine)->vector_state[j].trans;
		aux_nr_trans = &(*machine)->vector_state[j].nr_trans;
		aux_alloc_trans = &(*machine)->vector_state[j].alloc_trans;

		if ((*aux == NULL) || (*aux_nr_trans == *aux_alloc_trans))
		{	// se realoca vectorul de tranzitii de pe starea respectiva
			// daca s-a atins limita
			*aux_alloc_trans = *aux_alloc_trans * 2;
			*aux = (Transition*)realloc(*aux, *aux_alloc_trans
			                            * sizeof(Transition));

			if (error == -1)
			{
				alocation_error(machine);
				return -1;
			}
		}

		fscanf(in, "%c %c ",
		       &(*aux)[*aux_nr_trans].tape1_read_symbol,
		       &(*aux)[*aux_nr_trans].tape2_read_symbol);
		free(cuv);
		error = get_word(in, &cuv);

		if (error == -1)
		{
			alocation_error(machine);
			return -1;
		}

		for (k = 0; k < (*machine)->nr_state; k++)
		{	// caut pointerul catre starea urmatoare
			char *temp = (*machine)->vector_state[k].current_state;

			if (!strcmp(temp, cuv))
			{	// il asignez tranzitiei pentru starea de la care plec
				(*aux)[*aux_nr_trans].next_state = temp;
				break;
			}
		}

		fscanf(in, "%c %c %c %c\n",
		       &(*aux)[*aux_nr_trans].tape1_write_symbol,
		       &(*aux)[*aux_nr_trans].tape1_direction,
		       &(*aux)[*aux_nr_trans].tape2_write_symbol,
		       &(*aux)[*aux_nr_trans].tape2_direction);
		(*aux_nr_trans)++;
		free(cuv);
	}

	return 0;
}

void work_machine(FILE* out, TuringMachine **machine)
{	// functia ce ruleaza masina
	char *state = (*machine)->initial_state;
	char error;
	unsigned int cursor1 = 1, cursor2 = 1;
	unsigned int i, j, sem;
	Transition *aux;
	unsigned int *aux_nr_trans;

	while (true)
	{
		sem = 0;

		for (i = 0; i < (*machine)->nr_final_state; i++)
		{
			if (strcmp((*machine)->final_state[i], state) == 0)
			{	// se ajunge in starea finala atunci se afiseaza benzile
				fprintf(out, "%s\n", (*machine)->band1);
				fprintf(out, "%s\n", (*machine)->band2);
				return;
			}
		}

		for (i = 0; i < (*machine)->nr_state; i++)
		{	// caut in vectorul cu stari starea curenta
			if (strcmp((*machine)->vector_state[i].current_state, state) == 0)
			{
				break;
			}
		}

		aux = (*machine)->vector_state[i].trans;
		aux_nr_trans = &(*machine)->vector_state[i].nr_trans;
		char car1_trans, car2_trans;
		char car1 = (*machine)->band1[cursor1];
		char car2 = (*machine)->band2[cursor2];

		for (j = 0; j < *aux_nr_trans; j++)
		{	// caut in vectorul de tranzitii de la starea curenta tranzitie
			// urmatoare corespunazatoare
			car1_trans = aux[j].tape1_read_symbol;
			car2_trans = aux[j].tape2_read_symbol;

			if ((car1 == car1_trans) && (car2 == car2_trans))
			{
				sem = true; // folosit pentru a determina daca s-a gasit
				break; // vreo tranzitie
			}
		}

		if (sem == false)
		{	// daca nu s-a gasit nici o tranzitie atunci masina s-a blocat
			fprintf(out, "The machine has blocked!\n");
			return;
		}

		(*machine)->band1[cursor1] = aux[j].tape1_write_symbol;
		(*machine)->band2[cursor2] = aux[j].tape2_write_symbol;
		// se efectueaza miscarile pe cele 2 benzi, in caz de se iese
		// inafara benzii se realoca banda respectiva
		if (aux[j].tape1_direction == 'R')
		{
			if ((cursor1 + 1) >= strlen((*machine)->band1))
			{
				error = resize_band(&(*machine)->band1);

				if (error == -1)
				{
					alocation_error(machine);
					return;
				}
			}

			cursor1++;
		}

		if (aux[j].tape1_direction == 'L')
		{
			cursor1--;
		}

		if (aux[j].tape2_direction == 'R')
		{
			if ((cursor2 + 1) >= strlen((*machine)->band2))
			{
				error = resize_band(&(*machine)->band2);

				if (error == -1)
				{
					alocation_error(machine);
					return;
				}
			}

			cursor2++;
		}

		if (aux[j].tape2_direction == 'L')
		{
			cursor2--;
		}

		state = aux[j].next_state;
	}

	return;
}

char resize_band(char **band)
{	// functie de realocare a benzii
	unsigned int i, old_size = strlen(*band);
	unsigned int size = old_size * 2;
	*band = (char*)realloc(*band, size * sizeof(char));

	for (i = old_size; i < size; i++)
	{
		(*band)[i] = '#';
	}

	(*band)[size - 1] = '\0';
	return *band == NULL ? -1 : 0;
}

void alocation_error(TuringMachine **machine)
{
	free_machine(machine);
	fprintf(stderr, "Eroare alocare memorie.\n");
}

void free_machine(TuringMachine **machine)
{	// functie de eliberare a memoriei pentru o structure de tipul TuringMachine
	if (*machine == NULL)
	{
		return;
	}

	unsigned int i;

	if ((*machine)->initial_state != NULL)
	{
		free((*machine)->initial_state);
	}

	if ((*machine)->final_state != NULL)
	{
		for (i = 0; i < (*machine)->nr_final_state; i++)
		{
			free((*machine)->final_state[i]);
		}

		free((*machine)->final_state);
	}

	if (((*machine)->vector_state) != NULL)
	{
		for (i = 0; i < (*machine)->nr_state; i++)
		{
			free((*machine)->vector_state[i].current_state);
			free((*machine)->vector_state[i].trans);
		}

		free((*machine)->vector_state);
	}

	if (((*machine)->band1) != NULL)
	{
		free((*machine)->band1);
	}

	if (((*machine)->band2) != NULL)
	{
		free((*machine)->band2);
	}

	free(*machine);
	*machine = NULL;
	return;
}

void print_turing(FILE *out, TuringMachine *machine)
{
	unsigned int i, j;
	fprintf(out, "%d\n", machine->nr_state);

	for (i = 0; i < machine->nr_state; i++)
	{
		fprintf(out, "%s ", machine->vector_state[i].current_state);
	}

	fprintf(out, "\n%d\n", machine->nr_final_state);

	for (i = 0; i < machine->nr_final_state; i++)
	{
		fprintf(out, "%s ", machine->final_state[i]);
	}

	fprintf(out, "\n%s\n", machine->initial_state);
	fprintf(out, "%d\n", machine->nr_all_trans);

	for (i = 0; i < machine->nr_state; i++)
	{
		for (j = 0; j < machine->vector_state[i].nr_trans; j++)
		{
			fprintf(out, "%s ", machine->vector_state[i].current_state);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape1_read_symbol);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape2_read_symbol);
			fprintf(out, "%s ", machine->vector_state[i].trans[j].next_state);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape1_write_symbol);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape1_direction);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape2_write_symbol);
			fprintf(out, "%c ", machine->vector_state[i].trans[j].tape2_direction);
			fprintf(out, "\n");
		}
	}

	fprintf(out, "%s\n", machine->band1);
	fprintf(out, "%s\n", machine->band2);

	return;
}