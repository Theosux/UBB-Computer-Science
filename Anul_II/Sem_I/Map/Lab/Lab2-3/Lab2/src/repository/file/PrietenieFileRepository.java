package repository.file;

import domain.Prietenie;
import domain.Tuple;
import domain.validators.Validator;

public class PrietenieFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Prietenie> {
    // repo in fisier csv pt prietenii

    public PrietenieFileRepository(Validator<Prietenie> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Prietenie extractEntity(String line) {
        String[] fields = line.split(",");
        return new Prietenie(Long.parseLong(fields[0]), Long.parseLong(fields[1]));
    }

    @Override
    protected String createEntityAsString(Prietenie p) {
        return p.getIdUtilizator1() + "," + p.getIdUtilizator2();
    }
}
