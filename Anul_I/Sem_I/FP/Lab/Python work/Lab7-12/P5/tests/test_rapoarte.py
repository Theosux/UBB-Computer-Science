from controller.service_persoane import ServicePersoane
from controller.service_evenimente import ServiceEvenimente
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository

def test_rapoarte():
    repo_p = PersoanaRepository()
    repo_e = EvenimentRepository()
    
    srv_p = ServicePersoane(repo_p, repo_e)
    srv_e = ServiceEvenimente(repo_p, repo_e)

    srv_p.adauga_persoana("1", "Ana", "A1")
    srv_p.adauga_persoana("2", "Barbu", "A2")
    srv_p.adauga_persoana("3", "Carmen", "A3")

    srv_e.adauga_eveniment("E1", "01.01", "10:00", "Zumba")
    srv_e.adauga_eveniment("E2", "02.01", "12:00", "Aerobic")
    srv_e.adauga_eveniment("E3", "03.01", "14:00", "Box")

    # Inscrieri
    # Ana (1): Zumba, Box
    srv_e.inscrie_persoana("1", "E1")
    srv_e.inscrie_persoana("1", "E3")
    
    # Barbu (2): Zumba
    srv_e.inscrie_persoana("2", "E1")

    # Carmen (3): Nimic

    # --- Raport 1: Evenimente pentru Ana ---
    rez = srv_e.raport_evenimente_persoana("1")
    assert len(rez) == 2
    assert rez[0].descriere == "Box"
    assert rez[1].descriere == "Zumba"

    # --- Raport 2: Persoane active ---
    rez = srv_e.raport_persoane_active()
    assert rez[0] == ("Ana", 2)
    assert rez[1] == ("Barbu", 1)

    # --- Raport 3: Top 20% evenimente ---
    rez = srv_e.raport_top_20_evenimente()
    assert len(rez) == 1
    assert rez[0] == ("Zumba", 2)

# --- Raport 4: Persoane inactive (crescător, include 0) ---
    rez = srv_e.raport_persoane_inactiv()
    assert len(rez) == 3
    assert rez[0] == ("Carmen", 0)
    assert rez[1] == ("Barbu", 1)
    assert rez[2] == ("Ana", 2)

    print("✅")
