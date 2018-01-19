Snake Version 7.43.2b 05/12/2017

Autorenschaft: 	Nicolai Gennrich, Sahra Teichmann,
				Marian Stiehler, Carina Pfaff

				
Benutzungshinweise
-------------------------------------------------------------------------
- getestet unter Windows, Mac und Linux


Beschreibung des Projektes
-------------------------------------------------------------------------
- Implementierung des Spiels Snake (Spielregeln unter https://de.wikipedia.org/wiki/Snake_(Computerspiel))
- Implementierung des Spiels Convey's Game of Life (Siehe README_GOL.md)
- Veränderung des Programmes in den OOP-Stil


Struktur des Programms
-------------------------------------------------------------------------
- CAbase dient als GUI des zellulären Automaten für die Spiele GameofLife und Snake
- im Konstruktor wird das Objekt Schlange bei Programmstart erzeugt
- über verschiedene Modi wird auf die unterschiedlichen Spiele verwiesen (evolutionChoice)
- mit Hilfe eines Timers wird das Spielfeld im Interval aktualisiert

jetzt: Spielmodus Snake
- in einem Interval kann nur einmal die Bewegungsrichtung der Schlange geändert werden; in jeder neuen Evolutionsphase wird movedOnTick dafür auf False gesetzt (setMovedOnTick)
- über (keyPressEvent) wird die Bewegungsrichtung der Schlange geändert, getMovedOnTick prüft hierfür, ob im Interval bereits eine Richtungsänderung vorgenommen wurde (nur Eine ist möglich je Interval)
- (spawnFood) setzt die Nahrung in das Spielfeld, nachdem geprüft wurde, ob die Nahrung sich nicht ein einem Feld der Schlange befindet
- (eat) prüft, ob der Kopf der Schlange mit der Nahrung übereinstimmt; falls ja wird isEating jetzt True
- (move) gibt die nächste Bewegung der Schlange vor
		- sofern isEating auf True gesetzt wurde wächst die Schlange (am Kopf), anstatt einer Bewegung;
		- andernfalls bewegt sich die Schlange, für jeden Schlangenpart in Richtung ihres Elternsteils, für den Kopfteil in die gewählte Bewegungsrichtung
- collision prüft ob die Schlange mit dem Rand oder mit sich selbst kollidiert, sofern diese Bedingung erfüllt wird stoppt der Timer und die Schlange stirbt;
eine Textbox macht darauf aufmerksam; durch Akzeptieren des Verlierens wird das Spiel neu gestartet (vorher löschen -> reset)


Bedienung GUI (bzgl. Snake)
-------------------------------------------------------------------------
- Der Spielmodus wird über die ComboBox ausgewählt (GameofLife oder Snake)
- Durch den Startbutton wird das Spiel gestartet, die 3-Elementige Schlange bewegt sich standardmäßig nach unten
- über die Tasten "4, 2, 6, 8" wird die Bewegung der Schlange gesteuert
- Durch Betätigung des Pausebuttons pausiert das Spiel (Wiederaufnahme mit "start")
- der "clear"-Button sorgt für einen Neustart des Spiels (in Ausgangsposition)
- Zellengröße wird durch das Universe-Size Feld gesteuert (quadratisches Spielfeld) (10 - 100 Zellen)
- Steuerung der Geschwindigkeit der Schlange über das Generation Interval (100 - 100000ms)
- durch das Erreichen der Nahrung, wächst die Schlange
- Nach dem Tod der Schlange (Spielverlust) wird ein neues Spiel gestartet (zurück zur Ausgangsposition)


Probleme
-------------------------------------------------------------------------
/


Feedback zu Milestone2
-------------------------------------------------------------------------
- vorab Info gewünscht, dass die Projekte (Milestones) aufeinander aufbauen
- guter Anschluss von Milestone2 an Milestone1 (Schwierigkeitsgrad)
- sinnvolle Fristverlängerung (DANKE)
- Aufgabenstellung verlangt zu wenig Programmierung im OOP-Stil