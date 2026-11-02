package ui;

import domain.CriteriiUtilizator;
import domain.Utilizator;
import domain.validators.ValidationException;
import service.ReteaService;
import service.ServiceException;
import repository.RepositoryException;

import java.util.Scanner;
import java.util.List;
import java.util.function.Predicate;

/**
 * the console interface, menu, options, prints; the errors are caught here
 */
public class Consola {

    private final ReteaService service;
    private final Scanner scanner = new Scanner(System.in);

    /**
     * @param service used for operations
     */
    public Consola(ReteaService service) {
        this.service = service;
    }

    /**
     * runs the menu until the user picks 0
     */
    public void run() {
        boolean ruleaza = true;
        while (ruleaza) {
            afiseazaMeniu();
            String optiune = scanner.nextLine().trim();
            try {
                switch (optiune) {
                    case "1":
                        adaugaUtilizator();
                        break;
                    case "2":
                        stergeUtilizator();
                        break;
                    case "3":
                        adaugaPrietenie();
                        break;
                    case "4":
                        stergePrietenie();
                        break;
                    case "5":
                        afiseazaUtilizatori();
                        break;
                    case "6":
                        System.out.println("Numar de comunitati: " + service.numarComunitati());
                        break;
                    case "7":
                        System.out.println("Cea mai sociabila comunitate: " + service.ceaMaiSociabilaComunitate());
                        break;
                    case "8":
                        cautaUtilizatori();
                        break;
                    case "9":
                        afiseazaDupaNrPrieteni();
                        break;
                    case "0":
                        ruleaza = false;
                        break;
                    default:
                        System.out.println("Optiune invalida!");
                }
            } catch (ValidationException | ServiceException e) {
                System.out.println("Eroare: " + e.getMessage());
            } catch (RepositoryException e) {   // Prindem si din repo
                System.out.println("Eroare la salvarea datelor: " + e.getMessage());
            }
            catch (NumberFormatException e) {
                System.out.println("Eroare: id-ul trebuie sa fie un numar!");
            }
        }
    }
    private void afiseazaMeniu() {
        System.out.println();
        System.out.println("1. Adauga utilizator");
        System.out.println("2. Sterge utilizator");
        System.out.println("3. Adauga prieten");
        System.out.println("4. Sterge prieten");
        System.out.println("5. Afiseaza utilizatorii si prietenii lor");
        System.out.println("6. Numar de comunitati");
        System.out.println("7. Cea mai sociabila comunitate");
        System.out.println("8. Cauta utilizatorii dupa nume");  // *
        System.out.println("9. Utilizatorii dupa numarul de prieteni"); // *
        System.out.println("0. Iesire");
        System.out.print("Optiune: ");
    }

    private void adaugaUtilizator() {
        System.out.print("Prenume: ");
        String firstName = scanner.nextLine().trim();
        System.out.print("Nume: ");
        String lastName = scanner.nextLine().trim();
        System.out.println("Adaugat: " + service.adaugaUtilizator(firstName, lastName));
    }

    private void stergeUtilizator() {
        Long id = citesteId("Id utilizator: ");
        System.out.println("Sters: " + service.stergeUtilizator(id));
    }

    private void adaugaPrietenie() {
        Long id1 = citesteId("Id primul utilizator: ");
        Long id2 = citesteId("Id al doilea utilizator: ");
        service.adaugaPrietenie(id1, id2);
        System.out.println("Prietenie adaugata.");
    }

    private void stergePrietenie() {
        Long id1 = citesteId("Id primul utilizator: ");
        Long id2 = citesteId("Id al doilea utilizator: ");
        service.stergePrietenie(id1, id2);
        System.out.println("Prietenie stearsa.");
    }

    private void afiseazaUtilizatori() {
        // * Iterable.forEach cu o lambda in loc de for-each
        service.getUtilizatori().forEach(u -> System.out.println("  " + u + " | prieteni: " + u.getFriends()));
    }

    private Long citesteId(String mesaj) {
        System.out.print(mesaj);
        return Long.parseLong(scanner.nextLine().trim());
    }

    private void cautaUtilizatori() {
        // * criteriile vin din CriteriiUtilizator si se combina cu or, and, negate, Predicate.not
        // * un criteriu nou = o lambda noua aici, fara metoda noua in repository
        System.out.print("Nume: ");
        String nume = scanner.nextLine().trim();
        afiseaza("Cu numele " + nume + " sau prenumele care incepe cu " + nume, service.cautaUtilizatori(
                CriteriiUtilizator.areNumele(nume).or(CriteriiUtilizator.prenumeleIncepeCu(nume))));
        afiseaza("Cu numele " + nume + " si cel putin 2 prieteni", service.cautaUtilizatori(
                CriteriiUtilizator.areNumele(nume).and(CriteriiUtilizator.areCelPutinPrieteni(2))));
        afiseaza("Fara numele " + nume, service.cautaUtilizatori(
                CriteriiUtilizator.areNumele(nume).negate()));
        // * CriteriiUtilizator::faraPrieteni = referinta la o metoda statica; Predicate.not ii da tipul Predicate
        afiseaza("Cu cel putin un prieten", service.cautaUtilizatori(
                Predicate.not(CriteriiUtilizator::faraPrieteni)));
    }

    private void afiseazaDupaNrPrieteni() {
        // * forEach primeste un Consumer: ce facem cu fiecare utilizator din lista sortata
        service.utilizatoriDupaNrPrieteni()
                .forEach(u -> System.out.println("  " + u + " - " + u.getFriends().size() + " prieteni"));
    }

    private void afiseaza(String titlu, List<Utilizator> utilizatori) {
        System.out.println(titlu + ":");
        // * System.out::println = referinta la metoda unui obiect anume (u -> System.out.println(u))
        utilizatori.forEach(System.out::println);
    }
}