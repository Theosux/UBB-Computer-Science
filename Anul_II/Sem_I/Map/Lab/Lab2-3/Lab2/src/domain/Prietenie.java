package domain;

public class Prietenie extends Entity<Tuple<Long, Long>> {
    // prietenie intre toi utilizatori, id-ul este practic tuplul

    public Prietenie(Long idUtilizator1, Long idUtilizator2) {
        // normalizam ordinea pentru a functiona comenzile pentru cazuri (2, 1) (2>1)

        if (idUtilizator1 != null && idUtilizator2 != null && idUtilizator1 > idUtilizator2) {
            Long aux = idUtilizator1;
            idUtilizator1 = idUtilizator2;
            idUtilizator2 = aux;
        }
        setId(new Tuple<>(idUtilizator1, idUtilizator2));
    }

    public Long getIdUtilizator1() {
        return getId().getLeft();
    }

    public Long getIdUtilizator2() {
        return getId().getRight();
    }

    @Override
    public String toString() {
        return getIdUtilizator1() + " - " + getIdUtilizator2();
    }
}
