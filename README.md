# Space-Invaders
Programski kod video igre Space Invaders (verzija Cat Invaders) koja je implementirana koristeći jezik C++ i SFML biblioteku
Igra je izrađena u Visual Studio 2022 (https://visualstudio.microsoft.com/vs/) uz prethodno instaliranu SFML biblioteku (https://www.sfml-dev.org/)


##  📚 Opis zadatka: 📚
Cilj zadatka je korištenjem SFML-a u programskom jeziku C++ implementirati igru Space Invaders.

Na sljedećoj slici prikazana je jedna situacija iz igre Space Invaders (mnogobrojne online verzije igre dostupne su guglanjem što je korisno ako se ranije niste susreli s ovom igrom). Prikaz originalne verzije igre Space Invaders koju je 1978. dizajnirao Tomohiro Nishikado možete vidjeti ovdje:  https://youtu.be/MU4psw3ccUI?t=11

### 🎮 Opis igre Space Invaders 🎮

1. Space Invaders je igra u kojoj igrač kontrolira laserski top koji se pomiče horizontalno u donjem dijelu ekrana. Igrač pomoću topa ispaljuje projektile koji uništavaju izvanzemaljce iz gornjeg dijela ekrana (za uništavanje jednog izvanzemaljca dovoljan je jedan projektil). Cilj igre je uništiti sve prikazane izvanzemaljce na ekranu pomoću projektila. Uništavanjem svakog izvanzemaljca, igrač dobiva određeni broj bodova (početno igrač ima 0 bodova).
2. Početno se na ekranu nalazi 55 izvanzemaljaca koji su raspoređeni u 5 redova po 11 izvanzemaljaca.
3. Izvanzemaljci se pomiču lijevo i desno (svi zajedno, kao grupa). Kad izvanzemaljci (kao grupa) dođu do jednog ruba ekrana, počinju se kretati k suprotnom rubu ekrana pri čemu se pri svakom takvom događaju promjene smjera pomaknu i malo prema dolje (tj. prema laserskom topu).
4. Izvanzemaljci mogu također povremeno ispaljivati projektile kojim mogu uništiti igrača (svaki projektil oduzima igraču jedan život - početno igrač ima tri života). Projektili igrača imaju drugačiju boju od projektila izvanzemaljaca (mogu imati i drugačiji oblik, s time da taj zahtjev na drugačiji oblik nije obavezan!). Projektili izvanzemaljaca ne utječu na druge izvanzemaljce (tj. izvanzemaljci ne mogu uništiti druge izvanzemaljce!).
5. Iako igrač početno ima tri života, igra odmah završava ako izvanzemaljci dođu do donjeg dijela ekrana.
6. Postoje tri vrste izvanzemaljaca - svaka vrsta ima različiti prikaz i donosi različiti broj bodova.
7. Pri svakom pomicanju izvanzemaljaca prema dolje, brzina kojom se izvanzemaljci pomiču malo se poveća.
8. Prilikom pomicanja izvanzemaljaca, postoji animacija izvanzemaljaca (primjerice, dovoljno je da se izmjenjuju dva različita prikaza za pojedinog izvanzemaljca).
9. Lasersi top je djelomično zaštićen obrambenim objektima. Ti objekti se ne pomiču. Objekti mogu biti uništeni projektilima igrača i projektilima izvanzemaljaca (pri čemu je potreban određen broj projektila da bi se takav objekt uništio). Objekt se također uništi ako se izvazemaljci dovoljno spuste pa se zalete u njega (pri čemu je uništen samo  taj objekt, ne i izvanzemaljac).
10 .Povremeno se pojavljuje poseban ,,tajanstveni brod'' koji radi prolazak kroz gornji dio ekrana. Ako igrač uspije projektilom pogoditi takav brod, dobiva dodatne bodove.
11. Pri svakom ispaljivanju projektila koje napravi laserski top, čuje se određeni zvučni efekt. Također se čuje efekt pri uništavanju pojedinog izvanzemaljca. Možete razmotriti i dodavanje pozadinske glazbe (ali pozadinska glazba nije obavezna!).
12. Ako korisnik uništi sve izvanzemaljce na ekranu, javlja se novih 55 izvanzemaljaca koji se raspoređeni kao na početku igre, s time da su sada brži i pojavljuju se malo niže. Ako igrač uništi i tih 55 izvanzemaljaca, stvara se novih 55 izvanzemaljaca, i tako dalje.

### VAŽNI ZAHTJEVI 

U svakom trenutku korisniku mora biti prikazan broj ostvarenih bodova i koliko mu je života preostalo. Upotrebom satova u SFML-u treba postići da brzina igre ne ovisi o računalu na kojem se igra izvršava. Također, obavezno je korištenje klasa u kodu!


### Raspodjela bodova

OSNOVNA VERZIJA: ispravno napravljena igra koja zadovoljava zahtjeve od zahtjeva 1. do zahtjeva 5. (uključivo i zahtjev 1. i zahtjev 5.) iz gornjeg opisa te važne zahtjeve, nosi ukupno 10 bodova.
Samo ako je ispravno napravljena osnovna verzija, moguće je za ostale stavke iz gornjeg opisa i dodatne uvjete navedene ispod koji su ispravno napravljeni dobiti još i sljedeće bodove:

za 6. zahtjev iz gornjeg opisa ukupno 2 boda
za 7. zahtjev iz gornjeg opisa ukupno 1 bod
za 8. zahtjev iz gornjeg opisa ukupno 1 bod
za 9. zahtjev iz gornjeg opisa ukupno 4 boda
za 10. zahtjev iz gornjeg opisa ukupno 2 boda
za 11. zahtjev iz gornjeg opisa ukupno 1 bod
za 12. zahtjev iz gornjeg opisa ukupno 2 boda
za izradu izbornika koji se javlja početno, ali i nakon što igrač izgubi, ukupno 3 boda
za vlastiti dizajn (ali koji je gledljiv osmijeh ) - primjerice, pogledajte kako je izgledala popularna igra Chicken Invaders - ukupno 2 boda
pamćenje i prikaz dosad najvećeg broja ostvarenih bodova (tzv. high score) - ukupno 1 bod
za dodavanjem opcije da igrač ima pauzu tijekom igre - ukupno 1 bod
ostale opcije koje ovdje nisu navedene, ali želite da Vam se boduju - max. 2 boda (ukupno za sve njih), ovisno o težini i količini posla - takve stvari potrebno je napomenuti u polju za tekst uz zadatak na Merlinu, ali s prijedlogom bodovanja i obavezno objašnjenjem tog prijedloga.
VAŽNO: Ukoliko nije napravljena OSNOVNA VERZIJA tada se po ostalim kriterijima neće dodjeljivati bodovi! Na ovome zadatku nije moguće ostvariti više od 20 bodova, te nije moguće ukupno na svim zadaćama ostvariti više od 60 bodova. U polje za opis teksta uz zadatak napišite što ste sve implementirali (kako bi Vam se to bodovalo) te upute za igru! Nemojte predavati datoteke koje ispravljač već ima (poput datoteke Graphics.hpp iz SFML-a).

---Kraj opisa (zadan od strane predavača)---

### 💻 OD TOGA NAPRAVLJENO / IMPLEMENTIRANO (moj komentar prilikom predaje): 💻
"(1.-5. što se i traži;)
6. Postoje tri vrste izvanzemaljaca - svaka vrsta ima različiti prikaz i donosi različiti broj bodova;
9. Lasersi top je djelomično zaštićen obrambenim objektima. Ti objekti se ne pomiču. Objekti mogu biti uništeni projektilima igrača i projektilima izvanzemaljaca (pri čemu je potreban određen broj projektila da bi se takav objekt uništio). Objekt se također uništi ako se izvazemaljci dovoljno spuste pa se zalete u njega (pri čemu je uništen samo  taj objekt, ne i izvanzemaljac). S time da nisam gledao da se inzvanzemaljac zabije u zid već kada se spuste na tu razinu što mi je ipak imalo malo više smisla. Iako bi se samo za zabijanje u zib provjeravao hit box, ali opet to bi onda ovisilo i o načinu na koji se taj zid postepeno uništava. 
10. Povremeno se pojavljuje poseban ,,tajanstveni brod'' koji radi prolazak kroz gornji dio ekrana. Ako igrač uspije projektilom pogoditi takav brod, dobiva dodatne bodove.


Preostali dodatni zahtjevi:

za vlastiti dizajn (ali koji je gledljiv osmijeh ) - primjerice, pogledajte kako je izgledala popularna igra Chicken Invaders - 
Napravljena je igra Cat Invaders - sve macke su nacrtane u https://www.pixilart.com/, dakle sve tri vrste enemija, brod od igraca, bonus brod koji je prilagodjen s određenim natpisom, i štitovi koji se gađanjem postepeno uništavaju (kao što se i može vidjeti u direktoriju slike)
pamćenje i prikaz dosad najvećeg broja ostvarenih bodova (tzv. high score) 
ostale opcija: dodana je pozadinska glazba u stilu retro igara (free to use je na platformi youtube), također dodana je i pozadinska slika, i napravljen je LAST SCORE koji je na početku, to jest prilikom pokretanja igre 0, ali ako igrač izgubi ispisuje se iz prethodne razine taj score i tako u krug, npr. ako je 500, pa 400 biti će 400.
Upute za igru: Brod se kontrolira strelicama lijevo i desno (lijevo za lijevi smjer, desno za desni), meci se ispaljuju pomoću tipke spacebar!

Napomena 1.: "Upotrebom satova u SFML-u treba postići da brzina igre ne ovisi o računalu na kojem se igra izvršava. Također, obavezno je korištenje klasa u kodu!" 
Ovo sam pokušao srediti na način tako da sam pored svakog pomaka od objekta bilo to alien, brod, bullet, dodao i varijablu speed koja je jednaka u svim .h datotekama i u igri.h sam svaki put dohvaćao u varijablu vri koliko je protelko vremena te u funkciji gdje se brod, alien... pomiče po ekranu dodao pomak*speed*b, gdje je vri u toj funkciji označen s b,  i u prozor.h frame limit je stavljen na 200. Nadam se da sam uspješno to implementirao osmijeh"


### povratni komentar (od predavača)

*Izvrsno, brzina je pri testiranju na mom laptopu bila dobra. Pohvala za samostalno crtanje likova. Pri predaji ne bi trebali slati datoteku highcore.txt jer onda se iz nje pročita početni highscore koji nije bio 0. Zbog toga 0.5/1 bodova na uvjetu highscore. Na osnovnoj verziji oduzeto pola boda jer ako igrač slučajno završi ispod štita, projektili se brzo uništavaju i dobivamo strojnicu koja vrlo brzo uništi štit iako to igrač ne očekuje zbog inače brzine kojom se ispaljuju projektili, tj. inače je samo jedan na ekranu, a on se ne uništi tako brzo (trebalo bi možda mjeriti neko minimalno vrijeme od zadnjeg ispaljivanja projektila).
Bodovi:
9.5 (osnovna verzija) + 2 (zahtjev 6) + 4 (zahtjev 9) + 0.5 (highscore) + 2 (dizajn) + 0.5 (glazba spada na neki način pod uvjet 11, ali bez zvučnih efekata) + 2 (last score kao "ostale opcije koje nisu navedene") + 2 (zahtjev 10)
Ukupno ostvarno 20 bodova (toliko je max)* 
