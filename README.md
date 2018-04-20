# rvs18-spa-dz-02
## Domaća zadaća 02 za SPA u 2018
### ROK PREDAJE: 30.4.2018. 08:59
Cilj ove domaće zadaće je osnažiti studentovo znanje rada s linearnim listama.
### Uvod
Igra života je igra za 0 igrača koju je osmislio britanski matematičar John Horton Conway 1970:
- http://en.wikipedia.org/wiki/Conway's_Game_of_Life
- http://www.youtube.com/watch?v=CgOcEZinQ2I&feature=share&list=FLwikA_t8e6TSJW-LlAHkKw

Ova igra se sastoji od niza organizama koji žive u vlastitim ćelijama u dvodimenzionalnom svijetu.
Konfiguracija organizama se mijenja u diskretnim vremenskim trenucima, pri čemu svaka ćelija matrice
može biti prazna (mrtva) ili zauzeta (živa). Nova generacija organizama u ćelijama nastaje na osnovu stare
generacije organizama ovisno o sadržaju osam susjednih ćelija svake pojedine ćelije (sve izvan matrice
smatramo mrtvim organizmima). Pravila za formiranje nove generacije organizama su sljedeća:
1. Živi organizam u ćeliji preživljava u sljedećoj generaciji ukoliko je broj njegovih susjeda dva ili tri.
2. Živi organizam u ćeliji umire u sljedećoj generaciji ukoliko je broj njegovih susjeda manji od dva
(zbog usamljenosti) ili veći od tri (zbog prenaseljenosti).
3. U praznoj ćeliji se rađa novi organizam ukoliko se u točno tri njene susjedne ćelije nalaze živi
organizmi.

Igra života počinje od zadane početne konfiguracije i u diskretnim trenucima se formiraju sljedeće
konfiguracije organizama istovremenom primjenom gornjih pravila na sve ćelije prethodne konfiguracije.
Ovo znači da se prelazak u sljedeću generaciju sastoji od dva koraka:
1. Izračunati što će se dogoditi sa svakom ćelijom na osnovu gornjih pravila.
2. Primijeniti izračunato na sve ćelije.

Igra nema kraja.
### Vaš zadatak
Vaš zadatak je napraviti implementaciju Igre života. Pri tome na raspolaganju imate nekoliko opcija od
kojih trebate odabrati jednu:
- a) Uzeti gotove datoteke program.cpp i game_of_life.h iz priloga te na temelju njih izgraditi igru (tj.
implementirati game_of_life.cpp), pri čemu članove klase možete mijenjati prema potrebi. Ovaj
pristup koristi dvodimenzionalno polje, tj. polje čiji svaki element čuva novo polje
(http://www.cplusplus.com/doc/tutorial/arrays/).
- b) Kao a), samo što pobrišete dvodimenzionalno polje i umjesto njega koristite obično polje,
array<T,N> ili vector<T>. Pri tome u kontejneru prvih N elemenata smatrate podacima o
prvom retku, sljedećih N elemenata podacima o drugom retku, itd.
- c) Implementirati igru u SFML-u s kontinuiranim osvježavanjem svake 2 sekunde.

Neka prilikom inicijalizacije igre postoji 25% šanse da će u ćeliji biti živi organizam.

Prilozi:
- Izvršna datoteka Game_of_Life.exe s gotovim rješenjem (samo za ilustraciju).
- Ako ne možete pokrenuti izvršnu datoteku, Screenshots.docx sadrži nekoliko snimki ekrana za
ilustraciju.
- Opcija a – datoteke\game_of_life.h
- Opcija a – datoteke\program.cpp
### Bodovanje
Ova domaća zadaća nosi najviše 2 boda iz ishoda 2. Potpuno funkcionalna igra će nositi 2 boda, bez
obzira koja opcija izrade je izabrana.
### Bonus
Sva rješenja napravljena u SFML-u ulaze u natjecanje za bonuse u iznosima od 1, 2 i 3 sdolara. Bonusi će
biti podijeljeni prema vizualnom WAAAAUUUU efektu izazvanom kod asistenata, nastavnika te kolega
studenata.
### Predaja rješenja
Kad ste gotovi, rješenje stavite na svoj GitHub i pošaljite svom asistentu e-mail s linkom.
