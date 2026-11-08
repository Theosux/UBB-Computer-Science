package repository.file;

import domain.Entity;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.RepositoryException;

import java.io.UncheckedIOException;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Files;
import java.nio.charset.StandardCharsets;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * Repo that keeps the entities in memory and in a text file (one entity per line)
 * Template method: the writing and reading happen here, once, the subclasses only say how a line becomes an entity and the other way around
 * The file is loaded when the repo is created, and updated at every crud command of the repo
 *
 * @param <ID> the ID type of the entities
 * @param <E> the type of the entity
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E>  {

    private final String fileName;

    /**
     * Creates the repo and loads the entities
     * If the file doesn't exist it gets created and the repo starts empty
     *
     * @param validator the validation strategy for the entities
     * @param fileName relative path
     * @throws RepositoryException if the file cannot be read or contains a corrupt line
     */
    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
        loadData();
    }

    /**
     * Creates an entity from a line of the file
     * @param line the line
     * @return the entity described by the line
     * @throws IllegalArgumentException if the line doesn't have the correct format
     * @throws DateTimeParseException if the date is not in ISO format
     */
    protected abstract E extractEntity(String line);

    /**
     * Converts an entity into a line of the file
     * @param entity the entity that must be converted
     * @return the text line that describes the entity
     */
    protected abstract String createEntityAsString(E entity);

    private void loadData() {
        // citeste liniile din fisier si salveaza entitatile in memorie
            // fisier lipsa: repo gol, fisierul se creeaza la primul save (fara mesaj din repository)
        Path path = Path.of(fileName); // *
        if (!Files.exists(path)) // *
            return;

        List<String> lines; // *
        // * Files.lines tine fisierul deschis cat citim din stream, try-with-resources il inchide
        try (Stream<String> stream = Files.lines(path, StandardCharsets.UTF_8)) {
            lines = stream.collect(Collectors.toList());
        } catch (IOException | UncheckedIOException e) {
            // * UncheckedIOException = IOException aruncata in timpul parcurgerii stream-ului, impachetata de Java
                throw new RepositoryException("Eroare la citirea fisierului " + fileName, e);
            }
        // * parcurgem indicii 0..n-1 ca sa stim numarul liniei (indice + 1)
        IntStream.range(0, lines.size())
                .filter(i -> !lines.get(i).isBlank())
                .forEach(i -> loadLine(i + 1, lines.get(i)));
        }

    /**
     * Saves in memory the entity described by a line of the file
     *
     * @param lineNumber the number of the line in the file, starting from 1
     * @param line the line
     * @throws RepositoryException if the line is corrupt or the id already exists in the file
     */
    private void loadLine(int lineNumber, String line) {
        // * corpul while-ului de la Lab3, mutat intr-o metoda
        // linie corupta: oprim incarcarea cu un mesaj clar (fisier, nr linie, motiv), cauza ramane in exceptie
        E result;
        try {
            result = super.save(extractEntity(line));
        } catch (IllegalArgumentException | DateTimeParseException | ValidationException e) {
            throw new RepositoryException(lineError(lineNumber, line, e.getMessage()), e);
        }
        // acelasi id de doua ori in fisier
        if (result != null)
            throw new RepositoryException(lineError(lineNumber, line, "id-ul exista deja in fisier"));
    }

    private String lineError(int lineNumber, String line, String reason) {
        // mesajul pt o linie corupta, de ex: data/utilizatori.txt, linia 3 "abc;Ion;Pop": ...

        return fileName + ", linia " + lineNumber + " \"" + line + "\": " + reason;
    }

    private void writeToFile() {
        // rescrie tot fisierul cu entitatile din memorie

        // * fiecare entitate devine o linie (map), liniile se strang intr-o lista (collect)
        List<String> lines = stream()
                .map(this::createEntityAsString)
                .collect(Collectors.toList());
        try {
            // * Files.write scrie fiecare linie urmata de un sfarsit de linie, ca writer.newLine()
            Files.write(Path.of(fileName), lines, StandardCharsets.UTF_8);
        } catch (IOException e) {
            // RepositoryException in loc de RuntimeException, cu IOException ca si cauza
            throw new RepositoryException("Eroare la scrierea fisierului " + fileName, e);
        }
    }

    /**
     * @param entity the entity that must be saved, not null
     * @return null if the entity was saved, otherwise, the entity (it already exists)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null)
            writeToFile();
        return result;
    }

    /**
     * @param id entity that must be deleted, not null
     * @return the deleted entity, null if there is no entity with that id
     * @throws IllegalArgumentException if id is null
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null)
            writeToFile();
        return result;
    }

    /**
     * @param entity the entity with the new data, not null
     * @return null if the entity was updated, otherwise, the entity (if it doesn't exist)
     * @throws IllegalArgumentException if the entity is null
     * @throws ValidationException if the entity is not valid
     * @throws RepositoryException if the data cannot be persisted
     */
    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null)
            writeToFile();
        return result;
    }
}
