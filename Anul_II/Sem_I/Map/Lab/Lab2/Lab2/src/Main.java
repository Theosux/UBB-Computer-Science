import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.PrietenieValidator;
import domain.validators.UtilizatorValidator;
import repository.Repository;
import repository.file.PrietenieFileRepository;
import repository.file.UtilizatorFileRepository;
import service.ReteaService;
import ui.Consola;

public class Main {

    public static void main(String[] args) {
        Repository<Long, Utilizator> repoUtilizatori =
                new UtilizatorFileRepository(new UtilizatorValidator(), "data/utilizatori.csv");
        Repository<Tuple<Long, Long>, Prietenie> repoPrietenii =
                new PrietenieFileRepository(new PrietenieValidator(), "data/prietenii.csv");

        ReteaService service = new ReteaService(repoUtilizatori, repoPrietenii);
        Consola consola = new Consola(service);
        consola.run();
    }
}