package service;

import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import repository.Repository;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

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
        for (Prietenie p : repoPrietenii.findAll()) {
            Utilizator u1 = repoUtilizatori.findOne(p.getIdUtilizator1());
            Utilizator u2 = repoUtilizatori.findOne(p.getIdUtilizator2());
            // * prietenie salvata cu un utilizator care nu exista: fisierele nu sunt consistente, oprim cu mesaj clar
            if (u1 == null || u2 == null)
                throw new ServiceException("Prietenia " + p + " are un utilizator care nu exista!");
            u1.getFriends().add(u2);
            u2.getFriends().add(u1);
        }
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
        for (Utilizator prieten : u.getFriends()) {
            prieten.getFriends().remove(u);
            repoPrietenii.delete(new Prietenie(id, prieten.getId()).getId());
        }
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
        Utilizator u1 = repoUtilizatori.findOne(id1);
        Utilizator u2 = repoUtilizatori.findOne(id2);
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

        List<Utilizator> celMaiBun = new ArrayList<>();
        int maxim = -1;
        for (List<Utilizator> comunitate : comunitati()) {
            int drum = 0;
            for (Utilizator start : comunitate)
                drum = Math.max(drum, celMaiLungDrum(start, new HashSet<>()));
            if (drum > maxim) {
                maxim = drum;
                celMaiBun = comunitate;
            }
        }
        return celMaiBun;
    }

    private Long urmatorulId() {
        // cel mai mare id + 1, pt adaugare

        long maxim = 0;
        for (Utilizator u : repoUtilizatori.findAll())
            if (u.getId() > maxim)
                maxim = u.getId();
        return maxim + 1;
    }

    private Utilizator gasesteUtilizator(Long id) {
        // stergere, adaugare gaseste utilizator dupa id

        Utilizator u = repoUtilizatori.findOne(id);
        if (u == null)
            throw new ServiceException("Nu exista utilizatorul cu id-ul " + id + "!");
        return u;
    }

    private List<List<Utilizator>> comunitati() {
        // pt fiecare utilizator nevizitat rulam dfs, cate dfs uri rulam = nr comunitati


        List<List<Utilizator>> rezultat = new ArrayList<>();
        Set<Utilizator> vizitati = new HashSet<>();
        for (Utilizator u : repoUtilizatori.findAll()) {
            if (!vizitati.contains(u)) {
                List<Utilizator> comunitate = new ArrayList<>();
                dfs(u, vizitati, comunitate);
                rezultat.add(comunitate);
            }
        }
        return rezultat;
    }

    private void dfs(Utilizator u, Set<Utilizator> vizitati, List<Utilizator> comunitate) {
        // dfs: adauga in comunitate toti utilizatorii la care se ajunge din u

        vizitati.add(u);
        comunitate.add(u);
        for (Utilizator prieten : u.getFriends())
            if (!vizitati.contains(prieten))
                dfs(prieten, vizitati, comunitate);
    }

    private int celMaiLungDrum(Utilizator u, Set<Utilizator> vizitati) {
        // backtracking: lungimea celui mai lung drum (fara utilizatori repetati) care porneste din u

        vizitati.add(u);
        int maxim = 0;
        for (Utilizator prieten : u.getFriends())
            if (!vizitati.contains(prieten))
                maxim = Math.max(maxim, 1 + celMaiLungDrum(prieten, vizitati));
        vizitati.remove(u);
        return maxim;
    }
}