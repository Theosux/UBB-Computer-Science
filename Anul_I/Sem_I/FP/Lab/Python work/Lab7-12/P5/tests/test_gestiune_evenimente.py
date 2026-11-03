from controller.service_evenimente import ServiceEvenimente
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository

def test_gestiune_evenimente():
    repo_p = PersoanaRepository()
    repo_e = EvenimentRepository()
    srv = ServiceEvenimente(repo_p, repo_e)

    # 1. Adaugare
    assert len(srv.get_all()) == 0
    srv.adauga_eveniment("10", "01.01.2025", "12:00", "Party")
    assert len(srv.get_all()) == 1
    
    # 2. Eroare Duplicat
    try:
        srv.adauga_eveniment("10", "Altadata", "13:00", "Altceva")
        assert False
    except ValueError as e:
        assert "exista deja" in str(e)

    # 3. Modificare
    srv.modifica_eveniment("10", "02.01.2025", "14:00", "Super Party")
    ev = srv._repo_evenimente.find("10")
    assert ev.data == "02.01.2025"
    assert ev.descriere == "Super Party"

    # 4. Stergere
    srv.sterge_eveniment("10")
    assert len(srv.get_all()) == 0

    # 5. Test Adaugare Random
    id_rnd, data, timp, desc = srv.adauga_eveniment_random()
    assert len(srv.get_all()) == 1
    assert srv._repo_evenimente.find(id_rnd).descriere == desc

    print("✅")
