from p1functionsdict import get_ui_choice, parse_prompt, get_sentence, adaugare_numar, get_option, get_sub_option, list_sort, afisare_numere, parte_imaginara, modul_mic, modul_egal, suma_numere, stergere_numar, stergere_interval, inlocuire_numar, filtrare_prim, modulx, undo, istoric_lista, produs_subsecventa
from p1testedict import teste
from p1UIprints import print_main_ui, print_stergere_ui, print_cautare_ui, print_operatii_ui, print_filtrare_ui, print_filtrare_modul_ui, print_choose_ui, print_main_ui_two


def main():

    l = []
    istoric = []

    print_choose_ui()

    choice = get_ui_choice()

    if (choice == 2):
        print_main_ui_two()
        while True:
            prompt = get_sentence()
            if prompt == "exit":
                break
            parse_prompt(prompt, l, istoric)

    if (choice == 1):
        print_main_ui() #printeaza comenzile principale

        while True:

            option = get_option()

            if option == 1:
                istoric_lista(l, istoric)
                adaugare_numar(l)


            elif option == 2:
                print_stergere_ui() #printeaza comenzile de stergere

                sub_option = get_sub_option()

                if sub_option == 1:
                    istoric_lista(l, istoric)
                    stergere_numar(l)

                elif sub_option == 2:
                    istoric_lista(l, istoric)
                    stergere_interval(l)

                elif sub_option == 3:
                    istoric_lista(l, istoric)
                    inlocuire_numar(l)

                else:
                    print("Suboptiune necunoscuta, intoarcere la meniu principal")

            elif option == 3:
                print_cautare_ui() #printeaza comenzile de cautare

                sub_option = get_sub_option()

                if sub_option == 1:
                    parte_imaginara(l)

                elif sub_option == 2:
                    modul_mic(l)

                elif sub_option == 3:
                    modul_egal(l)

                else:
                    print("Suboptiune necunoscuta, intoarcere la meniu principal")

            elif option == 4:
                print_operatii_ui() #printeaza comenzile de operatii

                sub_option = get_sub_option()

                if sub_option == 1:
                    suma_numere(l)

                elif sub_option == 2:
                    produs_subsecventa(l)

                elif sub_option == 3:
                    list_sort(l)
                
                else:
                    print("Suboptiune necunoscuta, intoarcere la meniu principal")


            elif option == 5:
                print_filtrare_ui() #printeaza comenzile de filtrare

                sub_option = get_sub_option()

                if sub_option == 1:
                    print(filtrare_prim(l))

                elif sub_option == 2:
                    print_filtrare_modul_ui() #printeaza comenzile de filtrare cu modul
                    modulx(l)

                else:
                    print("Suboptiune necunoscuta, intoarcere la meniu principal")


            elif option == 6:
                undo(l, istoric)
            

            elif option == 7:
                afisare_numere(l)


            elif option == 0:
                print("Programul s-a incheiat")
                return 0
            

            else:
                print("Optiune inexistenta/neimplementata")

teste()
main()