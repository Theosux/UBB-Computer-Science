import unittest

def ruleaza_teste():
    """
    Rulează toate testele definite folosind unittest.
    Folosește TestLoader pentru a descoperi testele in folderul 'tests'.
    """
    loader = unittest.TestLoader()
    # Caută teste în folderul 'tests' care respectă pattern-ul 'test_*.py'
    suite = loader.discover('tests', pattern='test_unittest.py')
    
    # Rulează testele și afișează rezultatul în consolă
    runner = unittest.TextTestRunner()
    result = runner.run(suite)
    
    return result.wasSuccessful()

def teste_file():
    teste_trecute = ruleaza_teste()

    if not teste_trecute:
        print("Teste file picate")
        return
    print("\n")