import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.PrietenieValidator;
import domain.validators.UtilizatorValidator;
import domain.validators.ValidationException;
import domain.validators.Validator;
import repository.Repository;
import repository.RepositoryException;
import repository.factory.RepositoryFactory;
import service.ReteaService;
import service.ServiceException;
import ui.Consola;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * Main class
 */
public class Main {

    /**
     * Reads the config, gets the repos from the factory and starts the console
     * If the app cannot start, a message is printed
     *
     * @param args cmd args (we don't use them)
     */
    public static void main(String[] args) {
        // * pornirea poate da erori pt config gresit, linie corupta, baza de date oprita
        try {
            // config
            Properties config = incarcaConfiguratie("/config.properties");
            RepositoryFactory factory = new RepositoryFactory(config);

            // regula noua de validare scrisa ca lambda, fara clasa noua si fara sa modificam UtilizatorValidator
            Validator<Utilizator> lungimeNume = u -> {
                // * 50, nu 20: la demo trebuie sa incapa numele cu '); DROP TABLE users; --
                if (u.getFirstName().length() > 50 || u.getLastName().length() > 50)
                    throw new ValidationException("prenumele si numele au cel mult 50 de caractere;");
            };
            // andThen: intai regulile vechi (care verifica si null), apoi lungimea
            Validator<Utilizator> validatorUtilizatori = new UtilizatorValidator().andThen(lungimeNume);

            // main nu mai face new pe repo-uri concrete, le cere de la factory (tipul e doar interfata Repository)
            Repository<Long, Utilizator> repoUtilizatori =
                    factory.createUtilizatorRepository(validatorUtilizatori);
            Repository<Tuple<Long, Long>, Prietenie> repoPrietenii =
                    factory.createPrietenieRepository(new PrietenieValidator());

            ReteaService service = new ReteaService(repoUtilizatori, repoPrietenii);
            Consola consola = new Consola(service);
            consola.run();
        } catch (RepositoryException | ServiceException e) {
            // * fara UnsupportedOperationException: repo-urile DB sunt implementate, nu mai arunca
            System.out.println("Aplicatia nu poate porni: " + e.getMessage());
        }
    }

    /**
     * loads the config file
     *
     * @param resursa the name of the resource file
     * @return the properties read from the file
     * @throws RepositoryException if the resources don't exist or cannot be read
     */
    private static Properties incarcaConfiguratie(String resursa) {
        // getResourceAsStream cauta fisierul in classpath, try-with-resources il inchide singur

        try (InputStream in = Main.class.getResourceAsStream(resursa)) {
            if (in == null)
                throw new RepositoryException("Nu exista fisierul de configurare " + resursa);
            Properties config = new Properties();
            config.load(in);
            return config;
        } catch (IOException e) {
            throw new RepositoryException("Nu se poate citi fisierul de configurare " + resursa, e);
        }
    }
}
