package repository.file;

import domain.Utilizator;
import domain.validators.Validator;

public class UtilizatorFileRepository extends AbstractFileRepository<Long, Utilizator> {
    public UtilizatorFileRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Utilizator extractEntity(String line) {
        String[] fields = line.split(",", -1);
        Utilizator u = new Utilizator(fields[1], fields[2]);
        u.setId(Long.parseLong(fields[0]));
        return u;
    }

    @Override
    protected String createEntityAsString(Utilizator u) {
        return u.getId() + "," + u.getFirstName() + "," + u.getLastName();
    }
}
