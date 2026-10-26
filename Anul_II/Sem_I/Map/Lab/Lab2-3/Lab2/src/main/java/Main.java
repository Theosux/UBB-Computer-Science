import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.PrietenieValidator;
import domain.validators.UtilizatorValidator;
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
        // * pornirea poate da erori pt config gresit, linie corupta, db neimplementat
        try {
            // * config
            Properties config = incarcaConfiguratie("/config.properties");
            RepositoryFactory factory = new RepositoryFactory(config);

            // * main nu mai face new pe repo-uri concrete, le cere de la factory (tipul e doar interfata Repository)
            Repository<Long, Utilizator> repoUtilizatori =
                    factory.createUtilizatorRepository(new UtilizatorValidator());
            Repository<Tuple<Long, Long>, Prietenie> repoPrietenii =
                    factory.createPrietenieRepository(new PrietenieValidator());

            ReteaService service = new ReteaService(repoUtilizatori, repoPrietenii);
            Consola consola = new Consola(service);
            consola.run();
        } catch (RepositoryException | ServiceException | UnsupportedOperationException e) {
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
        // * getResourceAsStream cauta fisierul in classpath, try-with-resources il inchide singur

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