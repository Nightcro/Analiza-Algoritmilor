#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Program realizat de Mindru Alexandru-Ionut
// Grupa 321CB

#define initial_size 2 // folosit pentru alocarea initiala a unor pointeri
#define true 1
#define false 0

typedef struct
{
	char *next_state;
	char tape1_read_symbol, tape2_read_symbol;
	char tape1_write_symbol, tape2_write_symbol;
	char tape1_direction, tape2_direction;
} Transition;

typedef struct
{
	char *current_state; // starea curenta
	unsigned int nr_trans, alloc_trans; // numar tranzitii / numarul
										// maxim alocat care poate fi dublat
	Transition *trans; // vectorul cu tranzitii de la starea curenta
} State;

typedef struct
{
	unsigned int nr_state; // numarul de stari
	unsigned int nr_final_state; // numarul de stari finale
	unsigned int nr_all_trans; // numarul de tranzitii total
	char *initial_state, **final_state; // starea initiala si vectorul cu stari
	 									// finale
	State *vector_state; // vectorul cu stari
	char *band1, *band2; // cele 2 benzi
} TuringMachine;

char get_word(FILE *in, char **cuv);
TuringMachine* initialise_turing_machine();
TuringMachine* read(FILE *in);
char read_trans(FILE *in, TuringMachine **machine);
void work_machine(FILE* out, TuringMachine **machine);
char resize_band(char **band);
void alocation_error(TuringMachine **machine);
void free_machine(TuringMachine **machine);
void print_turing(FILE *out, TuringMachine *machine);