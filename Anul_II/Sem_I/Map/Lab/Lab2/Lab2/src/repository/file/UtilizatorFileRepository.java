package repository.file;

import domain.Utilizator;
import domain.validators.Validator;

public class UtilizatorFileRepository extends AbstractFileRepository<Long, Utilizator> {
    // repo in fisier csv pt utilizatori

    public UtilizatorFileRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Utilizator extractEntity(String line) {
        // linia devine entitate (-1 pastreaza campurile goale de la final)

        String[] fields = line.split(",", -1);
        Utilizator u = new Utilizator(fields[1], fields[2]);
        u.setId(Long.parseLong(fields[0]));
        return u;
    }

    @Override
    protected String createEntityAsString(Utilizator u) {
        // entitatea devine linie

        return u.getId() + "," + u.getFirstName() + "," + u.getLastName();
    }
}
