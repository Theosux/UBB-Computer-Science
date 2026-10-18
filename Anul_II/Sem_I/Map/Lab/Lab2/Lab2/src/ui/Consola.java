package ui;

import domain.Utilizator;
import domain.validators.ValidationException;
import service.ReteaService;
import service.ServiceException;

import java.util.Scanner;

public class Consola {
    private final ReteaService service;
    private final Scanner scanner = new Scanner(System.in);

    public Consola(ReteaService service) {
        this.service = service;
    }

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
                    case "0":
                        ruleaza = false;
                        break;
                    default:
                        System.out.println("Optiune invalida!");
                }
            } catch (ValidationException | ServiceException e) {
                System.out.println("Eroare: " + e.getMessage());
            } catch (NumberFormatException e) {
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
        for (Utilizator u : service.getUtilizatori())
            System.out.println("  " + u + " | prieteni: " + u.getFriends());
    }

    private Long citesteId(String mesaj) {
        System.out.print(mesaj);
        return Long.parseLong(scanner.nextLine().trim());
    }
}