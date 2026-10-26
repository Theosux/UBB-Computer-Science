package domain;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

/**
 * A friendship between two users. The id is a pair of user ids (the id is the tuple)
 * We always make the first id the smallest one, friendship (1, 2) = (2, 1)
 */
public class Prietenie extends Entity<Tuple<Long, Long>> {

    // * data de cand sunt prieteni, format ISO
    private final LocalDateTime dataPrieteniei;

    /**
     * Creates the friendship with a given date
     *
     * @param idUtilizator1 user id
     * @param idUtilizator2 user2 id
     * @param dataPrieteniei the date and time when the friendship was made
     */
    public Prietenie(Long idUtilizator1, Long idUtilizator2, LocalDateTime dataPrieteniei) {
        // normalizam ordinea pentru a functiona comenzile pentru cazuri (2, 1) (2>1)

        if (idUtilizator1 != null && idUtilizator2 != null && idUtilizator1 > idUtilizator2) {
            Long aux = idUtilizator1;
            idUtilizator1 = idUtilizator2;
            idUtilizator2 = aux;
        }
        setId(new Tuple<>(idUtilizator1, idUtilizator2));
        this.dataPrieteniei = dataPrieteniei;
    }

    /**
     * Creates the friendship with the current date
     *
     * @param idUtilizator1 user id
     * @param idUtilizator2 user2 id
     */
    public Prietenie(Long idUtilizator1, Long idUtilizator2) {
        // * prietenie noua, data e momentul de acum
        this(idUtilizator1, idUtilizator2, LocalDateTime.now().truncatedTo(ChronoUnit.MINUTES));
    }

    /**
     * @return the smaller id
     */
    public Long getIdUtilizator1() {
        return getId().getLeft();
    }

    /**
     * @return the bigger id
     */
    public Long getIdUtilizator2() {
        return getId().getRight();
    }

    /**
     * @return the date and time when the friendship was made
     */
    public LocalDateTime getDataPrieteniei() {
        return dataPrieteniei;
    }

    /**
     *
     * @return the friendship as text
     */
    @Override
    public String toString() {
        return getIdUtilizator1() + " - " + getIdUtilizator2() + " (din " + dataPrieteniei + ")";
    }
}
