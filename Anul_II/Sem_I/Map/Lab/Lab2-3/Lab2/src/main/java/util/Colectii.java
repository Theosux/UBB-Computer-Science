package util;

import java.util.ArrayList;
import java.util.List;

/**
 * Helper methods for collections
 */
public class Colectii {
    // * clasa utilitara: doar metode statice, nu se creeaza obiecte
    private Colectii() {
    }

    /**
     * Copies the elements of an Iterable into a new list
     *
     * @param elemente the elements, for example the result of Repository.findAll()
     * @return a new modifiable list with all the elements, in the same order
     * @param <T> the type of the elements
     */
    public static <T> List<T> catreLista(Iterable<T> elemente) {
        List<T> lista = new ArrayList<>();
        // * lista::add = referinta la metoda unui obiect anume (x -> lista.add(x))
        elemente.forEach(lista::add);
        return lista;
    }
}
