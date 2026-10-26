Laborator 3 - Retea de socializare

Cum functioneaza factory-ul:
	RepositoryFactory este singura clasa care face new la repository-uri concrete cu ajutorul a doua metode(una pentru user una pentru prietenii). Amandoua intorc tipul abstract Repository<ID, E>
	Tipul de persistenta se citeste din config(src/main/resources/config.properties), repository.type (MEMORY, FILE, DATABASE), se foloseste enum-ul RepositoryType si ambele metode vor citi aceeasi cheie (useri, prieteni folosesc 		acelasi tip de persistenta)
	Parametrii (file.utilizatori, file.prietenii, db.url, db.user, db.password) se iau tot din config - cheie lipsa/valoare necunoscuta arunca RepositoryException
	Main incarca configul intr-un try-with-resources, apoi cere repo de la factory

Trecere la baze de date(lab4):
	Se scrie codul si implementarea metodelor din Repoul pentru db
	In config selectam DATABASE la repository.type si introducem datele de conectare la db

Fisier lipsa, linii corupte:
	Fisier lipsa: repo porneste gol, iar fisierul se creeaza la prima salvare
	Linie corupta (id gresit, numar invalid de campuri, data format dif de ISO, date invalide pentru validator, id duplicat): incarcarea se opreste cu un mesaj clar, contine fisierul, linia, motivul. Exceptia originala se pastreaza 		(exception chaining) ca si cauza in RepositoryException si se afiseaza in main iar aplicatia nu porneste. Daca nu oprim incarcarea la o modificare fisierul ar pierde linia corupta.
	Pentru test: in config: file.utilizatori=data/utilizatori_corupt.txt

Principii SOLID:
	SRP: fiecare clasa are un singur rol (validator, repository, factory, service, consola)
	OCP: un tip nou de persistenta inseamna clase noi de repository; service-ul si ui-ul nu se modifica, un validator nou nu modifica repo-ul
	LSP: InMemoryRepository, repo-urile in fisier si cele DB pot inlocui interfata Repository
	DIP: ReteaService si Main depind de interfata Repository, nu de clasele concrete

Sabloane proiectare:
	Factory: RepositoryFactory
	Template Method: AbstractFileRepository (loadData, writeToFile -> extractEntity, createEntityAsString)
	Strategy: Validator<T> cu UtilizatorValidator si PrietenieValidator, primit prin constructor de repository
	Decorator: BufferedReader peste FileReader si BufferedWriter peste FileWriter

Simple Factory vs Abstract Factory(OCP):
	Simple Factory: codul de creare e intr-un singur loc
		(dezvantaj) la un tip nou de persistenta trebuie modificat switch-ul din factory, deci nu respecta OCP
	Abstract Factory: o interfata RepositoryFactory cu cate o implementare pt fiecare tip (FileRepoF, DbRepoF), tip nou inseamna clasa noua, fara modificari in cod (OCP) si garanteaza ca toate repo-urile vin din aceeasi familie
		(dezavantaj) mai multe clase, alegerea implementarii va trebui facuta undeva(Main)

Unde e validarea:
	Validarea e in repository (Strategy), deci entitatile sunt validate la save/update. Alte reguli (userii exista, prietenia nu exista deja, la stergerea unui user se sterg si prieteniile) sunt in service.