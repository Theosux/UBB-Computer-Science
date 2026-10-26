package repository.file;

import domain.Entity;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.InMemoryRepository;
import repository.RepositoryException;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.time.format.DateTimeParseException;

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
            // * fisier lipsa: repo gol, fisierul se creeaza la primul save (fara mesaj din repository)
            if (!new File(fileName).exists())
                return;

            try (BufferedReader reader = new BufferedReader(new FileReader(fileName, StandardCharsets.UTF_8))) {
                String line;
                int lineNumber = 0;
                while ((line = reader.readLine()) != null) {
                    lineNumber++;
                    if (line.isBlank())
                        continue;
                    // * linie corupta: oprim incarcarea cu un mesaj clar (fisier, nr linie, motiv), cauza ramane in exceptie
                    E result;
                    try {
                        result = super.save(extractEntity(line));
                    } catch (IllegalArgumentException | DateTimeParseException | ValidationException e) {
                        throw new RepositoryException(lineError(lineNumber, line, e.getMessage()), e);
                    }
                    // * acelasi id de doua ori in fisier
                    if (result != null)
                        throw new RepositoryException(lineError(lineNumber, line, "id-ul exista deja in fisier"));
                }
            } catch (IOException e) {
                throw new RepositoryException("Eroare la citirea fisierului " + fileName, e);
            }
        }

    private String lineError(int lineNumber, String line, String reason) {
        // * mesajul pt o linie corupta, de ex: data/utilizatori.txt, linia 3 "abc;Ion;Pop": ...

        return fileName + ", linia " + lineNumber + " \"" + line + "\": " + reason;
    }

    private void writeToFile() {
        // rescrie tot fisierul cu entitatile din memorie

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, StandardCharsets.UTF_8))) {
            for (E entity : findAll()) {
                writer.write(createEntityAsString(entity));
                writer.newLine();
            }
        } catch (IOException e) {
            // * RepositoryException in loc de RuntimeException, cu IOException ca si cauza
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
