from controller.service_persoane import ServicePersoane
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository

def test_gestiune_persoane():
    repo_p = PersoanaRepository()
    repo_e = EvenimentRepository() 
    srv = ServicePersoane(repo_p, repo_e)

    # 1. Adaugare
    assert len(srv.get_all()) == 0
    srv.adauga_persoana("1", "Ana", "Cluj")
    assert len(srv.get_all()) == 1
    assert srv._repo_persoane.find("1").nume == "Ana"

    # 2. Eroare Duplicat
    try:
        srv.adauga_persoana("1", "Altcineva", "Alta adresa")
        assert False 
    except ValueError as e:
        assert "exista deja" in str(e)

    # 3. Modificare
    srv.modifica_persoana("1", "Ana Maria", "Cluj-Napoca")
    p = srv._repo_persoane.find("1")
    assert p.nume == "Ana Maria"
    assert p.adresa == "Cluj-Napoca"

    # 4. Eroare Modificare Inexistent
    try:
        srv.modifica_persoana("99", "Test", "Test")
        assert False
    except ValueError as e:
        assert "nu a fost găsită" in str(e)

    # 5. Stergere
    srv.sterge_persoana("1")
    assert len(srv.get_all()) == 0

    # 6. Eroare Stergere Inexistent
    try:
        srv.sterge_persoana("99")
        assert False
    except ValueError as e:
        assert "nu a fost găsită" in str(e)

    # 7. Test Adaugare Random
    id_rnd, nume_rnd, adr_rnd = srv.adauga_persoana_random()
    assert len(srv.get_all()) == 1
    p_rnd = srv._repo_persoane.find(id_rnd)
    assert p_rnd.nume == nume_rnd

    print("✅")