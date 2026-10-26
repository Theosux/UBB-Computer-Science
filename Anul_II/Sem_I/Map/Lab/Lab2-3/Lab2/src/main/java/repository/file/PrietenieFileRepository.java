package repository.file;

import domain.Prietenie;
import domain.Tuple;
import domain.validators.Validator;
import java.time.LocalDateTime;

/**
 * repo with a text file for friendships, one friendship per line with the format: idU1;idU2;dataP
 */
public class PrietenieFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Prietenie> {

    /**
     * @param validator the validation strategy for friendships
     * @param fileName relative path to the text file
     */
    public PrietenieFileRepository(Validator<Prietenie> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * @param line the line
     * @return the friendship described by the line
     * @throws IllegalArgumentException if the line doesn't have 3 fields or an id is not a number
     * @throws java.time.format.DateTimeParseException if the date is not in ISO format
     */
    @Override
    protected Prietenie extractEntity(String line) {
        // * format nou: id1;id2;data, cu ; si -1 ca la utilizatori
        String[] fields = line.split(";", -1);
        if (fields.length != 3)
            throw new IllegalArgumentException("linia trebuie sa aiba 3 campuri: id1;id2;data");
        // * LocalDateTime.parse citeste data in format ISO (2026-10-19T10:30)
        return new Prietenie(Long.parseLong(fields[0]), Long.parseLong(fields[1]),
                LocalDateTime.parse(fields[2]));
    }

    /**
     * @param p the friendship that must be converted
     * @return the line that describes the friendship
     */
    @Override
    protected String createEntityAsString(Prietenie p) {
        // * toString-ul lui LocalDateTime scrie data tot in format ISO
        return p.getIdUtilizator1() + ";" + p.getIdUtilizator2() + ";" + p.getDataPrieteniei();
    }
}
