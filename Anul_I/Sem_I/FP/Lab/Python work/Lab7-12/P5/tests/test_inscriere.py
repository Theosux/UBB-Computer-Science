from controller.service_persoane import ServicePersoane
from controller.service_evenimente import ServiceEvenimente
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository

def test_inscriere():
    repo_p = PersoanaRepository()
    repo_e = EvenimentRepository()
    
    srv_p = ServicePersoane(repo_p, repo_e)
    srv_e = ServiceEvenimente(repo_p, repo_e)

    srv_p.adauga_persoana("1", "Ion", "Cj")
    srv_e.adauga_eveniment("100", "01.01", "10:00", "Meci")

    srv_e.inscrie_persoana("1", "100")
    ev = repo_e.find("100")
    assert "1" in ev.participanti
    assert len(ev.participanti) == 1

    try:
        srv_e.inscrie_persoana("1", "100")
        assert False
    except ValueError as e:
        assert "deja inscrisa" in str(e)

    try:
        srv_e.inscrie_persoana("99", "100") # Persoana nu exista
        assert False
    except ValueError as e:
        assert "Nu exista persoana" in str(e)

    try:
        srv_e.inscrie_persoana("1", "999") # Eveniment nu exista
        assert False
    except ValueError as e:
        assert "Nu exista evenimentul" in str(e)

    print("✅")