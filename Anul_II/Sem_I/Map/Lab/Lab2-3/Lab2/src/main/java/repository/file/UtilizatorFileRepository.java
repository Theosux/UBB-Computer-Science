package repository.file;

import domain.Utilizator;
import domain.validators.Validator;

/**
 * repo with a text file for users, one user per line, with the format: id;prenume;nume
 */
public class UtilizatorFileRepository extends AbstractFileRepository<Long, Utilizator> {

    /**
     * @param validator the validation strategy for users
     * @param fileName relative path to the text file
     * @throws repository.RepositoryException if the file cannot be read or contains a corrupt line
     */
    public UtilizatorFileRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * @param line the line
     * @return the user described by a line
     * @throws IllegalArgumentException if the line doesn't have 3 fields, or the id is not a number
     */
    @Override
    protected Utilizator extractEntity(String line) {
        // linia devine entitate (-1 pastreaza campurile goale de la final)

        // * separator ;
        String[] fields = line.split(";", -1);
        // * linie corupta
        if (fields.length != 3)
            throw new IllegalArgumentException("linia trebuie sa aiba 3 campuri: id;prenume;nume");
        Utilizator u = new Utilizator(fields[1], fields[2]);
        u.setId(Long.parseLong(fields[0]));
        return u;
    }

    /**
     * @param u the entity that must be converted
     * @return the line
     */
    @Override
    protected String createEntityAsString(Utilizator u) {
        // entitatea devine linie

        return u.getId() + ";" + u.getFirstName() + ";" + u.getLastName();
    }
}
