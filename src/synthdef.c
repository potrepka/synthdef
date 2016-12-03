#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "byteio.h"
#include "synthdef.h"

int readSynthDef(FILE *fp, sc_t *scp) {
  sc_t sc = (sc_t)malloc(sizeof(struct sc));
  *scp = sc;

  int id;
  if (readInt(fp, &id) == 0 || id != 0x53436766) // SCgf
    return 0;
  sc->id = id;

  int version;
  if (readInt(fp, &version) == 0 || version != 2)
    return 0;
  sc->version = version;

  short numSynthDefs;
  if (readShort(fp, &numSynthDefs) == 0)
    return 0;
  sc->numSynthDefs = numSynthDefs;

  int a;
  int b;
  int c;

  if (numSynthDefs != 0) {
    sc_synthDef_t *synthDefs =
        (sc_synthDef_t *)malloc(numSynthDefs * sizeof(sc_synthDef_t));
    sc->synthDefs = synthDefs;

    for (a = 0; a < numSynthDefs; a++) {
      synthDefs[a] = (sc_synthDef_t)malloc(sizeof(struct sc_synthDef));

      char *name;
      if (readString(fp, &name) == 0)
        return 0;
      synthDefs[a]->name = name;

      int numConstants;
      if (readInt(fp, &numConstants) == 0)
        return 0;
      synthDefs[a]->numConstants = numConstants;

      if (numConstants != 0) {
        float *constants = (float *)malloc(numConstants * sizeof(float));
        synthDefs[a]->constants = constants;
        for (b = 0; b < numConstants; b++) {
          float f;
          if (readFloat(fp, &f) == 0)
            return 0;
          constants[b] = f;
        }
      }

      int numParameters;
      if (readInt(fp, &numParameters) == 0)
        return 0;
      synthDefs[a]->numParameters = numParameters;

      if (numParameters != 0) {
        float *parameters = (float *)malloc(numParameters * sizeof(float));
        synthDefs[a]->parameters = parameters;
        for (b = 0; b < numParameters; b++) {
          float f;
          if (readFloat(fp, &f) == 0)
            return 0;
          parameters[b] = f;
        }
      }

      int numParameterNames;
      if (readInt(fp, &numParameterNames) == 0)
        return 0;
      synthDefs[a]->numParameterNames = numParameterNames;

      if (numParameterNames != 0) {
        sc_parameterName_t *parameterNames = (sc_parameterName_t *)malloc(
            numParameterNames * sizeof(sc_parameterName_t));
        synthDefs[a]->parameterNames = parameterNames;
        for (b = 0; b < numParameterNames; b++) {
          parameterNames[b] =
              (sc_parameterName_t)malloc(sizeof(struct sc_parameterName));

          char *name2;
          if (readString(fp, &name2) == 0)
            return 0;
          parameterNames[b]->name = name2;

          int index;
          if (readInt(fp, &index) == 0)
            return 0;
          parameterNames[b]->index = index;
        }
      }

      int numUGens;
      if (readInt(fp, &numUGens) == 0)
        return 0;
      synthDefs[a]->numUGens = numUGens;

      if (numUGens != 0) {
        sc_uGen_t *uGens = (sc_uGen_t *)malloc(numUGens * sizeof(sc_uGen_t));
        synthDefs[a]->uGens = uGens;
        for (b = 0; b < numUGens; b++) {
          uGens[b] = (sc_uGen_t)malloc(sizeof(struct sc_uGen));

          char *name2;
          if (readString(fp, &name2) == 0)
            return 0;
          uGens[b]->name = name2;

          char rate;
          if (readChar(fp, &rate) == 0)
            return 0;
          uGens[b]->rate = rate;

          int numInputs;
          if (readInt(fp, &numInputs) == 0)
            return 0;
          uGens[b]->numInputs = numInputs;

          int numOutputs;
          if (readInt(fp, &numOutputs) == 0)
            return 0;
          uGens[b]->numOutputs = numOutputs;

          short specialIndex;
          if (readShort(fp, &specialIndex) == 0)
            return 0;
          uGens[b]->specialIndex = specialIndex;

          if (numInputs != 0) {
            sc_uGen_input_t *inputs =
                (sc_uGen_input_t *)malloc(numInputs * sizeof(sc_uGen_input_t));
            uGens[b]->inputs = inputs;
            for (c = 0; c < numInputs; c++) {
              inputs[c] = (sc_uGen_input_t)malloc(sizeof(struct sc_uGen_input));

              int uGen;
              if (readInt(fp, &uGen) == 0)
                return 0;
              inputs[c]->uGen = uGen;

              int index;
              if (readInt(fp, &index) == 0)
                return 0;
              inputs[c]->index = index;
            }
          }

          if (numOutputs != 0) {
            sc_uGen_output_t *outputs = (sc_uGen_output_t *)malloc(
                numOutputs * sizeof(sc_uGen_output_t));
            uGens[b]->outputs = outputs;
            for (c = 0; c < numOutputs; c++) {
              outputs[c] =
                  (sc_uGen_output_t)malloc(sizeof(struct sc_uGen_output));

              char rate2;
              if (readChar(fp, &rate2) == 0)
                return 0;
              outputs[c]->rate = rate2;
            }
          }
        }
      }

      short numVariants;
      if (readShort(fp, &numVariants) == 0)
        return 0;
      synthDefs[a]->numVariants = numVariants;

      if (numVariants != 0) {
        sc_variant_t *variants =
            (sc_variant_t *)malloc(numVariants * sizeof(sc_variant_t));
        synthDefs[a]->variants = variants;
        for (b = 0; b < numVariants; b++) {
          variants[c] = (sc_variant_t)malloc(sizeof(struct sc_variant));

          char *name2;
          if (readString(fp, &name2) == 0)
            return 0;
          variants[b]->name = name2;

          if (numParameters != 0) {
            float *values = (float *)malloc(numParameters * sizeof(float));
            variants[b]->values = values;
            for (c = 0; c < numParameters; c++) {
              float f;
              if (readFloat(fp, &f) == 0)
                return 0;
              values[c] = f;
            }
          }
        }
      }
    }
  }

  return 1;
}

int writeSynthDef(FILE *fp, sc_t sc) {
  if (writeInt(fp, sc->id) == 0)
    return 0;

  if (writeInt(fp, sc->version) == 0)
    return 0;

  if (writeShort(fp, sc->numSynthDefs) == 0)
    return 0;

  int a;
  int b;
  int c;

  if (sc->synthDefs != NULL) {
    for (a = 0; a < sc->numSynthDefs; a++) {
      if (sc->synthDefs[a] != NULL) {
        if (writeString(fp, sc->synthDefs[a]->name) == 0)
          return 0;

        if (writeInt(fp, sc->synthDefs[a]->numConstants) == 0)
          return 0;

        if (sc->synthDefs[a]->constants != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numConstants; b++) {
            if (writeFloat(fp, sc->synthDefs[a]->constants[b]) == 0)
              return 0;
          }
        }

        if (writeInt(fp, sc->synthDefs[a]->numParameters) == 0)
          return 0;

        if (sc->synthDefs[a]->parameters != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numParameters; b++) {
            if (writeFloat(fp, sc->synthDefs[a]->parameters[b]) == 0)
              return 0;
          }
        }

        if (writeInt(fp, sc->synthDefs[a]->numParameterNames) == 0)
          return 0;

        if (sc->synthDefs[a]->parameterNames != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numParameterNames; b++) {
            if (sc->synthDefs[a]->parameterNames[b] != NULL) {
              if (writeString(fp, sc->synthDefs[a]->parameterNames[b]->name) ==
                  0)
                return 0;

              if (writeInt(fp, sc->synthDefs[a]->parameterNames[b]->index) == 0)
                return 0;
            }
          }
        }

        if (writeInt(fp, sc->synthDefs[a]->numUGens) == 0)
          return 0;

        if (sc->synthDefs[a]->uGens != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numUGens; b++) {
            if (sc->synthDefs[a]->uGens[b] != NULL) {
              if (writeString(fp, sc->synthDefs[a]->uGens[b]->name) == 0)
                return 0;

              if (writeChar(fp, sc->synthDefs[a]->uGens[b]->rate) == 0)
                return 0;

              if (writeInt(fp, sc->synthDefs[a]->uGens[b]->numInputs) == 0)
                return 0;

              if (writeInt(fp, sc->synthDefs[a]->uGens[b]->numOutputs) == 0)
                return 0;

              if (writeShort(fp, sc->synthDefs[a]->uGens[b]->specialIndex) == 0)
                return 0;

              if (sc->synthDefs[a]->uGens[b]->inputs != NULL) {
                for (c = 0; c < sc->synthDefs[a]->uGens[b]->numInputs; c++) {
                  if (sc->synthDefs[a]->uGens[b]->inputs[c] != NULL) {
                    if (writeInt(fp,
                                 sc->synthDefs[a]->uGens[b]->inputs[c]->uGen) ==
                        0)
                      return 0;

                    if (writeInt(
                            fp, sc->synthDefs[a]->uGens[b]->inputs[c]->index) ==
                        0)
                      return 0;
                  }
                }
              }

              if (sc->synthDefs[a]->uGens[b]->outputs != NULL) {
                for (c = 0; c < sc->synthDefs[a]->uGens[b]->numOutputs; c++) {
                  if (sc->synthDefs[a]->uGens[b]->outputs[c] != NULL) {
                    if (writeChar(
                            fp, sc->synthDefs[a]->uGens[b]->outputs[c]->rate) ==
                        0)
                      return 0;
                  }
                }
              }
            }
          }
        }

        if (writeShort(fp, sc->synthDefs[a]->numVariants) == 0)
          return 0;

        if (sc->synthDefs[a]->variants != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numVariants; b++) {
            if (sc->synthDefs[a]->variants[b] != NULL) {
              if (writeString(fp, sc->synthDefs[a]->variants[b]->name) == 0)
                return 0;

              if (sc->synthDefs[a]->variants[b]->values != NULL) {
                for (c = 0; c < sc->synthDefs[a]->numParameters; c++) {
                  if (writeFloat(fp,
                                 sc->synthDefs[a]->variants[b]->values[c]) == 0)
                    return 0;
                }
              }
            }
          }
        }
      }
    }
  }

  return 1;
}

void freeSynthDef(sc_t sc) {
  int a;
  int b;
  int c;

  if (sc->synthDefs != NULL) {
    for (a = 0; a < sc->numSynthDefs; a++) {
      if (sc->synthDefs[a] != NULL) {
        if (sc->synthDefs[a]->name != NULL)
          free(sc->synthDefs[a]->name);
        if (sc->synthDefs[a]->constants != NULL)
          free(sc->synthDefs[a]->constants);
        if (sc->synthDefs[a]->parameters != NULL)
          free(sc->synthDefs[a]->parameters);
        if (sc->synthDefs[a]->parameterNames != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numParameterNames; b++) {
            if (sc->synthDefs[a]->parameterNames[b] != NULL) {
              if (sc->synthDefs[a]->parameterNames[b]->name != NULL)
                free(sc->synthDefs[a]->parameterNames[b]->name);
              free(sc->synthDefs[a]->parameterNames[b]);
            }
          }
          free(sc->synthDefs[a]->parameterNames);
        }
        if (sc->synthDefs[a]->uGens != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numUGens; b++) {
            if (sc->synthDefs[a]->uGens[b] != NULL) {
              if (sc->synthDefs[a]->uGens[b]->name != NULL)
                free(sc->synthDefs[a]->uGens[b]->name);
              if (sc->synthDefs[a]->uGens[b]->inputs != NULL) {
                for (c = 0; c < sc->synthDefs[a]->uGens[b]->numInputs; c++) {
                  if (sc->synthDefs[a]->uGens[b]->inputs[c] != NULL) {
                    free(sc->synthDefs[a]->uGens[b]->inputs[c]);
                  }
                }
                free(sc->synthDefs[a]->uGens[b]->inputs);
              }
              if (sc->synthDefs[a]->uGens[b]->outputs != NULL) {
                for (c = 0; c < sc->synthDefs[a]->uGens[b]->numOutputs; c++) {
                  if (sc->synthDefs[a]->uGens[b]->outputs[c] != NULL) {
                    free(sc->synthDefs[a]->uGens[b]->outputs[c]);
                  }
                }
                free(sc->synthDefs[a]->uGens[b]->outputs);
              }
              free(sc->synthDefs[a]->uGens[b]);
            }
          }
          free(sc->synthDefs[a]->uGens);
        }
        if (sc->synthDefs[a]->variants != NULL) {
          for (b = 0; b < sc->synthDefs[a]->numVariants; b++) {
            if (sc->synthDefs[a]->variants[b] != NULL) {
              if (sc->synthDefs[a]->variants[b]->name != NULL)
                free(sc->synthDefs[a]->variants[b]->name);
              if (sc->synthDefs[a]->variants[b]->values != NULL)
                free(sc->synthDefs[a]->variants[b]->values);
              free(sc->synthDefs[a]->variants[b]);
            }
          }
          free(sc->synthDefs[a]->variants);
        }
        free(sc->synthDefs[a]);
      }
    }
    free(sc->synthDefs);
  }
  free(sc);
}

int readString(FILE *fp, char **sp) {
  char size;
  if (readChar(fp, &size) == 0)
    return 0;
  char *s = (char *)malloc((size + 1) * sizeof(char));
  int i;
  for (i = 0; i < size; i++) {
    if (readChar(fp, s + i) == 0) {
      free(s);
      return 0;
    }
  }
  s[i] = '\0';
  *sp = s;
  return 1;
}

int writeString(FILE *fp, char *s) {
  char size = strlen(s);
  if (writeChar(fp, size) == 0)
    return 0;
  int i;
  for (i = 0; i < size; i++) {
    if (writeChar(fp, s[i]) == 0)
      return 0;
  }
  return 1;
}
