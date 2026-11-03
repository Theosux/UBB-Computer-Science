import unittest
import os
from domain.persoana import Persoana
from domain.eveniment import Eveniment
from repository.repo_persoane import PersoanaRepository
from repository.repo_evenimente import EvenimentRepository
from repository.repo_persoane_file import PersoanaFileRepository
from controller.service_persoane import ServicePersoane
from controller.service_evenimente import ServiceEvenimente

class TestServicePersoaneWhiteBox(unittest.TestCase):
    """
    White-box testing pentru ServicePersoane.
    """
    def setUp(self):
        # Setup inainte de fiecare TEST
        self.repo_p = PersoanaRepository()
        self.repo_e = EvenimentRepository()
        self.srv = ServicePersoane(self.repo_p, self.repo_e)

    def test_adauga_persoana_success(self):
        res = self.srv.adauga_persoana("1", "Ion", "Cluj")
        self.assertEqual(len(self.srv.get_all()), 1)
        self.assertEqual(self.srv.get_all()[0].nume, "Ion")

    def test_adauga_persoana_duplicate(self):
        self.srv.adauga_persoana("1", "Ion", "Cluj")
        with self.assertRaises(ValueError):
            self.srv.adauga_persoana("1", "Vasile", "Bucuresti")

    def test_sterge_persoana_valid(self):
        self.srv.adauga_persoana("1", "Ion", "Cluj")
        
        ev = Eveniment("100", "01.01.2024", "10:00", "Test")
        ev.participanti.append("1")
        self.repo_e.store(ev)

        self.srv.sterge_persoana("1")
        
        self.assertEqual(len(self.srv.get_all()), 0)
        self.assertNotIn("1", self.repo_e.find("100").participanti)

    def test_sterge_persoana_invalid(self):
        with self.assertRaises(ValueError):
            self.srv.sterge_persoana("999")

class TestServiceInscriereBlackBox(unittest.TestCase):
    """
    Black-box testing pentru inscriere_persoana.
    """
    def setUp(self):
        self.repo_p = PersoanaRepository()
        self.repo_e = EvenimentRepository()
        self.srv_e = ServiceEvenimente(self.repo_p, self.repo_e)
        
        p = Persoana("1", "Ana", "Cluj")
        self.repo_p.store(p)
        e = Eveniment("100", "12.12.2024", "12:00", "Party")
        self.repo_e.store(e)

    def test_inscriere_valida(self):
        self.srv_e.inscrie_persoana("1", "100")
        ev = self.repo_e.find("100")
        self.assertIn("1", ev.participanti)

    def test_inscriere_invalida_persoana_inexistenta(self):
        with self.assertRaisesRegex(ValueError, "Nu exista persoana"):
            self.srv_e.inscrie_persoana("99", "100")

    def test_inscriere_invalida_eveniment_inexistent(self):
        with self.assertRaisesRegex(ValueError, "Nu exista evenimentul"):
            self.srv_e.inscrie_persoana("1", "999")

    def test_inscriere_invalida_deja_inscris(self):
        self.srv_e.inscrie_persoana("1", "100")
        with self.assertRaisesRegex(ValueError, "deja inscrisa"):
            self.srv_e.inscrie_persoana("1", "100")

class TestFileRepository(unittest.TestCase):
    """
    Teste de integrare pentru scrierea in fisier
    """
    def setUp(self):
        self.filename = "test_persoane.txt"
        self.repo = PersoanaFileRepository(self.filename)

    def tearDown(self):
        if os.path.exists(self.filename):
            os.remove(self.filename)

    def test_file_persistence(self):
        p = Persoana("50", "TestFile", "Strada Test")
        self.repo.store(p)
        
        
        repo_nou = PersoanaFileRepository(self.filename)
        loaded_p = repo_nou.find("50")
        
        self.assertIsNotNone(loaded_p)
        self.assertEqual(loaded_p.nume, "TestFile")

if __name__ == '__main__':
    unittest.main()