from controller.service_evenimente import ServiceEvenimente
from controller.service_persoane import ServicePersoane

from repository.repo_evenimente import EvenimentRepository
from repository.repo_persoane import PersoanaRepository

from repository.repo_persoane_file import PersoanaFileRepository
from repository.repo_evenimente_file import EvenimentFileRepository

from repository.repo_persoane_json import PersoanaJSONRepository
from repository.repo_evenimente_json import EvenimentJSONRepository

from ui.ui import Consola
from ui.ui import prints
from tests.teste import teste
from tests.test_unittest_run import teste_file

def main():
    teste()
    teste_file()
    prints()
        
    cmd = input("Opțiune: ")
    
    if cmd == '1':
        repo_persoane = PersoanaRepository()
        repo_evenimente = EvenimentRepository()
    elif cmd == '2':
        repo_persoane = PersoanaFileRepository("persoane.txt")
        repo_evenimente = EvenimentFileRepository("evenimente.txt")
    elif cmd == '3':
        repo_persoane = PersoanaJSONRepository("persoane.json")
        repo_evenimente = EvenimentJSONRepository("evenimente.json")
    else: 
        return

    srv_persoane = ServicePersoane(repo_persoane, repo_evenimente)
    srv_evenimente = ServiceEvenimente(repo_persoane, repo_evenimente)

    consola = Consola(srv_persoane, srv_evenimente)
    consola.run()

if __name__ == "__main__":
    main()