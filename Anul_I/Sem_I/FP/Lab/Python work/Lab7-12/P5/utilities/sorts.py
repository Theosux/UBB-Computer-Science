from functools import cmp_to_key

class Sorter:
    @staticmethod
    def _default_key(x):
        return x

    @staticmethod
    def _merge_sort(lista, key, reverse):
        if len(lista) <= 1:
            return lista

        mijloc = len(lista) // 2
        stanga = Sorter._merge_sort(lista[:mijloc], key, reverse)
        dreapta = Sorter._merge_sort(lista[mijloc:], key, reverse)

        return Sorter._merge(stanga, dreapta, key, reverse)

    @staticmethod
    def _merge(stanga, dreapta, key, reverse):
        rezultat = []
        i = j = 0
        while i < len(stanga) and j < len(dreapta):
            val_stanga = key(stanga[i])
            val_dreapta = key(dreapta[j])
            
            conditie = (val_stanga >= val_dreapta) if reverse else (val_stanga <= val_dreapta)
            
            if conditie:
                rezultat.append(stanga[i])
                i += 1
            else:
                rezultat.append(dreapta[j])
                j += 1
        rezultat.extend(stanga[i:])
        rezultat.extend(dreapta[j:])
        return rezultat

    @staticmethod
    def _bingo_sort(lista, key, reverse):
        n = len(lista)
        if n <= 1:
            return lista

        if reverse:
            bingo_val = key(max(lista, key=key))
            next_bingo_fn = max
            compare = lambda x, y: x < y 
        else:
            bingo_val = key(min(lista, key=key))
            next_bingo_fn = min
            compare = lambda x, y: x > y 

        pos = 0
        
        while pos < n:
            start_pos = pos
            found_next_bingo = False
            next_bingo_candidate = None

            for i in range(start_pos, n):
                val_i = key(lista[i])
                
                if val_i == bingo_val:
                    lista[i], lista[pos] = lista[pos], lista[i]
                    pos += 1
                else:
                    if not found_next_bingo:
                        next_bingo_candidate = val_i
                        found_next_bingo = True
                    else:
                        if compare(next_bingo_candidate, val_i): 
                            next_bingo_candidate = val_i

            if found_next_bingo:
                bingo_val = next_bingo_candidate
            else:
                break 
                
        return lista

    @staticmethod
    def generic_sort(lista, key=None, reverse=False, cmp=None, algorithm='merge'):
        if lista is None:
            return []
            
        if cmp is not None and key is None:
            key = cmp_to_key(cmp)
            
        if key is None:
            key = Sorter._default_key

        lista_de_sortat = list(lista)

        if algorithm == 'bingo':
            return Sorter._bingo_sort(lista_de_sortat, key, reverse)
        else:
            return Sorter._merge_sort(lista_de_sortat, key, reverse)