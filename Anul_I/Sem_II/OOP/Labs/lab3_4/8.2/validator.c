#include "validator.h"
#include <string.h>

int validator(Produs p) {
    if (p.id < 0) return 0;
    if (strlen(p.tip) == 0) return 0;
    if (strlen(p.producator) == 0) return 0;
    if (strlen(p.model) == 0) return 0;
    if (p.pret < 0) return 0;
    if (p.cantitate < 0) return 0;
    return 1;
}