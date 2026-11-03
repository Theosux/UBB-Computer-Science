from tests.test_gestiune_persoane import test_gestiune_persoane
from tests.test_gestiune_evenimente import test_gestiune_evenimente
from tests.test_inscriere import test_inscriere
from tests.test_cautari import test_cautari
from tests.test_rapoarte import test_rapoarte



def teste():
    print("rulăm testele")
    try:
        test_gestiune_persoane()
        test_gestiune_evenimente()
        test_inscriere()
        test_cautari()
        test_rapoarte()
        print("\n Teste trecute")
    except AssertionError as e:
        print(f"\n Teste picate: {e}")
    except Exception as e:
        print(f"\n Eroare: {e}")

if __name__ == "__main__":
    teste()