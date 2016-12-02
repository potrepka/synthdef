#ifndef _synthdef_h
#define _synthdef_h

typedef struct sc_parameterName {
	char *name;
	int index;
} *sc_parameterName_t;

typedef struct sc_uGen_input {
	// index of unit generator or -1 for a constant
	int uGen;
	// uGen output index OR constant index
	int index;
} *sc_uGen_input_t;

typedef struct sc_uGen_output {
	// 0 = scalar, 1 = control, 2 = audio
	char rate;
} *sc_uGen_output_t;

typedef struct sc_uGen {
	char *name;
	// 0 = scalar, 1 = control, 2 = audio
	char rate;
	int numInputs;
	int numOutputs;
	// if unused, set to 0
	short specialIndex;
	sc_uGen_input_t *inputs;
	sc_uGen_output_t *outputs;
} *sc_uGen_t;

typedef struct sc_variant {
	char *name;
	float *values;
} *sc_variant_t;

typedef struct sc_synthDef {
	char *name;

	int numConstants;
	float *constants;

	int numParameters;
	float *parameters;

	int numParameterNames;
	sc_parameterName_t *parameterNames;

	int numUGens;
	sc_uGen_t *uGens;

	short numVariants;
	sc_variant_t *variants;
} *sc_synthDef_t;

typedef struct sc {
	int id;
	int version;
	short numSynthDefs;
	sc_synthDef_t *synthDefs;
} *sc_t;

int readSynthDef(FILE *fp, sc_t *scp);
int writeSynthDef(FILE *fp, sc_t sc);
void freeSynthDef(sc_t sc);

int readString(FILE *fp, char **sp);
int writeString(FILE *fp, char *s);

#endif
