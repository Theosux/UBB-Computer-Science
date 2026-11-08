package service;

import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import repository.Repository;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Comparator;
import java.util.function.Predicate;
import java.util.LinkedHashSet;
import java.util.Optional;
import java.util.function.Supplier;
import java.util.stream.Collectors;

/**
 * The logic of the social network, the friend lists of the users are consistent with the friendships from the repo
 */
public class ReteaService {

    private final Repository<Long, Utilizator> repoUtilizatori;
    private final Repository<Tuple<Long, Long>, Prietenie> repoPrietenii;

    /**
     * Creates the service and rebuilds the friend lists
     *
     * @param repoUtilizatori the users repo
     * @param repoPrietenii the friendships repo
     */
    public ReteaService(Repository<Long, Utilizator> repoUtilizatori,
                        Repository<Tuple<Long, Long>, Prietenie> repoPrietenii) {
        this.repoUtilizatori = repoUtilizatori;
        this.repoPrietenii = repoPrietenii;
        incarcaPrieteni();
    }

    private void incarcaPrieteni() {
        // * Iterable.forEach in loc de for; this::leagaPrieteni = referinta la metoda acestui obiect (p -> leagaPrieteni(p))
        repoPrietenii.findAll().forEach(this::leagaPrieteni);
    }

    private void leagaPrieteni(Prietenie p) {
        // * corpul for-ului de la Lab3, mutat intr-o metoda
        // prietenie salvata cu un utilizator care nu exista: fisierele nu sunt consistente, oprim cu mesaj clar
        // * Supplier: stie sa creeze exceptia, dar o creeaza doar daca utilizatorul lipseste
        Supplier<ServiceException> eroare =
                () -> new ServiceException("Prietenia " + p + " are un utilizator care nu exista!");
        Utilizator u1 = cautaUtilizator(p.getIdUtilizator1()).orElseThrow(eroare); // *
        Utilizator u2 = cautaUtilizator(p.getIdUtilizator2()).orElseThrow(eroare); // *
        u1.getFriends().add(u2);
        u2.getFriends().add(u1);
    }

    /**
     * Adds a new user with a generated id
     *
     * @param firstName the first name
     * @param lastName the second one
     * @return the added user
     * @throws domain.validators.ValidationException if the name is not valid
     * @throws repository.RepositoryException if the data cannot be persisted
     */
    public Utilizator adaugaUtilizator(String firstName, String lastName) {
        Utilizator u = new Utilizator(firstName, lastName);
        u.setId(urmatorulId());
        repoUtilizatori.save(u);
        return u;
    }

    /**
     * Deletes a user and all of their friendships
     *
     * @param id the id of the user
     * @return the deleted user
     * @throws ServiceException there is no user with that id
     * @throws repository.RepositoryException if the data cannot be persisted
     */
    public Utilizator stergeUtilizator(Long id) {
        Utilizator u = gasesteUtilizator(id);
        // * forEach in loc de for: pentru fiecare prieten, il scoatem pe u din lista lui si stergem prietenia
        u.getFriends().forEach(prieten -> {
            prieten.getFriends().remove(u);
            repoPrietenii.delete(new Prietenie(id, prieten.getId()).getId());
        });
        return repoUtilizatori.delete(id);
    }

    /**
     * Adds a friendship between two users
     *
     * @param id1 user 1
     * @param id2 user 2
     * @throws ServiceException if the user doesn't exist or the friendship already exists
     * @throws domain.validators.ValidationException if the two ids are equal
     * @throws repository.RepositoryException if the data cannot be persisted
     */
    public void adaugaPrietenie(Long id1, Long id2) {
        Utilizator u1 = gasesteUtilizator(id1);
        Utilizator u2 = gasesteUtilizator(id2);
        if (repoPrietenii.save(new Prietenie(id1, id2)) != null)
            throw new ServiceException("Prietenia exista deja!");
        u1.getFriends().add(u2);
        u2.getFriends().add(u1);
    }

    /**
     * Deletes the friendship between two users
     *
     * @param id1 user 1
     * @param id2 user 2
     * @throws ServiceException if the two users are not friends
     * @throws repository.RepositoryException if the data cannot be persisted
     */
    public void stergePrietenie(Long id1, Long id2) {
        Prietenie p = new Prietenie(id1, id2);
        if (repoPrietenii.delete(p.getId()) == null)
            throw new ServiceException("Nu exista prietenie intre " + id1 + " si " + id2 + "!");
        Utilizator u1 = gasesteUtilizator(id1); // *
        Utilizator u2 = gasesteUtilizator(id2); // *
        u1.getFriends().remove(u2);
        u2.getFriends().remove(u1);
    }

    /**
     * @return all the users
     */
    public Iterable<Utilizator> getUtilizatori() { // pt afisarea in UI prin repo
        return repoUtilizatori.findAll();
    }

    /**
     * Searches the users with a criterion given by the caller
     * @param criteriu the condition the users must satisfy
     * @return the users that satisfy the criterion, sorted by last name, then by first name
     */
    public List<Utilizator> cautaUtilizatori(Predicate<Utilizator> criteriu) {
        // * repo-ul filtreaza (findAll cu Predicate), noi sortam rezultatul cu un stream
        // * comparatorul e construit, nu scris de mana: intai dupa nume, la egalitate dupa prenume
        return repoUtilizatori.findAll(criteriu).stream()
                .sorted(Comparator.comparing(Utilizator::getLastName).thenComparing(Utilizator::getFirstName))
                .collect(Collectors.toList());
    }

    /**
     * @return all the users, the ones with more friends first
     */
    public List<Utilizator> utilizatoriDupaNrPrieteni() {
        // * variabila intermediara: in sort(comparingInt(u -> ...).reversed()) compilatorul nu stie tipul lui u
        Comparator<Utilizator> dupaNrPrieteni = Comparator.comparingInt(u -> u.getFriends().size());
        // * findAll() e Iterable, care nu are sort; copiem intr-o lista noua si sortam lista
        List<Utilizator> rezultat = Colectii.catreLista(repoUtilizatori.findAll());
        rezultat.sort(dupaNrPrieteni.reversed()
                .thenComparing(Utilizator::getLastName)
                .thenComparing(Utilizator::getFirstName));
        return rezultat;
    }

    /**
     * @return nr of communities
     */
    public int numarComunitati() {
        return comunitati().size();
    }

    /**
     * @return the users from the longest friendship path
     */
    public List<Utilizator> ceaMaiSociabilaComunitate() {
        // incercam fiecare utilizator ca start si gasim cel mai lung drum, comunitatea cu cel mai lung drum este cea mai sociabila

        // * max intoarce Optional (nu exista maxim daca nu exista comunitati); la egalitate ramane prima, ca la Lab3
        // * map(ArrayList::new) = referinta la constructor: Set-ul devine lista; orElse = lista goala daca nu sunt utilizatori
        return comunitati().stream()
                .max(Comparator.comparingInt(this::celMaiLungDrumDin))
                .map(ArrayList::new)
                .orElse(new ArrayList<>());
    }

    private Long urmatorulId() {
        // cel mai mare id + 1, pt adaugare

        // * map: utilizator -> id; reduce: combina id-urile doua cate doua cu Long::max, pornind de la 0
        return repoUtilizatori.stream()
                .map(Utilizator::getId)
                .reduce(0L, Long::max) + 1;
    }

    /**
     * Searches a user by id; the result may be missing, so it is an Optional
     *
     * @param id the id of the user, not null
     * @return an Optional with the user, Optional.empty() if there is no user with that id
     * @throws IllegalArgumentException if id is null
     */
    private Optional<Utilizator> cautaUtilizator(Long id) {
        // * repo-ul intoarce null daca nu exista, Optional.ofNullable il transforma in Optional.empty()
        return Optional.ofNullable(repoUtilizatori.findOne(id));
    }

    private Utilizator gasesteUtilizator(Long id) {
        // stergere, adaugare gaseste utilizator dupa id

        // * orElseThrow: utilizatorul, sau exceptia creata de lambda daca Optional-ul e gol
        return cautaUtilizator(id)
                .orElseThrow(() -> new ServiceException("Nu exista utilizatorul cu id-ul " + id + "!"));
    }

    private List<Set<Utilizator>> comunitati() {
        // * pt fiecare utilizator calculam comunitatea lui; utilizatorii din aceeasi comunitate dau acelasi Set
        // * distinct pastreaza o singura data fiecare comunitate, deci cate raman = nr comunitati
        return repoUtilizatori.stream()
                .map(this::comunitateaLui)
                .distinct()
                .collect(Collectors.toList());
    }

    /**
     * Finds the community of a user: all the users that can be reached from him through friendships
     *
     * @param u the user
     * @return the users of the community, in the order of the dfs (u is the first one)
     */
    private Set<Utilizator> comunitateaLui(Utilizator u) {
        // * LinkedHashSet: retine ordinea in care dfs-ul adauga utilizatorii, ca lista de la Lab3
        Set<Utilizator> comunitate = new LinkedHashSet<>();
        dfs(u, comunitate);
        return comunitate;
    }

    private void dfs(Utilizator u, Set<Utilizator> comunitate) {
        // dfs: adauga in comunitate toti utilizatorii la care se ajunge din u
        // * comunitatea e si multimea celor vizitati
        comunitate.add(u);
        // * filter doar citeste comunitatea; forEach o modifica, prin dfs (efectul secundar e in forEach, nu in filter)
        u.getFriends().stream()
                .filter(prieten -> !comunitate.contains(prieten))
                .forEach(prieten -> dfs(prieten, comunitate));
    }

    /**
     * @param comunitate the users of a community
     * @return the length of the longest path (without repeated users) inside the community
     */
    private int celMaiLungDrumDin(Set<Utilizator> comunitate) {
        // * fiecare utilizator e incercat ca start (map), apoi pastram maximul (reduce)
        return comunitate.stream()
                .map(start -> celMaiLungDrum(start, new HashSet<>()))
                .reduce(0, Integer::max);
    }

    private int celMaiLungDrum(Utilizator u, Set<Utilizator> vizitati) {
        // backtracking: lungimea celui mai lung drum (fara utilizatori repetati) care porneste din u
        // * ramane cu for (exceptie justificata in readme): vizitati se modifica si se reface la fiecare pas
        vizitati.add(u);
        int maxim = 0;
        for (Utilizator prieten : u.getFriends())
            if (!vizitati.contains(prieten))
                maxim = Math.max(maxim, 1 + celMaiLungDrum(prieten, vizitati));
        vizitati.remove(u);
        return maxim;
    }
}