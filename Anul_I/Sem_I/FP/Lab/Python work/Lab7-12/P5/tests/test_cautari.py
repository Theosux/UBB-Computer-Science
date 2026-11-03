from controller.service_persoane import ServicePersoane
from controller.service_evenimente import ServiceEvenimente
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository

def test_cautari():
    repo_p = PersoanaRepository()
    repo_e = EvenimentRepository()
    
    srv_p = ServicePersoane(repo_p, repo_e)
    srv_e = ServiceEvenimente(repo_p, repo_e)

    srv_p.adauga_persoana("1", "Ana Pop", "Cj")
    srv_p.adauga_persoana("2", "Popescu Ion", "Buc")
    
    srv_e.adauga_eveniment("10", "01.01", "10:00", "Fotbal")
    srv_e.adauga_eveniment("11", "02.01", "12:00", "Tenis")

    # 1. Cautare Persoane
    rez = srv_p.cauta_persoane("pop")
    assert len(rez) == 2 # Ana Pop, Popescu Ion

    rez = srv_p.cauta_persoane("ana")
    assert len(rez) == 1
    assert rez[0].personID == "1"

    # 2. Cautare Evenimente
    rez = srv_e.cauta_evenimente("Fotbal")
    assert len(rez) == 1
    
    rez = srv_e.cauta_evenimente("01")
    assert len(rez) == 2 # 01.01 si 02.01 contin "01"

    print("✅")